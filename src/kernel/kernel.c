#include <stdint.h>
#include <stddef.h>

#define SCREEN_W 320
#define SCREEN_H 200
#define VGA ((volatile uint8_t *)0xA0000)

#define HDR_H          20
#define FTR_H          16
#define NAV_W          76
#define FILES_VISIBLE  13

#define COL_BLACK 0
#define COL_BLUE 1
#define COL_GREEN 2
#define COL_CYAN 3
#define COL_RED 4
#define COL_MAGENTA 5
#define COL_BROWN 6
#define COL_LGRAY 7
#define COL_DGRAY 8
#define COL_BBLUE 9
#define COL_BGREEN 10
#define COL_BCYAN 11
#define COL_BRED 12
#define COL_YELLOW 14
#define COL_WHITE 15

typedef struct {
    uint16_t conventional_kb;
    uint16_t e801_below_16m_kb;
    uint16_t e801_above_16m_64k;
    uint8_t reserved[58];
} boot_info_t;

typedef struct {
    char vendor[13];
    uint32_t max_leaf;
    uint32_t signature;
    uint32_t features_ecx;
    uint32_t features_edx;
} cpu_info_t;

typedef struct {
    int present;
    char model[41];
    uint32_t sectors28;
} ata_device_t;

typedef struct {
    uint8_t type;
    uint32_t lba;
    uint32_t sectors;
} partition_t;

typedef struct {
    char name[13];
    uint32_t size;
    uint32_t cluster;
    uint8_t attr;
} disk_file_t;

typedef struct {
    const char *name;
    const char *data;
} rom_file_t;

static uint32_t g_boot_drive;
static const boot_info_t *g_boot_info;
static cpu_info_t g_cpu;
static ata_device_t g_ata[4];
static partition_t g_partitions[4];
static disk_file_t g_disk_files[32];
static int g_disk_file_count;
static int g_selected_page;
static int g_selected_file;
static int g_mouse_x = 160;
static int g_mouse_y = 100;
static int g_mouse_present;
static int g_mouse_buttons;
static int g_mouse_click;
static int g_selected_disk = 0;
static int g_file_scroll = 0;
static uint8_t g_sector[512];
static uint8_t g_preview[512];

static uint32_t g_fat_part_lba;
static uint32_t g_fat_data_lba;
static uint16_t g_fat_bytes_per_sector;
static uint8_t g_fat_sectors_per_cluster;
static uint8_t g_fat_type;

static const char g_readme[] =
    "CaYaBasicOS\n"
    "\n"
    "THIS ISO BOOTS WITHOUT GRUB OR A HOST OS. IT USES A SMALL CUSTOM\n"
    "BOOT SECTOR, VGA GRAPHICS, PS/2 INPUT POLLING AND ATA PIO.\n"
    "\n"
    "FILES HERE ARE READ-ONLY. DISK FAT16/FAT32 SUPPORT IS ALSO READ-ONLY\n"
    "AND LIMITED TO SIMPLE ROOT DIRECTORY INSPECTION.";

static const char g_status_file[] =
    "STATUS\n"
    "VIDEO: VGA MODE 13H\n"
    "INPUT: KEYBOARD, PS/2 MOUSE WHEN AVAILABLE\n"
    "STORAGE: PRIMARY ATA PIO IDENTIFY AND READ28\n"
    "FILESYSTEM: ROM CAYA FS + LIMITED FAT16/FAT32 ROOT VIEW";

static const char g_license_file[] =
    "NO EXTERNAL RUNTIME LIBRARIES ARE LINKED INTO THIS IMAGE.\n"
    "BUILD TOOLS ARE ONLY USED TO TRANSLATE SOURCE INTO A BOOTABLE ISO.";

static const rom_file_t g_rom_files[] = {
    {"README.TXT", g_readme},
    {"STATUS.LOG", g_status_file},
    {"LICENSE.TXT", g_license_file},
};

#define ROM_FILE_COUNT ((int)(sizeof(g_rom_files) / sizeof(g_rom_files[0])))

static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static inline uint16_t inw(uint16_t port)
{
    uint16_t value;
    __asm__ volatile ("inw %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static inline void io_wait(void)
{
    outb(0x80, 0);
}

static void *mem_set(void *dst, int value, size_t count)
{
    uint8_t *d = (uint8_t *)dst;
    while (count--) {
        *d++ = (uint8_t)value;
    }
    return dst;
}

static void *mem_copy(void *dst, const void *src, size_t count)
{
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;
    while (count--) {
        *d++ = *s++;
    }
    return dst;
}

static size_t str_len(const char *s)
{
    size_t n = 0;
    while (s && s[n]) {
        n++;
    }
    return n;
}

static char upper_char(char c)
{
    if (c >= 'a' && c <= 'z') {
        return (char)(c - 32);
    }
    return c;
}

static uint16_t le16(const uint8_t *p)
{
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

static uint32_t le32(const uint8_t *p)
{
    return (uint32_t)p[0] |
           ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

static void u32_to_dec(uint32_t value, char *out)
{
    char tmp[11];
    int i = 0;
    int j = 0;
    if (value == 0) {
        out[0] = '0';
        out[1] = 0;
        return;
    }
    while (value > 0 && i < 10) {
        tmp[i++] = (char)('0' + (value % 10));
        value /= 10;
    }
    while (i > 0) {
        out[j++] = tmp[--i];
    }
    out[j] = 0;
}

static void u32_to_hex(uint32_t value, char *out)
{
    static const char hex[] = "0123456789ABCDEF";
    out[0] = '0';
    out[1] = 'X';
    for (int i = 0; i < 8; i++) {
        out[2 + i] = hex[(value >> (28 - i * 4)) & 0xF];
    }
    out[10] = 0;
}

static void put_pixel(int x, int y, uint8_t color)
{
    if ((unsigned)x < SCREEN_W && (unsigned)y < SCREEN_H) {
        VGA[y * SCREEN_W + x] = color;
    }
}

static void fill_rect(int x, int y, int w, int h, uint8_t color)
{
    if (x < 0) {
        w += x;
        x = 0;
    }
    if (y < 0) {
        h += y;
        y = 0;
    }
    if (x + w > SCREEN_W) {
        w = SCREEN_W - x;
    }
    if (y + h > SCREEN_H) {
        h = SCREEN_H - y;
    }
    if (w <= 0 || h <= 0) {
        return;
    }
    for (int yy = 0; yy < h; yy++) {
        for (int xx = 0; xx < w; xx++) {
            VGA[(y + yy) * SCREEN_W + (x + xx)] = color;
        }
    }
}

static void draw_rect(int x, int y, int w, int h, uint8_t color)
{
    for (int i = 0; i < w; i++) {
        put_pixel(x + i, y, color);
        put_pixel(x + i, y + h - 1, color);
    }
    for (int i = 0; i < h; i++) {
        put_pixel(x, y + i, color);
        put_pixel(x + w - 1, y + i, color);
    }
}

typedef struct {
    char ch;
    uint8_t row[7];
} glyph_t;

static const glyph_t g_font[] = {
    {' ', {0, 0, 0, 0, 0, 0, 0}},
    {'!', {4, 4, 4, 4, 4, 0, 4}},
    {'.', {0, 0, 0, 0, 0, 6, 6}},
    {',', {0, 0, 0, 0, 0, 4, 8}},
    {':', {0, 4, 4, 0, 4, 4, 0}},
    {';', {0, 4, 4, 0, 4, 4, 8}},
    {'-', {0, 0, 0, 31, 0, 0, 0}},
    {'_', {0, 0, 0, 0, 0, 0, 31}},
    {'/', {1, 2, 2, 4, 8, 8, 16}},
    {'\\', {16, 8, 8, 4, 2, 2, 1}},
    {'+', {0, 4, 4, 31, 4, 4, 0}},
    {'=', {0, 0, 31, 0, 31, 0, 0}},
    {'(', {2, 4, 8, 8, 8, 4, 2}},
    {')', {8, 4, 2, 2, 2, 4, 8}},
    {'[', {14, 8, 8, 8, 8, 8, 14}},
    {']', {14, 2, 2, 2, 2, 2, 14}},
    {'<', {1, 2, 4, 8, 4, 2, 1}},
    {'>', {16, 8, 4, 2, 4, 8, 16}},
    {'?', {14, 17, 1, 2, 4, 0, 4}},
    {'0', {14, 17, 19, 21, 25, 17, 14}},
    {'1', {4, 12, 4, 4, 4, 4, 14}},
    {'2', {14, 17, 1, 2, 4, 8, 31}},
    {'3', {30, 1, 1, 14, 1, 1, 30}},
    {'4', {2, 6, 10, 18, 31, 2, 2}},
    {'5', {31, 16, 16, 30, 1, 1, 30}},
    {'6', {6, 8, 16, 30, 17, 17, 14}},
    {'7', {31, 1, 2, 4, 8, 8, 8}},
    {'8', {14, 17, 17, 14, 17, 17, 14}},
    {'9', {14, 17, 17, 15, 1, 2, 12}},
    {'A', {14, 17, 17, 31, 17, 17, 17}},
    {'B', {30, 17, 17, 30, 17, 17, 30}},
    {'C', {14, 17, 16, 16, 16, 17, 14}},
    {'D', {30, 17, 17, 17, 17, 17, 30}},
    {'E', {31, 16, 16, 30, 16, 16, 31}},
    {'F', {31, 16, 16, 30, 16, 16, 16}},
    {'G', {14, 17, 16, 23, 17, 17, 15}},
    {'H', {17, 17, 17, 31, 17, 17, 17}},
    {'I', {14, 4, 4, 4, 4, 4, 14}},
    {'J', {1, 1, 1, 1, 17, 17, 14}},
    {'K', {17, 18, 20, 24, 20, 18, 17}},
    {'L', {16, 16, 16, 16, 16, 16, 31}},
    {'M', {17, 27, 21, 21, 17, 17, 17}},
    {'N', {17, 25, 21, 19, 17, 17, 17}},
    {'O', {14, 17, 17, 17, 17, 17, 14}},
    {'P', {30, 17, 17, 30, 16, 16, 16}},
    {'Q', {14, 17, 17, 17, 21, 18, 13}},
    {'R', {30, 17, 17, 30, 20, 18, 17}},
    {'S', {15, 16, 16, 14, 1, 1, 30}},
    {'T', {31, 4, 4, 4, 4, 4, 4}},
    {'U', {17, 17, 17, 17, 17, 17, 14}},
    {'V', {17, 17, 17, 17, 17, 10, 4}},
    {'W', {17, 17, 17, 21, 21, 21, 10}},
    {'X', {17, 17, 10, 4, 10, 17, 17}},
    {'Y', {17, 17, 10, 4, 4, 4, 4}},
    {'Z', {31, 1, 2, 4, 8, 16, 31}},
};

static const uint8_t *glyph_rows(char c)
{
    c = upper_char(c);
    for (size_t i = 0; i < sizeof(g_font) / sizeof(g_font[0]); i++) {
        if (g_font[i].ch == c) {
            return g_font[i].row;
        }
    }
    return g_font[0].row;
}

static void draw_char(int x, int y, char c, uint8_t color)
{
    const uint8_t *rows = glyph_rows(c);
    for (int yy = 0; yy < 7; yy++) {
        for (int xx = 0; xx < 5; xx++) {
            if (rows[yy] & (1 << (4 - xx))) {
                put_pixel(x + xx, y + yy, color);
            }
        }
    }
}

static void draw_text(int x, int y, const char *text, uint8_t color)
{
    int start_x = x;
    while (*text) {
        if (*text == '\n') {
            y += 9;
            x = start_x;
        } else {
            draw_char(x, y, *text, color);
            x += 6;
        }
        text++;
    }
}

static void draw_kv(int x, int *y, const char *key, const char *value)
{
    draw_text(x, *y, key, COL_BCYAN);
    draw_text(x + 102, *y, value, COL_WHITE);
    *y += 10;
}

static void cpuid_call(uint32_t leaf, uint32_t subleaf, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
    __asm__ volatile (
        "cpuid"
        : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
        : "a"(leaf), "c"(subleaf)
    );
}

static void detect_cpu(void)
{
    uint32_t a, b, c, d;
    cpuid_call(0, 0, &a, &b, &c, &d);
    g_cpu.max_leaf = a;
    mem_copy(&g_cpu.vendor[0], &b, 4);
    mem_copy(&g_cpu.vendor[4], &d, 4);
    mem_copy(&g_cpu.vendor[8], &c, 4);
    g_cpu.vendor[12] = 0;

    if (g_cpu.max_leaf >= 1) {
        cpuid_call(1, 0, &a, &b, &c, &d);
        g_cpu.signature = a;
        g_cpu.features_ecx = c;
        g_cpu.features_edx = d;
    }
}

static int wait_input_empty(void)
{
    for (int i = 0; i < 100000; i++) {
        if ((inb(0x64) & 0x02) == 0) {
            return 1;
        }
    }
    return 0;
}

static int wait_output_full(void)
{
    for (int i = 0; i < 100000; i++) {
        if (inb(0x64) & 0x01) {
            return 1;
        }
    }
    return 0;
}

static uint8_t ps2_read_data(void)
{
    if (!wait_output_full()) {
        return 0;
    }
    return inb(0x60);
}

static uint8_t ps2_mouse_write(uint8_t value)
{
    wait_input_empty();
    outb(0x64, 0xD4);
    wait_input_empty();
    outb(0x60, value);
    return ps2_read_data();
}

static void init_ps2_mouse(void)
{
    while (inb(0x64) & 0x01) {
        (void)inb(0x60);
    }

    wait_input_empty();
    outb(0x64, 0xA8);
    wait_input_empty();
    outb(0x64, 0x20);
    uint8_t status = ps2_read_data();
    status &= (uint8_t)~0x20;
    status |= 0x02;
    wait_input_empty();
    outb(0x64, 0x60);
    wait_input_empty();
    outb(0x60, status);

    uint8_t ack_defaults = ps2_mouse_write(0xF6);
    uint8_t ack_enable = ps2_mouse_write(0xF4);
    g_mouse_present = (ack_defaults == 0xFA || ack_enable == 0xFA);
}

static void rescan_fat(void); /* forward declaration */

static void adjust_file_scroll(void)
{
    if (g_selected_file < g_file_scroll) {
        g_file_scroll = g_selected_file;
    } else if (g_selected_file >= g_file_scroll + FILES_VISIBLE) {
        g_file_scroll = g_selected_file - FILES_VISIBLE + 1;
    }
}

static void handle_key(uint8_t scancode)
{
    if (scancode & 0x80) {
        return;
    }

    if (scancode >= 0x02 && scancode <= 0x06) {
        g_selected_page = scancode - 0x02;
        g_file_scroll = 0;
        return;
    }

    if (scancode == 0x48) {
        if (g_selected_page == 4 && g_selected_file > 0) {
            g_selected_file--;
            adjust_file_scroll();
        } else if (g_selected_page == 2 && g_selected_disk > 0) {
            g_selected_disk--;
            rescan_fat();
        } else if (g_selected_page > 0) {
            g_selected_page--;
            g_file_scroll = 0;
        }
    } else if (scancode == 0x50) {
        int total_files = ROM_FILE_COUNT + g_disk_file_count;
        if (g_selected_page == 4 && g_selected_file + 1 < total_files) {
            g_selected_file++;
            adjust_file_scroll();
        } else if (g_selected_page == 2 && g_selected_disk < 3) {
            g_selected_disk++;
            rescan_fat();
        } else if (g_selected_page < 4) {
            g_selected_page++;
            g_file_scroll = 0;
        }
    }
}

static void handle_mouse_packet(uint8_t b0, uint8_t b1, uint8_t b2)
{
    int old_buttons = g_mouse_buttons;
    int dx = (int8_t)b1;
    int dy = (int8_t)b2;
    g_mouse_buttons = b0 & 0x07;
    g_mouse_x += dx;
    g_mouse_y -= dy;
    if (g_mouse_x < 0) {
        g_mouse_x = 0;
    }
    if (g_mouse_y < 0) {
        g_mouse_y = 0;
    }
    if (g_mouse_x >= SCREEN_W) {
        g_mouse_x = SCREEN_W - 1;
    }
    if (g_mouse_y >= SCREEN_H) {
        g_mouse_y = SCREEN_H - 1;
    }
    if ((g_mouse_buttons & 1) && !(old_buttons & 1)) {
        g_mouse_click = 1;
    }
}

static void process_mouse_click(void)
{
    if (!g_mouse_click) {
        return;
    }
    g_mouse_click = 0;

    if (g_mouse_x < 72) {
        for (int i = 0; i < 5; i++) {
            int top = 28 + i * 24;
            if (g_mouse_y >= top && g_mouse_y < top + 18) {
                g_selected_page = i;
                g_file_scroll = 0;
                return;
            }
        }
    }

    if (g_selected_page == 2 && g_mouse_x >= 84 && g_mouse_x < 230 && g_mouse_y >= 46) {
        int d = (g_mouse_y - 46) / 11;
        if (d >= 0 && d < 4) {
            g_selected_disk = d;
            rescan_fat();
            return;
        }
    }

    if (g_selected_page == 4 && g_mouse_x >= 84 && g_mouse_x < 174 && g_mouse_y >= 42) {
        int row = (g_mouse_y - 42) / 10;
        int idx = g_file_scroll + row;
        int total = ROM_FILE_COUNT + g_disk_file_count;
        if (idx >= 0 && idx < total) {
            g_selected_file = idx;
            adjust_file_scroll();
        }
    }
}

static void poll_input(void)
{
    static uint8_t mouse_packet[3];
    static int mouse_index;

    while (inb(0x64) & 0x01) {
        uint8_t status = inb(0x64);
        uint8_t data = inb(0x60);
        if ((status & 0x20) && g_mouse_present) {
            if (mouse_index == 0 && (data & 0x08) == 0) {
                continue;
            }
            mouse_packet[mouse_index++] = data;
            if (mouse_index == 3) {
                handle_mouse_packet(mouse_packet[0], mouse_packet[1], mouse_packet[2]);
                mouse_index = 0;
            }
        } else {
            handle_key(data);
        }
    }
    process_mouse_click();
}

static int ata_wait_not_busy(uint16_t base)
{
    for (int i = 0; i < 1000000; i++) {
        if ((inb(base + 7) & 0x80) == 0) {
            return 1;
        }
    }
    return 0;
}

static int ata_wait_drq(uint16_t base)
{
    for (int i = 0; i < 1000000; i++) {
        uint8_t s = inb(base + 7);
        if (s & 0x01) {
            return 0;
        }
        if (s & 0x08) {
            return 1;
        }
    }
    return 0;
}

static void trim_model(char *s)
{
    for (int i = 39; i >= 0; i--) {
        if (s[i] == ' ' || s[i] == 0) {
            s[i] = 0;
        } else {
            break;
        }
    }
}

static void ata_identify(int drive)
{
    uint16_t id[256];
    uint16_t base = (drive < 2) ? 0x1F0 : 0x170;
    int slave = drive & 1;
    mem_set(id, 0, sizeof(id));

    outb(base + 6, (uint8_t)(0xA0 | (slave << 4)));
    io_wait();
    outb(base + 2, 0);
    outb(base + 3, 0);
    outb(base + 4, 0);
    outb(base + 5, 0);
    outb(base + 7, 0xEC);

    uint8_t status = inb(base + 7);
    if (status == 0) {
        return;
    }
    if (!ata_wait_not_busy(base)) {
        return;
    }
    if (inb(base + 4) != 0 || inb(base + 5) != 0) {
        return;
    }
    if (!ata_wait_drq(base)) {
        return;
    }

    for (int i = 0; i < 256; i++) {
        id[i] = inw(base);
    }

    g_ata[drive].present = 1;
    for (int i = 0; i < 20; i++) {
        uint16_t w = id[27 + i];
        g_ata[drive].model[i * 2] = (char)(w >> 8);
        g_ata[drive].model[i * 2 + 1] = (char)(w & 0xFF);
    }
    g_ata[drive].model[40] = 0;
    trim_model(g_ata[drive].model);
    g_ata[drive].sectors28 = (uint32_t)id[60] | ((uint32_t)id[61] << 16);
}

static int ata_read28(int drive, uint32_t lba, uint8_t *buffer)
{
    if ((unsigned)drive >= 4 || !g_ata[drive].present || lba >= 0x0FFFFFFF) {
        return 0;
    }
    uint16_t base = (drive < 2) ? 0x1F0 : 0x170;
    int slave = drive & 1;
    if (!ata_wait_not_busy(base)) {
        return 0;
    }

    outb(base + 6, (uint8_t)(0xE0 | (slave << 4) | ((lba >> 24) & 0x0F)));
    outb(base + 2, 1);
    outb(base + 3, (uint8_t)(lba & 0xFF));
    outb(base + 4, (uint8_t)((lba >> 8) & 0xFF));
    outb(base + 5, (uint8_t)((lba >> 16) & 0xFF));
    outb(base + 7, 0x20);

    if (!ata_wait_drq(base)) {
        return 0;
    }
    for (int i = 0; i < 256; i++) {
        uint16_t w = inw(base);
        buffer[i * 2] = (uint8_t)(w & 0xFF);
        buffer[i * 2 + 1] = (uint8_t)(w >> 8);
    }
    return 1;
}

static void parse_partitions(void)
{
    for (int i = 0; i < 4; i++) {
        const uint8_t *p = &g_sector[446 + i * 16];
        g_partitions[i].type = p[4];
        g_partitions[i].lba = le32(p + 8);
        g_partitions[i].sectors = le32(p + 12);
    }
}

static int is_fat_type(uint8_t t)
{
    return t == 0x04 || t == 0x06 || t == 0x0E || t == 0x0B || t == 0x0C;
}

static void make_83_name(const uint8_t *entry, char *out)
{
    int p = 0;
    for (int i = 0; i < 8; i++) {
        if (entry[i] == ' ') {
            break;
        }
        out[p++] = (char)entry[i];
    }
    if (entry[8] != ' ') {
        out[p++] = '.';
        for (int i = 8; i < 11; i++) {
            if (entry[i] == ' ') {
                break;
            }
            out[p++] = (char)entry[i];
        }
    }
    out[p] = 0;
}

static void add_dir_entries_from_sector(const uint8_t *sector)
{
    for (int off = 0; off < 512 && g_disk_file_count < 32; off += 32) {
        const uint8_t *e = sector + off;
        if (e[0] == 0) {
            return;
        }
        if (e[0] == 0xE5 || e[11] == 0x0F || (e[11] & 0x08)) {
            continue;
        }
        make_83_name(e, g_disk_files[g_disk_file_count].name);
        g_disk_files[g_disk_file_count].attr = e[11];
        g_disk_files[g_disk_file_count].cluster =
            ((uint32_t)le16(e + 20) << 16) | le16(e + 26);
        g_disk_files[g_disk_file_count].size = le32(e + 28);
        g_disk_file_count++;
    }
}

static uint32_t fat_cluster_lba(uint32_t cluster)
{
    if (cluster < 2 || g_fat_sectors_per_cluster == 0) {
        return 0;
    }
    return g_fat_data_lba + (cluster - 2) * g_fat_sectors_per_cluster;
}

static void scan_fat_partition(const partition_t *part, int drive)
{
    if (!ata_read28(drive, part->lba, g_sector)) {
        return;
    }
    uint16_t bps = le16(g_sector + 11);
    uint8_t spc = g_sector[13];
    uint16_t reserved = le16(g_sector + 14);
    uint8_t fats = g_sector[16];
    uint16_t root_entries = le16(g_sector + 17);
    uint16_t fat16_size = le16(g_sector + 22);
    uint32_t fat32_size = le32(g_sector + 36);
    uint32_t root_cluster = le32(g_sector + 44);
    uint32_t fat_size = fat16_size ? fat16_size : fat32_size;

    if (bps != 512 || spc == 0 || fats == 0 || fat_size == 0) {
        return;
    }

    g_fat_part_lba = part->lba;
    g_fat_bytes_per_sector = bps;
    g_fat_sectors_per_cluster = spc;

    uint32_t root_dir_sectors = ((uint32_t)root_entries * 32 + (bps - 1)) / bps;
    uint32_t root_dir_lba = part->lba + reserved + fats * fat_size;
    g_fat_data_lba = root_dir_lba + root_dir_sectors;

    if (root_entries == 0) {
        g_fat_type = 32;
        uint32_t lba = fat_cluster_lba(root_cluster);
        for (uint8_t s = 0; s < spc && s < 8 && g_disk_file_count < 32; s++) {
            if (ata_read28(drive, lba + s, g_sector)) {
                add_dir_entries_from_sector(g_sector);
            }
        }
    } else {
        g_fat_type = 16;
        for (uint32_t s = 0; s < root_dir_sectors && s < 8 && g_disk_file_count < 32; s++) {
            if (ata_read28(drive, root_dir_lba + s, g_sector)) {
                add_dir_entries_from_sector(g_sector);
            }
        }
    }
}

static void rescan_fat(void)
{
    g_disk_file_count = 0;
    g_fat_type = 0;
    g_fat_part_lba = 0;
    g_fat_data_lba = 0;
    g_selected_file = 0;
    g_file_scroll = 0;
    mem_set(g_partitions, 0, sizeof(g_partitions));

    int d = g_selected_disk;
    if ((unsigned)d >= 4 || !g_ata[d].present) {
        return;
    }
    if (!ata_read28(d, 0, g_sector)) {
        return;
    }
    if (g_sector[510] != 0x55 || g_sector[511] != 0xAA) {
        return;
    }
    parse_partitions();
    for (int i = 0; i < 4; i++) {
        if (is_fat_type(g_partitions[i].type) && g_partitions[i].lba != 0) {
            scan_fat_partition(&g_partitions[i], d);
            break;
        }
    }
}

static void scan_storage(void)
{
    for (int i = 0; i < 4; i++) {
        ata_identify(i);
    }
    rescan_fat();
}

static uint8_t cmos_read(uint8_t reg)
{
    outb(0x70, reg);
    return inb(0x71);
}

static uint8_t bcd_to_bin(uint8_t v)
{
    return (uint8_t)((v & 0x0F) + ((v >> 4) * 10));
}

static void draw_header(void)
{
    fill_rect(0, 0, SCREEN_W, SCREEN_H, COL_BLACK);
    fill_rect(0, 0, SCREEN_W, 20, COL_BLUE);
    draw_text(8, 7, "CaYaBasicOS", COL_WHITE);
    draw_text(224, 7, "BARE METAL", COL_YELLOW);
}

static void draw_nav(void)
{
    static const char *names[] = {"1 CPU", "2 RAM", "3 STORAGE", "4 SYSTEM", "5 FILES"};
    fill_rect(0, HDR_H, NAV_W, SCREEN_H - HDR_H, COL_DGRAY);
    for (int i = 0; i < 5; i++) {
        int y = 28 + i * 24;
        uint8_t bg = (i == g_selected_page) ? COL_BBLUE : COL_DGRAY;
        uint8_t fg = (i == g_selected_page) ? COL_WHITE : COL_LGRAY;
        fill_rect(6, y - 4, 64, 18, bg);
        draw_rect(6, y - 4, 64, 18, (i == g_selected_page) ? COL_BCYAN : COL_LGRAY);
        draw_text(12, y, names[i], fg);
    }
}

static void draw_footer(void)
{
    fill_rect(NAV_W, SCREEN_H - FTR_H, SCREEN_W - NAV_W, FTR_H, COL_DGRAY);
    draw_text(NAV_W + 8, SCREEN_H - FTR_H + 5, "KEYS 1-5  UP/DN  MOUSE CLICK", COL_LGRAY);
}

static void draw_cpu_page(void)
{
    int y = 32;
    char buf[32];
    uint32_t sig = g_cpu.signature;
    uint32_t stepping = sig & 0xF;
    uint32_t model = (sig >> 4) & 0xF;
    uint32_t family = (sig >> 8) & 0xF;
    uint32_t ext_model = (sig >> 16) & 0xF;
    uint32_t ext_family = (sig >> 20) & 0xFF;
    if (family == 6 || family == 15) {
        model += ext_model << 4;
    }
    if (family == 15) {
        family += ext_family;
    }

    draw_text(86, y, "PROCESSOR", COL_YELLOW);
    y += 16;
    draw_kv(86, &y, "VENDOR", g_cpu.vendor);
    u32_to_dec(g_cpu.max_leaf, buf);
    draw_kv(86, &y, "CPUID LEAF", buf);
    u32_to_dec(family, buf);
    draw_kv(86, &y, "FAMILY", buf);
    u32_to_dec(model, buf);
    draw_kv(86, &y, "MODEL", buf);
    u32_to_dec(stepping, buf);
    draw_kv(86, &y, "STEPPING", buf);
    u32_to_hex(g_cpu.features_edx, buf);
    draw_kv(86, &y, "FEATURE EDX", buf);
    u32_to_hex(g_cpu.features_ecx, buf);
    draw_kv(86, &y, "FEATURE ECX", buf);
}

static void draw_ram_page(void)
{
    int y = 32;
    char buf[32];
    uint32_t below16 = g_boot_info ? g_boot_info->e801_below_16m_kb : 0;
    uint32_t above16 = g_boot_info ? ((uint32_t)g_boot_info->e801_above_16m_64k * 64) : 0;
    uint32_t total = (g_boot_info ? g_boot_info->conventional_kb : 0) + below16 + above16;

    draw_text(86, y, "MEMORY", COL_YELLOW);
    y += 16;
    u32_to_dec(g_boot_info ? g_boot_info->conventional_kb : 0, buf);
    draw_kv(86, &y, "CONVENTIONAL KB", buf);
    u32_to_dec(below16, buf);
    draw_kv(86, &y, "EXT BELOW 16M KB", buf);
    u32_to_dec(above16, buf);
    draw_kv(86, &y, "EXT ABOVE 16M KB", buf);
    u32_to_dec(total, buf);
    draw_kv(86, &y, "TOTAL KB", buf);
    u32_to_dec(total / 1024, buf);
    draw_kv(86, &y, "TOTAL MB", buf);
}

static void draw_storage_page(void)
{
    int y = 26;
    char buf[32];
    static const char *drive_names[] = {
        "PRI MASTER", "PRI SLAVE",
        "SEC MASTER", "SEC SLAVE"
    };
    draw_text(86, y, "STORAGE  [UP/DN:SEL DISK]", COL_YELLOW);
    y += 14;

    for (int d = 0; d < 4; d++) {
        uint8_t fg = (d == g_selected_disk) ? COL_WHITE : COL_BCYAN;
        if (d == g_selected_disk) {
            fill_rect(84, y - 2, SCREEN_W - NAV_W - 8, 11, COL_BLUE);
        }
        draw_text(86, y, drive_names[d], fg);
        if (g_ata[d].present) {
            draw_text(150, y, g_ata[d].model[0] ? g_ata[d].model : "ATA DEVICE", fg);
        } else {
            draw_text(150, y, "N/A", COL_DGRAY);
        }
        y += 11;
        if (d == g_selected_disk && g_ata[d].present) {
            u32_to_dec(g_ata[d].sectors28 / 2048, buf);
            draw_kv(96, &y, "SIZE MB", buf);
        }
    }

    y += 4;
    draw_text(86, y, "MBR PARTITIONS", COL_YELLOW);
    y += 12;
    for (int i = 0; i < 4; i++) {
        draw_text(86, y, "P", COL_BCYAN);
        draw_char(92, y, (char)('1' + i), COL_BCYAN);
        draw_text(104, y, "TYPE", COL_LGRAY);
        u32_to_hex(g_partitions[i].type, buf);
        draw_text(134, y, buf + 8, COL_WHITE);
        draw_text(154, y, "LBA", COL_LGRAY);
        u32_to_dec(g_partitions[i].lba, buf);
        draw_text(178, y, buf, COL_WHITE);
        y += 10;
    }
}

static void draw_system_page(void)
{
    int y = 32;
    char buf[32];
    char timebuf[16];
    draw_text(86, y, "SYSTEM", COL_YELLOW);
    y += 16;

    u32_to_hex(g_boot_drive, buf);
    draw_kv(86, &y, "BOOT DRIVE", buf);
    draw_kv(86, &y, "VIDEO", "VGA MODE 13H");
    draw_kv(86, &y, "KEYBOARD", "PS2 POLLING");
    draw_kv(86, &y, "MOUSE", g_mouse_present ? "PS2 ENABLED" : "NOT DETECTED");
    draw_kv(86, &y, "FILESYSTEM", g_fat_type == 32 ? "FAT32 FOUND" : (g_fat_type == 16 ? "FAT16 FOUND" : "ROM ONLY"));

    uint8_t h = bcd_to_bin(cmos_read(0x04));
    uint8_t m = bcd_to_bin(cmos_read(0x02));
    uint8_t s = bcd_to_bin(cmos_read(0x00));
    timebuf[0] = (char)('0' + h / 10);
    timebuf[1] = (char)('0' + h % 10);
    timebuf[2] = ':';
    timebuf[3] = (char)('0' + m / 10);
    timebuf[4] = (char)('0' + m % 10);
    timebuf[5] = ':';
    timebuf[6] = (char)('0' + s / 10);
    timebuf[7] = (char)('0' + s % 10);
    timebuf[8] = 0;
    draw_kv(86, &y, "CMOS TIME", timebuf);
}

static void preview_disk_file(const disk_file_t *file)
{
    mem_set(g_preview, 0, sizeof(g_preview));
    if ((file->attr & 0x10) || file->cluster < 2 || g_fat_type == 0) {
        return;
    }
    uint32_t lba = fat_cluster_lba(file->cluster);
    if (lba) {
        ata_read28(g_selected_disk, lba, g_preview);
    }
}

static void draw_wrapped_bytes(int x, int y, const uint8_t *data, int max_bytes, uint8_t color)
{
    int col = 0;
    int line = 0;
    for (int i = 0; i < max_bytes && line < 10; i++) {
        char c = (char)data[i];
        if (c == 0) {
            break;
        }
        if (c == '\r') {
            continue;
        }
        if (c == '\n' || col >= 32) {
            line++;
            col = 0;
            if (c == '\n') {
                continue;
            }
        }
        if (c < 32 || c > 126) {
            c = '.';
        }
        draw_char(x + col * 6, y + line * 9, c, color);
        col++;
    }
}

static void draw_files_page(void)
{
    int y = 32;
    char buf[32];
    int total = ROM_FILE_COUNT + g_disk_file_count;
    if (total > 0 && g_selected_file >= total) {
        g_selected_file = total - 1;
    }
    if (g_file_scroll > 0 && g_file_scroll >= total) {
        g_file_scroll = total > 0 ? total - 1 : 0;
    }

    draw_text(86, y, "FILES", COL_YELLOW);
    draw_text(184, y, "PREVIEW", COL_YELLOW);
    y += 12;

    for (int i = 0; i < FILES_VISIBLE && (g_file_scroll + i) < total; i++) {
        int file_idx = g_file_scroll + i;
        uint8_t bg = (file_idx == g_selected_file) ? COL_BLUE : COL_BLACK;
        uint8_t fg = (file_idx == g_selected_file) ? COL_WHITE : COL_LGRAY;
        fill_rect(84, y - 2 + i * 10, 88, 9, bg);
        if (file_idx < ROM_FILE_COUNT) {
            draw_text(88, y + i * 10, g_rom_files[file_idx].name, fg);
        } else {
            const disk_file_t *df = &g_disk_files[file_idx - ROM_FILE_COUNT];
            draw_text(88, y + i * 10, df->name, fg);
        }
    }

    /* Scroll indicators */
    if (g_file_scroll > 0) {
        draw_text(166, y, "^", COL_BCYAN);
    }
    if (g_file_scroll + FILES_VISIBLE < total) {
        draw_text(166, y + (FILES_VISIBLE - 1) * 10, "v", COL_BCYAN);
    }

    if (g_fat_type) {
        u32_to_dec(g_disk_file_count, buf);
        draw_text(86, SCREEN_H - FTR_H - 10, "DISK ROOT FILES:", COL_BCYAN);
        draw_text(176, SCREEN_H - FTR_H - 10, buf, COL_WHITE);
    } else {
        draw_text(86, SCREEN_H - FTR_H - 10, "NO FAT16/FAT32 ATA ROOT FOUND", COL_LGRAY);
    }

    if (total == 0) {
        draw_text(184, 48, "NO FILES", COL_LGRAY);
        return;
    }

    if (g_selected_file < ROM_FILE_COUNT) {
        draw_wrapped_bytes(184, 48, (const uint8_t *)g_rom_files[g_selected_file].data,
                           (int)str_len(g_rom_files[g_selected_file].data), COL_WHITE);
    } else {
        disk_file_t *file = &g_disk_files[g_selected_file - ROM_FILE_COUNT];
        int meta_y = 62;
        draw_text(184, 48, file->name, COL_BCYAN);
        u32_to_dec(file->size, buf);
        draw_kv(184, &meta_y, "SIZE", buf);
        preview_disk_file(file);
        draw_wrapped_bytes(184, 76, g_preview, 320, COL_WHITE);
    }
}

static void draw_mouse_cursor(void)
{
    int x = g_mouse_x;
    int y = g_mouse_y;
    /* Clean right-triangle arrow: left vertical edge + diagonal right edge,
       closed at the base with a horizontal line */
    for (int i = 0; i < 8; i++) {
        put_pixel(x,     y + i, COL_WHITE); /* left edge */
        put_pixel(x + i, y + i, COL_WHITE); /* diagonal */
    }
    /* Close the base of the triangle (row 7 already has x and x+7,
       fill the interior bottom edge) */
    for (int i = 1; i < 7; i++) {
        put_pixel(x + i, y + 7, COL_WHITE);
    }
}

static void render(void)
{
    draw_header();
    draw_nav();
    fill_rect(NAV_W, HDR_H, SCREEN_W - NAV_W, SCREEN_H - HDR_H - FTR_H, COL_BLACK);
    draw_rect(NAV_W + 4, HDR_H + 6, SCREEN_W - NAV_W - 8, SCREEN_H - HDR_H - FTR_H - 10, COL_DGRAY);

    if (g_selected_page == 0) {
        draw_cpu_page();
    } else if (g_selected_page == 1) {
        draw_ram_page();
    } else if (g_selected_page == 2) {
        draw_storage_page();
    } else if (g_selected_page == 3) {
        draw_system_page();
    } else {
        draw_files_page();
    }

    draw_footer();
    draw_mouse_cursor();
}

static void delay_frame(void)
{
    for (volatile int i = 0; i < 25000; i++) {
        io_wait();
    }
}

void kmain(uint32_t boot_drive, const boot_info_t *boot_info)
{
    g_boot_drive = boot_drive;
    g_boot_info = boot_info;
    g_selected_page = 0;
    g_selected_file = 0;
    g_disk_file_count = 0;
    g_fat_type = 0;
    mem_set(g_partitions, 0, sizeof(g_partitions));
    mem_set(g_ata, 0, sizeof(g_ata));

    detect_cpu();
    init_ps2_mouse();
    scan_storage();

    for (;;) {
        poll_input();
        render();
        delay_frame();
    }
}
