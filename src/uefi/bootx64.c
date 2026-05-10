#include <stdint.h>
#include <stddef.h>

#if defined(__clang__) || defined(__GNUC__)
#define CY_UNUSED __attribute__((unused))
#else
#define CY_UNUSED
#endif

#define EFI_SUCCESS 0
#define EFI_ERROR_BIT 0x8000000000000000ULL
#define EFI_WARN_DELETE_FAILURE 0x0000000000000002ULL
#define EFI_INVALID_PARAMETER (EFI_ERROR_BIT | 2ULL)
#define EFI_UNSUPPORTED (EFI_ERROR_BIT | 3ULL)
#define EFI_BUFFER_TOO_SMALL (EFI_ERROR_BIT | 5ULL)
#define EFI_NOT_READY (EFI_ERROR_BIT | 6ULL)
#define EFI_DEVICE_ERROR (EFI_ERROR_BIT | 7ULL)
#define EFI_WRITE_PROTECTED (EFI_ERROR_BIT | 8ULL)
#define EFI_OUT_OF_RESOURCES (EFI_ERROR_BIT | 9ULL)
#define EFI_VOLUME_CORRUPTED (EFI_ERROR_BIT | 10ULL)
#define EFI_NO_MEDIA (EFI_ERROR_BIT | 12ULL)
#define EFI_MEDIA_CHANGED (EFI_ERROR_BIT | 13ULL)
#define EFI_NOT_FOUND (EFI_ERROR_BIT | 14ULL)
#define EFI_ACCESS_DENIED (EFI_ERROR_BIT | 15ULL)
#define EFI_ALREADY_STARTED (EFI_ERROR_BIT | 20ULL)
#define EFI_END_OF_FILE (EFI_ERROR_BIT | 31ULL)
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL         0x00000002
#define AllHandles 0
#define BY_PROTOCOL 2
#define EfiLoaderData 2

typedef uint8_t BOOLEAN;
typedef uint16_t CHAR16;
typedef uint64_t UINTN;
typedef uint64_t EFI_STATUS;
typedef void *EFI_HANDLE;
typedef void *EFI_EVENT;
typedef uint64_t EFI_PHYSICAL_ADDRESS;
typedef uint64_t EFI_VIRTUAL_ADDRESS;

typedef struct {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
} EFI_GUID;

typedef struct {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
} EFI_TABLE_HEADER;

typedef struct {
    uint8_t Type;
    uint8_t SubType;
    uint8_t Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct {
    uint16_t ScanCode;
    CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_STATUS (*Reset)(EFI_SIMPLE_TEXT_INPUT_PROTOCOL *, BOOLEAN);
    EFI_STATUS (*ReadKeyStroke)(EFI_SIMPLE_TEXT_INPUT_PROTOCOL *, EFI_INPUT_KEY *);
    EFI_EVENT WaitForKey;
};

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void *Reset;
    EFI_STATUS (*OutputString)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *, CHAR16 *);
    void *TestString;
    void *QueryMode;
    void *SetMode;
    void *SetAttribute;
    void *ClearScreen;
    void *SetCursorPosition;
    void *EnableCursor;
    void *Mode;
};

typedef struct EFI_BOOT_SERVICES EFI_BOOT_SERVICES;
struct EFI_BOOT_SERVICES {
    EFI_TABLE_HEADER Hdr;
    void *RaiseTPL;
    void *RestoreTPL;
    EFI_STATUS (*AllocatePages)(uint32_t, uint32_t, UINTN, EFI_PHYSICAL_ADDRESS *);
    EFI_STATUS (*FreePages)(EFI_PHYSICAL_ADDRESS, UINTN);
    EFI_STATUS (*GetMemoryMap)(UINTN *, void *, UINTN *, UINTN *, uint32_t *);
    EFI_STATUS (*AllocatePool)(uint32_t, UINTN, void **);
    EFI_STATUS (*FreePool)(void *);
    void *CreateEvent;
    void *SetTimer;
    void *WaitForEvent;
    void *SignalEvent;
    void *CloseEvent;
    void *CheckEvent;
    void *InstallProtocolInterface;
    void *ReinstallProtocolInterface;
    void *UninstallProtocolInterface;
    EFI_STATUS (*HandleProtocol)(EFI_HANDLE, EFI_GUID *, void **);
    void *Reserved;
    void *RegisterProtocolNotify;
    EFI_STATUS (*LocateHandle)(uint32_t, EFI_GUID *, void *, UINTN *, EFI_HANDLE *);
    void *LocateDevicePath;
    void *InstallConfigurationTable;
    EFI_STATUS (*LoadImage)(BOOLEAN, EFI_HANDLE, void *, void *, UINTN, EFI_HANDLE *);
    EFI_STATUS (*StartImage)(EFI_HANDLE, UINTN *, CHAR16 **);
    void *Exit;
    void *UnloadImage;
    void *ExitBootServices;
    void *GetNextMonotonicCount;
    EFI_STATUS (*Stall)(UINTN);
    EFI_STATUS (*SetWatchdogTimer)(UINTN, uint64_t, UINTN, CHAR16 *);
    EFI_STATUS (*ConnectController)(EFI_HANDLE, EFI_HANDLE *, void *, BOOLEAN);
    EFI_STATUS (*DisconnectController)(EFI_HANDLE, EFI_HANDLE, EFI_HANDLE);
    EFI_STATUS (*OpenProtocol)(EFI_HANDLE, EFI_GUID *, void **, EFI_HANDLE, EFI_HANDLE, uint32_t);
    void *CloseProtocol;
    void *OpenProtocolInformation;
    void *ProtocolsPerHandle;
    EFI_STATUS (*LocateHandleBuffer)(uint32_t, EFI_GUID *, void *, UINTN *, EFI_HANDLE **);
    EFI_STATUS (*LocateProtocol)(EFI_GUID *, void *, void **);
    void *InstallMultipleProtocolInterfaces;
    void *UninstallMultipleProtocolInterfaces;
    void *CalculateCrc32;
    void *CopyMem;
    void *SetMem;
    void *CreateEventEx;
};

typedef struct {
    uint16_t Year;
    uint8_t  Month;
    uint8_t  Day;
    uint8_t  Hour;
    uint8_t  Minute;
    uint8_t  Second;
    uint8_t  Pad1;
    uint32_t Nanosecond;
    int16_t  TimeZone;
    uint8_t  Daylight;
    uint8_t  Pad2;
} EFI_TIME;

/* Minimal EFI_RUNTIME_SERVICES — GetVariable + GetTime + ResetSystem are wired,
 * the rest are kept opaque.                                                   */
typedef struct {
    EFI_TABLE_HEADER Hdr;
    EFI_STATUS (*GetTime)(EFI_TIME *Time, void *Capabilities);
    void *SetTime;
    void *GetWakeupTime;
    void *SetWakeupTime;
    void *SetVirtualAddressMap;
    void *ConvertPointer;
    EFI_STATUS (*GetVariable)(CHAR16 *, EFI_GUID *, uint32_t *, UINTN *, void *);
    void *GetNextVariableName;
    void *SetVariable;
    void *GetNextHighMonotonicCount;
    void (*ResetSystem)(uint32_t, EFI_STATUS, UINTN, void *);
} EFI_RUNTIME_SERVICES;

typedef struct {
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    uint32_t FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    void *ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef struct {
    uint32_t Version;
    uint32_t HorizontalResolution;
    uint32_t VerticalResolution;
    uint32_t PixelFormat;
    uint32_t PixelInformation[4];
    uint32_t PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
    uint32_t MaxMode;
    uint32_t Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    UINTN SizeOfInfo;
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINTN FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
    void *QueryMode;
    EFI_STATUS (*SetMode)(EFI_GRAPHICS_OUTPUT_PROTOCOL *, uint32_t);
    void *Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
};

typedef struct {
    int32_t RelativeMovementX;
    int32_t RelativeMovementY;
    int32_t RelativeMovementZ;
    BOOLEAN LeftButton;
    BOOLEAN RightButton;
} EFI_SIMPLE_POINTER_STATE;

typedef struct {
    uint64_t ResolutionX;
    uint64_t ResolutionY;
    uint64_t ResolutionZ;
    BOOLEAN LeftButton;
    BOOLEAN RightButton;
} EFI_SIMPLE_POINTER_MODE;

typedef struct EFI_SIMPLE_POINTER_PROTOCOL EFI_SIMPLE_POINTER_PROTOCOL;
struct EFI_SIMPLE_POINTER_PROTOCOL {
    EFI_STATUS (*Reset)(EFI_SIMPLE_POINTER_PROTOCOL *, BOOLEAN);
    EFI_STATUS (*GetState)(EFI_SIMPLE_POINTER_PROTOCOL *, EFI_SIMPLE_POINTER_STATE *);
    EFI_EVENT WaitForInput;
    EFI_SIMPLE_POINTER_MODE *Mode;
};

typedef struct {
    uint64_t AbsoluteMinX;
    uint64_t AbsoluteMinY;
    uint64_t AbsoluteMinZ;
    uint64_t AbsoluteMaxX;
    uint64_t AbsoluteMaxY;
    uint64_t AbsoluteMaxZ;
    uint32_t Attributes;
} EFI_ABSOLUTE_POINTER_MODE;

typedef struct {
    uint64_t CurrentX;
    uint64_t CurrentY;
    uint64_t CurrentZ;
    uint32_t ActiveButtons;
} EFI_ABSOLUTE_POINTER_STATE;

typedef struct EFI_ABSOLUTE_POINTER_PROTOCOL EFI_ABSOLUTE_POINTER_PROTOCOL;
struct EFI_ABSOLUTE_POINTER_PROTOCOL {
    EFI_STATUS (*Reset)(EFI_ABSOLUTE_POINTER_PROTOCOL *, BOOLEAN);
    EFI_STATUS (*GetState)(EFI_ABSOLUTE_POINTER_PROTOCOL *, EFI_ABSOLUTE_POINTER_STATE *);
    EFI_EVENT WaitForInput;
    EFI_ABSOLUTE_POINTER_MODE *Mode;
};

typedef struct {
    uint32_t MediaId;
    BOOLEAN RemovableMedia;
    BOOLEAN MediaPresent;
    BOOLEAN LogicalPartition;
    BOOLEAN ReadOnly;
    BOOLEAN WriteCaching;
    uint32_t BlockSize;
    uint32_t IoAlign;
    uint64_t LastBlock;
} EFI_BLOCK_IO_MEDIA;

typedef struct {
    uint64_t Revision;
    EFI_BLOCK_IO_MEDIA *Media;
    EFI_STATUS (*Reset)(void *, BOOLEAN);
    EFI_STATUS (*ReadBlocks)(void *, uint32_t, uint64_t, UINTN, void *);
    EFI_STATUS (*WriteBlocks)(void *, uint32_t, uint64_t, UINTN, void *);
    EFI_STATUS (*FlushBlocks)(void *);
} EFI_BLOCK_IO_PROTOCOL;

typedef struct EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;
struct EFI_FILE_PROTOCOL {
    uint64_t Revision;
    EFI_STATUS (*Open)(EFI_FILE_PROTOCOL *, EFI_FILE_PROTOCOL **, CHAR16 *, uint64_t, uint64_t);
    EFI_STATUS (*Close)(EFI_FILE_PROTOCOL *);
    EFI_STATUS (*Delete)(EFI_FILE_PROTOCOL *);
    EFI_STATUS (*Read)(EFI_FILE_PROTOCOL *, UINTN *, void *);
    EFI_STATUS (*Write)(EFI_FILE_PROTOCOL *, UINTN *, void *);
    EFI_STATUS (*GetPosition)(EFI_FILE_PROTOCOL *, uint64_t *);
    EFI_STATUS (*SetPosition)(EFI_FILE_PROTOCOL *, uint64_t);
    EFI_STATUS (*GetInfo)(EFI_FILE_PROTOCOL *, EFI_GUID *, UINTN *, void *);
    EFI_STATUS (*SetInfo)(EFI_FILE_PROTOCOL *, EFI_GUID *, UINTN, void *);
    EFI_STATUS (*Flush)(EFI_FILE_PROTOCOL *);
    void *OpenEx;
    void *ReadEx;
    void *WriteEx;
    void *FlushEx;
};

typedef struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    uint64_t Revision;
    EFI_STATUS (*OpenVolume)(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *, EFI_FILE_PROTOCOL **);
};

typedef struct {
    uint64_t Size;
    uint64_t FileSize;
    uint64_t PhysicalSize;
    uint64_t CreateTime[2];
    uint64_t LastAccessTime[2];
    uint64_t ModificationTime[2];
    uint64_t Attribute;
    CHAR16 FileName[1];
} EFI_FILE_INFO;

typedef struct {
    uint32_t Type;
    uint32_t Pad;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
} EFI_MEMORY_DESCRIPTOR;

#define MAX_SIMPLE_POINTERS 8
#define MAX_ABSOLUTE_POINTERS 8
#define MAX_VOLUMES 12
#define MAX_EXPLORER_WINDOWS 6
#define EXPLORER_MODE_DISKS 0
#define EXPLORER_MODE_VOLUMES 1
#define EXPLORER_MODE_FILES 2
#define EXPLORER_MODE_PART_INFO 3
#define ACTIVE_EXPLORER 0
#define ACTIVE_TERMINAL 1
#define EFI_ABSP_TOUCH_ACTIVE 0x00000001
#define EFI_ABSP_ALT_ACTIVE 0x00000002
#define EFI_FILE_MODE_READ 0x0000000000000001ULL
#define EFI_FILE_MODE_WRITE 0x0000000000000002ULL
#define EFI_FILE_MODE_CREATE 0x8000000000000000ULL
#define EFI_FILE_DIRECTORY 0x0000000000000010ULL
#define EFI_FILE_READ_ONLY 0x0000000000000001ULL

typedef struct {
    uint16_t ch;
    uint8_t row[7];
} glyph_t;

typedef struct {
    uint64_t blocks;
    uint32_t block_size;
    uint32_t media_id;
    uint32_t parent_disk_idx;
    EFI_HANDLE handle;
    uint8_t removable;
    uint8_t readonly;
    uint8_t logical_partition;
    uint8_t present;
    char fs_name[8];
} block_summary_t;

typedef struct {
    CHAR16 name[96];
    uint64_t size;
    uint64_t attr;
    uint8_t is_dir;
    /* NTFS-format timestamps (100-ns ticks since 1601-01-01 UTC).  Carried
     * through GetInfo so a copy/move op can transplant them onto the
     * destination via SetInfo instead of stamping "now".                     */
    uint64_t t_create;
    uint64_t t_modify;
    uint64_t t_access;
} file_entry_t;

#define NATIVE_FS_NONE  0
#define NATIVE_FS_RAW   1
#define NATIVE_FS_EXFAT 2
#define NATIVE_FS_NTFS  3

#define NATIVE_MAX_EXTENTS 64
#define NATIVE_MAX_DIR_ENTRIES 96
#define NTFS_MAX_RESIDENT_DATA 4096

typedef struct {
    uint64_t vcn;
    uint64_t lcn;
    uint64_t clusters;
    uint8_t sparse;
} native_extent_t;

typedef struct {
    CHAR16 label[32];
    EFI_HANDLE handle;
    uint32_t media_id;
    uint32_t block_idx;
    uint8_t read_only;
    uint8_t firmware_fs;
    uint8_t native_fs;
    uint8_t native_ready;
    uint8_t native_probe_failed;
    uint8_t native_writable;
    uint32_t exfat_bytes_per_sector;
    uint32_t exfat_sectors_per_cluster;
    uint32_t exfat_cluster_size;
    uint32_t exfat_fat_offset;
    uint32_t exfat_fat_length;
    uint32_t exfat_cluster_heap_offset;
    uint32_t exfat_cluster_count;
    uint32_t exfat_root_cluster;
    uint32_t exfat_active_fat;
    uint32_t exfat_bitmap_cluster;
    uint64_t exfat_bitmap_len;
    uint32_t exfat_upcase_cluster;
    uint64_t exfat_upcase_len;
    uint32_t ntfs_bytes_per_sector;
    uint32_t ntfs_sectors_per_cluster;
    uint32_t ntfs_cluster_size;
    uint64_t ntfs_total_sectors;
    uint64_t ntfs_mft_lcn;
    uint32_t ntfs_record_size;
    uint32_t ntfs_index_record_size;
    native_extent_t ntfs_mft_extents[NATIVE_MAX_EXTENTS];
    uint32_t ntfs_mft_extent_count;
    uint64_t ntfs_mft_record_count;
    native_extent_t ntfs_bitmap_extents[NATIVE_MAX_EXTENTS];
    uint32_t ntfs_bitmap_extent_count;
    uint64_t ntfs_bitmap_size;
    uint8_t ntfs_modify_pending;  /* 1 once we have written to NTFS structures and owe Windows
                                     a $LogFile invalidate + clean-shutdown sequence on flush. */
    uint8_t ntfs_dirty_owned;     /* 1 if we (not Windows) set the VOLUME_IS_DIRTY flag, meaning
                                     we are the ones responsible for clearing it on flush.       */
} volume_t;

typedef struct {
    file_entry_t pub;
    uint64_t exfat_primary_offset;
    uint64_t exfat_stream_offset;
    uint32_t exfat_parent_cluster;
    uint64_t exfat_parent_len;
    uint32_t exfat_first_cluster;
    uint8_t exfat_no_fat_chain;
    uint8_t exfat_secondary_count;
    uint8_t exfat_parent_no_fat;
    uint64_t exfat_data_len;
    uint64_t ntfs_file_ref;
} native_dirent_t;

typedef struct {
    EFI_FILE_PROTOCOL proto;
    uint32_t magic;
    uint32_t volume;
    uint8_t fs_type;
    uint8_t is_dir;
    uint64_t pos;
    uint64_t size;
    uint64_t attr;
    CHAR16 name[96];
    uint8_t can_write;
    native_dirent_t dirents[NATIVE_MAX_DIR_ENTRIES];
    uint32_t dir_count;
    uint32_t dir_pos;
    uint64_t exfat_capacity;
    uint64_t exfat_primary_offset;
    uint64_t exfat_stream_offset;
    uint32_t exfat_parent_cluster;
    uint64_t exfat_parent_len;
    uint32_t exfat_first_cluster;
    uint8_t exfat_no_fat_chain;
    uint8_t exfat_secondary_count;
    uint8_t exfat_parent_no_fat;
    uint8_t ntfs_resident;
    uint32_t ntfs_resident_size;
    uint32_t ntfs_resident_capacity;
    uint64_t ntfs_file_ref;
    uint64_t ntfs_parent_ref;
    uint64_t ntfs_allocated_size;
    uint8_t ntfs_resident_data[NTFS_MAX_RESIDENT_DATA];
    native_extent_t extents[NATIVE_MAX_EXTENTS];
    uint32_t extent_count;
    /* NTFS-format timestamps (100-ns intervals since 1601-01-01 UTC) cached
     * from $STANDARD_INFORMATION at open time so GetInfo can return them and
     * SetInfo can write them back unchanged on a copy/move.                  */
    uint64_t ntfs_t_create;
    uint64_t ntfs_t_modify;  /* last_data_change_time */
    uint64_t ntfs_t_access;  /* last_access_time      */
} native_file_handle_t;

typedef struct {
    uint32_t volume;
    uint32_t mode;
    uint32_t disk;
    CHAR16 path[256];
    file_entry_t entries[32];
    uint32_t entry_count;
    uint32_t selected;
    uint32_t scroll;
    uint32_t vol_map[MAX_VOLUMES];
    uint32_t vol_count;
    uint8_t visible;
    uint8_t active;
    int x;
    int y;
    int w;
    int h;
} explorer_window_t;

void *memcpy(void *dest, const void *src, size_t count)
{
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    while (count--) {
        *d++ = *s++;
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t count)
{
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    if (d == s || !count) {
        return dest;
    }
    if (d < s) {
        while (count--) {
            *d++ = *s++;
        }
    } else {
        d += count;
        s += count;
        while (count--) {
            *--d = *--s;
        }
    }
    return dest;
}

void *memset(void *dest, int value, size_t count)
{
    uint8_t *d = (uint8_t *)dest;
    while (count--) {
        *d++ = (uint8_t)value;
    }
    return dest;
}

int memcmp(const void *a, const void *b, size_t count)
{
    const uint8_t *pa = (const uint8_t *)a;
    const uint8_t *pb = (const uint8_t *)b;
    while (count--) {
        if (*pa != *pb) {
            return (int)*pa - (int)*pb;
        }
        pa++;
        pb++;
    }
    return 0;
}

static EFI_SYSTEM_TABLE *g_st;
static EFI_BOOT_SERVICES *g_bs;
static EFI_HANDLE g_image;
static EFI_SIMPLE_TEXT_INPUT_PROTOCOL *g_in;
static EFI_GRAPHICS_OUTPUT_PROTOCOL *g_gop;
static uint32_t g_simple_ptr_count;
static uint32_t g_abs_ptr_count;
static uint32_t *g_fb;
static uint32_t *g_backbuffer;
static uint32_t g_w;
static uint32_t g_h;
static uint32_t g_stride;
static uint32_t g_pixel_format;
static uint32_t g_red_mask;
static uint32_t g_green_mask;
static uint32_t g_blue_mask;
static uint32_t g_page;
static int g_mouse_x = 320;
static int g_mouse_y = 200;
static int64_t g_mouse_fx;
static int64_t g_mouse_fy;
static int g_mouse_buttons;
static int g_mouse_click;
static uint32_t g_dirty = 1;
static uint64_t g_memory_mb;
static block_summary_t g_blocks[12];
static uint32_t g_block_count;
static uint32_t g_disk_count;
static uint32_t g_disk_map[12];
static uint32_t g_storage_scroll;
static volume_t g_volumes[MAX_VOLUMES];
static uint32_t g_volume_count;
static explorer_window_t g_windows[MAX_EXPLORER_WINDOWS];
static explorer_window_t g_temp_window;
static uint32_t g_active_window;
static uint32_t g_active_surface;
static uint8_t g_viewer_open;
static uint8_t g_viewer_edit;      /* 1 = edit mode active */
static CHAR16 g_viewer_title[96];
static char g_viewer_text[8192];
static uint32_t g_viewer_cursor;   /* byte offset of cursor in g_viewer_text */
static uint32_t g_viewer_vol;      /* volume index for save-back */
static CHAR16 g_viewer_path[256];  /* full path for save-back */
static uint32_t g_viewer_scroll;   /* first visible line (0-based) */
static uint32_t g_viewer_last_cursor_for_scroll;  /* cursor value when last auto-scrolled */
static uint8_t g_terminal_visible;
static char g_terminal_input[96];
static char g_terminal_lines[10][96];
static uint32_t g_terminal_line_count;
static uint32_t g_terminal_volume;
static CHAR16 g_terminal_path[256];
static int g_terminal_x;
static int g_terminal_y;
static int g_terminal_w;
static int g_terminal_h;
static uint8_t g_io_buffer[2048];
static uint8_t g_fs_block_buffer[4096];
static uint8_t g_fs_sector_buffer[4096];
static uint8_t g_ntfs_record_buffer[4096];
static uint8_t g_ntfs_record_buffer2[4096];
static native_dirent_t g_native_dir_scratch[NATIVE_MAX_DIR_ENTRIES];
static uint32_t g_last_click_window = 0xFFFFFFFFU;
static uint32_t g_last_click_entry = 0xFFFFFFFFU;
static int g_wheel_delta;
static int g_drag_kind;   /* 1=move explorer 2=move terminal 3=resize explorer */
static int g_drag_index;
static int g_drag_dx;
static int g_drag_dy;
static int g_drag_ox, g_drag_oy, g_drag_ow, g_drag_oh; /* resize: original rect */
static int g_resize_corner;  /* 0=TL 1=TR 2=BL 3=BR */
static uint32_t g_loop_ticks;
/* Transfer progress overlay */
static uint8_t g_transfer_active;
static uint8_t g_transfer_is_move;
static uint8_t g_transfer_is_dir;
static uint64_t g_transfer_total;
static uint64_t g_transfer_done;
static uint32_t g_transfer_file_count;
static CHAR16 g_transfer_src_name[96];
static CHAR16 g_transfer_dst_vol[32];
/* File/folder create dialog */
static uint8_t g_create_open;
static uint8_t g_create_is_dir;   /* 1 = create directory */
static uint32_t g_create_win_idx;
static CHAR16 g_create_name[96];
/* Confirm dialog */
#define CONFIRM_DELETE 1
#define CONFIRM_COPY   2
#define CONFIRM_MOVE   3
static uint8_t g_confirm_open;
static uint8_t g_confirm_action;
static CHAR16 g_confirm_msg[128];
/* Pending operation parameters (used by confirm flow) */
static uint32_t g_pending_src_win;
static uint32_t g_pending_dst_win;
static uint32_t g_pending_src_vol;
static uint32_t g_pending_dst_vol;
static CHAR16 g_pending_src_path[256];
static CHAR16 g_pending_dst_path[256];
static uint8_t g_pending_is_dir;
/* Rename dialog */
static uint8_t  g_rename_open;
static uint32_t g_rename_win_idx;
static CHAR16   g_rename_name[96];      /* new name input */
static CHAR16   g_rename_old_path[256]; /* full old path */
static uint32_t g_rename_vol;           /* volume for rename */
/* Context menu (right-click) */
static uint8_t  g_ctx_open;
static int      g_ctx_x, g_ctx_y;       /* screen position */
static uint32_t g_ctx_win;              /* explorer window index */
static uint32_t g_ctx_entry;            /* entry index in window */
/* File entry context menu items */
#define CTX_RENAME 0
#define CTX_COPY   1
#define CTX_MOVE   2
#define CTX_DELETE 3
#define CTX_ITEM_COUNT 4
/* Background (empty-area) context menu items */
#define CTX_BG_NEW_FILE   0
#define CTX_BG_NEW_FOLDER 1
#define CTX_BG_ITEM_COUNT 2
static uint8_t g_ctx_mode;             /* 0=file menu, 1=background menu */
static uint8_t g_mouse_right_click;     /* right-click event flag */
static uint8_t g_ctx_hover;            /* hovered item index */
static uint8_t g_storage_refresh_needed;
static uint8_t g_fs_refresh_needed;
static EFI_HANDLE g_fs_driver_handles[64];
static uint32_t g_fs_driver_handle_count;
static uint8_t g_external_fs_drivers_loaded;
static char g_last_error[96];

/* ============================================================================
 * CYX runtime state — tiny built-in script app system (.cyx files)
 * ============================================================================ */
#define CYX_MAX_SRC          16384
#define CYX_MAX_LINES        512
#define CYX_MAX_TOKENS       8
#define CYX_TOK_LEN          80
#define CYX_MAX_VARS         48
#define CYX_VAR_NAME_LEN     16
#define CYX_VAR_STR_LEN      64
#define CYX_MAX_HANDLERS     48
#define CYX_MAX_LABELS_GOTO  96
#define CYX_MAX_BUTTONS      24
#define CYX_MAX_LABELS       24
#define CYX_MAX_INPUTS       6
#define CYX_MAX_OPS          1024

#define CYX_EV_START 0
#define CYX_EV_CLICK 1
#define CYX_EV_KEY   2
#define CYX_EV_DRAG  3
#define CYX_EV_MOVE  4
#define CYX_EV_TICK  5

#define CYX_OP_PIXEL    1
#define CYX_OP_LINE     2
#define CYX_OP_RECT     3
#define CYX_OP_FILLRECT 4
#define CYX_OP_TEXT     5
#define CYX_OP_FILL     6

typedef struct {
    uint8_t  op;
    uint8_t  text_len;
    int16_t  a, b, c, d;
    uint32_t color;
    char     text[16];
} cyx_op_t;

typedef struct {
    char    name[CYX_VAR_NAME_LEN];
    int32_t ival;
    char    sval[CYX_VAR_STR_LEN];
    uint8_t is_string;
    uint8_t used;
} cyx_var_t;

typedef struct {
    uint8_t  type;
    char     target[16];
    uint16_t start_line;
    uint16_t end_line;
} cyx_handler_t;

typedef struct {
    char     name[16];
    uint16_t line;
} cyx_lblpos_t;

typedef struct {
    char     id[16];
    int16_t  x, y, w, h;
    char     text[40];
} cyx_btn_t;

typedef struct {
    char     id[16];
    int16_t  x, y;
    uint32_t color;
    char     text[64];
} cyx_lab_t;

typedef struct {
    char     id[16];
    int16_t  x, y, w, h;
    char     text[64];
    uint16_t cursor;
    uint8_t  focused;
} cyx_inp_t;

static char     g_cyx_src[CYX_MAX_SRC];
static uint32_t g_cyx_src_len;
static uint16_t g_cyx_line_off[CYX_MAX_LINES];
static uint16_t g_cyx_line_count;
static cyx_handler_t g_cyx_handlers[CYX_MAX_HANDLERS];
static uint16_t g_cyx_handler_count;
static cyx_lblpos_t g_cyx_labels[CYX_MAX_LABELS_GOTO];
static uint16_t g_cyx_label_count;

static uint8_t  g_cyx_running;
static int16_t  g_cyx_win_x, g_cyx_win_y;
static int16_t  g_cyx_canvas_w, g_cyx_canvas_h;
static char     g_cyx_title[48];
static char     g_cyx_status[96];

static uint32_t g_cyx_src_vol;
static CHAR16   g_cyx_src_path[256];
static CHAR16   g_cyx_src_name[64];

static cyx_op_t g_cyx_ops[CYX_MAX_OPS];
static uint16_t g_cyx_op_count;

static cyx_var_t g_cyx_vars[CYX_MAX_VARS];

static cyx_btn_t g_cyx_btns[CYX_MAX_BUTTONS];
static uint16_t g_cyx_btn_count;
static cyx_lab_t g_cyx_labs[CYX_MAX_LABELS];
static uint16_t g_cyx_lab_count;
static cyx_inp_t g_cyx_inps[CYX_MAX_INPUTS];
static uint16_t g_cyx_inp_count;

static int16_t  g_cyx_mx, g_cyx_my;
static int16_t  g_cyx_prev_mx, g_cyx_prev_my;
static uint8_t  g_cyx_have_prev;
static uint8_t  g_cyx_mouse_in_canvas;
static uint8_t  g_cyx_left_was_down;
static char     g_cyx_last_key[16];
static char     g_cyx_last_click_btn[16];
static int32_t  g_cyx_tick;
static uint32_t g_cyx_last_tick_at;
static uint16_t g_cyx_jump_target;
static uint8_t  g_cyx_did_goto;
static uint8_t  g_cyx_did_exit;
static uint8_t  g_cyx_has_error;
static char     g_cyx_error[96];
static int32_t  g_cyx_error_line;

static uint8_t  g_cyx_choose_open;
static uint32_t g_cyx_choose_vol;
static CHAR16   g_cyx_choose_path[256];
static CHAR16   g_cyx_choose_name[64];
static uint8_t  g_cyx_choose_hover;

static char g_cpu_vendor[13];
static uint32_t g_cpu_sig;
static uint32_t g_cpu_ecx;
static uint32_t g_cpu_edx;
static CHAR16 g_firmware[64];
/* Extended hardware info */
static char g_cpu_brand[49];       /* CPUID 0x80000002-4 */
static uint32_t g_cpu_cores;       /* physical cores (CPUID 0x4) */
static uint32_t g_cpu_threads;     /* logical threads (CPUID 1 EBX[23:16]) */
static uint32_t g_cpu_max_leaf;    /* max standard CPUID leaf */
static uint32_t g_cpu_max_ext;     /* max extended CPUID leaf */
static uint8_t  g_secure_boot;     /* 0=off/unknown, 1=on, 2=setup mode */
static uint32_t g_uefi_rev;        /* g_st->FirmwareRevision */
static uint32_t g_gop_modes;       /* total GOP display modes */
static uint32_t g_gop_cur_mode;    /* current GOP mode index */
static uint32_t g_acpi_present;    /* 1 if ACPI config table found */
static uint32_t g_memory_conv_mb;  /* conventional (available) RAM in MB */
static uint32_t g_memory_types[16]; /* page counts per EFI memory type */
static uint32_t g_cpu_apic;
static uint32_t g_cpu_has_ht;
static uint32_t g_cpu_has_aes;
static uint32_t g_cpu_has_avx;
static uint32_t g_cpu_has_sse4;
static uint32_t g_cpu_has_vt;      /* VMX / SVM */
static uint32_t g_cpu_has_nx;      /* NX/XD bit */
static uint32_t g_cpu_has_rdrand;
static uint32_t g_cpu_cache_kb;    /* L2 cache size in KB (CPUID 0x80000006) */
static uint32_t g_real_vol_count;  /* volumes on detected physical disks only */

/* GPU / display adapter info */
#define MAX_GPU_ADAPTERS 4
typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t stride;
    uint32_t pixel_format;
    uint32_t max_modes;
    uint32_t cur_mode;
    uint8_t  has_edid;
    char     mfr_id[4];      /* 3-letter EDID manufacturer ID */
    uint16_t product_code;
    uint16_t mfr_year;
    char     monitor_name[14]; /* descriptor block name */
} gpu_info_t;

static gpu_info_t g_gpus[MAX_GPU_ADAPTERS];
static uint32_t   g_gpu_count;

static const EFI_GUID GopGuid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
static const EFI_GUID PointerGuid = {0x31878c87, 0x0b75, 0x11d5, {0x9a, 0x4f, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
static const EFI_GUID AbsolutePointerGuid = {0x8d59d32b, 0xc655, 0x4ae9, {0x9b, 0x15, 0xf2, 0x59, 0x04, 0x99, 0x2a, 0x43}};
static const EFI_GUID BlockIoGuid = {0x964e5b21, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
static const EFI_GUID DiskIoGuid = {0xce345171, 0xba0b, 0x11d2, {0x8e, 0x4f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
static const EFI_GUID SimpleFileSystemGuid = {0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
static const EFI_GUID FileInfoGuid = {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
static const EFI_GUID DevicePathGuid = {0x09576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
static const EFI_GUID DriverBindingGuid = {0x18a031ab, 0xb443, 0x4d1a, {0xa5, 0xc0, 0x0c, 0x09, 0x26, 0x1e, 0x9f, 0x71}};

static int content_x(void);
static int content_y(void);

static const glyph_t Font[] = {
    {' ', {0, 0, 0, 0, 0, 0, 0}},
    {'.', {0, 0, 0, 0, 0, 6, 6}},
    {',', {0, 0, 0, 0, 0, 4, 8}},
    {':', {0, 4, 4, 0, 4, 4, 0}},
    {'-', {0, 0, 0, 31, 0, 0, 0}},
    {'_', {0, 0, 0, 0, 0, 0, 31}},
    {'/', {1, 2, 2, 4, 8, 8, 16}},
    {'\\', {16, 8, 8, 4, 2, 2, 1}},
    {'+', {0, 4, 4, 31, 4, 4, 0}},
    {'=', {0, 0, 31, 0, 31, 0, 0}},
    {'<', {1, 2, 4, 8, 4, 2, 1}},
    {'>', {16, 8, 4, 2, 4, 8, 16}},
    {'#', {10, 31, 10, 10, 31, 10, 0}},
    {'*', {0, 21, 14, 31, 14, 21, 0}},
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
    /* Lowercase a-z */
    {'a', {0, 0, 14, 1, 15, 17, 15}},
    {'b', {16, 16, 16, 30, 17, 17, 30}},
    {'c', {0, 0, 14, 16, 16, 16, 14}},
    {'d', {1, 1, 15, 17, 17, 17, 15}},
    {'e', {0, 0, 14, 17, 31, 16, 14}},
    {'f', {7, 8, 8, 30, 8, 8, 8}},
    {'g', {0, 0, 14, 17, 17, 15, 14}},
    {'h', {16, 16, 30, 18, 18, 18, 18}},
    {'i', {4, 0, 12, 4, 4, 4, 14}},
    {'j', {2, 0, 3, 1, 1, 17, 14}},
    {'k', {16, 16, 18, 20, 24, 20, 18}},
    {'l', {12, 4, 4, 4, 4, 4, 14}},
    {'m', {0, 0, 27, 21, 21, 21, 21}},
    {'n', {0, 0, 30, 18, 18, 18, 18}},
    {'o', {0, 0, 14, 17, 17, 17, 14}},
    {'p', {0, 0, 30, 17, 30, 16, 16}},
    {'q', {0, 0, 15, 17, 15, 1, 1}},
    {'r', {0, 0, 14, 24, 16, 16, 16}},
    {'s', {0, 0, 15, 16, 14, 1, 30}},
    {'t', {8, 8, 30, 8, 8, 8, 6}},
    {'u', {0, 0, 17, 17, 17, 17, 14}},
    {'v', {0, 0, 17, 17, 17, 10, 4}},
    {'w', {0, 0, 17, 17, 21, 21, 10}},
    {'x', {0, 0, 17, 10, 4, 10, 17}},
    {'y', {0, 17, 17, 17, 15, 1, 14}},
    {'z', {0, 0, 31, 2, 4, 8, 31}},
    {0x00C7, {14, 17, 16, 16, 17, 14, 4}},
    {0x00D6, {10, 0, 14, 17, 17, 17, 14}},
    {0x00DC, {10, 0, 17, 17, 17, 17, 14}},
    {0x011E, {4, 0, 14, 16, 23, 17, 15}},
    {0x0130, {4, 0, 14, 4, 4, 4, 14}},
    {0x015E, {15, 16, 14, 1, 30, 4, 8}},
    {0x00E7, {0, 14, 16, 16, 17, 14, 4}},
    {0x00F6, {10, 0, 14, 17, 17, 17, 14}},
    {0x00FC, {10, 0, 17, 17, 17, 17, 14}},
    {0x011F, {4, 0, 14, 16, 23, 17, 15}},
    {0x0131, {0, 0, 12, 4, 4, 4, 14}},
    {0x015F, {0, 15, 16, 14, 1, 30, 4}},
};

static const uint8_t *glyph_rows(uint16_t c)
{
    for (uint32_t i = 0; i < sizeof(Font) / sizeof(Font[0]); i++) {
        if (Font[i].ch == c) {
            return Font[i].row;
        }
    }
    return Font[0].row;
}

static uint16_t utf8_next(const char **text)
{
    const uint8_t *s = (const uint8_t *)*text;
    uint16_t cp = *s++;
    if (cp >= 0xC2 && cp <= 0xDF && *s) {
        cp = (uint16_t)(((cp & 0x1F) << 6) | (*s++ & 0x3F));
    } else if (cp >= 0xE0 && cp <= 0xEF && s[0] && s[1]) {
        cp = (uint16_t)(((cp & 0x0F) << 12) | ((s[0] & 0x3F) << 6) | (s[1] & 0x3F));
        s += 2;
    }
    *text = (const char *)s;
    return cp;
}

static void cpuid_call(uint32_t leaf, uint32_t subleaf, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
    __asm__ volatile ("cpuid" : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d) : "a"(leaf), "c"(subleaf));
}

static void detect_cpu(void)
{
    uint32_t a, b, c, d;
    cpuid_call(0, 0, &a, &b, &c, &d);
    *((uint32_t *)&g_cpu_vendor[0]) = b;
    *((uint32_t *)&g_cpu_vendor[4]) = d;
    *((uint32_t *)&g_cpu_vendor[8]) = c;
    g_cpu_vendor[12] = 0;
    g_cpu_max_leaf = a;
    cpuid_call(1, 0, &a, &b, &c, &d);
    g_cpu_sig = a;
    g_cpu_ecx = c;
    g_cpu_edx = d;
    g_cpu_threads = (b >> 16) & 0xFF;
    if (g_cpu_threads == 0) g_cpu_threads = 1;
    g_cpu_apic    = (d >> 9)  & 1;
    g_cpu_has_ht  = (d >> 28) & 1;
    g_cpu_has_aes = (c >> 25) & 1;
    g_cpu_has_avx = (c >> 28) & 1;
    g_cpu_has_sse4= (c >> 19) & 1;  /* SSE4.1 */
    g_cpu_has_vt  = (c >> 5)  & 1;  /* VMX */
    g_cpu_has_rdrand = (c >> 30) & 1;
}

/* EFI_EDID_ACTIVE_PROTOCOL GUID */
static const EFI_GUID EdidActiveGuid = {0xbd8c1056, 0x9f36, 0x44ec,
    {0x92, 0xa8, 0xa6, 0x33, 0x7f, 0x81, 0x79, 0x86}};

typedef struct {
    uint32_t SizeOfEdid;
    uint8_t *Edid;
} EFI_EDID_ACTIVE_PROTOCOL;

/* Decode 3-letter EDID manufacturer ID from bytes 8-9 (big-endian packed) */
static void edid_mfr_id(const uint8_t *e, char *out)
{
    uint16_t v = (uint16_t)((e[8] << 8) | e[9]);
    out[0] = (char)(((v >> 10) & 0x1F) + 'A' - 1);
    out[1] = (char)(((v >>  5) & 0x1F) + 'A' - 1);
    out[2] = (char)(( v        & 0x1F) + 'A' - 1);
    out[3] = 0;
}

/* Extract monitor name from EDID descriptor blocks (bytes 54..125) */
static void edid_monitor_name(const uint8_t *e, char *out, uint32_t max)
{
    if (!max) return;
    out[0] = 0;
    /* Each descriptor block: 18 bytes starting at offset 54 */
    for (uint32_t d = 0; d < 4; d++) {
        const uint8_t *desc = e + 54 + d * 18;
        /* Pixel clock = 0 and tag = 0xFC → monitor name */
        if (desc[0] == 0 && desc[1] == 0 && desc[2] == 0 && desc[3] == 0xFC) {
            uint32_t i = 0;
            for (uint32_t j = 5; j < 18 && i < max - 1; j++) {
                char ch = (char)desc[j];
                if (ch == '\n' || ch == '\r') break;
                out[i++] = ch;
            }
            out[i] = 0;
            return;
        }
    }
}

static void detect_gpu(void)
{
    g_gpu_count = 0;

    /* Enumerate all handles that support GOP */
    UINTN handle_count = 0;
    EFI_HANDLE *handles = 0;
    EFI_STATUS st = g_bs->LocateHandleBuffer(BY_PROTOCOL,
        (EFI_GUID *)&GopGuid, 0, &handle_count, &handles);
    if (st != EFI_SUCCESS || !handles) {
        /* Fallback: use the already-located g_gop */
        if (g_gop && g_gop->Mode && g_gop->Mode->Info) {
            gpu_info_t *gi = &g_gpus[0];
            gi->width        = g_gop->Mode->Info->HorizontalResolution;
            gi->height       = g_gop->Mode->Info->VerticalResolution;
            gi->stride       = g_gop->Mode->Info->PixelsPerScanLine;
            gi->pixel_format = g_gop->Mode->Info->PixelFormat;
            gi->max_modes    = g_gop->Mode->MaxMode;
            gi->cur_mode     = g_gop->Mode->Mode;
            g_gpu_count = 1;
        }
        return;
    }

    for (UINTN i = 0; i < handle_count && g_gpu_count < MAX_GPU_ADAPTERS; i++) {
        EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = 0;
        if (g_bs->OpenProtocol(handles[i], (EFI_GUID *)&GopGuid,
                (void **)&gop, g_image, 0,
                EFI_OPEN_PROTOCOL_GET_PROTOCOL) != EFI_SUCCESS || !gop || !gop->Mode) {
            continue;
        }
        gpu_info_t *gi = &g_gpus[g_gpu_count];
        gi->width        = gop->Mode->Info ? gop->Mode->Info->HorizontalResolution : 0;
        gi->height       = gop->Mode->Info ? gop->Mode->Info->VerticalResolution   : 0;
        gi->stride       = gop->Mode->Info ? gop->Mode->Info->PixelsPerScanLine    : 0;
        gi->pixel_format = gop->Mode->Info ? gop->Mode->Info->PixelFormat          : 0;
        gi->max_modes    = gop->Mode->MaxMode;
        gi->cur_mode     = gop->Mode->Mode;

        /* Try EDID active protocol on same handle */
        EFI_EDID_ACTIVE_PROTOCOL *edid = 0;
        if (g_bs->OpenProtocol(handles[i], (EFI_GUID *)&EdidActiveGuid,
                (void **)&edid, g_image, 0,
                EFI_OPEN_PROTOCOL_GET_PROTOCOL) == EFI_SUCCESS
            && edid && edid->SizeOfEdid >= 128 && edid->Edid) {
            gi->has_edid    = 1;
            edid_mfr_id(edid->Edid, gi->mfr_id);
            gi->product_code = (uint16_t)(edid->Edid[8] | (edid->Edid[9] << 8));
            gi->mfr_year     = (uint16_t)(1990 + edid->Edid[17]);
            edid_monitor_name(edid->Edid, gi->monitor_name, sizeof(gi->monitor_name));
        }

        g_gpu_count++;
    }
    g_bs->FreePool(handles);

    /* If no GOP found via enumeration, still use primary */
    if (g_gpu_count == 0 && g_gop && g_gop->Mode) {
        g_gpus[0].width     = g_gop->Mode->Info ? g_gop->Mode->Info->HorizontalResolution : 0;
        g_gpus[0].height    = g_gop->Mode->Info ? g_gop->Mode->Info->VerticalResolution   : 0;
        g_gpus[0].max_modes = g_gop->Mode->MaxMode;
        g_gpus[0].cur_mode  = g_gop->Mode->Mode;
        g_gpu_count = 1;
    }
}

static void detect_hw_extended(void)
{
    uint32_t a, b, c, d;

    /* CPU brand string (CPUID 0x80000002..4) */
    cpuid_call(0x80000000, 0, &a, &b, &c, &d);
    g_cpu_max_ext = a;
    if (a >= 0x80000004) {
        uint32_t *p = (uint32_t *)g_cpu_brand;
        cpuid_call(0x80000002, 0, &p[0], &p[1], &p[2], &p[3]);
        cpuid_call(0x80000003, 0, &p[4], &p[5], &p[6], &p[7]);
        cpuid_call(0x80000004, 0, &p[8], &p[9], &p[10], &p[11]);
        g_cpu_brand[48] = 0;
        /* Trim leading spaces */
        char *s = g_cpu_brand;
        while (*s == ' ') s++;
        if (s != g_cpu_brand) {
            uint32_t i = 0;
            while (s[i]) { g_cpu_brand[i] = s[i]; i++; }
            g_cpu_brand[i] = 0;
        }
    } else {
        /* Fallback: copy vendor */
        uint32_t i = 0;
        while (g_cpu_vendor[i] && i < 48) { g_cpu_brand[i] = g_cpu_vendor[i]; i++; }
        g_cpu_brand[i] = 0;
    }

    /* NX bit (CPUID 0x80000001 EDX bit 20) */
    if (g_cpu_max_ext >= 0x80000001) {
        cpuid_call(0x80000001, 0, &a, &b, &c, &d);
        g_cpu_has_nx = (d >> 20) & 1;
        /* SVM (AMD VT) */
        if (!g_cpu_has_vt) {
            g_cpu_has_vt = (c >> 2) & 1;
        }
    }

    /* L2 cache (CPUID 0x80000006) */
    if (g_cpu_max_ext >= 0x80000006) {
        cpuid_call(0x80000006, 0, &a, &b, &c, &d);
        g_cpu_cache_kb = (c >> 16) & 0xFFFF;
    }

    /* Physical cores via CPUID leaf 4 */
    if (g_cpu_max_leaf >= 4) {
        cpuid_call(4, 0, &a, &b, &c, &d);
        g_cpu_cores = ((a >> 26) & 0x3F) + 1;
    } else {
        g_cpu_cores = g_cpu_has_ht ? g_cpu_threads / 2 : g_cpu_threads;
        if (!g_cpu_cores) g_cpu_cores = 1;
    }

    /* Secure Boot via UEFI GetVariable */
    g_secure_boot = 0;
    static const EFI_GUID GlobalVarGuid = {0x8be4df61, 0x93ca, 0x11d2,
        {0xaa, 0x0d, 0x00, 0xe0, 0x98, 0x03, 0x2b, 0x8c}};
    if (g_st->RuntimeServices && g_st->RuntimeServices->GetVariable) {
        CHAR16 sb_name[] = {L'S',L'e',L'c',L'u',L'r',L'e',L'B',L'o',L'o',L't',0};
        uint8_t sb_val = 0;
        UINTN sb_sz = 1;
        uint32_t sb_attr = 0;
        EFI_STATUS st = g_st->RuntimeServices->GetVariable(
            sb_name, (EFI_GUID *)&GlobalVarGuid, &sb_attr, &sb_sz, &sb_val);
        if (st == EFI_SUCCESS) {
            g_secure_boot = sb_val ? 1 : 2; /* 1=enabled, 2=setup/disabled */
        }
        /* SetupMode */
        CHAR16 sm_name[] = {L'S',L'e',L't',L'u',L'p',L'M',L'o',L'd',L'e',0};
        uint8_t sm_val = 0;
        UINTN sm_sz = 1;
        uint32_t sm_attr2 = 0;
        if (g_st->RuntimeServices->GetVariable(
            sm_name, (EFI_GUID *)&GlobalVarGuid, &sm_attr2, &sm_sz, &sm_val) == EFI_SUCCESS) {
            if (sm_val) g_secure_boot = 3; /* setup mode */
        }
    }

    /* UEFI firmware revision */
    g_uefi_rev = g_st->FirmwareRevision;

    /* ACPI table presence (look for ACPI 2.0 or 1.0 GUIDs in config table) */
    static const EFI_GUID Acpi2Guid = {0x8868e871, 0xe4f1, 0x11d3,
        {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
    static const EFI_GUID Acpi1Guid = {0xeb9d2d30, 0x2d88, 0x11d3,
        {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
    g_acpi_present = 0;
    if (g_st->ConfigurationTable && g_st->NumberOfTableEntries) {
        typedef struct { EFI_GUID Guid; void *Table; } EFI_CONFIG_TABLE;
        EFI_CONFIG_TABLE *ct = (EFI_CONFIG_TABLE *)g_st->ConfigurationTable;
        for (UINTN i = 0; i < g_st->NumberOfTableEntries; i++) {
            EFI_GUID *g = &ct[i].Guid;
            if ((g->Data1 == Acpi2Guid.Data1 && g->Data2 == Acpi2Guid.Data2) ||
                (g->Data1 == Acpi1Guid.Data1 && g->Data2 == Acpi1Guid.Data2)) {
                g_acpi_present = 1;
                break;
            }
        }
    }

    /* GOP mode count */
    if (g_gop && g_gop->Mode) {
        g_gop_modes    = g_gop->Mode->MaxMode;
        g_gop_cur_mode = g_gop->Mode->Mode;
    }

    /* Memory type breakdown */
    {
        UINTN map_size = 0, key = 0, desc_size = 0;
        uint32_t desc_ver = 0;
        void *map = 0;
        g_bs->GetMemoryMap(&map_size, map, &key, &desc_size, &desc_ver);
        map_size += desc_size * 16;
        if (map_size && g_bs->AllocatePool(EfiLoaderData, map_size, &map) == EFI_SUCCESS) {
            if (g_bs->GetMemoryMap(&map_size, map, &key, &desc_size, &desc_ver) == EFI_SUCCESS
                && desc_size >= sizeof(EFI_MEMORY_DESCRIPTOR)) {
                uint8_t *p = (uint8_t *)map;
                uint64_t conv_pages = 0;
                for (UINTN off = 0; off + desc_size <= map_size; off += desc_size) {
                    EFI_MEMORY_DESCRIPTOR *md = (EFI_MEMORY_DESCRIPTOR *)(p + off);
                    if (md->Type < 16) g_memory_types[md->Type] += (uint32_t)md->NumberOfPages;
                    if (md->Type == 7) conv_pages += md->NumberOfPages; /* EfiConventionalMemory */
                }
                g_memory_conv_mb = (uint32_t)((conv_pages * 4096ULL) / (1024ULL * 1024ULL));
            }
            g_bs->FreePool(map);
        }
    }
}

static void u64_to_dec(uint64_t value, char *out)
{
    char tmp[24];
    uint32_t i = 0;
    uint32_t j = 0;
    if (value == 0) {
        out[0] = '0';
        out[1] = 0;
        return;
    }
    while (value && i < sizeof(tmp)) {
        tmp[i++] = (char)('0' + (value % 10));
        value /= 10;
    }
    while (i) {
        out[j++] = tmp[--i];
    }
    out[j] = 0;
}

static uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
    if (g_pixel_format == 0) {
        return (uint32_t)r | ((uint32_t)g << 8) | ((uint32_t)b << 16);
    }
    if (g_pixel_format == 1) {
        return (uint32_t)b | ((uint32_t)g << 8) | ((uint32_t)r << 16);
    }
    if (g_pixel_format == 2 && g_red_mask && g_green_mask && g_blue_mask) {
        uint32_t pixel = 0;
        uint32_t masks[3] = {g_red_mask, g_green_mask, g_blue_mask};
        uint8_t values[3] = {r, g, b};
        for (int i = 0; i < 3; i++) {
            uint32_t mask = masks[i];
            uint32_t shift = 0;
            uint32_t width = 0;
            while (shift < 32 && ((mask >> shift) & 1U) == 0) {
                shift++;
            }
            while (shift + width < 32 && ((mask >> (shift + width)) & 1U)) {
                width++;
            }
            if (width) {
                uint32_t maxv = (1U << width) - 1U;
                pixel |= (((uint32_t)values[i] * maxv + 127U) / 255U) << shift;
            }
        }
        return pixel;
    }
    return (uint32_t)b | ((uint32_t)g << 8) | ((uint32_t)r << 16);
}

static void put_pixel(int x, int y, uint32_t color)
{
    if (!g_backbuffer || x < 0 || y < 0 || (uint32_t)x >= g_w || (uint32_t)y >= g_h) {
        return;
    }
    g_backbuffer[(uint32_t)y * g_w + (uint32_t)x] = color;
}

static void fill_rect(int x, int y, int w, int h, uint32_t color)
{
    if (x < 0) {
        w += x;
        x = 0;
    }
    if (y < 0) {
        h += y;
        y = 0;
    }
    if ((uint32_t)(x + w) > g_w) {
        w = (int)g_w - x;
    }
    if ((uint32_t)(y + h) > g_h) {
        h = (int)g_h - y;
    }
    if (w <= 0 || h <= 0) {
        return;
    }
    for (int yy = 0; yy < h; yy++) {
        for (int xx = 0; xx < w; xx++) {
            g_backbuffer[(uint32_t)(y + yy) * g_w + (uint32_t)(x + xx)] = color;
        }
    }
}

static void draw_rect(int x, int y, int w, int h, uint32_t color)
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

static uint32_t ui_scale(void)
{
    uint32_t sx = g_w / 640;
    uint32_t sy = g_h / 400;
    uint32_t s = sx < sy ? sx : sy;
    if (s < 1) {
        s = 1;
    }
    if (s > 3) {
        s = 3;
    }
    return s;
}

static void draw_char_cp(int x, int y, uint16_t c, uint32_t color, uint32_t scale)
{
    const uint8_t *rows = glyph_rows(c);
    for (uint32_t yy = 0; yy < 7; yy++) {
        for (uint32_t xx = 0; xx < 5; xx++) {
            if (rows[yy] & (1 << (4 - xx))) {
                fill_rect(x + (int)(xx * scale), y + (int)(yy * scale), (int)scale, (int)scale, color);
            }
        }
    }
}

static void draw_text(int x, int y, const char *text, uint32_t color)
{
    uint32_t scale = ui_scale();
    int start = x;
    while (*text) {
        uint16_t cp = utf8_next(&text);
        if (cp == '\n') {
            y += (int)(9 * scale);
            x = start;
        } else {
            draw_char_cp(x, y, cp, color, scale);
            x += (int)(6 * scale);
        }
    }
}

static void draw_text_scale(int x, int y, const char *text, uint32_t color, uint32_t scale)
{
    int start = x;
    while (*text) {
        uint16_t cp = utf8_next(&text);
        if (cp == '\n') {
            y += (int)(9 * scale);
            x = start;
        } else {
            draw_char_cp(x, y, cp, color, scale);
            x += (int)(6 * scale);
        }
    }
}

static void draw_text16_limited(int x, int y, const CHAR16 *text, uint32_t color, uint32_t max_chars)
{
    uint32_t scale = ui_scale();
    uint32_t i = 0;
    while (text && text[i] && i < max_chars) {
        draw_char_cp(x, y, text[i], color, scale);
        x += (int)(6 * scale);
        i++;
    }
}

/* ASCII draw with max_chars clipping (prevents overflow out of window bounds) */
static void draw_text_n(int x, int y, const char *text, uint32_t color, uint32_t max_chars)
{
    uint32_t scale = ui_scale();
    uint32_t i = 0;
    while (*text && i < max_chars) {
        uint16_t cp = utf8_next(&text);
        if (cp == '\n') break;
        draw_char_cp(x, y, cp, color, scale);
        x += (int)(6 * scale);
        i++;
    }
}

static CY_UNUSED void draw_text_area(int x, int y, int w, int h, const char *text, uint32_t color)
{
    uint32_t scale = ui_scale();
    int char_w = (int)(6 * scale);
    int line_h = (int)(9 * scale);
    int start_x = x;
    int bottom = y + h;
    int max_cols = char_w ? w / char_w : 0;
    int col = 0;
    if (max_cols < 1) {
        return;
    }
    while (text && *text && y + line_h <= bottom) {
        uint16_t cp = utf8_next(&text);
        if (cp == '\n') {
            y += line_h;
            x = start_x;
            col = 0;
            continue;
        }
        if (col >= max_cols) {
            y += line_h;
            x = start_x;
            col = 0;
            if (y + line_h > bottom) {
                break;
            }
        }
        draw_char_cp(x, y, cp, color, scale);
        x += char_w;
        col++;
    }
}

static uint32_t c16_len(const CHAR16 *s)
{
    uint32_t n = 0;
    while (s && s[n]) {
        n++;
    }
    return n;
}

static void ascii_copy(char *dst, const char *src, uint32_t max)
{
    uint32_t i = 0;
    if (!max) {
        return;
    }
    while (src && src[i] && i + 1 < max) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0;
}

static uint32_t ascii_len(const char *s)
{
    uint32_t n = 0;
    while (s && s[n]) {
        n++;
    }
    return n;
}

static int ascii_eq(const char *a, const char *b)
{
    uint32_t i = 0;
    while (a && b && a[i] && b[i]) {
        char ca = a[i];
        char cb = b[i];
        if (ca >= 'A' && ca <= 'Z') {
            ca = (char)(ca + 32);
        }
        if (cb >= 'A' && cb <= 'Z') {
            cb = (char)(cb + 32);
        }
        if (ca != cb) {
            return 0;
        }
        i++;
    }
    return a && b && a[i] == b[i];
}

static int memeq_ascii(const uint8_t *buf, uint32_t off, const char *text, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        if (buf[off + i] != (uint8_t)text[i]) {
            return 0;
        }
    }
    return 1;
}

static void set_last_error(const char *text)
{
    ascii_copy(g_last_error, text, sizeof(g_last_error));
}

#define EFI_RESET_COLD 0
#define EFI_RESET_WARM 1
#define EFI_RESET_SHUTDOWN 2

static void native_flush_volume(uint32_t volume);
static void ntfs_invalidate_logfile(uint32_t volume);
static void ntfs_clear_volume_dirty(uint32_t volume);
static void ntfs_set_volume_dirty(uint32_t volume);
static void ntfs_begin_modify(uint32_t volume);
static uint64_t efi_time_to_ntfs_time(const EFI_TIME *t);
static void ntfs_time_to_efi_time(uint64_t ntfs, EFI_TIME *out);
static uint64_t ntfs_time_now(void);

static int system_reset(uint32_t type)
{
    for (uint32_t i = 0; i < g_volume_count; i++) {
        native_flush_volume(i);
    }
    if (g_st && g_st->RuntimeServices && g_st->RuntimeServices->ResetSystem) {
        g_st->RuntimeServices->ResetSystem(type, EFI_SUCCESS, 0, 0);
    }
    return 0;
}

/* Forward declaration — render() is defined later but called from copy loop */
static void render(void);
/* Forward declarations for the CYX runtime (defined just before render) */
static int cyx_name_has_ext(const CHAR16 *name);
static void cyx_open_chooser(uint32_t vol, const CHAR16 *path, const CHAR16 *name);
static void draw_cyx_app_window(void);
static void draw_cyx_chooser_dialog(void);
static int cyx_chooser_handle_key(EFI_INPUT_KEY *k);
static int cyx_chooser_handle_click(void);
static int cyx_app_handle_key(EFI_INPUT_KEY *k);
static int cyx_app_handle_click(void);
static void cyx_per_frame(void);
/* Forward declaration — defined after copy_selected_to_other */
static void c16_to_confirm_msg(CHAR16 *dst, uint32_t max, const CHAR16 *name, const CHAR16 *action);
/* Forward declarations for functions called before definition */
static void set_active_window(uint32_t index);
static void copy_selected_to_other(uint8_t move_after_copy);
static void delete_selected(void);
static void open_create_dialog_impl(uint32_t win_idx, uint8_t is_dir);
static void open_create_folder_dialog(void);

static void c16_copy(CHAR16 *dst, const CHAR16 *src, uint32_t max)
{
    uint32_t i = 0;
    if (!max) {
        return;
    }
    while (src && src[i] && i + 1 < max) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0;
}

static void c16_append(CHAR16 *dst, const CHAR16 *src, uint32_t max)
{
    uint32_t i = c16_len(dst);
    if (!max || i >= max) {
        return;
    }
    for (uint32_t j = 0; src && src[j] && i + 1 < max; j++) {
        dst[i++] = src[j];
    }
    dst[i] = 0;
}

static void c16_append_char(CHAR16 *dst, CHAR16 ch, uint32_t max)
{
    uint32_t i = c16_len(dst);
    if (i + 1 < max) {
        dst[i++] = ch;
        dst[i] = 0;
    }
}

static int c16_equal(const CHAR16 *a, const CHAR16 *b)
{
    uint32_t i = 0;
    while (a && b && a[i] && b[i]) {
        if (a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    return a && b && a[i] == b[i];
}

static int c16_is_dotdot(const CHAR16 *s)
{
    return s && s[0] == L'.' && s[1] == L'.' && s[2] == 0;
}

static void c16_from_ascii(CHAR16 *dst, const char *src, uint32_t max)
{
    uint32_t i = 0;
    if (!max) {
        return;
    }
    while (src && src[i] && i + 1 < max) {
        dst[i] = (CHAR16)(uint8_t)src[i];
        i++;
    }
    dst[i] = 0;
}

static void c16_to_ascii(char *dst, const CHAR16 *src, uint32_t max)
{
    uint32_t i = 0;
    if (!max) {
        return;
    }
    while (src && src[i] && i + 1 < max) {
        CHAR16 c = src[i];
        dst[i] = (c >= 32 && c < 127) ? (char)c : '?';
        i++;
    }
    dst[i] = 0;
}

static void c16_join_path(CHAR16 *out, uint32_t max, const CHAR16 *path, const CHAR16 *name)
{
    uint32_t p = 0;
    if (!max) {
        return;
    }
    if (path && path[0]) {
        while (path[p] && p + 1 < max) {
            out[p] = path[p];
            p++;
        }
    }
    if (p && out[p - 1] != L'\\' && p + 1 < max) {
        out[p++] = L'\\';
    }
    for (uint32_t i = 0; name && name[i] && p + 1 < max; i++) {
        out[p++] = name[i];
    }
    out[p] = 0;
}

static void c16_parent(CHAR16 *path)
{
    uint32_t n = c16_len(path);
    if (n == 0) {
        return;
    }
    while (n && path[n - 1] == L'\\') {
        path[--n] = 0;
    }
    while (n && path[n - 1] != L'\\') {
        path[--n] = 0;
    }
    if (n && path[n - 1] == L'\\') {
        path[n - 1] = 0;
    }
}

static uint16_t le16(const uint8_t *p)
{
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

static uint32_t le32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static uint64_t le64(const uint8_t *p)
{
    return (uint64_t)le32(p) | ((uint64_t)le32(p + 4) << 32);
}

static void put_le16(uint8_t *p, uint16_t v)
{
    p[0] = (uint8_t)(v & 0xFF);
    p[1] = (uint8_t)((v >> 8) & 0xFF);
}

static void put_le32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)(v & 0xFF);
    p[1] = (uint8_t)((v >> 8) & 0xFF);
    p[2] = (uint8_t)((v >> 16) & 0xFF);
    p[3] = (uint8_t)((v >> 24) & 0xFF);
}

static void put_le64(uint8_t *p, uint64_t v)
{
    for (uint32_t i = 0; i < 8; i++) {
        p[i] = (uint8_t)((v >> (i * 8)) & 0xFF);
    }
}

static uint32_t align_u32(uint32_t v, uint32_t align)
{
    return align ? (v + align - 1) & ~(align - 1) : v;
}

static CHAR16 c16_ascii_upper(CHAR16 c)
{
    if (c >= L'a' && c <= L'z') {
        return (CHAR16)(c - 32);
    }
    return c;
}

static int c16_equal_ci(const CHAR16 *a, const CHAR16 *b)
{
    uint32_t i = 0;
    while (a && b && a[i] && b[i]) {
        if (c16_ascii_upper(a[i]) != c16_ascii_upper(b[i])) {
            return 0;
        }
        i++;
    }
    return a && b && a[i] == b[i];
}

static int c16_next_component(const CHAR16 **pp, CHAR16 *out, uint32_t max)
{
    const CHAR16 *p = pp ? *pp : 0;
    uint32_t i = 0;
    if (!p || !out || !max) {
        return 0;
    }
    while (*p == L'\\' || *p == L'/') {
        p++;
    }
    if (!*p) {
        *pp = p;
        out[0] = 0;
        return 0;
    }
    while (*p && *p != L'\\' && *p != L'/' && i + 1 < max) {
        out[i++] = *p++;
    }
    out[i] = 0;
    while (*p == L'\\' || *p == L'/') {
        p++;
    }
    *pp = p;
    return 1;
}

static int c16_path_has_more(const CHAR16 *p)
{
    while (p && (*p == L'\\' || *p == L'/')) {
        p++;
    }
    return p && *p;
}

static void native_zero_dirent(native_dirent_t *e)
{
    memset(e, 0, sizeof(*e));
}

static int volume_is_browsable(uint32_t volume)
{
    return volume < g_volume_count &&
           (g_volumes[volume].firmware_fs || g_volumes[volume].native_ready);
}

static const char *native_fs_driver_name(uint8_t native_fs)
{
    if (native_fs == NATIVE_FS_EXFAT) {
        return "NATIVE EXFAT";
    }
    if (native_fs == NATIVE_FS_NTFS) {
        return "NATIVE NTFS";
    }
    if (native_fs == NATIVE_FS_RAW) {
        return "NATIVE RAW";
    }
    return "YOK";
}

static EFI_BLOCK_IO_PROTOCOL *native_block_io(uint32_t block_idx)
{
    EFI_BLOCK_IO_PROTOCOL *bio = 0;
    if (block_idx >= g_block_count) {
        return 0;
    }
    if (g_bs->OpenProtocol(g_blocks[block_idx].handle, (EFI_GUID *)&BlockIoGuid,
                           (void **)&bio, g_image, 0,
                           EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL) != EFI_SUCCESS) {
        if (g_bs->HandleProtocol(g_blocks[block_idx].handle, (EFI_GUID *)&BlockIoGuid,
                                 (void **)&bio) != EFI_SUCCESS) {
            return 0;
        }
    }
    return bio;
}

static int native_read_volume_bytes(uint32_t volume, uint64_t offset, UINTN size, void *dst)
{
    if (volume >= g_volume_count || !dst) {
        return 0;
    }
    volume_t *vol = &g_volumes[volume];
    if (vol->block_idx >= g_block_count) {
        return 0;
    }
    EFI_BLOCK_IO_PROTOCOL *bio = native_block_io(vol->block_idx);
    if (!bio || !bio->Media || !bio->ReadBlocks || !bio->Media->MediaPresent) {
        return 0;
    }
    uint32_t bs = bio->Media->BlockSize;
    if (!bs || bs > sizeof(g_fs_sector_buffer)) {
        return 0;
    }
    uint8_t *out = (uint8_t *)dst;
    while (size) {
        uint64_t lba = offset / bs;
        uint32_t in_sector = (uint32_t)(offset % bs);
        UINTN take = bs - in_sector;
        if (take > size) {
            take = size;
        }
        if (bio->ReadBlocks(bio, bio->Media->MediaId, lba, bs, g_fs_block_buffer) != EFI_SUCCESS) {
            return 0;
        }
        memcpy(out, g_fs_block_buffer + in_sector, take);
        out += take;
        offset += take;
        size -= take;
    }
    return 1;
}

static int native_write_volume_bytes(uint32_t volume, uint64_t offset, UINTN size, const void *src)
{
    if (volume >= g_volume_count || !src) {
        return 0;
    }
    volume_t *vol = &g_volumes[volume];
    if (vol->block_idx >= g_block_count || g_blocks[vol->block_idx].readonly) {
        return 0;
    }
    EFI_BLOCK_IO_PROTOCOL *bio = native_block_io(vol->block_idx);
    if (!bio || !bio->Media || !bio->ReadBlocks || !bio->WriteBlocks || !bio->Media->MediaPresent ||
        bio->Media->ReadOnly) {
        return 0;
    }
    /* Catch-all for NTFS: any byte we touch on an NTFS volume needs Windows to
     * see the dirty bit + an invalidated $LogFile on next mount, even if the
     * write came from an auto-repair path (index-root name fixup, security-id
     * backfill, MFT mirror sync) rather than a top-level user op.            */
    if (vol->native_fs == NATIVE_FS_NTFS && !vol->ntfs_modify_pending) {
        ntfs_begin_modify(volume);
    }
    uint32_t bs = bio->Media->BlockSize;
    if (!bs || bs > sizeof(g_fs_block_buffer)) {
        return 0;
    }
    const uint8_t *in = (const uint8_t *)src;
    while (size) {
        uint64_t lba = offset / bs;
        uint32_t in_sector = (uint32_t)(offset % bs);
        UINTN take = bs - in_sector;
        if (take > size) {
            take = size;
        }
        if (bio->ReadBlocks(bio, bio->Media->MediaId, lba, bs, g_fs_block_buffer) != EFI_SUCCESS) {
            return 0;
        }
        memcpy(g_fs_block_buffer + in_sector, in, take);
        if (bio->WriteBlocks(bio, bio->Media->MediaId, lba, bs, g_fs_block_buffer) != EFI_SUCCESS) {
            return 0;
        }
        in += take;
        offset += take;
        size -= take;
    }
    return 1;
}

static void native_flush_volume(uint32_t volume)
{
    if (volume >= g_volume_count || g_volumes[volume].block_idx >= g_block_count) {
        return;
    }
    volume_t *vol = &g_volumes[volume];
    /* If we have modified an NTFS volume since the last flush, leave it in a
     * state Windows will accept on the next mount: invalidate the $LogFile so
     * old log records can never replay on top of our writes, then clear the
     * VOLUME_IS_DIRTY flag we set when modification began.                    */
    if (vol->native_fs == NATIVE_FS_NTFS && vol->ntfs_modify_pending) {
        ntfs_invalidate_logfile(volume);
        if (vol->ntfs_dirty_owned) {
            ntfs_clear_volume_dirty(volume);
            vol->ntfs_dirty_owned = 0;
        }
        vol->ntfs_modify_pending = 0;
    }
    EFI_BLOCK_IO_PROTOCOL *bio = native_block_io(g_volumes[volume].block_idx);
    if (bio && bio->FlushBlocks) {
        bio->FlushBlocks(bio);
    }
}

static uint64_t native_volume_size_bytes(uint32_t volume)
{
    if (volume >= g_volume_count || g_volumes[volume].block_idx >= g_block_count) {
        return 0;
    }
    block_summary_t *b = &g_blocks[g_volumes[volume].block_idx];
    return b->blocks * (uint64_t)b->block_size;
}

static UINTN native_file_info_size(const CHAR16 *name)
{
    return (UINTN)offsetof(EFI_FILE_INFO, FileName) + ((UINTN)c16_len(name) + 1) * sizeof(CHAR16);
}

static EFI_STATUS native_fill_file_info(const file_entry_t *entry, UINTN *size, void *buf)
{
    if (!entry || !size) {
        return EFI_INVALID_PARAMETER;
    }
    UINTN needed = native_file_info_size(entry->name);
    if (!buf || *size < needed) {
        *size = needed;
        return EFI_BUFFER_TOO_SMALL;
    }
    EFI_FILE_INFO *info = (EFI_FILE_INFO *)buf;
    memset(info, 0, needed);
    info->Size = needed;
    info->FileSize = entry->size;
    info->PhysicalSize = entry->size;
    info->Attribute = entry->attr;
    /* Convert each cached NTFS timestamp into the EFI_TIME slots inside the
     * FileInfo so callers (in particular the copy/move loop) can read source
     * times via GetInfo and replay them onto the destination via SetInfo.   */
    if (entry->t_create) {
        ntfs_time_to_efi_time(entry->t_create, (EFI_TIME *)&info->CreateTime[0]);
    }
    if (entry->t_access) {
        ntfs_time_to_efi_time(entry->t_access, (EFI_TIME *)&info->LastAccessTime[0]);
    }
    if (entry->t_modify) {
        ntfs_time_to_efi_time(entry->t_modify, (EFI_TIME *)&info->ModificationTime[0]);
    }
    c16_copy(info->FileName, entry->name,
             (uint32_t)((needed - offsetof(EFI_FILE_INFO, FileName)) / sizeof(CHAR16)));
    *size = needed;
    return EFI_SUCCESS;
}

static int native_add_dirent(native_dirent_t *entries, uint32_t *count, const native_dirent_t *entry)
{
    if (!entries || !count || !entry || *count >= NATIVE_MAX_DIR_ENTRIES) {
        return 0;
    }
    entries[*count] = *entry;
    (*count)++;
    return 1;
}

static int exfat_cluster_valid(volume_t *vol, uint32_t cluster)
{
    return cluster >= 2 && cluster < vol->exfat_cluster_count + 2;
}

static uint64_t exfat_cluster_offset(volume_t *vol, uint32_t cluster)
{
    return ((uint64_t)vol->exfat_cluster_heap_offset +
            (uint64_t)(cluster - 2) * vol->exfat_sectors_per_cluster) *
           vol->exfat_bytes_per_sector;
}

static int exfat_next_cluster(uint32_t volume, uint32_t cluster, uint32_t *next)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t val = 0;
    uint64_t fat_sector = (uint64_t)(vol->exfat_fat_offset +
                          vol->exfat_active_fat * vol->exfat_fat_length) *
                          vol->exfat_bytes_per_sector;
    if (!next || !exfat_cluster_valid(vol, cluster)) {
        return 0;
    }
    if (!native_read_volume_bytes(volume, fat_sector + (uint64_t)cluster * 4, sizeof(val), &val)) {
        return 0;
    }
    val = le32((uint8_t *)&val);
    if (val >= 0xFFFFFFF8U || val == 0xFFFFFFFFU) {
        *next = 0;
        return 1;
    }
    if (!exfat_cluster_valid(vol, val)) {
        return 0;
    }
    *next = val;
    return 1;
}

static int exfat_write_fat_entry(uint32_t volume, uint32_t cluster, uint32_t value)
{
    volume_t *vol = &g_volumes[volume];
    uint8_t raw[4];
    uint64_t fat_sector = (uint64_t)(vol->exfat_fat_offset +
                          vol->exfat_active_fat * vol->exfat_fat_length) *
                          vol->exfat_bytes_per_sector;
    if (!exfat_cluster_valid(vol, cluster)) {
        return 0;
    }
    put_le32(raw, value);
    return native_write_volume_bytes(volume, fat_sector + (uint64_t)cluster * 4, sizeof(raw), raw);
}

static int exfat_cluster_for_index(uint32_t volume, uint32_t first_cluster,
                                   uint8_t no_fat_chain, uint64_t cluster_index,
                                   uint32_t *cluster)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t cur = first_cluster;
    if (!cluster || !exfat_cluster_valid(vol, first_cluster)) {
        return 0;
    }
    if (no_fat_chain) {
        cur = first_cluster + (uint32_t)cluster_index;
        if (!exfat_cluster_valid(vol, cur)) {
            return 0;
        }
        *cluster = cur;
        return 1;
    }
    while (cluster_index--) {
        uint32_t next = 0;
        if (!exfat_next_cluster(volume, cur, &next) || !next) {
            return 0;
        }
        cur = next;
    }
    *cluster = cur;
    return 1;
}

static int exfat_read_stream(uint32_t volume, uint32_t first_cluster, uint8_t no_fat_chain,
                             uint64_t data_len, uint64_t offset, UINTN size, void *dst)
{
    volume_t *vol = &g_volumes[volume];
    uint8_t *out = (uint8_t *)dst;
    if (!dst || !vol->exfat_cluster_size) {
        return 0;
    }
    if (data_len != UINT64_MAX && offset + size > data_len) {
        if (offset >= data_len) {
            return 0;
        }
        size = (UINTN)(data_len - offset);
    }
    while (size) {
        uint64_t cluster_index = offset / vol->exfat_cluster_size;
        uint32_t in_cluster = (uint32_t)(offset % vol->exfat_cluster_size);
        uint32_t cluster = 0;
        if (!exfat_cluster_for_index(volume, first_cluster, no_fat_chain, cluster_index, &cluster)) {
            return 0;
        }
        UINTN take = vol->exfat_cluster_size - in_cluster;
        if (take > size) {
            take = size;
        }
        if (!native_read_volume_bytes(volume, exfat_cluster_offset(vol, cluster) + in_cluster, take, out)) {
            return 0;
        }
        out += take;
        offset += take;
        size -= take;
    }
    return 1;
}

static int exfat_write_stream(uint32_t volume, uint32_t first_cluster, uint8_t no_fat_chain,
                              uint64_t offset, UINTN size, const void *src)
{
    volume_t *vol = &g_volumes[volume];
    const uint8_t *in = (const uint8_t *)src;
    if (!src || !vol->exfat_cluster_size || !exfat_cluster_valid(vol, first_cluster)) {
        return 0;
    }
    while (size) {
        uint64_t cluster_index = offset / vol->exfat_cluster_size;
        uint32_t in_cluster = (uint32_t)(offset % vol->exfat_cluster_size);
        uint32_t cluster = 0;
        if (!exfat_cluster_for_index(volume, first_cluster, no_fat_chain, cluster_index, &cluster)) {
            return 0;
        }
        UINTN take = vol->exfat_cluster_size - in_cluster;
        if (take > size) {
            take = size;
        }
        if (!native_write_volume_bytes(volume, exfat_cluster_offset(vol, cluster) + in_cluster, take, in)) {
            return 0;
        }
        in += take;
        offset += take;
        size -= take;
    }
    return 1;
}

static uint64_t exfat_stream_capacity(uint32_t volume, uint32_t first_cluster,
                                      uint8_t no_fat_chain, uint64_t data_len)
{
    volume_t *vol = &g_volumes[volume];
    if (!vol->exfat_cluster_size || !exfat_cluster_valid(vol, first_cluster)) {
        return 0;
    }
    if (no_fat_chain) {
        uint64_t clusters = (data_len + vol->exfat_cluster_size - 1) / vol->exfat_cluster_size;
        if (!clusters) {
            clusters = 1;
        }
        return clusters * vol->exfat_cluster_size;
    }
    uint64_t clusters = 0;
    uint32_t cur = first_cluster;
    while (cur && exfat_cluster_valid(vol, cur) && clusters < vol->exfat_cluster_count) {
        clusters++;
        uint32_t next = 0;
        if (!exfat_next_cluster(volume, cur, &next)) {
            break;
        }
        cur = next;
    }
    return clusters * vol->exfat_cluster_size;
}

static uint64_t exfat_dir_limit(uint32_t volume, uint32_t first_cluster,
                                uint8_t no_fat_chain, uint64_t data_len)
{
    uint64_t limit = data_len;
    if (!limit) {
        limit = exfat_stream_capacity(volume, first_cluster, no_fat_chain, data_len);
    }
    if (limit > 256ULL * 1024ULL * 1024ULL) {
        limit = 256ULL * 1024ULL * 1024ULL;
    }
    return limit;
}

static int exfat_dir_has_live_after(uint32_t volume, uint32_t dir_cluster,
                                    uint8_t dir_no_fat, uint64_t limit,
                                    uint64_t start_off)
{
    uint64_t end = start_off + 65536ULL;
    if (end > limit) {
        end = limit;
    }
    while (start_off + 32 <= end) {
        UINTN take = sizeof(g_fs_sector_buffer);
        if (start_off + take > end) {
            take = (UINTN)(end - start_off);
        }
        take &= ~(UINTN)31;
        if (!take) {
            break;
        }
        if (!exfat_read_stream(volume, dir_cluster, dir_no_fat, limit,
                               start_off, take, g_fs_sector_buffer)) {
            return 0;
        }
        for (UINTN off = 0; off + 32 <= take; off += 32) {
            if (g_fs_sector_buffer[off] & 0x80) {
                return 1;
            }
        }
        start_off += take;
    }
    return 0;
}

static void exfat_repair_premature_end_marker(uint32_t volume, uint32_t dir_cluster,
                                              uint8_t dir_no_fat, uint64_t off)
{
    uint8_t deleted_file_entry = 0x05;
    if (volume >= g_volume_count || g_volumes[volume].read_only) {
        return;
    }
    exfat_write_stream(volume, dir_cluster, dir_no_fat, off, 1, &deleted_file_entry);
}

static uint16_t exfat_dirset_checksum(const uint8_t *entries, uint32_t entry_count)
{
    uint16_t checksum = 0;
    for (uint32_t i = 0; i < entry_count; i++) {
        for (uint32_t j = 0; j < 32; j++) {
            if (i == 0 && (j == 2 || j == 3)) {
                continue;
            }
            checksum = (uint16_t)(((checksum << 15) | (checksum >> 1)) + entries[i * 32 + j]);
        }
    }
    return checksum;
}

static uint16_t exfat_name_hash(const CHAR16 *name);
static int exfat_find_free_dir_slots(uint32_t volume, uint32_t dir_cluster, uint8_t dir_no_fat,
                                     uint64_t dir_len, uint32_t needed, uint64_t *slot_off);
static int exfat_mark_entryset_deleted(native_file_handle_t *h);
static int exfat_enum_dir(uint32_t volume, uint32_t first_cluster, uint8_t no_fat_chain,
                          uint64_t data_len, native_dirent_t *entries, uint32_t *count);

static int exfat_update_dirset_checksum(uint32_t volume, uint32_t parent_cluster,
                                        uint8_t parent_no_fat, uint64_t primary_off,
                                        uint8_t secondary_count)
{
    uint32_t entry_count = (uint32_t)secondary_count + 1;
    UINTN bytes = entry_count * 32;
    if (bytes > sizeof(g_fs_sector_buffer)) {
        return 0;
    }
    if (!exfat_read_stream(volume, parent_cluster, parent_no_fat, UINT64_MAX,
                           primary_off, bytes, g_fs_sector_buffer)) {
        return 0;
    }
    uint16_t sum = exfat_dirset_checksum(g_fs_sector_buffer, entry_count);
    uint8_t sum_bytes[2];
    put_le16(sum_bytes, sum);
    return exfat_write_stream(volume, parent_cluster, parent_no_fat,
                              primary_off + 2, sizeof(sum_bytes), sum_bytes);
}

static int exfat_parent_has_name(uint32_t volume, uint32_t parent_cluster,
                                 uint8_t parent_no_fat, uint64_t parent_len,
                                 const CHAR16 *name, uint64_t self_primary_off)
{
    uint32_t count = 0;
    if (!name || !exfat_enum_dir(volume, parent_cluster, parent_no_fat,
                                 parent_len, g_native_dir_scratch, &count)) {
        return 0;
    }
    for (uint32_t i = 0; i < count; i++) {
        if (g_native_dir_scratch[i].exfat_primary_offset != self_primary_off &&
            c16_equal_ci(g_native_dir_scratch[i].pub.name, name)) {
            return 1;
        }
    }
    return 0;
}

static int exfat_write_renamed_entryset(native_file_handle_t *h, const CHAR16 *new_name,
                                        uint64_t slot_off, uint32_t entry_count)
{
    uint32_t name_len = c16_len(new_name);
    uint32_t name_entries = entry_count >= 2 ? entry_count - 2 : 0;
    if (!h || !new_name || !name_len || !name_entries ||
        entry_count * 32 > sizeof(g_fs_sector_buffer)) {
        return 0;
    }
    uint8_t old_primary[32];
    uint8_t old_stream[32];
    if (!exfat_read_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                           UINT64_MAX, h->exfat_primary_offset, sizeof(old_primary), old_primary) ||
        !exfat_read_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                           UINT64_MAX, h->exfat_stream_offset, sizeof(old_stream), old_stream) ||
        old_primary[0] != 0x85 || old_stream[0] != 0xC0) {
        return 0;
    }
    memset(g_fs_sector_buffer, 0, entry_count * 32);
    memcpy(g_fs_sector_buffer, old_primary, 32);
    memcpy(g_fs_sector_buffer + 32, old_stream, 32);
    uint8_t *primary = g_fs_sector_buffer;
    uint8_t *stream = g_fs_sector_buffer + 32;
    primary[1] = (uint8_t)(entry_count - 1);
    stream[3] = (uint8_t)name_len;
    put_le16(stream + 4, exfat_name_hash(new_name));
    uint32_t name_pos = 0;
    for (uint32_t ne = 0; ne < name_entries; ne++) {
        uint8_t *n = g_fs_sector_buffer + (2 + ne) * 32;
        n[0] = 0xC1;
        for (uint32_t c = 0; c < 15 && name_pos < name_len; c++) {
            put_le16(n + 2 + c * 2, new_name[name_pos++]);
        }
    }
    put_le16(primary + 2, exfat_dirset_checksum(g_fs_sector_buffer, entry_count));
    return exfat_write_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                              slot_off, entry_count * 32, g_fs_sector_buffer);
}

static int exfat_rename_handle(native_file_handle_t *h, const CHAR16 *new_name)
{
    uint32_t name_len = c16_len(new_name);
    uint32_t old_entry_count;
    uint32_t old_name_capacity;
    uint32_t needed_name_entries;
    uint32_t needed_entry_count;
    uint64_t new_slot = 0;
    if (!h || h->fs_type != NATIVE_FS_EXFAT || !h->exfat_parent_cluster ||
        !new_name || !name_len || name_len > 95 || c16_is_dotdot(new_name) ||
        g_volumes[h->volume].read_only) {
        return 0;
    }
    if (exfat_parent_has_name(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                              h->exfat_parent_len, new_name, h->exfat_primary_offset)) {
        return 0;
    }
    old_entry_count = (uint32_t)h->exfat_secondary_count + 1;
    old_name_capacity = h->exfat_secondary_count > 0 ? (uint32_t)(h->exfat_secondary_count - 1) * 15 : 0;
    needed_name_entries = (name_len + 14) / 15;
    needed_entry_count = 2 + needed_name_entries;
    if (name_len <= old_name_capacity) {
        if (!exfat_write_renamed_entryset(h, new_name, h->exfat_primary_offset, old_entry_count)) {
            return 0;
        }
    } else {
        if (!exfat_find_free_dir_slots(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                                       h->exfat_parent_len, needed_entry_count + 1, &new_slot)) {
            return 0;
        }
        if (!exfat_write_renamed_entryset(h, new_name, new_slot, needed_entry_count)) {
            return 0;
        }
        if (!exfat_mark_entryset_deleted(h)) {
            return 0;
        }
        h->exfat_primary_offset = new_slot;
        h->exfat_stream_offset = new_slot + 32;
        h->exfat_secondary_count = (uint8_t)(needed_entry_count - 1);
    }
    c16_copy(h->name, new_name, sizeof(h->name) / sizeof(h->name[0]));
    return 1;
}

static int exfat_update_file_size(native_file_handle_t *h, uint64_t new_size)
{
    uint8_t stream[32];
    if (!h || h->fs_type != NATIVE_FS_EXFAT || h->is_dir || !h->exfat_parent_cluster) {
        return 0;
    }
    if (new_size > h->exfat_capacity) {
        return 0;
    }
    if (!exfat_read_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat, UINT64_MAX,
                           h->exfat_stream_offset, sizeof(stream), stream) || stream[0] != 0xC0) {
        return 0;
    }
    put_le64(stream + 8, new_size);
    put_le64(stream + 24, new_size);
    if (!exfat_write_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                            h->exfat_stream_offset, sizeof(stream), stream)) {
        return 0;
    }
    if (!exfat_update_dirset_checksum(h->volume, h->exfat_parent_cluster,
                                      h->exfat_parent_no_fat, h->exfat_primary_offset,
                                      h->exfat_secondary_count)) {
        return 0;
    }
    h->size = new_size;
    return 1;
}

static int exfat_update_stream(native_file_handle_t *h, uint32_t first_cluster,
                               uint8_t no_fat_chain, uint64_t valid_len,
                               uint64_t data_len)
{
    uint8_t stream[32];
    if (!h || h->fs_type != NATIVE_FS_EXFAT || !h->exfat_parent_cluster) {
        return 0;
    }
    if (!exfat_read_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat, UINT64_MAX,
                           h->exfat_stream_offset, sizeof(stream), stream) || stream[0] != 0xC0) {
        return 0;
    }
    stream[1] = first_cluster ? (uint8_t)(0x01 | (no_fat_chain ? 0x02 : 0)) : 0x01;
    put_le64(stream + 8, valid_len);
    stream[19] = 0;
    stream[20] = (uint8_t)(first_cluster & 0xFF);
    stream[21] = (uint8_t)((first_cluster >> 8) & 0xFF);
    stream[22] = (uint8_t)((first_cluster >> 16) & 0xFF);
    stream[23] = (uint8_t)((first_cluster >> 24) & 0xFF);
    put_le64(stream + 24, data_len);
    if (!exfat_write_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                            h->exfat_stream_offset, sizeof(stream), stream)) {
        return 0;
    }
    if (!exfat_update_dirset_checksum(h->volume, h->exfat_parent_cluster,
                                      h->exfat_parent_no_fat, h->exfat_primary_offset,
                                      h->exfat_secondary_count)) {
        return 0;
    }
    h->exfat_first_cluster = first_cluster;
    h->exfat_no_fat_chain = no_fat_chain;
    h->size = data_len;
    return 1;
}

static int exfat_bitmap_set(uint32_t volume, uint32_t cluster, uint8_t used)
{
    volume_t *vol = &g_volumes[volume];
    if (!exfat_cluster_valid(vol, cluster) || !vol->exfat_bitmap_cluster) {
        return 0;
    }
    uint64_t bit = (uint64_t)(cluster - 2);
    uint8_t b = 0;
    if (bit / 8 >= vol->exfat_bitmap_len) {
        return 0;
    }
    if (!exfat_read_stream(volume, vol->exfat_bitmap_cluster, 0, vol->exfat_bitmap_len,
                           bit / 8, 1, &b)) {
        return 0;
    }
    if (used) {
        b |= (uint8_t)(1U << (bit & 7));
    } else {
        b &= (uint8_t)~(1U << (bit & 7));
    }
    return exfat_write_stream(volume, vol->exfat_bitmap_cluster, 0, bit / 8, 1, &b);
}

static int exfat_bitmap_set_range(uint32_t volume, uint32_t first_cluster,
                                  uint32_t clusters, uint8_t used)
{
    volume_t *vol = &g_volumes[volume];
    uint64_t first_bit;
    uint64_t end_bit;
    if (!clusters || !exfat_cluster_valid(vol, first_cluster) ||
        !exfat_cluster_valid(vol, first_cluster + clusters - 1) ||
        !vol->exfat_bitmap_cluster) {
        return 0;
    }
    first_bit = (uint64_t)(first_cluster - 2);
    end_bit = first_bit + clusters;
    while (first_bit < end_bit) {
        uint64_t byte_off = first_bit / 8;
        UINTN take = sizeof(g_fs_sector_buffer);
        if (byte_off >= vol->exfat_bitmap_len) {
            return 0;
        }
        if (byte_off + take > vol->exfat_bitmap_len) {
            take = (UINTN)(vol->exfat_bitmap_len - byte_off);
        }
        if (!exfat_read_stream(volume, vol->exfat_bitmap_cluster, 0, vol->exfat_bitmap_len,
                               byte_off, take, g_fs_sector_buffer)) {
            return 0;
        }
        uint64_t chunk_end_bit = (byte_off + take) * 8;
        if (chunk_end_bit > end_bit) {
            chunk_end_bit = end_bit;
        }
        for (uint64_t bit = first_bit; bit < chunk_end_bit; bit++) {
            uint64_t rel = bit - byte_off * 8;
            uint8_t mask = (uint8_t)(1U << (rel & 7));
            if (used) {
                g_fs_sector_buffer[rel / 8] |= mask;
            } else {
                g_fs_sector_buffer[rel / 8] &= (uint8_t)~mask;
            }
        }
        if (!exfat_write_stream(volume, vol->exfat_bitmap_cluster, 0,
                                byte_off, take, g_fs_sector_buffer)) {
            return 0;
        }
        first_bit = chunk_end_bit;
    }
    return 1;
}

static int exfat_enum_dir(uint32_t volume, uint32_t first_cluster, uint8_t no_fat_chain,
                          uint64_t data_len, native_dirent_t *entries, uint32_t *count);

static int exfat_range_contains(uint32_t start, uint32_t count, uint32_t cluster)
{
    return count && cluster >= start && cluster < start + count;
}

static int exfat_range_intersects(uint32_t start, uint32_t count,
                                  uint32_t first_cluster, uint32_t clusters)
{
    if (!count || !clusters) {
        return 0;
    }
    return first_cluster < start + count && start < first_cluster + clusters;
}

static int exfat_chain_intersects_range(uint32_t volume, uint32_t first_cluster,
                                        uint8_t no_fat_chain, uint64_t data_len,
                                        uint32_t start, uint32_t count)
{
    volume_t *vol = &g_volumes[volume];
    if (!exfat_cluster_valid(vol, first_cluster)) {
        return 0;
    }
    if (no_fat_chain) {
        uint32_t clusters = (uint32_t)((data_len + vol->exfat_cluster_size - 1) /
                                       vol->exfat_cluster_size);
        if (!clusters) {
            clusters = 1;
        }
        return exfat_range_intersects(start, count, first_cluster, clusters);
    }
    uint32_t cur = first_cluster;
    uint32_t guard = 0;
    while (cur && exfat_cluster_valid(vol, cur) && guard++ < vol->exfat_cluster_count) {
        if (exfat_range_contains(start, count, cur)) {
            return 1;
        }
        uint32_t next = 0;
        if (!exfat_next_cluster(volume, cur, &next)) {
            break;
        }
        cur = next;
    }
    return 0;
}

static int exfat_range_is_reserved(uint32_t volume, uint32_t start, uint32_t count)
{
    volume_t *vol = &g_volumes[volume];
    if (exfat_chain_intersects_range(volume, vol->exfat_root_cluster, 0, 0, start, count)) {
        return 1;
    }
    if (exfat_chain_intersects_range(volume, vol->exfat_bitmap_cluster, 0,
                                     vol->exfat_bitmap_len, start, count)) {
        return 1;
    }
    if (exfat_chain_intersects_range(volume, vol->exfat_upcase_cluster, 0,
                                     vol->exfat_upcase_len, start, count)) {
        return 1;
    }
    return 0;
}

static int exfat_alloc_contiguous(uint32_t volume, uint32_t clusters, uint32_t *first_cluster)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t run_start = 0;
    uint32_t run_len = 0;
    uint64_t bitmap_bytes;
    if (!first_cluster || !clusters || !vol->exfat_bitmap_cluster) {
        return 0;
    }
    bitmap_bytes = ((uint64_t)vol->exfat_cluster_count + 7) / 8;
    if (bitmap_bytes > vol->exfat_bitmap_len) {
        bitmap_bytes = vol->exfat_bitmap_len;
    }
    for (uint64_t byte_off = 0; byte_off < bitmap_bytes; ) {
        UINTN take = sizeof(g_fs_sector_buffer);
        if (byte_off + take > bitmap_bytes) {
            take = (UINTN)(bitmap_bytes - byte_off);
        }
        if (!exfat_read_stream(volume, vol->exfat_bitmap_cluster, 0, vol->exfat_bitmap_len,
                               byte_off, take, g_fs_sector_buffer)) {
            return 0;
        }
        for (UINTN bi = 0; bi < take; bi++) {
            uint8_t b = g_fs_sector_buffer[bi];
            for (uint32_t bit = 0; bit < 8; bit++) {
                uint64_t cluster64 = byte_off * 8 + (uint64_t)bi * 8 + bit + 2;
                if (cluster64 >= (uint64_t)vol->exfat_cluster_count + 2) {
                    break;
                }
                if (!(b & (1U << bit))) {
                    if (!run_len) {
                        run_start = (uint32_t)cluster64;
                    }
                    run_len++;
                    if (run_len == clusters) {
                        if (exfat_range_is_reserved(volume, run_start, clusters)) {
                            run_len = 0;
                            continue;
                        }
                        if (!exfat_bitmap_set_range(volume, run_start, clusters, 1)) {
                            return 0;
                        }
                        *first_cluster = run_start;
                        return 1;
                    }
                } else {
                    run_len = 0;
                }
            }
        }
        byte_off += take;
    }
    return 0;
}

static void exfat_free_contiguous(uint32_t volume, uint32_t first_cluster, uint32_t clusters)
{
    exfat_bitmap_set_range(volume, first_cluster, clusters, 0);
}

static uint32_t exfat_clusters_for_len(uint32_t volume, uint64_t len)
{
    volume_t *vol = &g_volumes[volume];
    if (!vol->exfat_cluster_size || !len) {
        return 0;
    }
    uint64_t clusters = (len + vol->exfat_cluster_size - 1) / vol->exfat_cluster_size;
    if (clusters > vol->exfat_cluster_count) {
        clusters = vol->exfat_cluster_count;
    }
    return (uint32_t)clusters;
}

static void exfat_free_chain(uint32_t volume, uint32_t first_cluster)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t cur = first_cluster;
    uint32_t guard = 0;
    while (cur && exfat_cluster_valid(vol, cur) && guard++ < vol->exfat_cluster_count) {
        uint32_t next = 0;
        exfat_next_cluster(volume, cur, &next);
        exfat_bitmap_set(volume, cur, 0);
        exfat_write_fat_entry(volume, cur, 0);
        cur = next;
    }
}

static void exfat_free_handle_clusters(native_file_handle_t *h)
{
    if (!h || h->fs_type != NATIVE_FS_EXFAT || !h->exfat_first_cluster) {
        return;
    }
    if (h->exfat_no_fat_chain) {
        uint64_t len = h->exfat_capacity ? h->exfat_capacity : h->size;
        uint32_t clusters = exfat_clusters_for_len(h->volume, len);
        if (!clusters) {
            clusters = 1;
        }
        exfat_free_contiguous(h->volume, h->exfat_first_cluster, clusters);
    } else {
        exfat_free_chain(h->volume, h->exfat_first_cluster);
    }
}

static int exfat_mark_entryset_deleted(native_file_handle_t *h)
{
    if (!h || h->fs_type != NATIVE_FS_EXFAT || !h->exfat_parent_cluster ||
        h->exfat_secondary_count > 18) {
        return 0;
    }
    uint32_t entry_count = (uint32_t)h->exfat_secondary_count + 1;
    for (uint32_t i = 0; i < entry_count; i++) {
        uint8_t entry_type = 0;
        uint64_t off = h->exfat_primary_offset + (uint64_t)i * 32;
        if (!exfat_read_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                               UINT64_MAX, off, 1, &entry_type)) {
            return 0;
        }
        entry_type &= 0x7F;
        if (!exfat_write_stream(h->volume, h->exfat_parent_cluster, h->exfat_parent_no_fat,
                                off, 1, &entry_type)) {
            return 0;
        }
    }
    return 1;
}

static int exfat_directory_is_empty(native_file_handle_t *h)
{
    uint32_t count = 0;
    if (!h || !h->is_dir || !h->exfat_first_cluster) {
        return 0;
    }
    if (!exfat_enum_dir(h->volume, h->exfat_first_cluster, h->exfat_no_fat_chain,
                        h->size, g_native_dir_scratch, &count)) {
        return 0;
    }
    return count == 0;
}

static int exfat_zero_clusters(uint32_t volume, uint32_t first_cluster, uint32_t clusters)
{
    volume_t *vol = &g_volumes[volume];
    memset(g_fs_sector_buffer, 0, sizeof(g_fs_sector_buffer));
    for (uint32_t k = 0; k < clusters; k++) {
        uint64_t left = vol->exfat_cluster_size;
        uint64_t off = 0;
        while (left) {
            UINTN take = left > sizeof(g_fs_sector_buffer) ? sizeof(g_fs_sector_buffer) : (UINTN)left;
            if (!native_write_volume_bytes(volume, exfat_cluster_offset(vol, first_cluster + k) + off,
                                           take, g_fs_sector_buffer)) {
                return 0;
            }
            off += take;
            left -= take;
        }
    }
    return 1;
}

static int exfat_grow_file(native_file_handle_t *h, uint64_t wanted_size)
{
    volume_t *vol = &g_volumes[h->volume];
    uint32_t need_clusters = (uint32_t)((wanted_size + vol->exfat_cluster_size - 1) / vol->exfat_cluster_size);
    uint32_t old_clusters = (uint32_t)((h->exfat_capacity + vol->exfat_cluster_size - 1) / vol->exfat_cluster_size);
    uint32_t old_first = h->exfat_first_cluster;
    uint8_t old_no_fat = h->exfat_no_fat_chain;
    uint32_t new_first = 0;
    if (!need_clusters) {
        return 1;
    }
    if (old_first && !old_no_fat) {
        return 0;
    }
    if (!exfat_alloc_contiguous(h->volume, need_clusters, &new_first)) {
        return 0;
    }
    if (!exfat_zero_clusters(h->volume, new_first, need_clusters)) {
        exfat_free_contiguous(h->volume, new_first, need_clusters);
        return 0;
    }
    if (h->size && h->exfat_first_cluster) {
        uint64_t copied = 0;
        while (copied < h->size) {
            UINTN take = (h->size - copied) > sizeof(g_io_buffer) ? sizeof(g_io_buffer) : (UINTN)(h->size - copied);
            if (!exfat_read_stream(h->volume, h->exfat_first_cluster, h->exfat_no_fat_chain,
                                   h->size, copied, take, g_io_buffer) ||
                !exfat_write_stream(h->volume, new_first, 1, copied, take, g_io_buffer)) {
                exfat_free_contiguous(h->volume, new_first, need_clusters);
                return 0;
            }
            copied += take;
        }
    }
    if (!exfat_update_stream(h, new_first, 1, h->size, h->size)) {
        exfat_free_contiguous(h->volume, new_first, need_clusters);
        return 0;
    }
    if (old_first && old_no_fat && old_clusters) {
        exfat_free_contiguous(h->volume, old_first, old_clusters);
    }
    h->exfat_first_cluster = new_first;
    h->exfat_no_fat_chain = 1;
    h->exfat_capacity = (uint64_t)need_clusters * vol->exfat_cluster_size;
    return 1;
}

static int exfat_enum_dir(uint32_t volume, uint32_t first_cluster, uint8_t no_fat_chain,
                          uint64_t data_len, native_dirent_t *entries, uint32_t *count)
{
    uint64_t limit = exfat_dir_limit(volume, first_cluster, no_fat_chain, data_len);
    uint64_t off = 0;
    uint8_t de[32];
    if (!entries || !count) {
        return 0;
    }
    if (!limit) {
        return 0;
    }
    *count = 0;
    while (off + 32 <= limit && *count < NATIVE_MAX_DIR_ENTRIES) {
        if (!exfat_read_stream(volume, first_cluster, no_fat_chain, limit, off, sizeof(de), de)) {
            break;
        }
        if (de[0] == 0x00) {
            if (exfat_dir_has_live_after(volume, first_cluster, no_fat_chain, limit, off + 32)) {
                exfat_repair_premature_end_marker(volume, first_cluster, no_fat_chain, off);
                off += 32;
                continue;
            }
            break;
        }
        if (de[0] == 0x85) {
            uint8_t secondary = de[1];
            uint16_t attrs = le16(de + 4);
            if (secondary >= 2 && secondary <= 18) {
                uint8_t stream[32];
                if (exfat_read_stream(volume, first_cluster, no_fat_chain, limit,
                                      off + 32, sizeof(stream), stream) && stream[0] == 0xC0) {
                    native_dirent_t out;
                    native_zero_dirent(&out);
                    uint8_t flags = stream[1];
                    uint8_t name_len = stream[3];
                    out.exfat_primary_offset = off;
                    out.exfat_stream_offset = off + 32;
                    out.exfat_parent_cluster = first_cluster;
                    out.exfat_parent_no_fat = no_fat_chain;
                    out.exfat_parent_len = data_len;
                    out.exfat_secondary_count = secondary;
                    out.exfat_no_fat_chain = (flags & 0x02) ? 1 : 0;
                    out.exfat_first_cluster = le32(stream + 20);
                    out.exfat_data_len = le64(stream + 24);
                    out.pub.size = out.exfat_data_len;
                    out.pub.attr = (attrs & 0x10) ? EFI_FILE_DIRECTORY : 0;
                    if (attrs & 0x01) {
                        out.pub.attr |= EFI_FILE_READ_ONLY;
                    }
                    out.pub.is_dir = (attrs & 0x10) ? 1 : 0;
                    uint32_t name_pos = 0;
                    for (uint8_t s = 2; s <= secondary && name_pos < name_len; s++) {
                        uint8_t ne[32];
                        if (!exfat_read_stream(volume, first_cluster, no_fat_chain, limit,
                                               off + (uint64_t)s * 32, sizeof(ne), ne)) {
                            break;
                        }
                        if (ne[0] != 0xC1) {
                            continue;
                        }
                        for (uint32_t c = 0; c < 15 && name_pos < name_len &&
                                             name_pos + 1 < sizeof(out.pub.name) / sizeof(out.pub.name[0]); c++) {
                            out.pub.name[name_pos++] = le16(ne + 2 + c * 2);
                        }
                    }
                    out.pub.name[name_pos] = 0;
                    if (out.pub.name[0]) {
                        native_add_dirent(entries, count, &out);
                    }
                }
                off += ((uint64_t)secondary + 1) * 32;
                continue;
            }
        }
        off += 32;
    }
    return 1;
}

static int exfat_find_allocation_bitmap(uint32_t volume)
{
    volume_t *vol = &g_volumes[volume];
    uint64_t off = 0;
    uint64_t limit = exfat_dir_limit(volume, vol->exfat_root_cluster, 0, 0);
    uint8_t de[32];
    if (!limit || limit > 1024ULL * 1024ULL) {
        limit = 1024ULL * 1024ULL;
    }
    while (off + 32 <= limit) {
        if (!exfat_read_stream(volume, vol->exfat_root_cluster, 0, limit, off, sizeof(de), de)) {
            return 0;
        }
        if (de[0] == 0x00) {
            break;
        }
        if (de[0] == 0x81 && ((de[1] & 1U) == vol->exfat_active_fat)) {
            vol->exfat_bitmap_cluster = le32(de + 20);
            vol->exfat_bitmap_len = le64(de + 24);
        } else if (de[0] == 0x82) {
            vol->exfat_upcase_cluster = le32(de + 20);
            vol->exfat_upcase_len = le64(de + 24);
        }
        off += 32;
    }
    return exfat_cluster_valid(vol, vol->exfat_bitmap_cluster) &&
           vol->exfat_bitmap_len >= ((uint64_t)vol->exfat_cluster_count + 7) / 8;
}

static uint16_t exfat_name_hash(const CHAR16 *name)
{
    uint16_t hash = 0;
    for (uint32_t i = 0; name && name[i]; i++) {
        CHAR16 c = c16_ascii_upper(name[i]);
        uint8_t lo = (uint8_t)(c & 0xFF);
        uint8_t hi = (uint8_t)((c >> 8) & 0xFF);
        hash = (uint16_t)(((hash << 15) | (hash >> 1)) + lo);
        hash = (uint16_t)(((hash << 15) | (hash >> 1)) + hi);
    }
    return hash;
}

static int exfat_find_free_dir_slots(uint32_t volume, uint32_t dir_cluster, uint8_t dir_no_fat,
                                     uint64_t dir_len, uint32_t needed, uint64_t *slot_off)
{
    uint64_t limit = exfat_dir_limit(volume, dir_cluster, dir_no_fat, dir_len);
    uint64_t off = 0;
    uint32_t run = 0;
    uint64_t run_start = 0;
    uint8_t de[32];
    if (!slot_off || !needed) {
        return 0;
    }
    if (!limit) {
        return 0;
    }
    while (off + 32 <= limit) {
        if (!exfat_read_stream(volume, dir_cluster, dir_no_fat, limit, off, sizeof(de), de)) {
            return 0;
        }
        if (de[0] == 0x00 &&
            exfat_dir_has_live_after(volume, dir_cluster, dir_no_fat, limit, off + 32)) {
            exfat_repair_premature_end_marker(volume, dir_cluster, dir_no_fat, off);
        }
        if (de[0] == 0x00 || !(de[0] & 0x80)) {
            if (!run) {
                run_start = off;
            }
            run++;
            if (run >= needed) {
                *slot_off = run_start;
                return 1;
            }
        } else {
            run = 0;
        }
        off += 32;
    }
    return 0;
}

static int exfat_resolve_parent(uint32_t volume, const CHAR16 *path,
                                uint32_t *parent_cluster, uint8_t *parent_no_fat,
                                uint64_t *parent_len, CHAR16 *leaf, uint32_t leaf_max)
{
    volume_t *vol = &g_volumes[volume];
    const CHAR16 *p = path;
    CHAR16 comp[96];
    uint32_t dir_cluster = vol->exfat_root_cluster;
    uint8_t dir_no_fat = 0;
    uint64_t dir_len = 0;
    if (!c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]))) {
        return 0;
    }
    for (;;) {
        if (!c16_path_has_more(p)) {
            c16_copy(leaf, comp, leaf_max);
            *parent_cluster = dir_cluster;
            *parent_no_fat = dir_no_fat;
            *parent_len = dir_len;
            return leaf && leaf[0];
        }
        uint32_t tmp_count = 0;
        uint8_t found = 0;
        native_dirent_t next_dir;
        native_zero_dirent(&next_dir);
        if (!exfat_enum_dir(volume, dir_cluster, dir_no_fat, dir_len, g_native_dir_scratch, &tmp_count)) {
            return 0;
        }
        for (uint32_t i = 0; i < tmp_count; i++) {
            if (g_native_dir_scratch[i].pub.is_dir && c16_equal_ci(g_native_dir_scratch[i].pub.name, comp)) {
                next_dir = g_native_dir_scratch[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
        dir_cluster = next_dir.exfat_first_cluster;
        dir_no_fat = next_dir.exfat_no_fat_chain;
        dir_len = next_dir.exfat_data_len;
        c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]));
    }
}

static int exfat_create_entry(uint32_t volume, const CHAR16 *path, uint64_t attr,
                              native_file_handle_t *h)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t parent_cluster = 0;
    uint8_t parent_no_fat = 0;
    uint64_t parent_len = 0;
    CHAR16 name[96];
    uint32_t name_len = 0;
    uint32_t name_entries = 0;
    uint32_t entry_count = 0;
    uint32_t first_cluster = 0;
    uint64_t data_len = 0;
    uint8_t stream_flags = 0x01;
    uint64_t slot_off = 0;
    if (!h || !path || g_volumes[volume].read_only) {
        return 0;
    }
    if (!exfat_resolve_parent(volume, path, &parent_cluster, &parent_no_fat, &parent_len,
                              name, sizeof(name) / sizeof(name[0]))) {
        return 0;
    }
    while (name[name_len]) {
        name_len++;
    }
    if (!name_len || name_len > 95 || c16_is_dotdot(name)) {
        return 0;
    }
    name_entries = (name_len + 14) / 15;
    entry_count = 2 + name_entries;
    if (entry_count * 32 > sizeof(g_fs_sector_buffer)) {
        return 0;
    }
    if (!exfat_find_free_dir_slots(volume, parent_cluster, parent_no_fat, parent_len,
                                   entry_count + 1, &slot_off)) {
        return 0;
    }
    if (attr & EFI_FILE_DIRECTORY) {
        if (!exfat_alloc_contiguous(volume, 1, &first_cluster)) {
            return 0;
        }
        if (!exfat_zero_clusters(volume, first_cluster, 1)) {
            exfat_free_contiguous(volume, first_cluster, 1);
            return 0;
        }
        data_len = vol->exfat_cluster_size;
        stream_flags = 0x03;
    }
    memset(g_fs_sector_buffer, 0, entry_count * 32);
    uint8_t *primary = g_fs_sector_buffer;
    uint8_t *stream = g_fs_sector_buffer + 32;
    primary[0] = 0x85;
    primary[1] = (uint8_t)(entry_count - 1);
    put_le16(primary + 4, (attr & EFI_FILE_DIRECTORY) ? 0x10 : 0x20);
    stream[0] = 0xC0;
    stream[1] = stream_flags;
    stream[3] = (uint8_t)name_len;
    put_le16(stream + 4, exfat_name_hash(name));
    put_le64(stream + 8, data_len);
    stream[20] = (uint8_t)(first_cluster & 0xFF);
    stream[21] = (uint8_t)((first_cluster >> 8) & 0xFF);
    stream[22] = (uint8_t)((first_cluster >> 16) & 0xFF);
    stream[23] = (uint8_t)((first_cluster >> 24) & 0xFF);
    put_le64(stream + 24, data_len);
    uint32_t name_pos = 0;
    for (uint32_t ne = 0; ne < name_entries; ne++) {
        uint8_t *n = g_fs_sector_buffer + (2 + ne) * 32;
        n[0] = 0xC1;
        for (uint32_t c = 0; c < 15 && name_pos < name_len; c++) {
            put_le16(n + 2 + c * 2, name[name_pos++]);
        }
    }
    put_le16(primary + 2, exfat_dirset_checksum(g_fs_sector_buffer, entry_count));
    if (!exfat_write_stream(volume, parent_cluster, parent_no_fat, slot_off,
                            entry_count * 32, g_fs_sector_buffer)) {
        if (first_cluster) {
            exfat_free_contiguous(volume, first_cluster, 1);
        }
        return 0;
    }
    c16_copy(h->name, name, sizeof(h->name) / sizeof(h->name[0]));
    h->is_dir = (attr & EFI_FILE_DIRECTORY) ? 1 : 0;
    h->attr = attr & EFI_FILE_DIRECTORY ? EFI_FILE_DIRECTORY : 0;
    h->can_write = h->is_dir ? 0 : 1;
    h->size = data_len;
    h->exfat_capacity = data_len;
    h->exfat_primary_offset = slot_off;
    h->exfat_stream_offset = slot_off + 32;
    h->exfat_parent_cluster = parent_cluster;
    h->exfat_parent_no_fat = parent_no_fat;
    h->exfat_parent_len = parent_len;
    h->exfat_secondary_count = (uint8_t)(entry_count - 1);
    h->exfat_first_cluster = first_cluster;
    h->exfat_no_fat_chain = first_cluster ? 1 : 0;
    if (h->is_dir) {
        return exfat_enum_dir(volume, first_cluster, 1, data_len, h->dirents, &h->dir_count);
    }
    return 1;
}

static int exfat_init_volume(uint32_t volume)
{
    uint8_t *bs = g_fs_sector_buffer;
    volume_t *vol = &g_volumes[volume];
    if (!native_read_volume_bytes(volume, 0, 512, bs)) {
        return 0;
    }
    if (!memeq_ascii(bs, 3, "EXFAT   ", 8)) {
        return 0;
    }
    uint8_t bps_shift = bs[108];
    uint8_t spc_shift = bs[109];
    if (bps_shift < 9 || bps_shift > 12 || spc_shift > 25 || bs[110] < 1 || bs[110] > 2) {
        return 0;
    }
    vol->exfat_bytes_per_sector = 1U << bps_shift;
    vol->exfat_sectors_per_cluster = 1U << spc_shift;
    vol->exfat_cluster_size = vol->exfat_bytes_per_sector * vol->exfat_sectors_per_cluster;
    vol->exfat_fat_offset = le32(bs + 80);
    vol->exfat_fat_length = le32(bs + 84);
    vol->exfat_cluster_heap_offset = le32(bs + 88);
    vol->exfat_cluster_count = le32(bs + 92);
    vol->exfat_root_cluster = le32(bs + 96);
    vol->exfat_active_fat = le16(bs + 106) & 1U;
    vol->exfat_bitmap_cluster = 0;
    vol->exfat_bitmap_len = 0;
    vol->exfat_upcase_cluster = 0;
    vol->exfat_upcase_len = 0;
    if (!vol->exfat_cluster_size || !exfat_cluster_valid(vol, vol->exfat_root_cluster)) {
        return 0;
    }
    return exfat_find_allocation_bitmap(volume);
}

static const uint16_t g_days_per_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static int ntfs_is_leap_year(int y)
{
    return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

/* EFI_TIME → NTFS 100-ns-since-1601-UTC.  Returns 0 if the input is invalid. */
static uint64_t efi_time_to_ntfs_time(const EFI_TIME *t)
{
    if (!t || t->Year < 1601 || t->Year > 9999 || t->Month < 1 || t->Month > 12 ||
        t->Day < 1 || t->Day > 31 || t->Hour > 23 || t->Minute > 59 ||
        t->Second > 59 || t->Nanosecond > 999999999U) {
        return 0;
    }
    int leap_target = ntfs_is_leap_year(t->Year);
    if (t->Day - 1 >= g_days_per_month[leap_target][t->Month - 1]) {
        return 0;
    }
    uint64_t days = 0;
    for (uint16_t y = 1601; y < t->Year; y++) {
        days += ntfs_is_leap_year(y) ? 366 : 365;
    }
    for (int m = 1; m < t->Month; m++) {
        days += g_days_per_month[leap_target][m - 1];
    }
    days += (uint64_t)(t->Day - 1);
    int64_t total_secs = (int64_t)(days * 86400ULL +
                                   (uint64_t)t->Hour * 3600ULL +
                                   (uint64_t)t->Minute * 60ULL +
                                   (uint64_t)t->Second);
    if (t->TimeZone != 0x07FF) {
        total_secs -= (int64_t)t->TimeZone * 60;
    }
    if (total_secs < 0) {
        return 0;
    }
    return (uint64_t)total_secs * 10000000ULL + (uint64_t)(t->Nanosecond / 100);
}

/* NTFS 100-ns-since-1601-UTC → EFI_TIME (always emitted as UTC, TimeZone=0). */
static void ntfs_time_to_efi_time(uint64_t ntfs, EFI_TIME *out)
{
    if (!out) return;
    memset(out, 0, sizeof(*out));
    if (!ntfs) {
        return;
    }
    uint64_t secs = ntfs / 10000000ULL;
    uint32_t nano = (uint32_t)((ntfs % 10000000ULL) * 100ULL);
    uint64_t days = secs / 86400ULL;
    uint32_t tod  = (uint32_t)(secs % 86400ULL);
    uint32_t hour = tod / 3600;
    uint32_t mn   = (tod / 60) % 60;
    uint32_t sec  = tod % 60;
    uint16_t year = 1601;
    while (1) {
        uint64_t y_days = ntfs_is_leap_year(year) ? 366 : 365;
        if (days < y_days) break;
        days -= y_days;
        year++;
        if (year > 9999) {
            year = 9999;
            days = 0;
            break;
        }
    }
    int leap = ntfs_is_leap_year(year);
    uint8_t month = 1;
    while (month < 12 && days >= g_days_per_month[leap][month - 1]) {
        days -= g_days_per_month[leap][month - 1];
        month++;
    }
    out->Year       = year;
    out->Month      = month;
    out->Day        = (uint8_t)(days + 1);
    out->Hour       = (uint8_t)hour;
    out->Minute     = (uint8_t)mn;
    out->Second     = (uint8_t)sec;
    out->Nanosecond = nano;
    out->TimeZone   = 0;     /* UTC */
    out->Daylight   = 0;
}

/* Returns the current wall-clock time in NTFS format: 100-nanosecond intervals
 * since 1601-01-01 00:00:00 UTC.  When the firmware doesn't provide a clock or
 * returns a junk value we fall back to 2024-01-01 00:00:00 UTC instead of 0,
 * because all-zero timestamps look like "January 1, 1601" to Windows and make
 * the file look anomalous to Attachment Manager / SmartScreen — which is what
 * triggers the "Internet güvenlik ayarlarınız …" dialog when the file is
 * opened.                                                                    */
static uint64_t ntfs_time_now(void)
{
    static const uint64_t fallback = 133485408000000000ULL; /* 2024-01-01 UTC */
    EFI_TIME t;
    if (!g_st || !g_st->RuntimeServices || !g_st->RuntimeServices->GetTime) {
        return fallback;
    }
    if (g_st->RuntimeServices->GetTime(&t, 0) != EFI_SUCCESS) {
        return fallback;
    }
    uint64_t v = efi_time_to_ntfs_time(&t);
    return v ? v : fallback;
}

/* Fill the four NTFS timestamps (creation, data-change, mft-change, access)
 * starting at `dst` (each 8 bytes, little-endian) with a single value.       */
static void ntfs_put_timestamps(uint8_t *dst, uint64_t when)
{
    put_le64(dst,      when);
    put_le64(dst + 8,  when);
    put_le64(dst + 16, when);
    put_le64(dst + 24, when);
}

static int ntfs_apply_fixup(uint8_t *buf, uint32_t size, uint32_t sector_size, const char *sig)
{
    if (!buf || size < 16 || !memeq_ascii(buf, 0, sig, 4) || !sector_size) {
        return 0;
    }
    uint16_t usa_off = le16(buf + 4);
    uint16_t usa_count = le16(buf + 6);
    if (!usa_count || usa_off + (uint32_t)usa_count * 2 > size) {
        return 0;
    }
    for (uint32_t i = 1; i < usa_count; i++) {
        uint32_t pos = i * sector_size - 2;
        if (pos + 2 > size) {
            return 0;
        }
        buf[pos] = buf[usa_off + i * 2];
        buf[pos + 1] = buf[usa_off + i * 2 + 1];
    }
    return 1;
}

static int ntfs_parse_runlist(const uint8_t *run, uint32_t run_len,
                              native_extent_t *extents, uint32_t *extent_count)
{
    uint32_t p = 0;
    uint64_t vcn = 0;
    int64_t lcn = 0;
    if (!run || !extents || !extent_count) {
        return 0;
    }
    *extent_count = 0;
    while (p < run_len && run[p]) {
        uint8_t head = run[p++];
        uint8_t len_size = head & 0x0F;
        uint8_t off_size = (head >> 4) & 0x0F;
        if (!len_size || len_size > 8 || off_size > 8 || p + len_size + off_size > run_len) {
            return 0;
        }
        uint64_t clusters = 0;
        for (uint8_t i = 0; i < len_size; i++) {
            clusters |= (uint64_t)run[p++] << (i * 8);
        }
        int64_t delta = 0;
        if (off_size) {
            uint64_t raw = 0;
            for (uint8_t i = 0; i < off_size; i++) {
                raw |= (uint64_t)run[p++] << (i * 8);
            }
            if (off_size < 8 && (raw & (1ULL << (off_size * 8 - 1)))) {
                raw |= (~0ULL << (off_size * 8));
            }
            delta = (int64_t)raw;
            lcn += delta;
        }
        if (clusters && *extent_count < NATIVE_MAX_EXTENTS) {
            extents[*extent_count].vcn = vcn;
            extents[*extent_count].lcn = off_size ? (uint64_t)lcn : 0;
            extents[*extent_count].clusters = clusters;
            extents[*extent_count].sparse = off_size ? 0 : 1;
            (*extent_count)++;
        }
        vcn += clusters;
    }
    return 1;
}

static int ntfs_read_extents(uint32_t volume, const native_extent_t *extents, uint32_t extent_count,
                             uint64_t offset, UINTN size, void *dst)
{
    volume_t *vol = &g_volumes[volume];
    uint8_t *out = (uint8_t *)dst;
    if (!dst || !vol->ntfs_cluster_size) {
        return 0;
    }
    while (size) {
        uint64_t vcn = offset / vol->ntfs_cluster_size;
        uint32_t in_cluster = (uint32_t)(offset % vol->ntfs_cluster_size);
        const native_extent_t *ex = 0;
        for (uint32_t i = 0; i < extent_count; i++) {
            if (vcn >= extents[i].vcn && vcn < extents[i].vcn + extents[i].clusters) {
                ex = &extents[i];
                break;
            }
        }
        if (!ex) {
            return 0;
        }
        uint64_t run_cluster = vcn - ex->vcn;
        UINTN take = vol->ntfs_cluster_size - in_cluster;
        uint64_t run_left = (ex->clusters - run_cluster) * (uint64_t)vol->ntfs_cluster_size - in_cluster;
        if (take > size) {
            take = size;
        }
        if (take > run_left) {
            take = (UINTN)run_left;
        }
        if (ex->sparse) {
            memset(out, 0, take);
        } else if (!native_read_volume_bytes(volume, ((ex->lcn + run_cluster) *
                   (uint64_t)vol->ntfs_cluster_size) + in_cluster, take, out)) {
            return 0;
        }
        out += take;
        offset += take;
        size -= take;
    }
    return 1;
}

static int ntfs_write_extents(uint32_t volume, const native_extent_t *extents, uint32_t extent_count,
                              uint64_t offset, UINTN size, const void *src)
{
    volume_t *vol = &g_volumes[volume];
    const uint8_t *in = (const uint8_t *)src;
    if (!src || !vol->ntfs_cluster_size) {
        return 0;
    }
    while (size) {
        uint64_t vcn = offset / vol->ntfs_cluster_size;
        uint32_t in_cluster = (uint32_t)(offset % vol->ntfs_cluster_size);
        const native_extent_t *ex = 0;
        for (uint32_t i = 0; i < extent_count; i++) {
            if (vcn >= extents[i].vcn && vcn < extents[i].vcn + extents[i].clusters) {
                ex = &extents[i];
                break;
            }
        }
        if (!ex || ex->sparse) {
            return 0;
        }
        uint64_t run_cluster = vcn - ex->vcn;
        UINTN take = vol->ntfs_cluster_size - in_cluster;
        uint64_t run_left = (ex->clusters - run_cluster) * (uint64_t)vol->ntfs_cluster_size - in_cluster;
        if (take > size) {
            take = size;
        }
        if (take > run_left) {
            take = (UINTN)run_left;
        }
        if (!native_write_volume_bytes(volume, ((ex->lcn + run_cluster) *
                    (uint64_t)vol->ntfs_cluster_size) + in_cluster, take, in)) {
            return 0;
        }
        in += take;
        offset += take;
        size -= take;
    }
    return 1;
}

static int ntfs_read_attr_bytes(uint32_t volume, uint64_t file_ref, uint32_t type,
                                uint8_t unnamed, uint64_t offset, UINTN size, void *dst);
static int ntfs_write_attr_bytes(uint32_t volume, uint64_t file_ref, uint32_t type,
                                 uint8_t unnamed, uint64_t offset, UINTN size, const void *src);
static const uint8_t *ntfs_find_attr(const uint8_t *rec, uint32_t rec_size, uint32_t type,
                                     uint8_t unnamed, uint32_t *attr_len);
static int ntfs_read_mft_record(uint32_t volume, uint64_t file_ref, uint8_t *rec);
static int ntfs_write_mft_record(uint32_t volume, uint64_t file_ref, const uint8_t *rec);
static void ntfs_update_record_filename_sizes(uint8_t *rec, uint32_t rec_size,
                                              uint64_t allocated_size, uint64_t real_size);
static int ntfs_enum_dir(uint32_t volume, uint64_t file_ref, native_dirent_t *entries, uint32_t *count);

static int ntfs_bitmap_byte(uint32_t volume, uint64_t bit, uint8_t *byte, uint64_t *byte_off)
{
    volume_t *vol = &g_volumes[volume];
    uint64_t off = bit / 8;
    if (!byte || !byte_off || off >= vol->ntfs_bitmap_size) {
        return 0;
    }
    if (!ntfs_read_attr_bytes(volume, 6, 0x80, 1, off, 1, byte)) {
        return 0;
    }
    *byte_off = off;
    return 1;
}

static int ntfs_set_volume_bitmap_range(uint32_t volume, uint64_t first_cluster,
                                        uint64_t clusters, uint8_t used)
{
    volume_t *vol = &g_volumes[volume];
    uint64_t total_clusters = vol->ntfs_sectors_per_cluster ?
        vol->ntfs_total_sectors / vol->ntfs_sectors_per_cluster : 0;
    if (!clusters || first_cluster + clusters > total_clusters) {
        return 0;
    }
    while (clusters) {
        uint64_t byte_off = first_cluster / 8;
        uint64_t bit_in_byte = first_cluster & 7;
        uint8_t b = 0;
        uint64_t tmp = 0;
        uint32_t take_bits = (uint32_t)(8 - bit_in_byte);
        if (take_bits > clusters) {
            take_bits = (uint32_t)clusters;
        }
        if (!ntfs_bitmap_byte(volume, first_cluster, &b, &tmp)) {
            return 0;
        }
        for (uint32_t i = 0; i < take_bits; i++) {
            uint8_t mask = (uint8_t)(1U << (bit_in_byte + i));
            if (used) {
                b |= mask;
            } else {
                b &= (uint8_t)~mask;
            }
        }
        if (!ntfs_write_attr_bytes(volume, 6, 0x80, 1, byte_off, 1, &b)) {
            return 0;
        }
        first_cluster += take_bits;
        clusters -= take_bits;
    }
    return 1;
}

static int ntfs_alloc_contiguous_clusters(uint32_t volume, uint64_t clusters, uint64_t *first_cluster)
{
    volume_t *vol = &g_volumes[volume];
    uint64_t total_clusters = vol->ntfs_sectors_per_cluster ?
        vol->ntfs_total_sectors / vol->ntfs_sectors_per_cluster : 0;
    uint64_t run_start = 0;
    uint64_t run_len = 0;
    uint64_t bitmap_bytes = (total_clusters + 7) / 8;
    if (!first_cluster || !clusters || !vol->ntfs_bitmap_size) {
        return 0;
    }
    if (bitmap_bytes > vol->ntfs_bitmap_size) {
        bitmap_bytes = vol->ntfs_bitmap_size;
    }
    for (uint64_t byte_off = 0; byte_off < bitmap_bytes; ) {
        UINTN take = sizeof(g_fs_sector_buffer);
        if (byte_off + take > bitmap_bytes) {
            take = (UINTN)(bitmap_bytes - byte_off);
        }
        if (!ntfs_read_attr_bytes(volume, 6, 0x80, 1, byte_off, take, g_fs_sector_buffer)) {
            return 0;
        }
        for (UINTN bi = 0; bi < take; bi++) {
            uint8_t b = g_fs_sector_buffer[bi];
            for (uint32_t bit = 0; bit < 8; bit++) {
                uint64_t c = byte_off * 8 + (uint64_t)bi * 8 + bit;
                if (c >= total_clusters) {
                    break;
                }
                if (!(b & (1U << bit))) {
                    if (!run_len) {
                        run_start = c;
                    }
                    run_len++;
                    if (run_len == clusters) {
                        if (!ntfs_set_volume_bitmap_range(volume, run_start, clusters, 1)) {
                            return 0;
                        }
                        *first_cluster = run_start;
                        return 1;
                    }
                } else {
                    run_len = 0;
                }
            }
        }
        byte_off += take;
    }
    return 0;
}

static void ntfs_free_extents(uint32_t volume, const native_extent_t *extents, uint32_t extent_count)
{
    for (uint32_t i = 0; i < extent_count; i++) {
        if (!extents[i].sparse && extents[i].clusters) {
            ntfs_set_volume_bitmap_range(volume, extents[i].lcn, extents[i].clusters, 0);
        }
    }
}

static int ntfs_read_attr_bytes(uint32_t volume, uint64_t file_ref, uint32_t type,
                                uint8_t unnamed, uint64_t offset, UINTN size, void *dst)
{
    uint32_t attr_len = 0;
    const uint8_t *attr;
    if (!dst || !ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer2)) {
        return 0;
    }
    attr = ntfs_find_attr(g_ntfs_record_buffer2, g_volumes[volume].ntfs_record_size,
                          type, unnamed, &attr_len);
    if (!attr) {
        return 0;
    }
    if (attr[8] == 0) {
        uint32_t val_len = le32(attr + 16);
        uint16_t val_off = le16(attr + 20);
        if (offset + size > val_len || val_off + offset + size > attr_len) {
            return 0;
        }
        memcpy(dst, attr + val_off + offset, size);
        return 1;
    }
    native_extent_t ext[NATIVE_MAX_EXTENTS];
    uint32_t ext_count = 0;
    uint16_t run_off = le16(attr + 32);
    uint64_t real_size = le64(attr + 48);
    if (offset + size > real_size || run_off >= attr_len ||
        !ntfs_parse_runlist(attr + run_off, attr_len - run_off, ext, &ext_count)) {
        return 0;
    }
    return ntfs_read_extents(volume, ext, ext_count, offset, size, dst);
}

static int ntfs_write_attr_bytes(uint32_t volume, uint64_t file_ref, uint32_t type,
                                 uint8_t unnamed, uint64_t offset, UINTN size, const void *src)
{
    uint32_t attr_len = 0;
    uint8_t *attr;
    if (!src || !ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer2)) {
        return 0;
    }
    attr = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer2, g_volumes[volume].ntfs_record_size,
                                     type, unnamed, &attr_len);
    if (!attr) {
        return 0;
    }
    if (attr[8] == 0) {
        uint32_t val_len = le32(attr + 16);
        uint16_t val_off = le16(attr + 20);
        if (offset + size > val_len || val_off + offset + size > attr_len) {
            return 0;
        }
        memcpy(attr + val_off + offset, src, size);
        return ntfs_write_mft_record(volume, file_ref, g_ntfs_record_buffer2);
    }
    native_extent_t ext[NATIVE_MAX_EXTENTS];
    uint32_t ext_count = 0;
    uint16_t run_off = le16(attr + 32);
    uint64_t real_size = le64(attr + 48);
    if (offset + size > real_size || run_off >= attr_len ||
        !ntfs_parse_runlist(attr + run_off, attr_len - run_off, ext, &ext_count)) {
        return 0;
    }
    return ntfs_write_extents(volume, ext, ext_count, offset, size, src);
}

static const uint8_t *ntfs_find_attr(const uint8_t *rec, uint32_t rec_size, uint32_t type,
                                     uint8_t unnamed, uint32_t *attr_len)
{
    uint32_t off = le16(rec + 20);
    while (off + 16 <= rec_size) {
        uint32_t atype = le32(rec + off);
        if (atype == 0xFFFFFFFFU) {
            break;
        }
        uint32_t len = le32(rec + off + 4);
        if (len < 16 || off + len > rec_size) {
            break;
        }
        uint8_t name_len = rec[off + 9];
        if (atype == type && (!unnamed || name_len == 0)) {
            if (attr_len) {
                *attr_len = len;
            }
            return rec + off;
        }
        off += len;
    }
    return 0;
}

static int ntfs_read_mft_record(uint32_t volume, uint64_t file_ref, uint8_t *rec)
{
    volume_t *vol = &g_volumes[volume];
    uint64_t off = file_ref * vol->ntfs_record_size;
    if (!rec || !vol->ntfs_record_size || vol->ntfs_record_size > 4096) {
        return 0;
    }
    if (vol->ntfs_mft_extent_count) {
        if (!ntfs_read_extents(volume, vol->ntfs_mft_extents, vol->ntfs_mft_extent_count,
                              off, vol->ntfs_record_size, rec)) {
            return 0;
        }
    } else {
        if (!native_read_volume_bytes(volume, vol->ntfs_mft_lcn * (uint64_t)vol->ntfs_cluster_size + off,
                                      vol->ntfs_record_size, rec)) {
            return 0;
        }
    }
    return ntfs_apply_fixup(rec, vol->ntfs_record_size, vol->ntfs_bytes_per_sector, "FILE");
}

static int ntfs_write_mft_record(uint32_t volume, uint64_t file_ref, const uint8_t *rec)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t size = vol->ntfs_record_size;
    if (!rec || !size || size > sizeof(g_fs_sector_buffer) || !vol->ntfs_bytes_per_sector) {
        return 0;
    }
    memcpy(g_fs_sector_buffer, rec, size);
    uint16_t usa_off = le16(g_fs_sector_buffer + 4);
    uint16_t usa_count = le16(g_fs_sector_buffer + 6);
    if (!usa_count || usa_off + (uint32_t)usa_count * 2 > size) {
        return 0;
    }
    uint16_t seq = (uint16_t)(le16(g_fs_sector_buffer + usa_off) + 1);
    if (!seq) {
        seq = 1;
    }
    put_le16(g_fs_sector_buffer + usa_off, seq);
    for (uint32_t i = 1; i < usa_count; i++) {
        uint32_t pos = i * vol->ntfs_bytes_per_sector - 2;
        if (pos + 2 > size) {
            return 0;
        }
        put_le16(g_fs_sector_buffer + usa_off + i * 2, le16(g_fs_sector_buffer + pos));
        put_le16(g_fs_sector_buffer + pos, seq);
    }
    int ok = ntfs_write_extents(volume, vol->ntfs_mft_extents, vol->ntfs_mft_extent_count,
                                file_ref * (uint64_t)vol->ntfs_record_size,
                                vol->ntfs_record_size, g_fs_sector_buffer);

    /* Mirror the first few system records into $MFTMirr (record 1) so that
     * Windows can recover if the primary $MFT copy is damaged.              */
    if (ok && file_ref <= 3) {
        uint32_t mirr_attr_len = 0;
        /* Read the $MFTMirr FILE record to locate its $DATA run-list.
         * Uses g_ntfs_record_buffer2 which is safe here: callers of
         * ntfs_write_mft_record have finished using it before this point. */
        if (ntfs_read_mft_record(volume, 1, g_ntfs_record_buffer2)) {
            const uint8_t *mirr_data = ntfs_find_attr(g_ntfs_record_buffer2,
                                                      vol->ntfs_record_size,
                                                      0x80, 1, &mirr_attr_len);
            if (mirr_data && mirr_data[8] != 0) {
                native_extent_t mirr_ext[NATIVE_MAX_EXTENTS];
                uint32_t mirr_ext_count = 0;
                uint16_t mirr_run_off = le16(mirr_data + 32);
                uint64_t mirr_real    = le64(mirr_data + 48);
                uint64_t mirror_off   = file_ref * (uint64_t)vol->ntfs_record_size;
                if (mirror_off + vol->ntfs_record_size <= mirr_real &&
                    mirr_run_off < mirr_attr_len &&
                    ntfs_parse_runlist(mirr_data + mirr_run_off,
                                       mirr_attr_len - mirr_run_off,
                                       mirr_ext, &mirr_ext_count)) {
                    /* g_fs_sector_buffer still holds the fixup-applied record */
                    ntfs_write_extents(volume, mirr_ext, mirr_ext_count,
                                       mirror_off, vol->ntfs_record_size,
                                       g_fs_sector_buffer);
                }
            }
        }
    }
    return ok;
}

static int ntfs_write_fixed_record_extents(uint32_t volume, const native_extent_t *extents,
                                           uint32_t extent_count, uint64_t offset,
                                           uint32_t size, uint8_t *rec)
{
    volume_t *vol = &g_volumes[volume];
    if (!rec || !size || size > sizeof(g_fs_sector_buffer) || !vol->ntfs_bytes_per_sector) {
        return 0;
    }
    memcpy(g_fs_sector_buffer, rec, size);
    uint16_t usa_off = le16(g_fs_sector_buffer + 4);
    uint16_t usa_count = le16(g_fs_sector_buffer + 6);
    if (!usa_count || usa_off + (uint32_t)usa_count * 2 > size) {
        return 0;
    }
    uint16_t seq = (uint16_t)(le16(g_fs_sector_buffer + usa_off) + 1);
    if (!seq) {
        seq = 1;
    }
    put_le16(g_fs_sector_buffer + usa_off, seq);
    for (uint32_t i = 1; i < usa_count; i++) {
        uint32_t pos = i * vol->ntfs_bytes_per_sector - 2;
        if (pos + 2 > size) {
            return 0;
        }
        put_le16(g_fs_sector_buffer + usa_off + i * 2, le16(g_fs_sector_buffer + pos));
        put_le16(g_fs_sector_buffer + pos, seq);
    }
    return ntfs_write_extents(volume, extents, extent_count, offset, size, g_fs_sector_buffer);
}

static uint32_t ntfs_attr_end_offset(const uint8_t *rec, uint32_t rec_size)
{
    uint32_t off = le16(rec + 20);
    while (off + 4 <= rec_size) {
        uint32_t type = le32(rec + off);
        if (type == 0xFFFFFFFFU) {
            return off;
        }
        if (off + 8 > rec_size) {
            break;
        }
        uint32_t len = le32(rec + off + 4);
        if (len < 16 || off + len > rec_size) {
            break;
        }
        off += len;
    }
    return 0;
}

static int ntfs_resize_attr(uint8_t *rec, uint32_t rec_size, uint32_t attr_off,
                            uint32_t old_len, uint32_t new_len)
{
    uint32_t used = le32(rec + 24);
    if (used < attr_off + old_len + 4 || used > rec_size) {
        uint32_t end = ntfs_attr_end_offset(rec, rec_size);
        if (!end) {
            return 0;
        }
        used = end + 4;
    }
    if (attr_off + old_len > used || attr_off + new_len + (used - attr_off - old_len) > rec_size) {
        return 0;
    }
    if (new_len != old_len) {
        memmove(rec + attr_off + new_len, rec + attr_off + old_len, used - attr_off - old_len);
        if (new_len > old_len) {
            memset(rec + attr_off + old_len, 0, new_len - old_len);
        }
        used = used - old_len + new_len;
        put_le32(rec + 24, used);
    }
    put_le32(rec + attr_off + 4, new_len);
    return 1;
}

static int ntfs_repair_directory_index_root_name(uint32_t volume, uint64_t file_ref)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t attr_len = 0;
    if (g_volumes[volume].read_only ||
        !ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer2)) {
        return 0;
    }
    if (!(le16(g_ntfs_record_buffer2 + 22) & 0x02)) {
        return 0;
    }
    uint8_t *root = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer2, vol->ntfs_record_size,
                                              0x90, 0, &attr_len);
    if (!root || root[8] != 0 || root[9] != 0) {
        return 0;
    }
    uint32_t val_len = le32(root + 16);
    uint16_t val_off = le16(root + 20);
    if (val_off + val_len > attr_len || val_off >= 32) {
        return 0;
    }
    uint32_t attr_off = (uint32_t)(root - g_ntfs_record_buffer2);
    uint32_t old_capacity = attr_len - val_off;
    uint32_t new_attr_len = align_u32(32 + old_capacity, 8);
    if (!ntfs_resize_attr(g_ntfs_record_buffer2, vol->ntfs_record_size,
                          attr_off, attr_len, new_attr_len)) {
        return 0;
    }
    root = g_ntfs_record_buffer2 + attr_off;
    memmove(root + 32, root + val_off, old_capacity);
    root[9] = 4;
    put_le16(root + 10, 24);
    put_le16(root + 20, 32);
    put_le16(root + 24, L'$');
    put_le16(root + 26, L'I');
    put_le16(root + 28, L'3');
    put_le16(root + 30, L'0');
    return ntfs_write_mft_record(volume, file_ref, g_ntfs_record_buffer2);
}

static uint64_t ntfs_attr_value_size(uint32_t volume, uint64_t file_ref,
                                     uint32_t type, uint8_t unnamed)
{
    uint32_t attr_len = 0;
    if (!ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer2)) {
        return 0;
    }
    const uint8_t *attr = ntfs_find_attr(g_ntfs_record_buffer2,
                                         g_volumes[volume].ntfs_record_size,
                                         type, unnamed, &attr_len);
    if (!attr) {
        return 0;
    }
    return attr[8] == 0 ? le32(attr + 16) : le64(attr + 48);
}

static int ntfs_read_standard_info(uint32_t volume, uint64_t file_ref, uint8_t *out, uint32_t out_len)
{
    uint32_t attr_len = 0;
    if (!out || out_len < 72 ||
        !ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer2)) {
        return 0;
    }
    const uint8_t *attr = ntfs_find_attr(g_ntfs_record_buffer2,
                                         g_volumes[volume].ntfs_record_size,
                                         0x10, 1, &attr_len);
    if (!attr || attr[8] != 0) {
        return 0;
    }
    uint32_t val_len = le32(attr + 16);
    uint16_t val_off = le16(attr + 20);
    if (val_off + val_len > attr_len || val_len < 48) {
        return 0;
    }
    memset(out, 0, out_len);
    if (val_len > out_len) {
        val_len = out_len;
    }
    memcpy(out, attr + val_off, val_len);
    return 1;
}

static uint32_t ntfs_security_id_from_record(uint32_t volume, uint64_t file_ref)
{
    uint8_t si[72];
    if (ntfs_read_standard_info(volume, file_ref, si, sizeof(si))) {
        return le32(si + 52);
    }
    return 0;
}

static uint32_t ntfs_child_security_id(uint32_t volume, uint64_t parent_ref)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t attr_len = 0;
    if (!ntfs_read_mft_record(volume, parent_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    const uint8_t *root = ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size, 0x90, 0, &attr_len);
    if (root && root[8] == 0) {
        uint32_t val_len = le32(root + 16);
        uint16_t val_off = le16(root + 20);
        if (val_off + val_len <= attr_len && val_len >= 32) {
            const uint8_t *ih = root + val_off + 16;
            uint32_t entries_off = le32(ih);
            uint32_t index_len = le32(ih + 4);
            uint32_t off = entries_off;
            while (entries_off < index_len && 16 + index_len <= val_len &&
                   off + 16 <= index_len) {
                const uint8_t *entry = ih + off;
                uint16_t len = le16(entry + 8);
                uint16_t flags = le16(entry + 12);
                if (len < 16 || off + len > index_len) {
                    break;
                }
                if (!(flags & 0x02)) {
                    uint64_t child_ref = le64(entry) & 0x0000FFFFFFFFFFFFULL;
                    uint32_t sec = ntfs_security_id_from_record(volume, child_ref);
                    if (sec) {
                        return sec;
                    }
                }
                if (flags & 0x02) {
                    break;
                }
                off += len;
            }
        }
    }
    const uint8_t *ia = ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size, 0xA0, 0, &attr_len);
    if (ia && ia[8] != 0 && vol->ntfs_index_record_size <= sizeof(g_fs_sector_buffer)) {
        native_extent_t ext[NATIVE_MAX_EXTENTS];
        uint32_t ext_count = 0;
        uint16_t run_off = le16(ia + 32);
        uint64_t real_size = le64(ia + 48);
        if (real_size > (uint64_t)vol->ntfs_index_record_size * 128ULL) {
            real_size = (uint64_t)vol->ntfs_index_record_size * 128ULL;
        }
        if (run_off < attr_len &&
            ntfs_parse_runlist(ia + run_off, attr_len - run_off, ext, &ext_count)) {
            for (uint64_t blk_off = 0; blk_off + vol->ntfs_index_record_size <= real_size;
                 blk_off += vol->ntfs_index_record_size) {
                if (!ntfs_read_extents(volume, ext, ext_count, blk_off,
                                       vol->ntfs_index_record_size, g_fs_sector_buffer) ||
                    !ntfs_apply_fixup(g_fs_sector_buffer, vol->ntfs_index_record_size,
                                      vol->ntfs_bytes_per_sector, "INDX")) {
                    continue;
                }
                const uint8_t *ih = g_fs_sector_buffer + 24;
                uint32_t entries_off = le32(ih);
                uint32_t index_len = le32(ih + 4);
                uint32_t off = entries_off;
                while (entries_off < index_len &&
                       24 + index_len <= vol->ntfs_index_record_size &&
                       off + 16 <= index_len) {
                    const uint8_t *entry = ih + off;
                    uint16_t len = le16(entry + 8);
                    uint16_t flags = le16(entry + 12);
                    if (len < 16 || off + len > index_len) {
                        break;
                    }
                    if (!(flags & 0x02)) {
                        uint64_t child_ref = le64(entry) & 0x0000FFFFFFFFFFFFULL;
                        uint32_t sec = ntfs_security_id_from_record(volume, child_ref);
                        if (sec) {
                            return sec;
                        }
                    }
                    if (flags & 0x02) {
                        break;
                    }
                    off += len;
                }
            }
        }
    }
    return 0;
}

static uint32_t ntfs_parent_security_id(uint32_t volume, uint64_t parent_ref)
{
    uint8_t si[72];
    if (ntfs_read_standard_info(volume, parent_ref, si, sizeof(si))) {
        uint32_t sec = le32(si + 52);
        if (sec) {
            return sec;
        }
    }
    uint32_t child_sec = ntfs_child_security_id(volume, parent_ref);
    if (child_sec) {
        return child_sec;
    }
    if (parent_ref != 5 && ntfs_read_standard_info(volume, 5, si, sizeof(si))) {
        uint32_t sec = le32(si + 52);
        if (sec) {
            return sec;
        }
    }
    if (parent_ref != 5) {
        child_sec = ntfs_child_security_id(volume, 5);
        if (child_sec) {
            return child_sec;
        }
    }
    return 0x00000100U;
}

static int ntfs_repair_record_security(uint32_t volume, uint64_t file_ref, uint64_t parent_ref)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t attr_len = 0;
    uint32_t security_id;
    if (g_volumes[volume].read_only || file_ref < 16 ||
        !ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer2)) {
        return 0;
    }
    uint8_t *si = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer2, vol->ntfs_record_size,
                                            0x10, 1, &attr_len);
    if (!si || si[8] != 0) {
        return 0;
    }
    uint32_t val_len = le32(si + 16);
    uint16_t val_off = le16(si + 20);
    if (val_off + val_len > attr_len || val_len < 72) {
        return 0;
    }
    security_id = ntfs_parent_security_id(volume, parent_ref);
    uint32_t current_id = le32(si + val_off + 52);
    if (current_id && !(current_id == 0x100U && security_id != current_id)) {
        return 0;
    }
    put_le32(si + val_off + 52, security_id);
    return ntfs_write_mft_record(volume, file_ref, g_ntfs_record_buffer2);
}

static CY_UNUSED uint32_t ntfs_existing_parent_security_id(uint32_t volume, uint64_t parent_ref)
{
    uint8_t si[72];
    if (ntfs_read_standard_info(volume, parent_ref, si, sizeof(si))) {
        uint32_t sec = le32(si + 52);
        if (sec) {
            return sec;
        }
    }
    uint32_t child_sec = ntfs_child_security_id(volume, parent_ref);
    if (child_sec) {
        return child_sec;
    }
    if (parent_ref != 5 && ntfs_read_standard_info(volume, 5, si, sizeof(si))) {
        uint32_t sec = le32(si + 52);
        if (sec) {
            return sec;
        }
    }
    if (parent_ref != 5) {
        child_sec = ntfs_child_security_id(volume, 5);
        if (child_sec) {
            return child_sec;
        }
    }
    return 0;
}

static CY_UNUSED uint32_t ntfs_read_resident_security_descriptor(uint32_t volume, uint64_t file_ref,
                                                       uint8_t *dst, uint32_t cap)
{
    uint32_t attr_len = 0;
    if (!dst || !cap ||
        !ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    const uint8_t *sd = ntfs_find_attr(g_ntfs_record_buffer,
                                       g_volumes[volume].ntfs_record_size,
                                       0x50, 1, &attr_len);
    if (!sd || sd[8] != 0) {
        return 0;
    }
    uint32_t val_len = le32(sd + 16);
    uint16_t val_off = le16(sd + 20);
    if (val_off + val_len > attr_len || val_len > cap || val_len < 20) {
        return 0;
    }
    memcpy(dst, sd + val_off, val_len);
    return val_len;
}

static uint64_t ntfs_record_reference_from_seq(uint64_t file_ref, uint16_t seq)
{
    return ((uint64_t)seq << 48) | (file_ref & 0x0000FFFFFFFFFFFFULL);
}

static uint64_t ntfs_make_file_ref(uint32_t volume, uint64_t file_ref)
{
    if (!ntfs_read_mft_record(volume, file_ref, g_fs_sector_buffer)) {
        return file_ref & 0x0000FFFFFFFFFFFFULL;
    }
    return ntfs_record_reference_from_seq(file_ref, le16(g_fs_sector_buffer + 16));
}

static uint32_t ntfs_build_filename_value(uint32_t volume, uint8_t *dst, uint64_t parent_ref,
                                          uint64_t allocated_size, uint64_t real_size,
                                          uint32_t attrs, const CHAR16 *name)
{
    uint32_t len = c16_len(name);
    if (!dst || !name || !name[0]) {
        return 0;
    }
    if (len > 255) {
        len = 255;
    }
    memset(dst, 0, 66 + len * 2);
    put_le64(dst, ntfs_make_file_ref(volume, parent_ref));
    /* Stamp creation/data-change/mft-change/access with current time (offsets
     * 8, 16, 24, 32 in $FILE_NAME).  Zero timestamps look like "1601-01-01"
     * to Windows and trip Attachment Manager into showing the Internet zone
     * warning when the file is opened.                                       */
    ntfs_put_timestamps(dst + 8, ntfs_time_now());
    put_le64(dst + 40, allocated_size);
    put_le64(dst + 48, real_size);
    put_le32(dst + 56, attrs);
    dst[64] = (uint8_t)len;
    dst[65] = 1;
    for (uint32_t i = 0; i < len; i++) {
        put_le16(dst + 66 + i * 2, name[i]);
    }
    return 66 + len * 2;
}

/* Build a permissive self-relative security descriptor that any local Windows
 * user can open without the "Şu an bu klasöre erişim izniniz yok / Devam"
 * UAC elevation prompt.  Owner is BUILTIN\Users (S-1-5-32-545) so the current
 * user — who is in that group — is treated as the owner; the DACL grants Full
 * Access to SYSTEM, Administrators, Users, Authenticated Users, and Everyone
 * with inheritance flags so child files/folders pick up the same rights.    */
static uint32_t ntfs_build_everyone_security_descriptor(uint8_t *dst, uint32_t cap)
{
    /* Sizes: header 20, owner SID (Users) 16, group SID (Users) 16, DACL ACL
     * header 8 + 5 ACEs (24+24+24+20+20 = 112) = 120, total = 172 bytes.    */
    if (!dst || cap < 172) {
        return 0;
    }
    memset(dst, 0, 172);

    /* SECURITY_DESCRIPTOR_RELATIVE header */
    dst[0] = 1;                              /* Revision */
    put_le16(dst + 2, 0x8004);               /* SE_SELF_RELATIVE | SE_DACL_PRESENT */
    put_le32(dst + 4,  20);                  /* OffsetOwner */
    put_le32(dst + 8,  36);                  /* OffsetGroup */
    put_le32(dst + 12, 0);                   /* OffsetSacl  */
    put_le32(dst + 16, 52);                  /* OffsetDacl  */

    /* Owner SID @ +20 — BUILTIN\Users (S-1-5-32-545), 16 bytes */
    uint8_t *sid = dst + 20;
    sid[0] = 1;  sid[1] = 2;  sid[7] = 5;
    put_le32(sid + 8,  32);
    put_le32(sid + 12, 545);

    /* Group SID @ +36 — BUILTIN\Users, 16 bytes */
    sid = dst + 36;
    sid[0] = 1;  sid[1] = 2;  sid[7] = 5;
    put_le32(sid + 8,  32);
    put_le32(sid + 12, 545);

    /* DACL @ +52 — ACL header (8 bytes) + 5 ACEs (112 bytes) = 120 bytes */
    uint8_t *acl = dst + 52;
    acl[0] = 2;                              /* ACL_REVISION */
    put_le16(acl + 2, 120);                  /* AclSize */
    put_le16(acl + 4, 5);                    /* AceCount */

    uint32_t off = 60;
    const uint32_t mask = 0x001F01FFU;       /* FILE_ALL_ACCESS */
    const uint8_t  flags = 0x03;             /* OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE */

    /* ACE 1 — BUILTIN\Administrators (S-1-5-32-544) Full Access (24 bytes) */
    dst[off + 0] = 0;                        /* ACCESS_ALLOWED_ACE_TYPE */
    dst[off + 1] = flags;
    put_le16(dst + off + 2, 24);
    put_le32(dst + off + 4, mask);
    sid = dst + off + 8;
    sid[0] = 1;  sid[1] = 2;  sid[7] = 5;
    put_le32(sid + 8,  32);
    put_le32(sid + 12, 544);
    off += 24;

    /* ACE 2 — BUILTIN\Users (S-1-5-32-545) Full Access (24 bytes) */
    dst[off + 0] = 0;
    dst[off + 1] = flags;
    put_le16(dst + off + 2, 24);
    put_le32(dst + off + 4, mask);
    sid = dst + off + 8;
    sid[0] = 1;  sid[1] = 2;  sid[7] = 5;
    put_le32(sid + 8,  32);
    put_le32(sid + 12, 545);
    off += 24;

    /* ACE 3 — NT AUTHORITY\SYSTEM (S-1-5-18) Full Access (20 bytes) */
    dst[off + 0] = 0;
    dst[off + 1] = flags;
    put_le16(dst + off + 2, 20);
    put_le32(dst + off + 4, mask);
    sid = dst + off + 8;
    sid[0] = 1;  sid[1] = 1;  sid[7] = 5;
    put_le32(sid + 8, 18);
    off += 20;

    /* ACE 4 — NT AUTHORITY\Authenticated Users (S-1-5-11) Full Access (20 bytes) */
    dst[off + 0] = 0;
    dst[off + 1] = flags;
    put_le16(dst + off + 2, 20);
    put_le32(dst + off + 4, mask);
    sid = dst + off + 8;
    sid[0] = 1;  sid[1] = 1;  sid[7] = 5;
    put_le32(sid + 8, 11);
    off += 20;

    /* ACE 5 — Everyone (S-1-1-0) Full Access (20 bytes) — closes the loop
     * for accounts that aren't in any of the named groups above.            */
    dst[off + 0] = 0;
    dst[off + 1] = flags;
    put_le16(dst + off + 2, 20);
    put_le32(dst + off + 4, mask);
    sid = dst + off + 8;
    sid[0] = 1;  sid[1] = 1;  sid[7] = 1;
    put_le32(sid + 8, 0);

    return 172;
}

static uint32_t ntfs_build_index_entry(uint32_t volume, uint8_t *dst, uint64_t file_ref,
                                       uint16_t seq, uint64_t parent_ref,
                                       uint64_t allocated_size, uint64_t real_size,
                                       uint32_t attrs, const CHAR16 *name)
{
    uint8_t fn[320];
    uint32_t fn_len = ntfs_build_filename_value(volume, fn, parent_ref,
                                                allocated_size, real_size, attrs, name);
    uint32_t entry_len = align_u32(16 + fn_len, 8);
    if (!dst || !fn_len || entry_len > 512) {
        return 0;
    }
    memset(dst, 0, entry_len);
    put_le64(dst, ntfs_record_reference_from_seq(file_ref, seq));
    put_le16(dst + 8, (uint16_t)entry_len);
    put_le16(dst + 10, (uint16_t)fn_len);
    put_le16(dst + 12, 0);
    memcpy(dst + 16, fn, fn_len);
    return entry_len;
}

static int ntfs_index_entry_name_compare(const uint8_t *a, const uint8_t *b)
{
    const uint8_t *afn = a + 16;
    const uint8_t *bfn = b + 16;
    uint16_t alen_bytes = le16(a + 10);
    uint16_t blen_bytes = le16(b + 10);
    uint8_t alen;
    uint8_t blen;
    uint8_t min;
    if (!a || !b || alen_bytes < 66 || blen_bytes < 66) {
        return 0;
    }
    alen = afn[64];
    blen = bfn[64];
    if (66 + alen * 2 > alen_bytes) {
        alen = (uint8_t)((alen_bytes - 66) / 2);
    }
    if (66 + blen * 2 > blen_bytes) {
        blen = (uint8_t)((blen_bytes - 66) / 2);
    }
    min = alen < blen ? alen : blen;
    for (uint32_t i = 0; i < min; i++) {
        CHAR16 ca = c16_ascii_upper(le16(afn + 66 + i * 2));
        CHAR16 cb = c16_ascii_upper(le16(bfn + 66 + i * 2));
        if (ca < cb) {
            return -1;
        }
        if (ca > cb) {
            return 1;
        }
    }
    if (alen < blen) {
        return -1;
    }
    if (alen > blen) {
        return 1;
    }
    return 0;
}

static int ntfs_index_entry_matches(const uint8_t *entry, uint64_t file_ref, const CHAR16 *name)
{
    uint16_t len = le16(entry + 8);
    uint16_t key_len = le16(entry + 10);
    uint64_t entry_ref = le64(entry) & 0x0000FFFFFFFFFFFFULL;
    if (!name) {
        return entry_ref == (file_ref & 0x0000FFFFFFFFFFFFULL);
    }
    if (file_ref && entry_ref != (file_ref & 0x0000FFFFFFFFFFFFULL)) {
        return 0;
    }
    if (key_len < 66 || len < 16 + key_len) {
        return 0;
    }
    const uint8_t *fn = entry + 16;
    uint8_t name_len = fn[64];
    if (66 + name_len * 2 > key_len || c16_len(name) != name_len) {
        return 0;
    }
    for (uint32_t i = 0; i < name_len; i++) {
        if (c16_ascii_upper(le16(fn + 66 + i * 2)) != c16_ascii_upper(name[i])) {
            return 0;
        }
    }
    return 1;
}

static int ntfs_insert_into_index_header(uint8_t *ih, uint32_t value_capacity,
                                         const uint8_t *entry, uint32_t entry_len)
{
    uint32_t entries_off = le32(ih);
    uint32_t index_len = le32(ih + 4);
    uint32_t alloc_size = le32(ih + 8);
    uint32_t insert_off;
    if (entries_off >= index_len || index_len > alloc_size ||
        alloc_size > value_capacity || !entry || !entry_len) {
        return 0;
    }
    insert_off = entries_off;
    while (insert_off + 16 <= index_len) {
        uint8_t *cur = ih + insert_off;
        uint16_t len = le16(cur + 8);
        uint16_t flags = le16(cur + 12);
        if (len < 16 || insert_off + len > index_len) {
            return 0;
        }
        if ((flags & 0x02) || ntfs_index_entry_name_compare(entry, cur) < 0) {
            break;
        }
        insert_off += len;
    }
    if (index_len + entry_len > alloc_size || index_len + entry_len > value_capacity) {
        return 0;
    }
    memmove(ih + insert_off + entry_len, ih + insert_off, index_len - insert_off);
    memcpy(ih + insert_off, entry, entry_len);
    put_le32(ih + 4, index_len + entry_len);
    return 1;
}

static int ntfs_update_index_header_entry(uint8_t *ih, uint32_t value_capacity,
                                          uint64_t file_ref, const CHAR16 *name,
                                          uint64_t allocated_size, uint64_t real_size)
{
    uint32_t entries_off = le32(ih);
    uint32_t index_len = le32(ih + 4);
    uint32_t off;
    if (entries_off >= index_len || index_len > value_capacity) {
        return 0;
    }
    off = entries_off;
    while (off + 16 <= index_len) {
        uint8_t *entry = ih + off;
        uint16_t len = le16(entry + 8);
        uint16_t key_len = le16(entry + 10);
        uint16_t flags = le16(entry + 12);
        if (len < 16 || off + len > index_len) {
            return 0;
        }
        if (!(flags & 0x02) && ntfs_index_entry_matches(entry, file_ref, name) &&
            key_len >= 66 && 16 + key_len <= len) {
            uint8_t *fn = entry + 16;
            /* $FILENAME layout (relative to fn):
             *   +0  : parent file reference (8 bytes)
             *   +8  : creation time        (8 bytes)
             *   +16 : alteration time      (8 bytes)  ← must NOT be overwritten
             *   +24 : MFT-changed time     (8 bytes)  ← must NOT be overwritten
             *   +32 : last-access time     (8 bytes)
             *   +40 : allocated size       (8 bytes)
             *   +48 : real/data size       (8 bytes)
             */
            put_le64(fn + 40, allocated_size);
            put_le64(fn + 48, real_size);
            return 1;
        }
        if (flags & 0x02) {
            break;
        }
        off += len;
    }
    return 0;
}

static int ntfs_remove_from_index_header(uint8_t *ih, uint32_t value_capacity,
                                         uint64_t file_ref, const CHAR16 *name)
{
    uint32_t entries_off = le32(ih);
    uint32_t index_len = le32(ih + 4);
    uint32_t off;
    if (entries_off >= index_len || index_len > value_capacity) {
        return 0;
    }
    off = entries_off;
    while (off + 16 <= index_len) {
        uint8_t *entry = ih + off;
        uint16_t len = le16(entry + 8);
        uint16_t flags = le16(entry + 12);
        if (len < 16 || off + len > index_len) {
            return 0;
        }
        if (!(flags & 0x02) && ntfs_index_entry_matches(entry, file_ref, name)) {
            memmove(entry, entry + len, index_len - off - len);
            put_le32(ih + 4, index_len - len);
            return 1;
        }
        if (flags & 0x02) {
            break;
        }
        off += len;
    }
    return 0;
}

static int ntfs_modify_resident_index_root(uint32_t volume, uint64_t parent_ref,
                                           const uint8_t *new_entry, uint32_t new_entry_len,
                                           uint64_t target_ref, const CHAR16 *target_name,
                                           uint64_t allocated_size, uint64_t real_size,
                                           uint8_t action)
{
    volume_t *vol = &g_volumes[volume];
    if (!ntfs_read_mft_record(volume, parent_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    uint32_t attr_len = 0;
    uint8_t *root = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size,
                                              0x90, 0, &attr_len);
    if (!root || root[8] != 0) {
        return 0;
    }
    uint32_t attr_off = (uint32_t)(root - g_ntfs_record_buffer);
    uint32_t val_len = le32(root + 16);
    uint16_t val_off = le16(root + 20);
    if (val_off + val_len > attr_len || val_len < 48) {
        return 0;
    }
    uint32_t capacity = attr_len - val_off;
    uint8_t *val = root + val_off;
    uint8_t *ih = val + 16;
    (void)capacity;
    if (action == 1) {
        if (ih[12] & 0x01) {
            return 0;
        }
        /* Match what Windows itself emits: keep allocated_size == index_length
         * and value_length == 16 + index_length.  Resize the resident attr up
         * front so the insert never has to fit into pre-existing slack — this
         * avoids the "INDEX_HEADER claims more buffer than the attribute
         * holds" inconsistency that makes Windows declare the dir corrupt.   */
        uint32_t old_index_len = le32(ih + 4);
        uint32_t new_index_len = old_index_len + new_entry_len;
        uint32_t need_attr = align_u32(val_off + 16 + new_index_len, 8);
        if (need_attr > attr_len) {
            if (!ntfs_resize_attr(g_ntfs_record_buffer, vol->ntfs_record_size,
                                  attr_off, attr_len, need_attr)) {
                return 0;
            }
            attr_len = need_attr;
            root = g_ntfs_record_buffer + attr_off;
            val_off = le16(root + 20);
            val = root + val_off;
            ih = val + 16;
        }
        put_le32(ih + 8, new_index_len);
        if (!ntfs_insert_into_index_header(ih, new_index_len, new_entry, new_entry_len)) {
            put_le32(ih + 8, old_index_len);
            return 0;
        }
        put_le32(root + 16, 16 + new_index_len);
    } else if (action == 2) {
        uint32_t cur_index_len = le32(ih + 4);
        if (!ntfs_update_index_header_entry(ih, cur_index_len, target_ref, target_name,
                                            allocated_size, real_size)) {
            return 0;
        }
    } else {
        uint32_t cur_index_len = le32(ih + 4);
        if (!ntfs_remove_from_index_header(ih, cur_index_len, target_ref, target_name)) {
            return 0;
        }
        uint32_t new_index_len = le32(ih + 4);
        put_le32(ih + 8, new_index_len);
        put_le32(root + 16, 16 + new_index_len);
    }
    return ntfs_write_mft_record(volume, parent_ref, g_ntfs_record_buffer);
}

static int ntfs_modify_index_allocation(uint32_t volume, uint64_t parent_ref,
                                        const uint8_t *new_entry, uint32_t new_entry_len,
                                        uint64_t target_ref, const CHAR16 *target_name,
                                        uint64_t allocated_size, uint64_t real_size,
                                        uint8_t action)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t attr_len = 0;
    native_extent_t ext[NATIVE_MAX_EXTENTS];
    uint32_t ext_count = 0;
    if (!ntfs_read_mft_record(volume, parent_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    const uint8_t *ia = ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size,
                                       0xA0, 0, &attr_len);
    if (!ia || ia[8] == 0) {
        return 0;
    }
    uint16_t run_off = le16(ia + 32);
    uint64_t real = le64(ia + 48);
    if (run_off >= attr_len ||
        !ntfs_parse_runlist(ia + run_off, attr_len - run_off, ext, &ext_count)) {
        return 0;
    }
    if (real > (uint64_t)vol->ntfs_index_record_size * 4096ULL) {
        real = (uint64_t)vol->ntfs_index_record_size * 4096ULL;
    }
    for (uint64_t off = 0; off + vol->ntfs_index_record_size <= real;
         off += vol->ntfs_index_record_size) {
        if (!ntfs_read_extents(volume, ext, ext_count, off,
                               vol->ntfs_index_record_size, g_fs_sector_buffer)) {
            break;
        }
        if (!ntfs_apply_fixup(g_fs_sector_buffer, vol->ntfs_index_record_size,
                              vol->ntfs_bytes_per_sector, "INDX")) {
            continue;
        }
        uint8_t *ih = g_fs_sector_buffer + 24;
        uint32_t entries_off = le32(ih);
        uint32_t index_len = le32(ih + 4);
        uint32_t alloc_size = le32(ih + 8);
        if (entries_off >= index_len || index_len > alloc_size ||
            24 + alloc_size > vol->ntfs_index_record_size) {
            continue;
        }
        int changed = 0;
        if (action == 1) {
            changed = ntfs_insert_into_index_header(ih, alloc_size, new_entry, new_entry_len);
        } else if (action == 2) {
            changed = ntfs_update_index_header_entry(ih, alloc_size, target_ref, target_name,
                                                     allocated_size, real_size);
        } else {
            changed = ntfs_remove_from_index_header(ih, alloc_size, target_ref, target_name);
        }
        if (changed) {
            return ntfs_write_fixed_record_extents(volume, ext, ext_count, off,
                                                   vol->ntfs_index_record_size,
                                                   g_fs_sector_buffer);
        }
    }
    return 0;
}

static int ntfs_insert_index_entry(uint32_t volume, uint64_t parent_ref, const uint8_t *entry,
                                   uint32_t entry_len)
{
    if (ntfs_modify_resident_index_root(volume, parent_ref, entry, entry_len,
                                        0, 0, 0, 0, 1)) {
        return 1;
    }
    return ntfs_modify_index_allocation(volume, parent_ref, entry, entry_len,
                                        0, 0, 0, 0, 1);
}

static int ntfs_update_parent_index_sizes(native_file_handle_t *h,
                                          uint64_t allocated_size, uint64_t real_size)
{
    if (!h || !h->ntfs_parent_ref || h->ntfs_file_ref < 16) {
        return 1;
    }
    if (ntfs_modify_resident_index_root(h->volume, h->ntfs_parent_ref, 0, 0,
                                        h->ntfs_file_ref, h->name,
                                        allocated_size, real_size, 2)) {
        return 1;
    }
    ntfs_modify_index_allocation(h->volume, h->ntfs_parent_ref, 0, 0,
                                 h->ntfs_file_ref, h->name,
                                 allocated_size, real_size, 2);
    return 1;
}

static int ntfs_remove_parent_index_entry(native_file_handle_t *h)
{
    if (!h || !h->ntfs_parent_ref || h->ntfs_file_ref < 16) {
        return 0;
    }
    if (ntfs_modify_resident_index_root(h->volume, h->ntfs_parent_ref, 0, 0,
                                        h->ntfs_file_ref, h->name, 0, 0, 3)) {
        return 1;
    }
    return ntfs_modify_index_allocation(h->volume, h->ntfs_parent_ref, 0, 0,
                                        h->ntfs_file_ref, h->name, 0, 0, 3);
}

static int ntfs_parent_has_name(uint32_t volume, uint64_t parent_ref,
                                const CHAR16 *name, uint64_t self_ref)
{
    uint32_t count = 0;
    if (!name || !ntfs_enum_dir(volume, parent_ref, g_native_dir_scratch, &count)) {
        return 0;
    }
    for (uint32_t i = 0; i < count; i++) {
        if (g_native_dir_scratch[i].ntfs_file_ref != self_ref &&
            c16_equal_ci(g_native_dir_scratch[i].pub.name, name)) {
            return 1;
        }
    }
    return 0;
}

static int ntfs_update_filename_attr(uint32_t volume, uint64_t file_ref, uint64_t parent_ref,
                                     const CHAR16 *new_name, uint64_t allocated_size,
                                     uint64_t real_size, uint32_t attrs)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t attr_len = 0;
    uint8_t fn_value[320];
    uint32_t fn_len;
    uint32_t new_attr_len;
    if (!new_name || !new_name[0] ||
        !ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    uint8_t *fn_attr = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size,
                                                 0x30, 1, &attr_len);
    if (!fn_attr || fn_attr[8] != 0) {
        return 0;
    }
    uint32_t attr_off = (uint32_t)(fn_attr - g_ntfs_record_buffer);
    uint16_t attr_id = le16(fn_attr + 14);
    uint8_t indexed_flag = fn_attr[22];
    /* Capture the existing 4 timestamps (creation, data-change, mft-change,
     * access) BEFORE we resize the attribute and clobber them — then preserve
     * them in the new value, only bumping last_mft_change_time to "now"
     * because the metadata (name) is what we just changed.                   */
    uint8_t old_times[32];
    int have_old_times = 0;
    {
        uint16_t old_val_off = le16(fn_attr + 20);
        uint32_t old_val_len = le32(fn_attr + 16);
        if (old_val_off + 40 <= attr_len && old_val_len >= 40) {
            memcpy(old_times, fn_attr + old_val_off + 8, 32);
            have_old_times = 1;
        }
    }
    fn_len = ntfs_build_filename_value(volume, fn_value, parent_ref,
                                       allocated_size, real_size, attrs, new_name);
    if (have_old_times && fn_len >= 40) {
        memcpy(fn_value + 8, old_times, 32);
        put_le64(fn_value + 24, ntfs_time_now()); /* last_mft_change_time */
    }
    new_attr_len = align_u32(24 + fn_len, 8);
    if (!fn_len || !ntfs_resize_attr(g_ntfs_record_buffer, vol->ntfs_record_size,
                                     attr_off, attr_len, new_attr_len)) {
        return 0;
    }
    fn_attr = g_ntfs_record_buffer + attr_off;
    memset(fn_attr, 0, new_attr_len);
    put_le32(fn_attr, 0x30);
    put_le32(fn_attr + 4, new_attr_len);
    fn_attr[8] = 0;
    put_le16(fn_attr + 14, attr_id);
    put_le32(fn_attr + 16, fn_len);
    put_le16(fn_attr + 20, 24);
    fn_attr[22] = indexed_flag;
    memcpy(fn_attr + 24, fn_value, fn_len);
    return ntfs_write_mft_record(volume, file_ref, g_ntfs_record_buffer);
}

static CY_UNUSED int ntfs_rename_handle(native_file_handle_t *h, const CHAR16 *new_name)
{
    uint32_t name_len = c16_len(new_name);
    CHAR16 old_name[96];
    uint8_t old_entry[512];
    uint8_t new_entry[512];
    uint32_t old_entry_len;
    uint32_t new_entry_len;
    uint32_t attrs;
    uint64_t allocated_size;
    uint16_t seq;
    if (!h || h->fs_type != NATIVE_FS_NTFS || h->ntfs_file_ref < 16 ||
        !h->ntfs_parent_ref || !new_name || !name_len || name_len > 95 ||
        c16_is_dotdot(new_name) || g_volumes[h->volume].read_only ||
        (h->attr & EFI_FILE_READ_ONLY)) {
        return 0;
    }
    if (ntfs_parent_has_name(h->volume, h->ntfs_parent_ref, new_name, h->ntfs_file_ref)) {
        return 0;
    }
    if (!ntfs_read_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer2)) {
        return 0;
    }
    seq = le16(g_ntfs_record_buffer2 + 16);
    c16_copy(old_name, h->name, sizeof(old_name) / sizeof(old_name[0]));
    attrs = h->is_dir ? 0x10000000U : 0x20U;
    if (h->attr & EFI_FILE_READ_ONLY) {
        attrs |= 0x01;
    }
    allocated_size = h->is_dir ? 0 : (h->ntfs_resident ? h->size : h->ntfs_allocated_size);
    /* Pull the file's existing $FILE_NAME timestamps out of the original
     * record so we can carry them through the rename instead of resetting
     * everything to "now".                                                   */
    uint8_t old_times[32];
    int have_old_times = 0;
    {
        uint32_t fn_attr_len = 0;
        const uint8_t *fn_old = ntfs_find_attr(g_ntfs_record_buffer2,
                                               g_volumes[h->volume].ntfs_record_size,
                                               0x30, 1, &fn_attr_len);
        if (fn_old && fn_old[8] == 0) {
            uint16_t fn_val_off = le16(fn_old + 20);
            uint32_t fn_val_len = le32(fn_old + 16);
            if (fn_val_off + 40 <= fn_attr_len && fn_val_len >= 40) {
                memcpy(old_times, fn_old + fn_val_off + 8, 32);
                have_old_times = 1;
            }
        }
    }
    old_entry_len = ntfs_build_index_entry(h->volume, old_entry, h->ntfs_file_ref, seq,
                                           h->ntfs_parent_ref, allocated_size, h->size,
                                           attrs, old_name);
    new_entry_len = ntfs_build_index_entry(h->volume, new_entry, h->ntfs_file_ref, seq,
                                           h->ntfs_parent_ref, allocated_size, h->size,
                                           attrs, new_name);
    if (!old_entry_len || !new_entry_len) {
        return 0;
    }
    /* Index entries embed a $FILE_NAME stream starting at offset 16 inside
     * the entry; offsets +8..+39 within that stream are the four timestamps.
     * Restore the originals on the rollback (old) entry exactly, and on the
     * new entry too — only bumping mft-change-time to "now".                 */
    if (have_old_times) {
        if (old_entry_len >= 56) {
            memcpy(old_entry + 24, old_times, 32);
        }
        if (new_entry_len >= 56) {
            memcpy(new_entry + 24, old_times, 32);
            put_le64(new_entry + 24 + 16, ntfs_time_now()); /* last_mft_change */
        }
    }
    if (!ntfs_remove_parent_index_entry(h)) {
        return 0;
    }
    if (!ntfs_update_filename_attr(h->volume, h->ntfs_file_ref, h->ntfs_parent_ref,
                                   new_name, allocated_size, h->size, attrs) ||
        !ntfs_insert_index_entry(h->volume, h->ntfs_parent_ref, new_entry, new_entry_len)) {
        ntfs_write_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer2);
        ntfs_insert_index_entry(h->volume, h->ntfs_parent_ref, old_entry, old_entry_len);
        return 0;
    }
    c16_copy(h->name, new_name, sizeof(h->name) / sizeof(h->name[0]));
    return 1;
}

static uint32_t ntfs_runlist_unsigned_size(uint64_t v)
{
    uint32_t n = 1;
    while (n < 8 && (v >> (n * 8))) {
        n++;
    }
    return n;
}

static uint32_t ntfs_runlist_signed_size(int64_t v)
{
    for (uint32_t n = 1; n < 8; n++) {
        int64_t min = -(1LL << (n * 8 - 1));
        int64_t max = (1LL << (n * 8 - 1)) - 1;
        if (v >= min && v <= max) {
            return n;
        }
    }
    return 8;
}

static uint32_t ntfs_encode_single_run(uint8_t *dst, uint64_t clusters, uint64_t lcn)
{
    uint32_t len_size = ntfs_runlist_unsigned_size(clusters);
    uint32_t off_size = ntfs_runlist_signed_size((int64_t)lcn);
    uint32_t p = 0;
    if (!dst || !clusters) {
        return 0;
    }
    dst[p++] = (uint8_t)((off_size << 4) | len_size);
    for (uint32_t i = 0; i < len_size; i++) {
        dst[p++] = (uint8_t)((clusters >> (i * 8)) & 0xFF);
    }
    for (uint32_t i = 0; i < off_size; i++) {
        dst[p++] = (uint8_t)((lcn >> (i * 8)) & 0xFF);
    }
    dst[p++] = 0;
    return p;
}

static int ntfs_zero_clusters(uint32_t volume, uint64_t first_cluster, uint64_t clusters)
{
    volume_t *vol = &g_volumes[volume];
    memset(g_fs_sector_buffer, 0, sizeof(g_fs_sector_buffer));
    for (uint64_t k = 0; k < clusters; k++) {
        uint64_t left = vol->ntfs_cluster_size;
        uint64_t off = 0;
        while (left) {
            UINTN take = left > sizeof(g_fs_sector_buffer) ? sizeof(g_fs_sector_buffer) : (UINTN)left;
            if (!native_write_volume_bytes(volume, (first_cluster + k) *
                                           (uint64_t)vol->ntfs_cluster_size + off,
                                           take, g_fs_sector_buffer)) {
                return 0;
            }
            off += take;
            left -= take;
        }
    }
    return 1;
}

static int ntfs_replace_data_attr_nonresident(native_file_handle_t *h,
                                              uint64_t first_cluster,
                                              uint64_t clusters,
                                              uint64_t real_size)
{
    volume_t *vol = &g_volumes[h->volume];
    uint32_t attr_len = 0;
    uint8_t *data;
    uint8_t run[32];
    uint32_t run_len = ntfs_encode_single_run(run, clusters, first_cluster);
    uint32_t new_len = align_u32(64 + run_len, 8);
    if (!run_len || !ntfs_read_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    data = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size,
                                     0x80, 1, &attr_len);
    if (!data) {
        return 0;
    }
    uint32_t attr_off = (uint32_t)(data - g_ntfs_record_buffer);
    uint16_t attr_id = le16(data + 14);
    if (!ntfs_resize_attr(g_ntfs_record_buffer, vol->ntfs_record_size,
                          attr_off, attr_len, new_len)) {
        return 0;
    }
    data = g_ntfs_record_buffer + attr_off;
    memset(data, 0, new_len);
    put_le32(data, 0x80);
    put_le32(data + 4, new_len);
    data[8] = 1;
    put_le16(data + 14, attr_id);
    put_le64(data + 16, 0);
    put_le64(data + 24, clusters - 1);
    put_le16(data + 32, 64);
    put_le64(data + 40, clusters * (uint64_t)vol->ntfs_cluster_size);
    put_le64(data + 48, real_size);
    put_le64(data + 56, real_size);
    memcpy(data + 64, run, run_len);
    ntfs_update_record_filename_sizes(g_ntfs_record_buffer, vol->ntfs_record_size,
                                      clusters * (uint64_t)vol->ntfs_cluster_size, real_size);
    if (!ntfs_write_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    h->ntfs_resident = 0;
    h->extent_count = 1;
    h->extents[0].vcn = 0;
    h->extents[0].lcn = first_cluster;
    h->extents[0].clusters = clusters;
    h->extents[0].sparse = 0;
    h->ntfs_allocated_size = clusters * (uint64_t)vol->ntfs_cluster_size;
    return 1;
}

static CY_UNUSED int ntfs_grow_file(native_file_handle_t *h, uint64_t wanted_size)
{
    volume_t *vol;
    uint64_t clusters;
    uint64_t first_cluster = 0;
    native_extent_t old_extents[NATIVE_MAX_EXTENTS];
    uint32_t old_extent_count = 0;
    uint8_t old_resident = 0;
    if (!h || h->fs_type != NATIVE_FS_NTFS || h->is_dir || !wanted_size) {
        return 0;
    }
    vol = &g_volumes[h->volume];
    clusters = (wanted_size + vol->ntfs_cluster_size - 1) / vol->ntfs_cluster_size;
    if (!clusters) {
        return 1;
    }
    if (!ntfs_alloc_contiguous_clusters(h->volume, clusters, &first_cluster)) {
        return 0;
    }
    if (!ntfs_zero_clusters(h->volume, first_cluster, clusters)) {
        ntfs_set_volume_bitmap_range(h->volume, first_cluster, clusters, 0);
        return 0;
    }
    native_extent_t new_ext;
    new_ext.vcn = 0;
    new_ext.lcn = first_cluster;
    new_ext.clusters = clusters;
    new_ext.sparse = 0;
    if (h->size) {
        uint64_t copied = 0;
        while (copied < h->size) {
            UINTN take = (h->size - copied) > sizeof(g_io_buffer) ? sizeof(g_io_buffer) : (UINTN)(h->size - copied);
            if (h->ntfs_resident) {
                memcpy(g_io_buffer, h->ntfs_resident_data + copied, take);
            } else if (!ntfs_read_extents(h->volume, h->extents, h->extent_count,
                                          copied, take, g_io_buffer)) {
                ntfs_set_volume_bitmap_range(h->volume, first_cluster, clusters, 0);
                return 0;
            }
            if (!ntfs_write_extents(h->volume, &new_ext, 1, copied, take, g_io_buffer)) {
                ntfs_set_volume_bitmap_range(h->volume, first_cluster, clusters, 0);
                return 0;
            }
            copied += take;
        }
    }
    old_resident = h->ntfs_resident;
    if (!old_resident) {
        old_extent_count = h->extent_count;
        for (uint32_t i = 0; i < old_extent_count; i++) {
            old_extents[i] = h->extents[i];
        }
    }
    if (!ntfs_replace_data_attr_nonresident(h, first_cluster, clusters, h->size)) {
        ntfs_set_volume_bitmap_range(h->volume, first_cluster, clusters, 0);
        return 0;
    }
    if (!old_resident) {
        ntfs_free_extents(h->volume, old_extents, old_extent_count);
    }
    ntfs_update_parent_index_sizes(h, h->ntfs_allocated_size, h->size);
    return 1;
}

static void ntfs_update_record_filename_sizes(uint8_t *rec, uint32_t rec_size,
                                              uint64_t allocated_size, uint64_t real_size)
{
    uint32_t off = le16(rec + 20);
    while (off + 16 <= rec_size) {
        uint32_t atype = le32(rec + off);
        if (atype == 0xFFFFFFFFU) {
            break;
        }
        uint32_t len = le32(rec + off + 4);
        if (len < 16 || off + len > rec_size) {
            break;
        }
        if (atype == 0x30 && rec[off + 8] == 0) {
            uint32_t val_len = le32(rec + off + 16);
            uint16_t val_off = le16(rec + off + 20);
            if (val_off + val_len <= len && val_len >= 56) {
                uint8_t *fn = rec + off + val_off;
                put_le64(fn + 40, allocated_size);
                put_le64(fn + 48, real_size);
            }
        }
        off += len;
    }
}

static CY_UNUSED int ntfs_update_data_size(native_file_handle_t *h, uint64_t new_size)
{
    volume_t *vol;
    uint32_t attr_len = 0;
    uint8_t *data;
    uint64_t index_allocated = 0;  /* 0 for resident; overridden below for non-resident */
    if (!h || h->fs_type != NATIVE_FS_NTFS || h->is_dir || h->ntfs_file_ref == 0) {
        return 0;
    }
    vol = &g_volumes[h->volume];
    if (!ntfs_read_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    data = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size, 0x80, 1, &attr_len);
    if (!data) {
        return 0;
    }
    if (data[8] == 0) {
        uint16_t val_off = le16(data + 20);
        uint32_t capacity = attr_len > val_off ? attr_len - val_off : 0;
        if (capacity > NTFS_MAX_RESIDENT_DATA) {
            capacity = NTFS_MAX_RESIDENT_DATA;
        }
        if (new_size > capacity) {
            return 0;
        }
        put_le32(data + 16, (uint32_t)new_size);
        /* Resident data: no clusters allocated, so allocated_size = 0 */
        ntfs_update_record_filename_sizes(g_ntfs_record_buffer, vol->ntfs_record_size, 0, new_size);
    } else {
        uint64_t allocated = le64(data + 40);
        if (new_size > allocated) {
            return 0;
        }
        put_le64(data + 48, new_size);
        put_le64(data + 56, new_size);
        ntfs_update_record_filename_sizes(g_ntfs_record_buffer, vol->ntfs_record_size, allocated, new_size);
        index_allocated = allocated;
    }
    if (!ntfs_write_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    h->size = new_size;
    if (h->ntfs_resident) {
        h->ntfs_resident_size = (uint32_t)new_size;
    }
    ntfs_update_parent_index_sizes(h, index_allocated, new_size);
    return 1;
}

static CY_UNUSED int ntfs_write_resident(native_file_handle_t *h, uint64_t offset, UINTN size, const void *src)
{
    volume_t *vol;
    uint32_t attr_len = 0;
    uint8_t *data;
    uint64_t end = offset + size;
    if (!h || !src || !h->ntfs_resident || end > h->ntfs_resident_capacity ||
        end > NTFS_MAX_RESIDENT_DATA) {
        return 0;
    }
    vol = &g_volumes[h->volume];
    if (!ntfs_read_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    data = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size, 0x80, 1, &attr_len);
    if (!data || data[8] != 0) {
        return 0;
    }
    uint16_t val_off = le16(data + 20);
    if (val_off + end > attr_len) {
        return 0;
    }
    memcpy(data + val_off + offset, src, size);
    if (end > h->size) {
        put_le32(data + 16, (uint32_t)end);
        /* Resident data has no cluster allocation, so allocated_size = 0 */
        ntfs_update_record_filename_sizes(g_ntfs_record_buffer, vol->ntfs_record_size, 0, end);
    }
    if (!ntfs_write_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    memcpy(h->ntfs_resident_data + offset, src, size);
    if (end > h->size) {
        h->size = end;
        h->ntfs_resident_size = (uint32_t)end;
        ntfs_update_parent_index_sizes(h, 0, end);
    }
    return 1;
}

static void ntfs_add_index_entry(const uint8_t *entry, uint32_t entry_len,
                                 native_dirent_t *entries, uint32_t *count)
{
    if (!entry || entry_len < 16 || !entries || !count || *count >= NATIVE_MAX_DIR_ENTRIES) {
        return;
    }
    uint16_t len = le16(entry + 8);
    uint16_t key_len = le16(entry + 10);
    uint16_t flags = le16(entry + 12);
    if ((flags & 0x02) || len < 16 || len > entry_len || key_len < 66 || 16 + key_len > len) {
        return;
    }
    const uint8_t *fn = entry + 16;
    uint8_t name_len = fn[64];
    uint8_t name_space = fn[65];
    if (!name_len || name_space == 2) {
        return;
    }
    native_dirent_t out;
    native_zero_dirent(&out);
    out.ntfs_file_ref = le64(entry) & 0x0000FFFFFFFFFFFFULL;
    uint32_t max_chars = sizeof(out.pub.name) / sizeof(out.pub.name[0]) - 1;
    if (name_len > max_chars) {
        name_len = (uint8_t)max_chars;
    }
    for (uint32_t i = 0; i < name_len; i++) {
        out.pub.name[i] = le16(fn + 66 + i * 2);
    }
    out.pub.name[name_len] = 0;
    out.pub.size = le64(fn + 48);
    uint32_t fattrs = le32(fn + 56);
    out.pub.attr = (fattrs & 0x10000000U) ? EFI_FILE_DIRECTORY : 0;
    if (fattrs & 0x01) {
        out.pub.attr |= EFI_FILE_READ_ONLY;
    }
    out.pub.is_dir = (fattrs & 0x10000000U) ? 1 : 0;
    native_add_dirent(entries, count, &out);
}

static void ntfs_parse_index_entries(uint32_t volume, uint64_t parent_ref,
                                     const uint8_t *base, uint32_t bytes,
                                     native_dirent_t *entries, uint32_t *count)
{
    uint32_t off = 0;
    while (off + 16 <= bytes && *count < NATIVE_MAX_DIR_ENTRIES) {
        uint16_t len = le16(base + off + 8);
        if (len < 16 || off + len > bytes) {
            break;
        }
        if (!(le16(base + off + 12) & 0x02)) {
            uint64_t child_ref = le64(base + off) & 0x0000FFFFFFFFFFFFULL;
            ntfs_repair_record_security(volume, child_ref, parent_ref);
        }
        ntfs_add_index_entry(base + off, len, entries, count);
        if (le16(base + off + 12) & 0x02) {
            break;
        }
        off += len;
    }
}

static int ntfs_enum_dir(uint32_t volume, uint64_t file_ref, native_dirent_t *entries, uint32_t *count)
{
    uint8_t *rec = g_ntfs_record_buffer;
    uint32_t attr_len = 0;
    if (!entries || !count) {
        return 0;
    }
    *count = 0;
    if (!ntfs_read_mft_record(volume, file_ref, rec)) {
        return 0;
    }
    if (ntfs_repair_directory_index_root_name(volume, file_ref)) {
        if (!ntfs_read_mft_record(volume, file_ref, rec)) {
            return 0;
        }
    }
    const uint8_t *root = ntfs_find_attr(rec, g_volumes[volume].ntfs_record_size, 0x90, 0, &attr_len);
    if (root && root[8] == 0) {
        uint32_t val_len = le32(root + 16);
        uint16_t val_off = le16(root + 20);
        if (val_off + val_len <= attr_len && val_len >= 32) {
            const uint8_t *val = root + val_off;
            const uint8_t *ih = val + 16;
            uint32_t entries_off = le32(ih);
            uint32_t index_len = le32(ih + 4);
            if (16 + entries_off <= val_len && entries_off < index_len && 16 + index_len <= val_len) {
                ntfs_parse_index_entries(volume, file_ref, ih + entries_off,
                                         index_len - entries_off, entries, count);
            }
        }
    }
    const uint8_t *ia = ntfs_find_attr(rec, g_volumes[volume].ntfs_record_size, 0xA0, 0, &attr_len);
    if (ia && ia[8] != 0 && g_volumes[volume].ntfs_index_record_size <= sizeof(g_fs_sector_buffer)) {
        native_extent_t ext[NATIVE_MAX_EXTENTS];
        uint32_t ext_count = 0;
        uint16_t run_off = le16(ia + 32);
        uint64_t real_size = le64(ia + 48);
        if (run_off < attr_len && ntfs_parse_runlist(ia + run_off, attr_len - run_off, ext, &ext_count)) {
            uint64_t max = real_size;
            if (max > (uint64_t)g_volumes[volume].ntfs_index_record_size * 256ULL) {
                max = (uint64_t)g_volumes[volume].ntfs_index_record_size * 256ULL;
            }
            for (uint64_t off = 0; off + g_volumes[volume].ntfs_index_record_size <= max &&
                                 *count < NATIVE_MAX_DIR_ENTRIES;
                 off += g_volumes[volume].ntfs_index_record_size) {
                if (!ntfs_read_extents(volume, ext, ext_count, off,
                                      g_volumes[volume].ntfs_index_record_size, g_fs_sector_buffer)) {
                    break;
                }
                if (!ntfs_apply_fixup(g_fs_sector_buffer, g_volumes[volume].ntfs_index_record_size,
                                      g_volumes[volume].ntfs_bytes_per_sector, "INDX")) {
                    continue;
                }
                const uint8_t *ih = g_fs_sector_buffer + 24;
                uint32_t entries_off = le32(ih);
                uint32_t index_len = le32(ih + 4);
                if (24 + entries_off <= g_volumes[volume].ntfs_index_record_size &&
                    entries_off < index_len &&
                    24 + index_len <= g_volumes[volume].ntfs_index_record_size) {
                    ntfs_parse_index_entries(volume, file_ref, ih + entries_off,
                                             index_len - entries_off, entries, count);
                }
            }
        }
    }
    return 1;
}

static int ntfs_set_mft_bitmap_bit(uint32_t volume, uint64_t file_ref, uint8_t used)
{
    uint64_t byte_off = file_ref / 8;
    uint8_t b = 0;
    uint8_t mask = (uint8_t)(1U << (file_ref & 7));
    uint64_t bitmap_size = ntfs_attr_value_size(volume, 0, 0xB0, 1);
    if (!bitmap_size || byte_off >= bitmap_size) {
        return 0;
    }
    if (!ntfs_read_attr_bytes(volume, 0, 0xB0, 1, byte_off, 1, &b)) {
        return 0;
    }
    if (used) {
        b |= mask;
    } else {
        b &= (uint8_t)~mask;
    }
    return ntfs_write_attr_bytes(volume, 0, 0xB0, 1, byte_off, 1, &b);
}

static int ntfs_alloc_mft_record(uint32_t volume, uint64_t *file_ref, uint16_t *seq)
{
    volume_t *vol = &g_volumes[volume];
    uint64_t bitmap_size = ntfs_attr_value_size(volume, 0, 0xB0, 1);
    uint64_t max_records = vol->ntfs_mft_record_count;
    if (!file_ref || !seq || !bitmap_size) {
        return 0;
    }
    if (!max_records || max_records > bitmap_size * 8) {
        max_records = bitmap_size * 8;
    }
    for (uint64_t byte_off = 2; byte_off < bitmap_size; ) {
        UINTN take = sizeof(g_fs_sector_buffer);
        if (byte_off + take > bitmap_size) {
            take = (UINTN)(bitmap_size - byte_off);
        }
        if (!ntfs_read_attr_bytes(volume, 0, 0xB0, 1, byte_off, take, g_fs_sector_buffer)) {
            return 0;
        }
        for (UINTN bi = 0; bi < take; bi++) {
            uint8_t b = g_fs_sector_buffer[bi];
            if (b == 0xFF) {
                continue;
            }
            for (uint32_t bit = 0; bit < 8; bit++) {
                uint64_t rec_no = (byte_off + bi) * 8 + bit;
                if (rec_no < 24 || rec_no >= max_records) {
                    continue;
                }
                if (!(b & (1U << bit))) {
                    if (!ntfs_set_mft_bitmap_bit(volume, rec_no, 1)) {
                        return 0;
                    }
                    *file_ref = rec_no;
                    *seq = 1;
                    if (ntfs_read_mft_record(volume, rec_no, g_ntfs_record_buffer2)) {
                        uint16_t old_seq = le16(g_ntfs_record_buffer2 + 16);
                        *seq = old_seq ? (uint16_t)(old_seq + 1) : 1;
                        if (!*seq) {
                            *seq = 1;
                        }
                    }
                    return 1;
                }
            }
        }
        byte_off += take;
    }
    return 0;
}

static int ntfs_append_resident_attr_named(uint8_t *rec, uint32_t rec_size, uint32_t *off,
                                           uint32_t type, uint16_t attr_id,
                                           const void *value, uint32_t value_len,
                                           uint32_t value_capacity,
                                           const CHAR16 *name, uint8_t name_len,
                                           uint8_t resident_flags)
{
    uint32_t cap = value_capacity > value_len ? value_capacity : value_len;
    uint16_t name_off = name_len ? 24 : 0;
    uint16_t val_off = (uint16_t)align_u32(24 + (uint32_t)name_len * 2, 8);
    uint32_t attr_len = align_u32((uint32_t)val_off + cap, 8);
    if (!rec || !off || *off + attr_len + 4 > rec_size) {
        return 0;
    }
    uint8_t *attr = rec + *off;
    memset(attr, 0, attr_len);
    put_le32(attr, type);
    put_le32(attr + 4, attr_len);
    attr[8] = 0;
    attr[9] = name_len;
    put_le16(attr + 10, name_off);
    put_le16(attr + 14, attr_id);
    put_le32(attr + 16, value_len);
    put_le16(attr + 20, val_off);
    attr[22] = resident_flags;
    for (uint32_t i = 0; i < name_len; i++) {
        put_le16(attr + name_off + i * 2, name[i]);
    }
    if (value && value_len) {
        memcpy(attr + val_off, value, value_len);
    }
    *off += attr_len;
    return 1;
}

static int ntfs_append_resident_attr(uint8_t *rec, uint32_t rec_size, uint32_t *off,
                                     uint32_t type, uint16_t attr_id,
                                     const void *value, uint32_t value_len,
                                     uint32_t value_capacity)
{
    return ntfs_append_resident_attr_named(rec, rec_size, off, type, attr_id,
                                           value, value_len, value_capacity, 0, 0, 0);
}

static int ntfs_build_empty_index_root(uint32_t volume, uint8_t *dst,
                                       uint32_t capacity, uint32_t *value_len)
{
    volume_t *vol = &g_volumes[volume];
    if (!dst || !value_len || capacity < 48) {
        return 0;
    }
    memset(dst, 0, capacity);
    put_le32(dst, 0x30);                   /* indexed attr type = $FILE_NAME */
    put_le32(dst + 4, 1);                  /* COLLATION_FILE_NAME */
    put_le32(dst + 8, vol->ntfs_index_record_size);
    /* clusters_per_index_record at +12 is a 1-byte SIGNED value; bytes 13..15
     * are reserved zeros.  When the record is smaller than a cluster the value
     * is encoded as -log2(bytes-per-record); otherwise it's the cluster count. */
    {
        int8_t enc;
        if (vol->ntfs_cluster_size && vol->ntfs_index_record_size >= vol->ntfs_cluster_size) {
            enc = (int8_t)(vol->ntfs_index_record_size / vol->ntfs_cluster_size);
        } else {
            int n = 0;
            uint32_t s = vol->ntfs_index_record_size;
            while (s > 1) { s >>= 1; n++; }
            enc = (int8_t)(-n);
        }
        dst[12] = (uint8_t)enc;
    }
    /* INDEX_HEADER (16 bytes) followed by a single END_ENTRY (16 bytes).
     * Match the layout Windows itself emits: allocated_size == index_length,
     * with the resident attribute's value_length set to exactly 16 + length. */
    uint8_t *ih = dst + 16;
    put_le32(ih, 16);              /* entries_offset = sizeof(INDEX_HEADER) */
    put_le32(ih + 4, 32);          /* index_length   = INDEX_HEADER + END_ENTRY */
    put_le32(ih + 8, 32);          /* allocated_size = index_length */
    ih[12] = 0;                    /* SMALL_INDEX flags */
    uint8_t *end = ih + 16;
    put_le16(end + 8, 16);         /* end-entry length */
    put_le16(end + 10, 0);         /* end-entry stream length */
    put_le16(end + 12, 0x02);      /* INDEX_ENTRY_END flag */
    *value_len = 48;
    return 1;
}

static int ntfs_build_file_record(uint32_t volume, uint64_t file_ref, uint16_t seq,
                                  uint64_t parent_ref, const CHAR16 *name,
                                  uint8_t is_dir, uint32_t security_id, uint8_t *rec)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t rec_size = vol->ntfs_record_size;
    uint16_t usa_count = (uint16_t)(rec_size / vol->ntfs_bytes_per_sector + 1);
    uint32_t first_attr = align_u32(0x30 + (uint32_t)usa_count * 2, 8);
    uint32_t off = first_attr;
    uint8_t std_info[72];
    uint8_t sec_desc[256];
    uint8_t fn_value[320];
    uint32_t fn_len;
    uint32_t sd_len;
    uint32_t std_info_len;
    uint32_t si_attrs = is_dir ? 0x10U : 0x20U;
    uint32_t fn_attrs = is_dir ? 0x10000000U : 0x20U;
    if (!rec || !name || !name[0] || !vol->ntfs_bytes_per_sector ||
        rec_size < 512 || rec_size > 4096 || first_attr + 4 > rec_size) {
        return 0;
    }
    /* Always emit our own permissive inline $SECURITY_DESCRIPTOR rather than
     * inheriting the parent's security_id.  On Windows-formatted removable
     * volumes the root's security_id resolves to a descriptor whose Owner is
     * BUILTIN\Administrators; a regular user opening a child created with the
     * inherited id is treated as "not the owner" and Windows shell pops the
     * "Şu an bu klasöre erişim izniniz yok / Devam" UAC prompt.  Our inline
     * SD has Owner = BUILTIN\Users and a Full-Access DACL for the common
     * accounts, which the current user always satisfies via group membership. */
    (void)security_id;
    security_id = 0;
    memset(rec, 0, rec_size);
    rec[0] = 'F'; rec[1] = 'I'; rec[2] = 'L'; rec[3] = 'E';
    put_le16(rec + 4, 0x30);
    put_le16(rec + 6, usa_count);
    put_le16(rec + 16, seq ? seq : 1);
    put_le16(rec + 18, 1);
    put_le16(rec + 20, (uint16_t)first_attr);
    put_le16(rec + 22, is_dir ? 0x03 : 0x01);
    put_le32(rec + 28, rec_size);
    put_le16(rec + 40, 4);
    put_le32(rec + 44, (uint32_t)file_ref);
    memset(std_info, 0, sizeof(std_info));
    /* $STANDARD_INFORMATION timestamps (offsets 0, 8, 16, 24).  Must be a
     * recent, non-zero time so Windows's Attachment Manager doesn't classify
     * the file as anomalous and pop the "Internet güvenlik ayarları" dialog. */
    ntfs_put_timestamps(std_info, ntfs_time_now());
    put_le32(std_info + 32, si_attrs);
    /* Skip storing security_id (offset 52) — leave it 0 so Windows uses the
     * inline $SECURITY_DESCRIPTOR attribute we attach below.                  */
    std_info_len = 48;
    if (!ntfs_append_resident_attr(rec, rec_size, &off, 0x10, 0,
                                   std_info, std_info_len, std_info_len)) {
        return 0;
    }
    sd_len = ntfs_build_everyone_security_descriptor(sec_desc, sizeof(sec_desc));
    if (!sd_len || !ntfs_append_resident_attr(rec, rec_size, &off, 0x50, 1,
                                              sec_desc, sd_len, sd_len)) {
        return 0;
    }
    fn_len = ntfs_build_filename_value(volume, fn_value, parent_ref, 0, 0, fn_attrs, name);
    if (!fn_len || !ntfs_append_resident_attr_named(rec, rec_size, &off, 0x30, 2,
                                                    fn_value, fn_len, fn_len, 0, 0, 1)) {
        return 0;
    }
    if (is_dir) {
        CHAR16 i30_name[5] = { L'$', L'I', L'3', L'0', 0 };
        uint32_t remain = off + 36 < rec_size ? rec_size - off - 36 : 0;
        uint32_t cap = remain > 512 ? 512 : (remain & ~7U);
        uint8_t root_value[512];
        uint32_t root_len = 0;
        if (!ntfs_build_empty_index_root(volume, root_value, cap, &root_len) ||
            !ntfs_append_resident_attr_named(rec, rec_size, &off, 0x90, 3,
                                             root_value, root_len, cap, i30_name, 4, 0)) {
            return 0;
        }
    } else {
        uint32_t remain = off + 28 < rec_size ? rec_size - off - 28 : 0;
        uint32_t cap = remain > NTFS_MAX_RESIDENT_DATA ? NTFS_MAX_RESIDENT_DATA : (remain & ~7U);
        if (!ntfs_append_resident_attr(rec, rec_size, &off, 0x80, 3, 0, 0, cap)) {
            return 0;
        }
    }
    if (off + 4 > rec_size) {
        return 0;
    }
    put_le32(rec + off, 0xFFFFFFFFU);
    put_le32(rec + 24, off + 4);
    return 1;
}

static int ntfs_resolve_parent(uint32_t volume, const CHAR16 *path,
                               uint64_t *parent_ref, CHAR16 *leaf, uint32_t leaf_max)
{
    const CHAR16 *p = path;
    CHAR16 comp[96];
    uint64_t dir_ref = 5;
    if (!parent_ref || !leaf || !c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]))) {
        return 0;
    }
    for (;;) {
        if (!c16_path_has_more(p)) {
            c16_copy(leaf, comp, leaf_max);
            *parent_ref = dir_ref;
            return leaf[0] && !c16_is_dotdot(leaf);
        }
        uint32_t count = 0;
        native_dirent_t next_dir;
        uint8_t found = 0;
        native_zero_dirent(&next_dir);
        if (!ntfs_enum_dir(volume, dir_ref, g_native_dir_scratch, &count)) {
            return 0;
        }
        for (uint32_t i = 0; i < count; i++) {
            if (g_native_dir_scratch[i].pub.is_dir &&
                c16_equal_ci(g_native_dir_scratch[i].pub.name, comp)) {
                next_dir = g_native_dir_scratch[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
        dir_ref = next_dir.ntfs_file_ref;
        c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]));
    }
}

static CY_UNUSED int ntfs_create_entry(uint32_t volume, const CHAR16 *path, uint64_t attr,
                             native_file_handle_t *h)
{
    uint64_t parent_ref = 0;
    uint64_t file_ref = 0;
    uint16_t seq = 1;
    CHAR16 name[96];
    uint8_t is_dir = (attr & EFI_FILE_DIRECTORY) ? 1 : 0;
    uint8_t index_entry[512];
    uint32_t entry_len;
    uint32_t ntfs_attrs = is_dir ? 0x10000000U : 0x20U;
    uint32_t security_id = 0;
    if (!h || !path || g_volumes[volume].read_only) {
        return 0;
    }
    if (!ntfs_resolve_parent(volume, path, &parent_ref, name, sizeof(name) / sizeof(name[0]))) {
        return 0;
    }
    ntfs_begin_modify(volume);
    if (!ntfs_alloc_mft_record(volume, &file_ref, &seq)) {
        return 0;
    }
    security_id = ntfs_parent_security_id(volume, parent_ref);
    if (!ntfs_build_file_record(volume, file_ref, seq, parent_ref, name, is_dir, security_id,
                                g_ntfs_record_buffer2) ||
        !ntfs_write_mft_record(volume, file_ref, g_ntfs_record_buffer2)) {
        ntfs_set_mft_bitmap_bit(volume, file_ref, 0);
        return 0;
    }
    entry_len = ntfs_build_index_entry(volume, index_entry, file_ref, seq, parent_ref,
                                       0, 0, ntfs_attrs, name);
    if (!entry_len || !ntfs_insert_index_entry(volume, parent_ref, index_entry, entry_len)) {
        put_le16(g_ntfs_record_buffer2 + 22, 0);
        ntfs_write_mft_record(volume, file_ref, g_ntfs_record_buffer2);
        ntfs_set_mft_bitmap_bit(volume, file_ref, 0);
        return 0;
    }
    c16_copy(h->name, name, sizeof(h->name) / sizeof(h->name[0]));
    h->is_dir = is_dir;
    h->attr = is_dir ? EFI_FILE_DIRECTORY : 0;
    h->can_write = is_dir ? 0 : 1;
    h->size = 0;
    h->ntfs_file_ref = file_ref;
    h->ntfs_parent_ref = parent_ref;
    h->ntfs_allocated_size = 0;
    h->ntfs_resident = is_dir ? 0 : 1;
    {
        uint64_t now = ntfs_time_now();
        h->ntfs_t_create = now;
        h->ntfs_t_modify = now;
        h->ntfs_t_access = now;
    }
    if (is_dir) {
        return ntfs_enum_dir(volume, file_ref, h->dirents, &h->dir_count);
    }
    if (!ntfs_read_mft_record(volume, file_ref, g_ntfs_record_buffer)) {
        return 0;
    }
    uint32_t data_len = 0;
    const uint8_t *data = ntfs_find_attr(g_ntfs_record_buffer, g_volumes[volume].ntfs_record_size,
                                         0x80, 1, &data_len);
    if (!data || data[8] != 0) {
        return 0;
    }
    uint16_t val_off = le16(data + 20);
    h->ntfs_resident_capacity = data_len > val_off ? data_len - val_off : 0;
    if (h->ntfs_resident_capacity > NTFS_MAX_RESIDENT_DATA) {
        h->ntfs_resident_capacity = NTFS_MAX_RESIDENT_DATA;
    }
    h->ntfs_allocated_size = h->ntfs_resident_capacity;
    h->ntfs_resident_size = 0;
    return 1;
}

static CY_UNUSED int ntfs_directory_is_empty(native_file_handle_t *h)
{
    uint32_t count = 0;
    if (!h || !h->is_dir) {
        return 0;
    }
    if (!ntfs_enum_dir(h->volume, h->ntfs_file_ref, g_native_dir_scratch, &count)) {
        return 0;
    }
    return count == 0;
}

static CY_UNUSED void ntfs_free_nonresident_attrs(uint32_t volume, const uint8_t *rec)
{
    uint32_t off = le16(rec + 20);
    uint32_t rec_size = g_volumes[volume].ntfs_record_size;
    while (off + 16 <= rec_size) {
        uint32_t atype = le32(rec + off);
        if (atype == 0xFFFFFFFFU) {
            break;
        }
        uint32_t len = le32(rec + off + 4);
        if (len < 16 || off + len > rec_size) {
            break;
        }
        if (rec[off + 8] != 0) {
            native_extent_t ext[NATIVE_MAX_EXTENTS];
            uint32_t ext_count = 0;
            uint16_t run_off = le16(rec + off + 32);
            if (run_off < len &&
                ntfs_parse_runlist(rec + off + run_off, len - run_off, ext, &ext_count)) {
                ntfs_free_extents(volume, ext, ext_count);
            }
        }
        off += len;
    }
}

static int ntfs_set_mft_fallback_extent(uint32_t volume)
{
    volume_t *vol = &g_volumes[volume];
    uint64_t total_clusters = vol->ntfs_sectors_per_cluster ?
                              vol->ntfs_total_sectors / vol->ntfs_sectors_per_cluster : 0;
    if (!total_clusters || vol->ntfs_mft_lcn >= total_clusters) {
        return 0;
    }
    vol->ntfs_mft_extents[0].vcn = 0;
    vol->ntfs_mft_extents[0].lcn = vol->ntfs_mft_lcn;
    vol->ntfs_mft_extents[0].clusters = total_clusters - vol->ntfs_mft_lcn;
    vol->ntfs_mft_extents[0].sparse = 0;
    vol->ntfs_mft_extent_count = 1;
    return 1;
}

/* Clear the VOLUME_IS_DIRTY flag in $Volume (MFT record 3) so that Windows
 * does not show a "scan and fix" dialog when it mounts the volume next time.  */
static void ntfs_clear_volume_dirty(uint32_t volume)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t attr_len = 0;
    if (!ntfs_read_mft_record(volume, 3, g_ntfs_record_buffer2)) {
        return;
    }
    uint8_t *vi = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer2,
                                            vol->ntfs_record_size, 0x70, 1, &attr_len);
    if (!vi || vi[8] != 0) {
        return; /* $VOLUME_INFORMATION must be resident */
    }
    uint32_t val_len = le32(vi + 16);
    uint16_t val_off = le16(vi + 20);
    /* value layout: 8 reserved + 1 major + 1 minor + 2 flags = 12 bytes minimum */
    if (val_len < 12 || val_off + 12 > attr_len) {
        return;
    }
    uint16_t flags = le16(vi + val_off + 10);
    if (!(flags & 0x0001U)) {
        return; /* already clean */
    }
    put_le16(vi + val_off + 10, (uint16_t)(flags & ~0x0001U));
    ntfs_write_mft_record(volume, 3, g_ntfs_record_buffer2);
}

/* Set the VOLUME_IS_DIRTY flag in $Volume so that, if we crash mid-write,
 * Windows will run CHKDSK on the next mount and repair our half-finished
 * structures rather than silently using them.  No-op if the flag was
 * already on (e.g. Windows itself left it dirty).                           */
static void ntfs_set_volume_dirty(uint32_t volume)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t attr_len = 0;
    if (!ntfs_read_mft_record(volume, 3, g_ntfs_record_buffer2)) {
        return;
    }
    uint8_t *vi = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer2,
                                            vol->ntfs_record_size, 0x70, 1, &attr_len);
    if (!vi || vi[8] != 0) {
        return;
    }
    uint32_t val_len = le32(vi + 16);
    uint16_t val_off = le16(vi + 20);
    if (val_len < 12 || val_off + 12 > attr_len) {
        return;
    }
    uint16_t flags = le16(vi + val_off + 10);
    if (flags & 0x0001U) {
        return; /* already dirty – not ours to clear later */
    }
    put_le16(vi + val_off + 10, (uint16_t)(flags | 0x0001U));
    if (ntfs_write_mft_record(volume, 3, g_ntfs_record_buffer2)) {
        vol->ntfs_dirty_owned = 1;
    }
}

/* Called from every NTFS modification entry point before any write goes out.
 * On the first call per modification batch we set the volume-dirty flag (so a
 * crash mid-write triggers CHKDSK) and remember that on flush we owe Windows
 * a $LogFile invalidate + dirty-clear.  Subsequent calls are cheap no-ops.   */
static void ntfs_begin_modify(uint32_t volume)
{
    if (volume >= g_volume_count) {
        return;
    }
    volume_t *vol = &g_volumes[volume];
    if (vol->native_fs != NATIVE_FS_NTFS || vol->read_only || vol->ntfs_modify_pending) {
        return;
    }
    vol->ntfs_modify_pending = 1;
    ntfs_set_volume_dirty(volume);
}

/* Write a valid "clean" RSTR restart page to both restart-page slots in
 * $LogFile (MFT record 2).  The key is to keep the RSTR magic intact but
 * set ClientInUseList = 0xFFFF (LOGFILE_NO_CLIENT) and clear the MOUNTED
 * flag so Windows treats the journal as containing no pending transactions
 * and mounts the volume without running CHKDSK.                             */
static void ntfs_invalidate_logfile(uint32_t volume)
{
    volume_t *vol = &g_volumes[volume];
    uint32_t attr_len = 0;
    native_extent_t ext[NATIVE_MAX_EXTENTS];
    uint32_t ext_count = 0;
    uint32_t page_size = 4096; /* overridden from first RSTR header */

    if (!ntfs_read_mft_record(volume, 2, g_ntfs_record_buffer2)) {
        return;
    }
    const uint8_t *data = ntfs_find_attr(g_ntfs_record_buffer2, vol->ntfs_record_size,
                                         0x80, 1, &attr_len);
    if (!data || data[8] == 0) {
        return; /* resident $LogFile would be extraordinary – skip */
    }
    uint16_t run_off      = le16(data + 32);
    uint64_t logfile_size = le64(data + 48);
    if (run_off >= attr_len ||
        !ntfs_parse_runlist(data + run_off, attr_len - run_off, ext, &ext_count)) {
        return;
    }

    /* Process both restart pages (at byte offset 0 and page_size). */
    for (int pass = 0; pass < 2; pass++) {
        uint64_t page_off  = (pass == 0) ? 0ULL : (uint64_t)page_size;
        uint32_t read_size = (page_size <= 4096u) ? page_size : 4096u;
        if (page_off + read_size > logfile_size) {
            break;
        }
        if (!ntfs_read_extents(volume, ext, ext_count, page_off, read_size,
                               g_ntfs_record_buffer)) {
            continue;
        }
        /* RSTR magic at offset 0 is never inside a USA-replaced position. */
        if (g_ntfs_record_buffer[0] != 'R' || g_ntfs_record_buffer[1] != 'S' ||
            g_ntfs_record_buffer[2] != 'T' || g_ntfs_record_buffer[3] != 'R') {
            continue;
        }
        /* On the first pass, get the actual SystemPageSize. */
        if (pass == 0) {
            uint32_t sys_ps = le32(g_ntfs_record_buffer + 16);
            if (sys_ps >= 512 && sys_ps <= 4096u) {
                page_size = sys_ps;
                if (page_size > read_size) {
                    read_size = page_size;
                    if (page_off + read_size > logfile_size) break;
                    if (!ntfs_read_extents(volume, ext, ext_count, page_off, read_size,
                                           g_ntfs_record_buffer)) continue;
                }
            }
        }

        uint16_t usa_off = le16(g_ntfs_record_buffer + 4);
        uint16_t usa_cnt = le16(g_ntfs_record_buffer + 6);
        uint16_t ra_off  = le16(g_ntfs_record_buffer + 24);
        if (!usa_cnt || usa_off + (uint32_t)usa_cnt * 2 > read_size) {
            continue;
        }

        /* Undo USA fixup so we can modify the logical restart area. */
        uint16_t old_seq = le16(g_ntfs_record_buffer + usa_off);
        for (uint16_t i = 1; i < usa_cnt; i++) {
            uint32_t pos = (uint32_t)i * vol->ntfs_bytes_per_sector - 2;
            if (pos + 2 > read_size) break;
            if (le16(g_ntfs_record_buffer + pos) == old_seq) {
                put_le16(g_ntfs_record_buffer + pos,
                         le16(g_ntfs_record_buffer + usa_off + i * 2));
            }
        }

        /* Mark the restart area as clean:
         *   CurrentLsn      = 0  (no pending log records)
         *   ClientInUseList = 0xFFFF (LOGFILE_NO_CLIENT = no active transactions)
         *   Flags           = 0  (clear RESTART_VOLUME_IS_MOUNTED)              */
        if (ra_off + 16 <= read_size) {
            put_le64(g_ntfs_record_buffer + ra_off +  0, 0);
            put_le16(g_ntfs_record_buffer + ra_off + 12, 0xFFFF);
            put_le16(g_ntfs_record_buffer + ra_off + 14, 0);
        }

        /* Re-apply USA fixup with an incremented sequence number. */
        uint16_t new_seq = (uint16_t)(old_seq + 1);
        if (!new_seq) new_seq = 1;
        put_le16(g_ntfs_record_buffer + usa_off, new_seq);
        for (uint16_t i = 1; i < usa_cnt; i++) {
            uint32_t pos = (uint32_t)i * vol->ntfs_bytes_per_sector - 2;
            if (pos + 2 > read_size) break;
            put_le16(g_ntfs_record_buffer + usa_off + i * 2,
                     le16(g_ntfs_record_buffer + pos));
            put_le16(g_ntfs_record_buffer + pos, new_seq);
        }

        ntfs_write_extents(volume, ext, ext_count, page_off, read_size, g_ntfs_record_buffer);
    }
}

static int ntfs_init_volume(uint32_t volume)
{
    uint8_t *bs = g_fs_sector_buffer;
    volume_t *vol = &g_volumes[volume];
    if (!native_read_volume_bytes(volume, 0, 512, bs)) {
        return 0;
    }
    if (!memeq_ascii(bs, 3, "NTFS    ", 8)) {
        return 0;
    }
    vol->ntfs_bytes_per_sector = le16(bs + 11);
    vol->ntfs_sectors_per_cluster = bs[13];
    vol->ntfs_cluster_size = vol->ntfs_bytes_per_sector * vol->ntfs_sectors_per_cluster;
    vol->ntfs_total_sectors = le64(bs + 40);
    vol->ntfs_mft_lcn = le64(bs + 48);
    int8_t rec_clusters = (int8_t)bs[64];
    int8_t idx_clusters = (int8_t)bs[68];
    if (rec_clusters < 0) {
        vol->ntfs_record_size = 1U << (uint8_t)(-rec_clusters);
    } else {
        vol->ntfs_record_size = (uint32_t)rec_clusters * vol->ntfs_cluster_size;
    }
    if (idx_clusters < 0) {
        vol->ntfs_index_record_size = 1U << (uint8_t)(-idx_clusters);
    } else {
        vol->ntfs_index_record_size = (uint32_t)idx_clusters * vol->ntfs_cluster_size;
    }
    if (!vol->ntfs_bytes_per_sector || !vol->ntfs_cluster_size ||
        vol->ntfs_record_size < 512 || vol->ntfs_record_size > 4096 ||
        vol->ntfs_index_record_size < 512 || vol->ntfs_index_record_size > sizeof(g_fs_sector_buffer)) {
        return 0;
    }
    vol->ntfs_mft_extent_count = 0;
    vol->ntfs_mft_record_count = 0;
    vol->ntfs_bitmap_extent_count = 0;
    vol->ntfs_bitmap_size = 0;
    if (!ntfs_read_mft_record(volume, 0, g_ntfs_record_buffer)) {
        return 0;
    }
    uint32_t attr_len = 0;
    const uint8_t *data = ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size, 0x80, 1, &attr_len);
    if (!data || data[8] == 0) {
        if (!ntfs_set_mft_fallback_extent(volume)) {
            return 0;
        }
    } else {
        uint16_t run_off = le16(data + 32);
        vol->ntfs_mft_record_count = le64(data + 48) / vol->ntfs_record_size;
        if (run_off >= attr_len ||
            !ntfs_parse_runlist(data + run_off, attr_len - run_off,
                                vol->ntfs_mft_extents, &vol->ntfs_mft_extent_count)) {
            if (!ntfs_set_mft_fallback_extent(volume)) {
                return 0;
            }
        }
    }
    if (!vol->ntfs_mft_extent_count) {
        if (!ntfs_set_mft_fallback_extent(volume)) {
            return 0;
        }
    }
    if (!vol->ntfs_mft_record_count) {
        uint64_t bytes = 0;
        for (uint32_t i = 0; i < vol->ntfs_mft_extent_count; i++) {
            bytes += vol->ntfs_mft_extents[i].clusters * (uint64_t)vol->ntfs_cluster_size;
        }
        vol->ntfs_mft_record_count = bytes / vol->ntfs_record_size;
    }
    if (ntfs_read_mft_record(volume, 6, g_ntfs_record_buffer)) {
        attr_len = 0;
        data = ntfs_find_attr(g_ntfs_record_buffer, vol->ntfs_record_size, 0x80, 1, &attr_len);
        if (data) {
            if (data[8] == 0) {
                vol->ntfs_bitmap_size = le32(data + 16);
            } else {
                vol->ntfs_bitmap_size = le64(data + 48);
                uint16_t run_off = le16(data + 32);
                if (run_off < attr_len) {
                    ntfs_parse_runlist(data + run_off, attr_len - run_off,
                                       vol->ntfs_bitmap_extents, &vol->ntfs_bitmap_extent_count);
                }
            }
        }
    }
    return 1;
}

static int native_init_volume(uint32_t volume)
{
    volume_t *vol = &g_volumes[volume];
    vol->native_ready = 0;
    vol->native_probe_failed = 0;
    vol->native_writable = 0;
    if (vol->native_fs == NATIVE_FS_EXFAT) {
        vol->native_ready = exfat_init_volume(volume) ? 1 : 0;
        vol->native_probe_failed = vol->native_ready ? 0 : NATIVE_FS_EXFAT;
        vol->native_writable = (vol->native_ready && !vol->read_only) ? 1 : 0;
        return vol->native_ready;
    }
    if (vol->native_fs == NATIVE_FS_NTFS) {
        vol->native_ready = ntfs_init_volume(volume) ? 1 : 0;
        vol->native_probe_failed = vol->native_ready ? 0 : NATIVE_FS_NTFS;
        vol->native_writable = (vol->native_ready && !vol->read_only &&
                                vol->ntfs_bitmap_size &&
                                ntfs_attr_value_size(volume, 0, 0xB0, 1)) ? 1 : 0;
        return vol->native_ready;
    }
    if (vol->native_fs == NATIVE_FS_RAW) {
        vol->native_ready = native_volume_size_bytes(volume) != 0 ? 1 : 0;
        vol->native_probe_failed = vol->native_ready ? 0 : NATIVE_FS_RAW;
        return vol->native_ready;
    }
    return 0;
}

static int native_ensure_ready(uint32_t volume)
{
    if (volume >= g_volume_count || g_volumes[volume].native_fs == NATIVE_FS_NONE) {
        return 0;
    }
    if (g_volumes[volume].native_ready) {
        return 1;
    }
    return native_init_volume(volume);
}

static void native_init_proto(native_file_handle_t *h);
static int native_open_file_by_path(uint32_t volume, const CHAR16 *path,
                                    EFI_FILE_PROTOCOL **file, uint64_t mode, uint64_t attr);

static int raw_open_native(native_file_handle_t *h, const CHAR16 *path)
{
    CHAR16 comp[96];
    const CHAR16 *p = path;
    if (!c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]))) {
        h->is_dir = 1;
        h->size = 0;
        h->attr = EFI_FILE_DIRECTORY;
        c16_from_ascii(h->name, "RAW", sizeof(h->name) / sizeof(h->name[0]));
        h->dir_count = 1;
        native_zero_dirent(&h->dirents[0]);
        c16_from_ascii(h->dirents[0].pub.name, "RAW_SECTORS.BIN",
                       sizeof(h->dirents[0].pub.name) / sizeof(h->dirents[0].pub.name[0]));
        h->dirents[0].pub.size = native_volume_size_bytes(h->volume);
        h->dirents[0].pub.attr = EFI_FILE_READ_ONLY;
        return 1;
    }
    if (c16_path_has_more(p)) {
        return 0;
    }
    CHAR16 raw_name[32];
    c16_from_ascii(raw_name, "RAW_SECTORS.BIN", sizeof(raw_name) / sizeof(raw_name[0]));
    if (!c16_equal_ci(comp, raw_name)) {
        return 0;
    }
    h->is_dir = 0;
    h->size = native_volume_size_bytes(h->volume);
    h->attr = EFI_FILE_READ_ONLY;
    c16_copy(h->name, raw_name, sizeof(h->name) / sizeof(h->name[0]));
    return 1;
}

static int exfat_open_native(native_file_handle_t *h, const CHAR16 *path)
{
    volume_t *vol = &g_volumes[h->volume];
    uint32_t dir_cluster = vol->exfat_root_cluster;
    uint8_t dir_nofat = 0;
    uint64_t dir_len = 0;
    CHAR16 comp[96];
    const CHAR16 *p = path;
    native_dirent_t found;
    native_zero_dirent(&found);
    if (!c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]))) {
        h->is_dir = 1;
        h->attr = EFI_FILE_DIRECTORY;
        c16_from_ascii(h->name, "ROOT", sizeof(h->name) / sizeof(h->name[0]));
        return exfat_enum_dir(h->volume, dir_cluster, dir_nofat, dir_len, h->dirents, &h->dir_count);
    }
    for (;;) {
        uint32_t tmp_count = 0;
        uint8_t got = 0;
        if (!exfat_enum_dir(h->volume, dir_cluster, dir_nofat, dir_len, g_native_dir_scratch, &tmp_count)) {
            return 0;
        }
        for (uint32_t i = 0; i < tmp_count; i++) {
            if (c16_equal_ci(g_native_dir_scratch[i].pub.name, comp)) {
                found = g_native_dir_scratch[i];
                got = 1;
                break;
            }
        }
        if (!got) {
            return 0;
        }
        if (!c16_path_has_more(p)) {
            c16_copy(h->name, found.pub.name, sizeof(h->name) / sizeof(h->name[0]));
            h->is_dir = found.pub.is_dir;
            h->size = found.pub.size;
            h->attr = found.pub.attr;
            h->can_write = (!h->is_dir && !g_volumes[h->volume].read_only &&
                            !(found.pub.attr & EFI_FILE_READ_ONLY)) ? 1 : 0;
            h->exfat_primary_offset = found.exfat_primary_offset;
            h->exfat_stream_offset = found.exfat_stream_offset;
            h->exfat_parent_cluster = found.exfat_parent_cluster;
            h->exfat_parent_no_fat = found.exfat_parent_no_fat;
            h->exfat_parent_len = found.exfat_parent_len;
            h->exfat_secondary_count = found.exfat_secondary_count;
            h->exfat_first_cluster = found.exfat_first_cluster;
            h->exfat_no_fat_chain = found.exfat_no_fat_chain;
            h->exfat_capacity = h->is_dir ? 0 :
                exfat_stream_capacity(h->volume, h->exfat_first_cluster,
                                      h->exfat_no_fat_chain, found.exfat_data_len);
            if (h->is_dir) {
                return exfat_enum_dir(h->volume, h->exfat_first_cluster, h->exfat_no_fat_chain,
                                      found.exfat_data_len, h->dirents, &h->dir_count);
            }
            return 1;
        }
        if (!found.pub.is_dir) {
            return 0;
        }
        dir_cluster = found.exfat_first_cluster;
        dir_nofat = found.exfat_no_fat_chain;
        dir_len = found.exfat_data_len;
        c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]));
    }
}

static int ntfs_open_native(native_file_handle_t *h, const CHAR16 *path)
{
    uint64_t dir_ref = 5;
    CHAR16 comp[96];
    const CHAR16 *p = path;
    native_dirent_t found;
    native_zero_dirent(&found);
    if (!c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]))) {
        h->is_dir = 1;
        h->attr = EFI_FILE_DIRECTORY;
        c16_from_ascii(h->name, "ROOT", sizeof(h->name) / sizeof(h->name[0]));
        return ntfs_enum_dir(h->volume, dir_ref, h->dirents, &h->dir_count);
    }
    for (;;) {
        uint32_t tmp_count = 0;
        uint8_t got = 0;
        if (!ntfs_enum_dir(h->volume, dir_ref, g_native_dir_scratch, &tmp_count)) {
            return 0;
        }
        for (uint32_t i = 0; i < tmp_count; i++) {
            if (c16_equal_ci(g_native_dir_scratch[i].pub.name, comp)) {
                found = g_native_dir_scratch[i];
                got = 1;
                break;
            }
        }
        if (!got) {
            return 0;
        }
        if (!c16_path_has_more(p)) {
            c16_copy(h->name, found.pub.name, sizeof(h->name) / sizeof(h->name[0]));
            h->is_dir = found.pub.is_dir;
            h->size = found.pub.size;
            h->attr = found.pub.attr;
            h->can_write = (!h->is_dir && !g_volumes[h->volume].read_only &&
                            !(found.pub.attr & EFI_FILE_READ_ONLY)) ? 1 : 0;
            h->ntfs_file_ref = found.ntfs_file_ref;
            h->ntfs_parent_ref = dir_ref;
            /* Snapshot $STANDARD_INFORMATION timestamps so GetInfo can return
             * them and copy/move can preserve the source's original times.   */
            if (ntfs_read_mft_record(h->volume, found.ntfs_file_ref, g_ntfs_record_buffer)) {
                uint32_t si_len = 0;
                const uint8_t *si = ntfs_find_attr(g_ntfs_record_buffer,
                                                   g_volumes[h->volume].ntfs_record_size,
                                                   0x10, 1, &si_len);
                if (si && si[8] == 0) {
                    uint16_t v_off = le16(si + 20);
                    uint32_t v_len = le32(si + 16);
                    if (v_off + 32 <= si_len && v_len >= 32) {
                        h->ntfs_t_create = le64(si + v_off + 0);
                        h->ntfs_t_modify = le64(si + v_off + 8);
                        h->ntfs_t_access = le64(si + v_off + 24);
                    }
                }
            }
            if (h->is_dir) {
                return ntfs_enum_dir(h->volume, found.ntfs_file_ref, h->dirents, &h->dir_count);
            }
            if (!ntfs_read_mft_record(h->volume, found.ntfs_file_ref, g_ntfs_record_buffer)) {
                return 0;
            }
            uint32_t attr_len = 0;
            const uint8_t *data = ntfs_find_attr(g_ntfs_record_buffer, g_volumes[h->volume].ntfs_record_size, 0x80, 1, &attr_len);
            if (!data) {
                h->size = 0;
                return 1;
            }
            if (data[8] == 0) {
                uint32_t val_len = le32(data + 16);
                uint16_t val_off = le16(data + 20);
                h->ntfs_resident = 1;
                h->ntfs_resident_size = val_len <= NTFS_MAX_RESIDENT_DATA ? val_len : NTFS_MAX_RESIDENT_DATA;
                h->ntfs_resident_capacity = attr_len > val_off ? attr_len - val_off : 0;
                if (h->ntfs_resident_capacity > NTFS_MAX_RESIDENT_DATA) {
                    h->ntfs_resident_capacity = NTFS_MAX_RESIDENT_DATA;
                }
                h->ntfs_allocated_size = h->ntfs_resident_capacity;
                h->size = val_len;
                if (val_off + h->ntfs_resident_size <= attr_len) {
                    memcpy(h->ntfs_resident_data, data + val_off, h->ntfs_resident_size);
                    return 1;
                }
                return 0;
            }
            uint16_t run_off = le16(data + 32);
            h->ntfs_allocated_size = le64(data + 40);
            h->size = le64(data + 48);
            if (run_off >= attr_len ||
                !ntfs_parse_runlist(data + run_off, attr_len - run_off, h->extents, &h->extent_count)) {
                return 0;
            }
            return 1;
        }
        if (!found.pub.is_dir) {
            return 0;
        }
        dir_ref = found.ntfs_file_ref;
        c16_next_component(&p, comp, sizeof(comp) / sizeof(comp[0]));
    }
}

static EFI_STATUS native_file_close(EFI_FILE_PROTOCOL *self)
{
    if (self && g_bs) {
        g_bs->FreePool(self);
    }
    return EFI_SUCCESS;
}

static EFI_STATUS native_file_delete(EFI_FILE_PROTOCOL *self)
{
    native_file_handle_t *h = (native_file_handle_t *)self;
    EFI_STATUS st = EFI_WRITE_PROTECTED;
    if (!h || h->magic != 0x43594653U) {
        return EFI_INVALID_PARAMETER;
    }
    if (h->fs_type == NATIVE_FS_EXFAT && h->exfat_parent_cluster &&
        !g_volumes[h->volume].read_only && !(h->attr & EFI_FILE_READ_ONLY)) {
        if (h->is_dir && !exfat_directory_is_empty(h)) {
            st = EFI_ACCESS_DENIED;
        } else if (!exfat_mark_entryset_deleted(h)) {
            st = EFI_DEVICE_ERROR;
        } else {
            exfat_free_handle_clusters(h);
            native_flush_volume(h->volume);
            st = EFI_SUCCESS;
        }
    }
    if (h->fs_type == NATIVE_FS_NTFS && h->ntfs_file_ref >= 16 &&
        !g_volumes[h->volume].read_only && !(h->attr & EFI_FILE_READ_ONLY)) {
        ntfs_begin_modify(h->volume);
        if (h->is_dir && !ntfs_directory_is_empty(h)) {
            st = EFI_ACCESS_DENIED;
        } else if (!ntfs_remove_parent_index_entry(h)) {
            st = EFI_DEVICE_ERROR;
        } else if (!ntfs_read_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer)) {
            st = EFI_DEVICE_ERROR;
        } else {
            ntfs_free_nonresident_attrs(h->volume, g_ntfs_record_buffer);
            uint16_t seq = (uint16_t)(le16(g_ntfs_record_buffer + 16) + 1);
            if (!seq) {
                seq = 1;
            }
            put_le16(g_ntfs_record_buffer + 16, seq);
            put_le16(g_ntfs_record_buffer + 22, 0);
            if (!ntfs_write_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer) ||
                !ntfs_set_mft_bitmap_bit(h->volume, h->ntfs_file_ref, 0)) {
                st = EFI_DEVICE_ERROR;
            } else {
                native_flush_volume(h->volume);
                st = EFI_SUCCESS;
            }
        }
    }
    native_file_close(self);
    return st;
}

static EFI_STATUS native_file_read(EFI_FILE_PROTOCOL *self, UINTN *size, void *buf)
{
    native_file_handle_t *h = (native_file_handle_t *)self;
    if (!h || h->magic != 0x43594653U || !size || !buf) {
        return EFI_INVALID_PARAMETER;
    }
    if (h->is_dir) {
        if (h->dir_pos >= h->dir_count) {
            *size = 0;
            return EFI_SUCCESS;
        }
        EFI_STATUS st = native_fill_file_info(&h->dirents[h->dir_pos].pub, size, buf);
        if (st == EFI_SUCCESS) {
            h->dir_pos++;
        }
        return st;
    }
    if (h->pos >= h->size) {
        *size = 0;
        return EFI_SUCCESS;
    }
    if (h->pos + *size > h->size) {
        *size = (UINTN)(h->size - h->pos);
    }
    if (!*size) {
        return EFI_SUCCESS;
    }
    int ok = 0;
    if (h->fs_type == NATIVE_FS_RAW) {
        ok = native_read_volume_bytes(h->volume, h->pos, *size, buf);
    } else if (h->fs_type == NATIVE_FS_EXFAT) {
        ok = exfat_read_stream(h->volume, h->exfat_first_cluster, h->exfat_no_fat_chain,
                               h->size, h->pos, *size, buf);
    } else if (h->fs_type == NATIVE_FS_NTFS) {
        if (h->ntfs_resident) {
            UINTN take = *size;
            if (h->pos + take > h->ntfs_resident_size) {
                take = h->pos < h->ntfs_resident_size ? (UINTN)(h->ntfs_resident_size - h->pos) : 0;
            }
            if (take) {
                memcpy(buf, h->ntfs_resident_data + h->pos, take);
            }
            if (take < *size) {
                memset((uint8_t *)buf + take, 0, *size - take);
            }
            ok = 1;
        } else {
            ok = ntfs_read_extents(h->volume, h->extents, h->extent_count, h->pos, *size, buf);
        }
    }
    if (!ok) {
        *size = 0;
        return EFI_DEVICE_ERROR;
    }
    h->pos += *size;
    return EFI_SUCCESS;
}

static EFI_STATUS native_file_write(EFI_FILE_PROTOCOL *self, UINTN *size, void *buf)
{
    native_file_handle_t *h = (native_file_handle_t *)self;
    if (!h || h->magic != 0x43594653U || !size || !buf) {
        return EFI_INVALID_PARAMETER;
    }
    if (!h->can_write || h->is_dir) {
        *size = 0;
        return EFI_WRITE_PROTECTED;
    }
    uint64_t end = h->pos + *size;
    if (h->fs_type == NATIVE_FS_NTFS) {
        int ok = 0;
        ntfs_begin_modify(h->volume);
        if (end > h->ntfs_allocated_size && !ntfs_grow_file(h, end)) {
            *size = 0;
            return EFI_OUT_OF_RESOURCES;
        }
        if (h->ntfs_resident) {
            ok = ntfs_write_resident(h, h->pos, *size, buf);
        } else {
            if (end <= h->ntfs_allocated_size &&
                ntfs_write_extents(h->volume, h->extents, h->extent_count, h->pos, *size, buf)) {
                ok = end <= h->size || ntfs_update_data_size(h, end);
            }
        }
        if (!ok) {
            *size = 0;
            return EFI_OUT_OF_RESOURCES;
        }
        h->pos = end;
        return EFI_SUCCESS;
    }
    if (h->fs_type != NATIVE_FS_EXFAT) {
        *size = 0;
        return EFI_WRITE_PROTECTED;
    }
    if (end > h->exfat_capacity) {
        if (!exfat_grow_file(h, end)) {
            *size = 0;
            return EFI_OUT_OF_RESOURCES;
        }
    }
    if (*size && !exfat_write_stream(h->volume, h->exfat_first_cluster, h->exfat_no_fat_chain,
                                     h->pos, *size, buf)) {
        *size = 0;
        return EFI_DEVICE_ERROR;
    }
    h->pos = end;
    if (end > h->size && !exfat_update_file_size(h, end)) {
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}

static EFI_STATUS native_file_get_position(EFI_FILE_PROTOCOL *self, uint64_t *pos)
{
    native_file_handle_t *h = (native_file_handle_t *)self;
    if (!h || !pos || h->magic != 0x43594653U) {
        return EFI_INVALID_PARAMETER;
    }
    *pos = h->pos;
    return EFI_SUCCESS;
}

static EFI_STATUS native_file_set_position(EFI_FILE_PROTOCOL *self, uint64_t pos)
{
    native_file_handle_t *h = (native_file_handle_t *)self;
    if (!h || h->magic != 0x43594653U) {
        return EFI_INVALID_PARAMETER;
    }
    h->pos = pos;
    return EFI_SUCCESS;
}

static EFI_STATUS native_file_get_info(EFI_FILE_PROTOCOL *self, EFI_GUID *guid, UINTN *size, void *buf)
{
    native_file_handle_t *h = (native_file_handle_t *)self;
    file_entry_t e;
    (void)guid;
    if (!h || h->magic != 0x43594653U) {
        return EFI_INVALID_PARAMETER;
    }
    memset(&e, 0, sizeof(e));
    c16_copy(e.name, h->name, sizeof(e.name) / sizeof(e.name[0]));
    e.size = h->size;
    e.attr = h->attr;
    e.is_dir = h->is_dir;
    if (h->fs_type == NATIVE_FS_NTFS) {
        e.t_create = h->ntfs_t_create;
        e.t_modify = h->ntfs_t_modify;
        e.t_access = h->ntfs_t_access;
    }
    return native_fill_file_info(&e, size, buf);
}

static EFI_STATUS native_file_set_info(EFI_FILE_PROTOCOL *self, EFI_GUID *guid, UINTN size, void *buf)
{
    (void)guid;
    native_file_handle_t *h = (native_file_handle_t *)self;
    if (!h || h->magic != 0x43594653U || !buf || size < offsetof(EFI_FILE_INFO, FileName)) {
        return EFI_INVALID_PARAMETER;
    }
    if (h->fs_type == NATIVE_FS_EXFAT) {
        EFI_FILE_INFO *info = (EFI_FILE_INFO *)buf;
        if (!c16_equal(info->FileName, h->name)) {
            if (exfat_rename_handle(h, info->FileName)) {
                native_flush_volume(h->volume);
                return EFI_SUCCESS;
            }
            return EFI_DEVICE_ERROR;
        }
        if (h->is_dir || !h->can_write) {
            return EFI_WRITE_PROTECTED;
        }
        if (info->FileSize <= h->exfat_capacity && exfat_update_file_size(h, info->FileSize)) {
            if (h->pos > h->size) {
                h->pos = h->size;
            }
            return EFI_SUCCESS;
        }
        return EFI_OUT_OF_RESOURCES;
    }
    if (h->fs_type == NATIVE_FS_NTFS) {
        EFI_FILE_INFO *info = (EFI_FILE_INFO *)buf;
        ntfs_begin_modify(h->volume);
        /* Apply caller-supplied timestamps (CreateTime/ModificationTime/
         * LastAccessTime) to $STANDARD_INFORMATION when they differ from the
         * cached values.  This is the path copy/move uses to transplant the
         * source file's original times onto the freshly-created destination
         * instead of leaving the destination stamped with "now".            */
        {
            uint64_t t_c = efi_time_to_ntfs_time((const EFI_TIME *)&info->CreateTime[0]);
            uint64_t t_m = efi_time_to_ntfs_time((const EFI_TIME *)&info->ModificationTime[0]);
            uint64_t t_a = efi_time_to_ntfs_time((const EFI_TIME *)&info->LastAccessTime[0]);
            int want_update = 0;
            if (t_c && t_c != h->ntfs_t_create) want_update = 1;
            if (t_m && t_m != h->ntfs_t_modify) want_update = 1;
            if (t_a && t_a != h->ntfs_t_access) want_update = 1;
            if (want_update && h->ntfs_file_ref >= 16 &&
                ntfs_read_mft_record(h->volume, h->ntfs_file_ref, g_ntfs_record_buffer)) {
                uint32_t si_len = 0;
                uint8_t *si = (uint8_t *)ntfs_find_attr(g_ntfs_record_buffer,
                                                       g_volumes[h->volume].ntfs_record_size,
                                                       0x10, 1, &si_len);
                if (si && si[8] == 0) {
                    uint16_t v_off = le16(si + 20);
                    uint32_t v_len = le32(si + 16);
                    if (v_off + 32 <= si_len && v_len >= 32) {
                        if (t_c) put_le64(si + v_off + 0,  t_c);
                        if (t_m) put_le64(si + v_off + 8,  t_m);
                        /* Bump last_mft_change_time to "now" — metadata changed. */
                        put_le64(si + v_off + 16, ntfs_time_now());
                        if (t_a) put_le64(si + v_off + 24, t_a);
                        if (ntfs_write_mft_record(h->volume, h->ntfs_file_ref,
                                                  g_ntfs_record_buffer)) {
                            if (t_c) h->ntfs_t_create = t_c;
                            if (t_m) h->ntfs_t_modify = t_m;
                            if (t_a) h->ntfs_t_access = t_a;
                        }
                    }
                }
            }
        }
        if (!c16_equal(info->FileName, h->name)) {
            if (ntfs_rename_handle(h, info->FileName)) {
                native_flush_volume(h->volume);
                return EFI_SUCCESS;
            }
            return EFI_DEVICE_ERROR;
        }
        if (h->is_dir || !h->can_write) {
            /* Allow timestamp-only updates on dirs/read-only files to succeed */
            return EFI_SUCCESS;
        }
        if (info->FileSize > h->ntfs_allocated_size && !ntfs_grow_file(h, info->FileSize)) {
            return EFI_OUT_OF_RESOURCES;
        }
        if (info->FileSize <= h->ntfs_allocated_size && ntfs_update_data_size(h, info->FileSize)) {
            if (h->pos > h->size) {
                h->pos = h->size;
            }
            return EFI_SUCCESS;
        }
        return EFI_OUT_OF_RESOURCES;
    }
    return EFI_WRITE_PROTECTED;
}

static EFI_STATUS native_file_flush(EFI_FILE_PROTOCOL *self)
{
    native_file_handle_t *h = (native_file_handle_t *)self;
    if (h && h->magic == 0x43594653U) {
        native_flush_volume(h->volume);
    }
    return EFI_SUCCESS;
}

static EFI_STATUS native_file_open(EFI_FILE_PROTOCOL *self, EFI_FILE_PROTOCOL **new_handle,
                                   CHAR16 *file_name, uint64_t mode, uint64_t attr)
{
    native_file_handle_t *h = (native_file_handle_t *)self;
    (void)attr;
    if (!h || !new_handle || h->magic != 0x43594653U) {
        return EFI_ACCESS_DENIED;
    }
    return native_open_file_by_path(h->volume, file_name, new_handle, mode, attr) ? EFI_SUCCESS : EFI_NOT_FOUND;
}

static void native_init_proto(native_file_handle_t *h)
{
    memset(h, 0, sizeof(*h));
    h->proto.Revision = 0x00010000;
    h->proto.Open = native_file_open;
    h->proto.Close = native_file_close;
    h->proto.Delete = native_file_delete;
    h->proto.Read = native_file_read;
    h->proto.Write = native_file_write;
    h->proto.GetPosition = native_file_get_position;
    h->proto.SetPosition = native_file_set_position;
    h->proto.GetInfo = native_file_get_info;
    h->proto.SetInfo = native_file_set_info;
    h->proto.Flush = native_file_flush;
    h->magic = 0x43594653U;
}

static int native_open_file_by_path(uint32_t volume, const CHAR16 *path,
                                    EFI_FILE_PROTOCOL **file, uint64_t mode, uint64_t attr)
{
    native_file_handle_t *h = 0;
    (void)attr;
    if (!file || volume >= g_volume_count || g_volumes[volume].native_fs == NATIVE_FS_NONE) {
        return 0;
    }
    *file = 0;
    if (!native_ensure_ready(volume)) {
        return 0;
    }
    if (g_bs->AllocatePool(EfiLoaderData, sizeof(native_file_handle_t), (void **)&h) != EFI_SUCCESS || !h) {
        return 0;
    }
    native_init_proto(h);
    h->volume = volume;
    h->fs_type = g_volumes[volume].native_fs;
    int ok = 0;
    if (h->fs_type == NATIVE_FS_RAW) {
        ok = raw_open_native(h, path);
    } else if (h->fs_type == NATIVE_FS_EXFAT) {
        ok = exfat_open_native(h, path);
        if (!ok && (mode & EFI_FILE_MODE_CREATE)) {
            ok = exfat_create_entry(volume, path, attr, h);
        }
    } else if (h->fs_type == NATIVE_FS_NTFS) {
        ok = ntfs_open_native(h, path);
        if (!ok && (mode & EFI_FILE_MODE_CREATE)) {
            ok = ntfs_create_entry(volume, path, attr, h);
        }
    }
    if (!ok) {
        g_bs->FreePool(h);
        return 0;
    }
    if (mode & (EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE)) {
        uint8_t create_dir_handle = ((mode & EFI_FILE_MODE_CREATE) &&
                                     (attr & EFI_FILE_DIRECTORY) && h->is_dir) ? 1 : 0;
        uint8_t delete_dir_handle = ((mode & EFI_FILE_MODE_WRITE) &&
                                     !(mode & EFI_FILE_MODE_CREATE) && h->is_dir) ? 1 : 0;
        if (h->fs_type != NATIVE_FS_EXFAT && h->fs_type != NATIVE_FS_NTFS) {
            g_bs->FreePool(h);
            return 0;
        }
        if ((!h->can_write || h->is_dir) && !create_dir_handle && !delete_dir_handle) {
            g_bs->FreePool(h);
            return 0;
        }
    }
    *file = &h->proto;
    return 1;
}

static int memory_type_is_ram(uint32_t type)
{
    return (type >= 1 && type <= 7) || type == 9 || type == 10 || type == 13 || type == 14;
}

static void connect_all_controllers(void)
{
    if (!g_bs->LocateHandle || !g_bs->ConnectController) {
        return;
    }
    UINTN size = 0;
    EFI_STATUS st = g_bs->LocateHandle(AllHandles, 0, 0, &size, 0);
    if (st != EFI_BUFFER_TOO_SMALL || !size) {
        return;
    }
    EFI_HANDLE *handles = 0;
    if (g_bs->AllocatePool(EfiLoaderData, size, (void **)&handles) != EFI_SUCCESS || !handles) {
        return;
    }
    st = g_bs->LocateHandle(AllHandles, 0, 0, &size, handles);
    if (st == EFI_SUCCESS) {
        UINTN count = size / sizeof(EFI_HANDLE);
        for (UINTN i = 0; i < count; i++) {
            g_bs->ConnectController(handles[i], 0, 0, 1);
        }
    }
    g_bs->FreePool(handles);
}

static int c16_ends_with_efi(const CHAR16 *name)
{
    uint32_t n = c16_len(name);
    if (n < 3) {
        return 0;
    }
    if (n >= 4 && name[n - 4] == L'.' &&
        c16_ascii_upper(name[n - 3]) == L'E' &&
        c16_ascii_upper(name[n - 2]) == L'F' &&
        c16_ascii_upper(name[n - 1]) == L'I') {
        return 1;
    }
    return c16_ascii_upper(name[n - 3]) == L'E' &&
           c16_ascii_upper(name[n - 2]) == L'F' &&
           c16_ascii_upper(name[n - 1]) == L'I';
}

static uint16_t device_path_node_len(const EFI_DEVICE_PATH_PROTOCOL *dp)
{
    return dp ? (uint16_t)(dp->Length[0] | ((uint16_t)dp->Length[1] << 8)) : 0;
}

static uint32_t device_path_size(const EFI_DEVICE_PATH_PROTOCOL *dp)
{
    uint32_t total = 0;
    while (dp && total < 4096) {
        uint16_t len = device_path_node_len(dp);
        if (len < 4) {
            return 0;
        }
        total += len;
        if (dp->Type == 0x7F && dp->SubType == 0xFF) {
            return total;
        }
        dp = (const EFI_DEVICE_PATH_PROTOCOL *)((const uint8_t *)dp + len);
    }
    return 0;
}

static EFI_DEVICE_PATH_PROTOCOL *handle_device_path(EFI_HANDLE handle)
{
    EFI_DEVICE_PATH_PROTOCOL *dp = 0;
    EFI_STATUS st;
    if (!handle) {
        return 0;
    }
    st = g_bs->OpenProtocol(handle, (EFI_GUID *)&DevicePathGuid, (void **)&dp,
                            g_image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (st != EFI_SUCCESS) {
        st = g_bs->HandleProtocol(handle, (EFI_GUID *)&DevicePathGuid, (void **)&dp);
    }
    return (st == EFI_SUCCESS) ? dp : 0;
}

static int device_path_has_prefix(const EFI_DEVICE_PATH_PROTOCOL *child,
                                  const EFI_DEVICE_PATH_PROTOCOL *parent)
{
    uint32_t child_size = device_path_size(child);
    uint32_t parent_size = device_path_size(parent);
    if (child_size < 4 || parent_size < 4) {
        return 0;
    }
    uint32_t parent_no_end = parent_size - 4;
    if (child_size < parent_no_end + 4) {
        return 0;
    }
    return memcmp(child, parent, parent_no_end) == 0;
}

static uint32_t find_block_for_fs_handle(EFI_HANDLE fs_handle, uint32_t media_id)
{
    uint32_t best = 0xFFFFFFFFU;
    uint32_t best_dp_size = 0;
    EFI_DEVICE_PATH_PROTOCOL *fs_dp = 0;
    for (uint32_t bi = 0; bi < g_block_count; bi++) {
        if (!g_blocks[bi].present) {
            continue;
        }
        if (g_blocks[bi].handle == fs_handle) {
            return bi;
        }
        if (media_id && g_blocks[bi].logical_partition &&
            g_blocks[bi].media_id == media_id) {
            best = bi;
        }
    }
    fs_dp = handle_device_path(fs_handle);
    if (!fs_dp) {
        return best;
    }
    for (uint32_t bi = 0; bi < g_block_count; bi++) {
        if (!g_blocks[bi].present || !g_blocks[bi].logical_partition) {
            continue;
        }
        EFI_DEVICE_PATH_PROTOCOL *block_dp = handle_device_path(g_blocks[bi].handle);
        uint32_t block_dp_size = device_path_size(block_dp);
        if (block_dp && block_dp_size > best_dp_size &&
            device_path_has_prefix(fs_dp, block_dp)) {
            best = bi;
            best_dp_size = block_dp_size;
        }
    }
    return best;
}

static EFI_DEVICE_PATH_PROTOCOL *build_driver_file_device_path(EFI_HANDLE fs_handle,
                                                               const CHAR16 *full_path)
{
    EFI_DEVICE_PATH_PROTOCOL *base = 0;
    uint32_t base_size;
    uint32_t base_no_end;
    uint32_t path_chars;
    uint16_t file_node_len;
    uint32_t total;
    uint8_t *out = 0;
    if (!fs_handle || !full_path) {
        return 0;
    }
    base = handle_device_path(fs_handle);
    if (!base) {
        return 0;
    }
    base_size = device_path_size(base);
    if (base_size < 4) {
        return 0;
    }
    path_chars = c16_len(full_path) + 1;
    file_node_len = (uint16_t)(4 + path_chars * sizeof(CHAR16));
    base_no_end = base_size - 4;
    total = base_no_end + file_node_len + 4;
    if (g_bs->AllocatePool(EfiLoaderData, total, (void **)&out) != EFI_SUCCESS || !out) {
        return 0;
    }
    memcpy(out, base, base_no_end);
    EFI_DEVICE_PATH_PROTOCOL *fp = (EFI_DEVICE_PATH_PROTOCOL *)(out + base_no_end);
    fp->Type = 0x04;
    fp->SubType = 0x04;
    fp->Length[0] = (uint8_t)(file_node_len & 0xFF);
    fp->Length[1] = (uint8_t)(file_node_len >> 8);
    memcpy(out + base_no_end + 4, full_path, path_chars * sizeof(CHAR16));
    EFI_DEVICE_PATH_PROTOCOL *end = (EFI_DEVICE_PATH_PROTOCOL *)(out + base_no_end + file_node_len);
    end->Type = 0x7F;
    end->SubType = 0xFF;
    end->Length[0] = 4;
    end->Length[1] = 0;
    return (EFI_DEVICE_PATH_PROTOCOL *)out;
}

static void remember_fs_driver_handle(EFI_HANDLE loaded)
{
    if (!loaded) {
        return;
    }
    for (uint32_t i = 0; i < g_fs_driver_handle_count; i++) {
        if (g_fs_driver_handles[i] == loaded) {
            return;
        }
    }
    if (g_fs_driver_handle_count < sizeof(g_fs_driver_handles) / sizeof(g_fs_driver_handles[0])) {
        g_fs_driver_handles[g_fs_driver_handle_count++] = loaded;
    }
}

static int handle_in_buffer(EFI_HANDLE handle, EFI_HANDLE *handles, UINTN count)
{
    for (UINTN i = 0; i < count; i++) {
        if (handles[i] == handle) {
            return 1;
        }
    }
    return 0;
}

static EFI_HANDLE *snapshot_driver_binding_handles(UINTN *count)
{
    EFI_HANDLE *handles = 0;
    UINTN local_count = 0;
    if (count) {
        *count = 0;
    }
    if (!g_bs->LocateHandleBuffer) {
        return 0;
    }
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&DriverBindingGuid,
                                 0, &local_count, &handles) != EFI_SUCCESS || !handles) {
        return 0;
    }
    if (count) {
        *count = local_count;
    }
    return handles;
}

static void remember_new_driver_binding_handles(EFI_HANDLE *before, UINTN before_count)
{
    EFI_HANDLE *after = 0;
    UINTN after_count = 0;
    after = snapshot_driver_binding_handles(&after_count);
    if (!after) {
        return;
    }
    for (UINTN i = 0; i < after_count; i++) {
        if (!handle_in_buffer(after[i], before, before_count)) {
            remember_fs_driver_handle(after[i]);
        }
    }
    g_bs->FreePool(after);
}

static void remember_all_driver_binding_handles(void)
{
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    handles = snapshot_driver_binding_handles(&count);
    if (!handles) {
        return;
    }
    for (UINTN i = 0; i < count; i++) {
        remember_fs_driver_handle(handles[i]);
    }
    g_bs->FreePool(handles);
}

static void connect_fs_drivers_to_protocol_handles(const EFI_GUID *protocol)
{
    EFI_HANDLE *controllers = 0;
    UINTN count = 0;
    if (!protocol || !g_bs->LocateHandleBuffer || !g_bs->ConnectController ||
        !g_fs_driver_handle_count) {
        return;
    }
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)protocol, 0,
                                 &count, &controllers) != EFI_SUCCESS || !controllers) {
        return;
    }
    for (UINTN c = 0; c < count; c++) {
        for (uint32_t d = 0; d < g_fs_driver_handle_count; d++) {
            EFI_HANDLE drivers[2];
            drivers[0] = g_fs_driver_handles[d];
            drivers[1] = 0;
            g_bs->ConnectController(controllers[c], drivers, 0, 1);
        }
    }
    g_bs->FreePool(controllers);
}

static void connect_fs_drivers_to_storage_handles(void)
{
    connect_fs_drivers_to_protocol_handles(&BlockIoGuid);
    connect_fs_drivers_to_protocol_handles(&DiskIoGuid);
}

static void reconnect_ntfs_with_external_fs_driver(void)
{
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    if (!g_external_fs_drivers_loaded || !g_bs->DisconnectController ||
        !g_bs->LocateHandleBuffer || !g_fs_driver_handle_count) {
        return;
    }
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&SimpleFileSystemGuid,
                                 0, &count, &handles) == EFI_SUCCESS && handles) {
        for (UINTN i = 0; i < count; i++) {
            uint32_t bi = find_block_for_fs_handle(handles[i], 0);
            if (bi < g_block_count && g_blocks[bi].logical_partition &&
                ascii_eq(g_blocks[bi].fs_name, "NTFS")) {
                g_bs->DisconnectController(g_blocks[bi].handle, 0, handles[i]);
                g_bs->DisconnectController(handles[i], 0, 0);
            }
        }
        g_bs->FreePool(handles);
    }
    connect_fs_drivers_to_storage_handles();
    connect_all_controllers();
    connect_fs_drivers_to_storage_handles();
}

static int start_loaded_image(EFI_HANDLE loaded)
{
    UINTN exit_sz = 0;
    CHAR16 *exit_data = 0;
    EFI_HANDLE *bindings_before = 0;
    UINTN bindings_before_count = 0;
    if (!loaded) {
        return 0;
    }
    bindings_before = snapshot_driver_binding_handles(&bindings_before_count);
    EFI_STATUS st = g_bs->StartImage(loaded, &exit_sz, &exit_data);
    if (st == EFI_SUCCESS || st == EFI_ALREADY_STARTED) {
        remember_fs_driver_handle(loaded);
        remember_new_driver_binding_handles(bindings_before, bindings_before_count);
        if (g_fs_driver_handle_count <= 1) {
            remember_all_driver_binding_handles();
        }
        if (bindings_before) {
            g_bs->FreePool(bindings_before);
        }
        return 1;
    }
    if (bindings_before) {
        g_bs->FreePool(bindings_before);
    }
    return 0;
}

static void load_efi_driver_from_dir(EFI_HANDLE fs_handle, EFI_FILE_PROTOCOL *dir,
                                     const CHAR16 *driver_dir, CHAR16 *name)
{
    EFI_FILE_PROTOCOL *f = 0;
    uint8_t info_buf[512];
    UINTN info_sz = sizeof(info_buf);
    void *image_buf = 0;
    EFI_HANDLE loaded = 0;
    CHAR16 full_path[260];
    EFI_DEVICE_PATH_PROTOCOL *dp = 0;
    if (!dir || !name || !g_bs->LoadImage || !g_bs->StartImage) {
        return;
    }
    full_path[0] = 0;
    c16_join_path(full_path, sizeof(full_path) / sizeof(full_path[0]), driver_dir, name);
    dp = build_driver_file_device_path(fs_handle, full_path);
    if (dp) {
        if (g_bs->LoadImage(0, g_image, dp, 0, 0, &loaded) == EFI_SUCCESS && start_loaded_image(loaded)) {
            g_bs->FreePool(dp);
            return;
        }
        g_bs->FreePool(dp);
        loaded = 0;
    }
    if (dir->Open(dir, &f, name, EFI_FILE_MODE_READ, 0) != EFI_SUCCESS || !f) {
        return;
    }
    if (f->GetInfo(f, (EFI_GUID *)&FileInfoGuid, &info_sz, info_buf) != EFI_SUCCESS) {
        f->Close(f);
        return;
    }
    EFI_FILE_INFO *info = (EFI_FILE_INFO *)info_buf;
    if (!info->FileSize || info->FileSize > 4ULL * 1024ULL * 1024ULL) {
        f->Close(f);
        return;
    }
    if (g_bs->AllocatePool(EfiLoaderData, (UINTN)info->FileSize, &image_buf) != EFI_SUCCESS || !image_buf) {
        f->Close(f);
        return;
    }
    UINTN read_sz = (UINTN)info->FileSize;
    if (f->Read(f, &read_sz, image_buf) == EFI_SUCCESS && read_sz == (UINTN)info->FileSize) {
        if (g_bs->LoadImage(0, g_image, 0, image_buf, read_sz, &loaded) == EFI_SUCCESS && loaded) {
            start_loaded_image(loaded);
        }
    }
    g_bs->FreePool(image_buf);
    f->Close(f);
}

static void load_external_fs_drivers(void)
{
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    uint32_t loaded_before = g_fs_driver_handle_count;
    if (!g_bs->LocateHandleBuffer || !g_bs->LoadImage || !g_bs->StartImage) {
        return;
    }
    if (g_external_fs_drivers_loaded) {
        connect_fs_drivers_to_storage_handles();
        connect_all_controllers();
        connect_fs_drivers_to_storage_handles();
        return;
    }
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&SimpleFileSystemGuid,
                                 0, &count, &handles) != EFI_SUCCESS) {
        return;
    }
    for (UINTN i = 0; i < count; i++) {
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs = 0;
        EFI_FILE_PROTOCOL *root = 0;
        EFI_FILE_PROTOCOL *dir = 0;
        EFI_STATUS st = g_bs->OpenProtocol(handles[i], (EFI_GUID *)&SimpleFileSystemGuid,
                                           (void **)&fs, g_image, 0,
                                           EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
        if (st != EFI_SUCCESS) {
            st = g_bs->HandleProtocol(handles[i], (EFI_GUID *)&SimpleFileSystemGuid, (void **)&fs);
        }
        if (st != EFI_SUCCESS || !fs || fs->OpenVolume(fs, &root) != EFI_SUCCESS || !root) {
            continue;
        }
        CHAR16 driver_dir_abs[] = L"\\EFI\\BOOT\\DRIVERS";
        CHAR16 driver_dir_rel[] = L"EFI\\BOOT\\DRIVERS";
        CHAR16 *driver_dir = driver_dir_abs;
        st = root->Open(root, &dir, driver_dir, EFI_FILE_MODE_READ, 0);
        if (st != EFI_SUCCESS || !dir) {
            driver_dir = driver_dir_rel;
            st = root->Open(root, &dir, driver_dir, EFI_FILE_MODE_READ, 0);
        }
        if (st != EFI_SUCCESS || !dir) {
            root->Close(root);
            continue;
        }
        for (;;) {
            uint8_t info_buf[512];
            UINTN sz = sizeof(info_buf);
            st = dir->Read(dir, &sz, info_buf);
            if (st != EFI_SUCCESS || sz == 0) {
                break;
            }
            EFI_FILE_INFO *info = (EFI_FILE_INFO *)info_buf;
            if (!(info->Attribute & EFI_FILE_DIRECTORY) && c16_ends_with_efi(info->FileName)) {
                load_efi_driver_from_dir(handles[i], dir, driver_dir_abs, info->FileName);
            }
        }
        dir->Close(dir);
        root->Close(root);
    }
    g_bs->FreePool(handles);
    if (g_fs_driver_handle_count > loaded_before) {
        g_external_fs_drivers_loaded = 1;
        connect_fs_drivers_to_storage_handles();
        connect_all_controllers();
        connect_fs_drivers_to_storage_handles();
    }
}

static void detect_memory(void)
{
    UINTN map_size = 0;
    UINTN key = 0;
    UINTN desc_size = 0;
    uint32_t desc_version = 0;
    void *map = 0;
    EFI_STATUS status = g_bs->GetMemoryMap(&map_size, map, &key, &desc_size, &desc_version);
    if (status == EFI_BUFFER_TOO_SMALL && desc_size) {
        map_size += desc_size * 16;
    } else {
        map_size = 131072;
        desc_size = sizeof(EFI_MEMORY_DESCRIPTOR);
    }
    if (g_bs->AllocatePool(EfiLoaderData, map_size, &map) != EFI_SUCCESS) {
        return;
    }
    status = g_bs->GetMemoryMap(&map_size, map, &key, &desc_size, &desc_version);
    if (status == EFI_BUFFER_TOO_SMALL) {
        g_bs->FreePool(map);
        map_size += 131072;
        map = 0;
        if (g_bs->AllocatePool(EfiLoaderData, map_size, &map) != EFI_SUCCESS) {
            return;
        }
        status = g_bs->GetMemoryMap(&map_size, map, &key, &desc_size, &desc_version);
    }
    if (status == EFI_SUCCESS && desc_size >= sizeof(EFI_MEMORY_DESCRIPTOR)) {
        uint64_t pages = 0;
        uint8_t *p = (uint8_t *)map;
        for (UINTN off = 0; off + desc_size <= map_size; off += desc_size) {
            EFI_MEMORY_DESCRIPTOR *d = (EFI_MEMORY_DESCRIPTOR *)(p + off);
            if (memory_type_is_ram(d->Type) && d->NumberOfPages < (1ULL << 44)) {
                pages += d->NumberOfPages;
            }
        }
        g_memory_mb = (pages * 4096ULL) / (1024ULL * 1024ULL);
    }
    g_bs->FreePool(map);
}

static void detect_storage(EFI_HANDLE image)
{
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&BlockIoGuid, 0, &count, &handles) != EFI_SUCCESS) {
        return;
    }
    g_block_count = 0;
    uint32_t last_phys_idx = 0;
    for (UINTN i = 0; i < count && g_block_count < sizeof(g_blocks) / sizeof(g_blocks[0]); i++) {
        EFI_BLOCK_IO_PROTOCOL *bio = 0;
        if (g_bs->OpenProtocol(handles[i], (EFI_GUID *)&BlockIoGuid, (void **)&bio, image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL) != EFI_SUCCESS) {
            if (g_bs->HandleProtocol(handles[i], (EFI_GUID *)&BlockIoGuid, (void **)&bio) != EFI_SUCCESS) {
                continue;
            }
        }
        if (!bio || !bio->Media) {
            continue;
        }
        g_blocks[g_block_count].handle = handles[i];
        g_blocks[g_block_count].present = bio->Media->MediaPresent;
        g_blocks[g_block_count].removable = bio->Media->RemovableMedia;
        g_blocks[g_block_count].readonly = bio->Media->ReadOnly;
        g_blocks[g_block_count].logical_partition = bio->Media->LogicalPartition;
        g_blocks[g_block_count].block_size = bio->Media->BlockSize;
        g_blocks[g_block_count].blocks = bio->Media->LastBlock + 1;
        g_blocks[g_block_count].media_id = bio->Media->MediaId;
        /* Track parent physical disk for partition handles */
        if (!bio->Media->LogicalPartition) {
            last_phys_idx = g_block_count;
        }
        g_blocks[g_block_count].parent_disk_idx = last_phys_idx;
        ascii_copy(g_blocks[g_block_count].fs_name, "RAW", sizeof(g_blocks[g_block_count].fs_name));
        if (bio->Media->MediaPresent && bio->ReadBlocks && bio->Media->BlockSize <= sizeof(g_fs_block_buffer)) {
            UINTN read_size = bio->Media->BlockSize;
            if (bio->ReadBlocks(bio, bio->Media->MediaId, 0, read_size, g_fs_block_buffer) == EFI_SUCCESS) {
                if (memeq_ascii(g_fs_block_buffer, 3, "NTFS    ", 8)) {
                    ascii_copy(g_blocks[g_block_count].fs_name, "NTFS", sizeof(g_blocks[g_block_count].fs_name));
                } else if (memeq_ascii(g_fs_block_buffer, 3, "EXFAT   ", 8)) {
                    ascii_copy(g_blocks[g_block_count].fs_name, "EXFAT", sizeof(g_blocks[g_block_count].fs_name));
                } else if (memeq_ascii(g_fs_block_buffer, 54, "FAT12   ", 8) || memeq_ascii(g_fs_block_buffer, 54, "FAT16   ", 8) ||
                           memeq_ascii(g_fs_block_buffer, 82, "FAT32   ", 8)) {
                    ascii_copy(g_blocks[g_block_count].fs_name, "FAT", sizeof(g_blocks[g_block_count].fs_name));
                }
            }
        }
        g_block_count++;
    }
    g_bs->FreePool(handles);
    /* Build physical-disk-only index: exclude partitions, absent media, and tiny virtual disks (<8MB) */
    g_disk_count = 0;
    for (uint32_t i = 0; i < g_block_count && g_disk_count < 12; i++) {
        if (!g_blocks[i].logical_partition && g_blocks[i].present &&
            (uint64_t)g_blocks[i].blocks * g_blocks[i].block_size >= 8ULL * 1024 * 1024) {
            g_disk_map[g_disk_count++] = i;
        }
    }
    g_storage_refresh_needed = 0;
}

static int open_volume_root(uint32_t volume, EFI_FILE_PROTOCOL **root)
{
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs = 0;
    if (!root) {
        return 0;
    }
    *root = 0;
    if (volume >= g_volume_count) {
        return 0;
    }
    if (!g_volumes[volume].firmware_fs) {
        return 0;
    }
    EFI_HANDLE h = g_volumes[volume].handle;
    EFI_STATUS st = g_bs->OpenProtocol(h, (EFI_GUID *)&SimpleFileSystemGuid, (void **)&fs, g_image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (st != EFI_SUCCESS) {
        st = g_bs->HandleProtocol(h, (EFI_GUID *)&SimpleFileSystemGuid, (void **)&fs);
    }
    if (st == EFI_SUCCESS && fs) {
        st = fs->OpenVolume(fs, root);
    }
    if (st == EFI_MEDIA_CHANGED || st == EFI_NO_MEDIA || st == EFI_DEVICE_ERROR) {
        g_fs_refresh_needed = 1;
        set_last_error("DOSYA BIRIMI DEGISTI, YENILENIYOR");
    }
    if (st != EFI_SUCCESS || !*root) {
        return 0;
    }
    return 1;
}

static int open_window_dir(explorer_window_t *win, EFI_FILE_PROTOCOL **dir)
{
    EFI_FILE_PROTOCOL *root = 0;
    if (win && win->volume < g_volume_count && g_volumes[win->volume].native_fs != NATIVE_FS_NONE) {
        return native_open_file_by_path(win->volume, win->path, dir, EFI_FILE_MODE_READ, EFI_FILE_DIRECTORY);
    }
    if (!open_volume_root(win->volume, &root)) {
        return 0;
    }
    if (!win->path[0]) {
        *dir = root;
        return 1;
    }
    EFI_STATUS st = root->Open(root, dir, win->path, EFI_FILE_MODE_READ, 0);
    root->Close(root);
    return st == EFI_SUCCESS && *dir;
}

static void load_window_entries(explorer_window_t *win)
{
    win->entry_count = 0;
    if (win->mode != EXPLORER_MODE_FILES) {
        return;
    }
    EFI_FILE_PROTOCOL *dir = 0;
    if (!open_window_dir(win, &dir)) {
        return;
    }
    if (win->path[0] && win->entry_count < sizeof(win->entries) / sizeof(win->entries[0])) {
        file_entry_t *up = &win->entries[win->entry_count++];
        up->name[0] = L'.';
        up->name[1] = L'.';
        up->name[2] = 0;
        up->size = 0;
        up->attr = EFI_FILE_DIRECTORY;
        up->is_dir = 1;
    }
    for (;;) {
        uint8_t info_buf[1024];
        UINTN sz = sizeof(info_buf);
        EFI_STATUS st = dir->Read(dir, &sz, info_buf);
        if (st == EFI_MEDIA_CHANGED || st == EFI_NO_MEDIA || st == EFI_DEVICE_ERROR) {
            g_fs_refresh_needed = 1;
            set_last_error("MEDYA DEGISTI, DOSYA LISTESI YENILENECEK");
            break;
        }
        if (st != EFI_SUCCESS || sz == 0) {
            break;
        }
        EFI_FILE_INFO *info = (EFI_FILE_INFO *)info_buf;
        if (!info->FileName[0] || (info->FileName[0] == L'.' && (!info->FileName[1] || c16_is_dotdot(info->FileName)))) {
            continue;
        }
        file_entry_t *e = &win->entries[win->entry_count];
        c16_copy(e->name, info->FileName, sizeof(e->name) / sizeof(e->name[0]));
        e->size = info->FileSize;
        e->attr = info->Attribute;
        e->is_dir = (info->Attribute & EFI_FILE_DIRECTORY) ? 1 : 0;
        win->entry_count++;
        if (win->entry_count >= sizeof(win->entries) / sizeof(win->entries[0])) {
            break;
        }
    }
    dir->Close(dir);
}

static void init_file_windows(uint8_t reset_paths)
{
    if (reset_paths) {
        g_active_window = 0;
        g_active_surface = ACTIVE_EXPLORER;
    }
    for (uint32_t i = 0; i < MAX_EXPLORER_WINDOWS; i++) {
        g_windows[i].active = i == g_active_window;
        if (reset_paths) {
            g_windows[i].visible = i < 2 ? 1 : 0;
            g_windows[i].mode = EXPLORER_MODE_DISKS;
            g_windows[i].disk = g_disk_count ? g_disk_map[0] : 0;
            g_windows[i].volume = g_volume_count ? (i < g_volume_count ? i : 0) : 0;
            g_windows[i].path[0] = 0;
            g_windows[i].selected = 0;
            g_windows[i].scroll = 0;
            g_windows[i].x = 0;
            g_windows[i].y = 0;
            g_windows[i].w = 0;
            g_windows[i].h = 0;
        } else if (g_windows[i].volume >= g_volume_count) {
            g_windows[i].volume = g_volume_count ? (i < g_volume_count ? i : 0) : 0;
            g_windows[i].path[0] = 0;
            g_windows[i].selected = 0;
            g_windows[i].scroll = 0;
        }
        if (g_windows[i].visible && g_windows[i].mode == EXPLORER_MODE_FILES) {
            load_window_entries(&g_windows[i]);
        }
    }
}

static void detect_file_systems(EFI_HANDLE image, uint8_t reset_windows)
{
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    g_volume_count = 0;
    if (g_external_fs_drivers_loaded) {
        connect_fs_drivers_to_storage_handles();
        connect_all_controllers();
        connect_fs_drivers_to_storage_handles();
        reconnect_ntfs_with_external_fs_driver();
    }
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&SimpleFileSystemGuid, 0, &count, &handles) == EFI_SUCCESS) {
        for (UINTN i = 0; i < count && g_volume_count < MAX_VOLUMES; i++) {
            EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs = 0;
            EFI_STATUS st = g_bs->OpenProtocol(handles[i], (EFI_GUID *)&SimpleFileSystemGuid, (void **)&fs, image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
            if (st != EFI_SUCCESS) {
                st = g_bs->HandleProtocol(handles[i], (EFI_GUID *)&SimpleFileSystemGuid, (void **)&fs);
            }
            if (st == EFI_SUCCESS && fs) {
                memset(&g_volumes[g_volume_count], 0, sizeof(g_volumes[g_volume_count]));
                g_volumes[g_volume_count].handle = handles[i];
                g_volumes[g_volume_count].read_only = 0;
                g_volumes[g_volume_count].firmware_fs = 1;
                g_volumes[g_volume_count].native_fs = NATIVE_FS_NONE;
                g_volumes[g_volume_count].block_idx = 0xFFFFFFFFU;
                c16_from_ascii(g_volumes[g_volume_count].label, "VOL", sizeof(g_volumes[g_volume_count].label) / sizeof(g_volumes[g_volume_count].label[0]));
                g_volumes[g_volume_count].label[3] = (CHAR16)(L'0' + (g_volume_count % 10));
                g_volumes[g_volume_count].label[4] = 0;
                /* Determine which block device this volume belongs to via MediaId */
                g_volumes[g_volume_count].media_id = 0;
                {
                    EFI_BLOCK_IO_PROTOCOL *bio2 = 0;
                    EFI_STATUS bst = g_bs->OpenProtocol(handles[i], (EFI_GUID *)&BlockIoGuid, (void **)&bio2, image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
                    if (bst != EFI_SUCCESS) {
                        bst = g_bs->HandleProtocol(handles[i], (EFI_GUID *)&BlockIoGuid, (void **)&bio2);
                    }
                    if (bst == EFI_SUCCESS && bio2 && bio2->Media) {
                        g_volumes[g_volume_count].media_id = bio2->Media->MediaId;
                    }
                    g_volumes[g_volume_count].block_idx =
                        find_block_for_fs_handle(handles[i], g_volumes[g_volume_count].media_id);
                    if (g_volumes[g_volume_count].block_idx < g_block_count) {
                        block_summary_t *blk = &g_blocks[g_volumes[g_volume_count].block_idx];
                        g_volumes[g_volume_count].read_only = blk->readonly;
                        if (blk->fs_name[0] && !ascii_eq(blk->fs_name, "RAW")) {
                            c16_from_ascii(g_volumes[g_volume_count].label, blk->fs_name,
                                           sizeof(g_volumes[g_volume_count].label) / sizeof(g_volumes[g_volume_count].label[0]));
                            uint32_t ln = c16_len(g_volumes[g_volume_count].label);
                            if (ln + 1 < sizeof(g_volumes[g_volume_count].label) / sizeof(g_volumes[g_volume_count].label[0])) {
                                g_volumes[g_volume_count].label[ln++] = (CHAR16)(L'0' + (g_volume_count % 10));
                                g_volumes[g_volume_count].label[ln] = 0;
                            }
                        }
                    }
                }
                g_volume_count++;
            }
        }
        g_bs->FreePool(handles);
    }
    /* Second pass: add partition handles that have no SimpleFileSystem (NTFS, exFAT, etc.).
       These are already enumerated in g_blocks with logical_partition == 1. */
    for (uint32_t i = 0; i < g_block_count && g_volume_count < MAX_VOLUMES; i++) {
        if (!g_blocks[i].logical_partition || !g_blocks[i].present) {
            continue;
        }
        /* Skip if this handle is already in g_volumes (already has SimpleFS) */
        uint8_t already = 0;
        for (uint32_t j = 0; j < g_volume_count; j++) {
            if (g_volumes[j].handle == g_blocks[i].handle ||
                g_volumes[j].block_idx == i) {
                already = 1;
                break;
            }
        }
        if (already) {
            continue;
        }
        uint8_t native_fs = NATIVE_FS_RAW;
        if (ascii_eq(g_blocks[i].fs_name, "EXFAT")) {
            native_fs = NATIVE_FS_EXFAT;
        } else if (ascii_eq(g_blocks[i].fs_name, "NTFS")) {
            native_fs = NATIVE_FS_NTFS;
        } else if (!ascii_eq(g_blocks[i].fs_name, "RAW")) {
            native_fs = NATIVE_FS_NONE;
        }
        if (native_fs == NATIVE_FS_NONE) {
            continue;
        }
        memset(&g_volumes[g_volume_count], 0, sizeof(g_volumes[g_volume_count]));
        g_volumes[g_volume_count].handle = g_blocks[i].handle;
        g_volumes[g_volume_count].read_only = g_blocks[i].readonly;
        g_volumes[g_volume_count].firmware_fs = 0;
        g_volumes[g_volume_count].native_fs = native_fs;
        g_volumes[g_volume_count].block_idx = i;
        g_volumes[g_volume_count].media_id = g_blocks[i].media_id;
        c16_from_ascii(g_volumes[g_volume_count].label, g_blocks[i].fs_name,
                       sizeof(g_volumes[g_volume_count].label) / sizeof(g_volumes[g_volume_count].label[0]));
        {
            uint32_t ln = c16_len(g_volumes[g_volume_count].label);
            if (ln + 1 < sizeof(g_volumes[g_volume_count].label) / sizeof(g_volumes[g_volume_count].label[0])) {
                g_volumes[g_volume_count].label[ln++] = (CHAR16)(L'0' + (g_volume_count % 10));
                g_volumes[g_volume_count].label[ln] = 0;
            }
        }
        native_init_volume(g_volume_count);
        g_volume_count++;
    }
    init_file_windows(reset_windows);
    g_fs_refresh_needed = 0;
    /* Count only volumes belonging to known physical disks or their logical partitions.
       Excludes ISO boot EFI partitions and other virtual devices. */
    g_real_vol_count = 0;
    for (uint32_t i = 0; i < g_volume_count; i++) {
        uint8_t is_real = 0;
        if (g_volumes[i].block_idx < g_block_count &&
            g_blocks[g_volumes[i].block_idx].logical_partition) {
            is_real = 1;
        }
        for (uint32_t k = 0; k < g_block_count && !is_real; k++) {
            if (g_blocks[k].handle != g_volumes[i].handle) continue;
            if (g_blocks[k].logical_partition) {
                is_real = 1;
            } else {
                /* Physical disk — only real if it's in g_disk_map (≥8MB, present) */
                for (uint32_t d = 0; d < g_disk_count && !is_real; d++) {
                    if (g_disk_map[d] == k) is_real = 1;
                }
            }
        }
        if (is_real) g_real_vol_count++;
    }
}

static int open_file_by_path(uint32_t volume, const CHAR16 *path, EFI_FILE_PROTOCOL **file, uint64_t mode, uint64_t attr)
{
    EFI_FILE_PROTOCOL *root = 0;
    if (file) {
        *file = 0;
    }
    if (volume < g_volume_count && g_volumes[volume].native_fs != NATIVE_FS_NONE) {
        return native_open_file_by_path(volume, path, file, mode, attr);
    }
    if (!open_volume_root(volume, &root)) {
        return 0;
    }
    EFI_STATUS st = root->Open(root, file, (CHAR16 *)path, mode, attr);
    root->Close(root);
    if (st == EFI_MEDIA_CHANGED || st == EFI_NO_MEDIA || st == EFI_DEVICE_ERROR) {
        g_fs_refresh_needed = 1;
        set_last_error("DOSYA ACILAMADI, MEDYA DEGISTI");
    }
    return st == EFI_SUCCESS && *file;
}

static int selected_full_path(explorer_window_t *win, CHAR16 *out, uint32_t max)
{
    if (!win || win->mode != EXPLORER_MODE_FILES || win->selected >= win->entry_count) {
        return 0;
    }
    c16_join_path(out, max, win->path, win->entries[win->selected].name);
    return 1;
}

/* For a given EFI_HANDLE, find its index in g_blocks[] (any kind of entry).
   Returns 0xFFFFFFFF if not found. */
static uint32_t find_block_idx_for_handle(EFI_HANDLE h)
{
    for (uint32_t j = 0; j < g_block_count; j++) {
        if (g_blocks[j].handle == h) {
            return j;
        }
    }
    return 0xFFFFFFFF;
}

/* For a given EFI_HANDLE (SimpleFileSystem or BlockIO handle), find the
   g_blocks[] index of its owning PHYSICAL disk handle.
   Returns 0xFFFFFFFF if not found. */
static uint32_t find_owner_disk_for_handle(EFI_HANDLE h)
{
    for (uint32_t j = 0; j < g_block_count; j++) {
        if (g_blocks[j].handle == h) {
            /* If this entry is a physical disk, it owns itself */
            if (!g_blocks[j].logical_partition) {
                return j;
            }
            /* Partition handle — return the parent physical disk index */
            return g_blocks[j].parent_disk_idx;
        }
    }
    return 0xFFFFFFFF;
}

/* Populate win->vol_map[] with volume indices that belong to win->disk.
   Uses EFI_HANDLE matching through detect_storage's parent tracking. */
static void build_volume_map_for_disk(explorer_window_t *win)
{
    win->vol_count = 0;
    if (win->disk >= g_block_count) {
        return;
    }
    for (uint32_t i = 0; i < g_volume_count && win->vol_count < MAX_VOLUMES; i++) {
        uint32_t owner = find_owner_disk_for_handle(g_volumes[i].handle);
        if (owner == 0xFFFFFFFFU && g_volumes[i].block_idx < g_block_count) {
            uint32_t bi = g_volumes[i].block_idx;
            owner = g_blocks[bi].logical_partition ? g_blocks[bi].parent_disk_idx : bi;
        }
        if (owner == win->disk) {
            win->vol_map[win->vol_count++] = i;
        }
    }
    for (uint32_t i = 0; i < g_volume_count && win->vol_count < MAX_VOLUMES; i++) {
        if (g_volumes[i].firmware_fs && g_volumes[i].block_idx == 0xFFFFFFFFU) {
            uint8_t exists = 0;
            for (uint32_t j = 0; j < win->vol_count; j++) {
                if (win->vol_map[j] == i) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                win->vol_map[win->vol_count++] = i;
            }
        }
    }
    /* Fallback: if no volumes matched (UEFI driver not loaded for this disk's FS),
       show all volumes so the user can still navigate */
    if (!win->vol_count) {
        for (uint32_t i = 0; i < g_volume_count && win->vol_count < MAX_VOLUMES; i++) {
            win->vol_map[win->vol_count++] = i;
        }
    }
}

static void open_selected_entry(explorer_window_t *win)
{
    if (!win) {
        return;
    }
    if (win->mode == EXPLORER_MODE_DISKS) {
        if (g_disk_count && win->selected < g_disk_count) {
            win->disk = g_disk_map[win->selected];
        }
        build_volume_map_for_disk(win);
        win->mode = EXPLORER_MODE_VOLUMES;
        win->selected = 0;
        win->scroll = 0;
        return;
    }
    if (win->mode == EXPLORER_MODE_VOLUMES) {
        if (win->vol_count && win->selected < win->vol_count) {
            uint32_t vi = win->vol_map[win->selected];
            win->volume = vi;
            if (!volume_is_browsable(vi) && vi < g_volume_count &&
                g_volumes[vi].native_fs != NATIVE_FS_NONE) {
                native_ensure_ready(vi);
            }
            if (!volume_is_browsable(vi)) {
                win->mode = EXPLORER_MODE_PART_INFO;
                win->entry_count = 0;
                win->selected = 0;
                win->scroll = 0;
            } else {
                win->path[0] = 0;
                win->mode = EXPLORER_MODE_FILES;
                win->selected = 0;
                win->scroll = 0;
                load_window_entries(win);
            }
        }
        return;
    }
    if (win->mode == EXPLORER_MODE_PART_INFO) {
        if (win->volume < g_volume_count && native_ensure_ready(win->volume)) {
            win->path[0] = 0;
            win->mode = EXPLORER_MODE_FILES;
            win->selected = 0;
            win->scroll = 0;
            load_window_entries(win);
        } else {
            set_last_error("NATIVE SURUCU BASLATILAMADI");
        }
        return;
    }
    if (win->selected >= win->entry_count) {
        return;
    }
    file_entry_t *e = &win->entries[win->selected];
    CHAR16 full[256];
    c16_join_path(full, sizeof(full) / sizeof(full[0]), win->path, e->name);
    if (c16_is_dotdot(e->name)) {
        c16_parent(win->path);
        win->selected = 0;
        win->scroll = 0;
        load_window_entries(win);
        return;
    }
    if (e->is_dir) {
        c16_copy(win->path, full, sizeof(win->path) / sizeof(win->path[0]));
        win->selected = 0;
        win->scroll = 0;
        load_window_entries(win);
        return;
    }
    if (cyx_name_has_ext(e->name)) {
        cyx_open_chooser(win->volume, full, e->name);
        return;
    }
    EFI_FILE_PROTOCOL *file = 0;
    if (!open_file_by_path(win->volume, full, &file, EFI_FILE_MODE_READ, 0)) {
        return;
    }
    UINTN sz = sizeof(g_viewer_text) - 1;
    if (file->Read(file, &sz, g_viewer_text) == EFI_SUCCESS) {
        g_viewer_text[sz] = 0;
        for (UINTN i = 0; i < sz; i++) {
            uint8_t c = (uint8_t)g_viewer_text[i];
            if (c == '\r') {
                g_viewer_text[i] = '\n';
            } else if (c < 32 && c != '\n' && c != '\t') {
                g_viewer_text[i] = '.';
            }
        }
        c16_copy(g_viewer_title, e->name, sizeof(g_viewer_title) / sizeof(g_viewer_title[0]));
        g_viewer_vol = win->volume;
        c16_copy(g_viewer_path, full, sizeof(g_viewer_path) / sizeof(g_viewer_path[0]));
        g_viewer_cursor = (uint32_t)sz;
        g_viewer_scroll = 0;
        g_viewer_edit = 0;
        g_viewer_open = 1;
    }
    file->Close(file);
}

static int set_file_size(EFI_FILE_PROTOCOL *file, uint64_t size)
{
    uint8_t fi_buf[sizeof(EFI_FILE_INFO) + 512];
    UINTN fi_sz = sizeof(fi_buf);
    if (!file) {
        return 0;
    }
    if (file->GetInfo(file, (EFI_GUID *)&FileInfoGuid, &fi_sz, fi_buf) != EFI_SUCCESS) {
        return 0;
    }
    ((EFI_FILE_INFO *)fi_buf)->FileSize = size;
    return file->SetInfo(file, (EFI_GUID *)&FileInfoGuid, fi_sz, fi_buf) == EFI_SUCCESS;
}

static int get_file_size(EFI_FILE_PROTOCOL *file, uint64_t *size)
{
    uint8_t fi_buf[sizeof(EFI_FILE_INFO) + 512];
    UINTN fi_sz = sizeof(fi_buf);
    if (!file || !size) {
        return 0;
    }
    if (file->GetInfo(file, (EFI_GUID *)&FileInfoGuid, &fi_sz, fi_buf) != EFI_SUCCESS) {
        return 0;
    }
    *size = ((EFI_FILE_INFO *)fi_buf)->FileSize;
    return 1;
}

static int preallocate_destination_file(uint32_t dst_vol, EFI_FILE_PROTOCOL *dst, uint64_t size)
{
    uint8_t zero = 0;
    UINTN one = 1;
    if (!size || dst_vol >= g_volume_count ||
        (g_volumes[dst_vol].native_fs != NATIVE_FS_EXFAT &&
         g_volumes[dst_vol].native_fs != NATIVE_FS_NTFS)) {
        return 1;
    }
    if (dst->SetPosition(dst, size - 1) != EFI_SUCCESS) {
        return 0;
    }
    if (dst->Write(dst, &one, &zero) != EFI_SUCCESS || one != 1) {
        return 0;
    }
    return dst->SetPosition(dst, 0) == EFI_SUCCESS;
}

/* Copy a single file; updates g_transfer_done + g_transfer_file_count; renders per ~128KB */
static int copy_single_file(uint32_t src_vol, const CHAR16 *src_path,
                             uint32_t dst_vol, const CHAR16 *dst_path,
                             uint8_t move_after)
{
    EFI_FILE_PROTOCOL *src = 0;
    EFI_FILE_PROTOCOL *dst = 0;
    uint64_t dst_size = 0;
    uint64_t src_size = 0;
    uint8_t ok = 1;
    /* Snapshot of the source's GetInfo so we can transplant CreateTime /
     * ModificationTime / LastAccessTime onto the destination once the data
     * copy is done.  Big enough for the largest path we ever pass through.  */
    uint8_t src_info_buf[sizeof(EFI_FILE_INFO) + 512];
    UINTN src_info_size = 0;
    int have_src_info = 0;
    /* Open source; need write permission too when we will delete it (move) */
    uint64_t src_mode = move_after
        ? (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE)
        : EFI_FILE_MODE_READ;
    if (!open_file_by_path(src_vol, src_path, &src, src_mode, 0)) {
        /* Fallback to read-only if write open fails (e.g. read-only media) */
        if (!open_file_by_path(src_vol, src_path, &src, EFI_FILE_MODE_READ, 0)) {
            return 0;
        }
    }
    get_file_size(src, &src_size);
    src_info_size = sizeof(src_info_buf);
    if (src->GetInfo(src, (EFI_GUID *)&FileInfoGuid, &src_info_size, src_info_buf) == EFI_SUCCESS) {
        have_src_info = 1;
    }
    /* Delete existing destination */
    EFI_FILE_PROTOCOL *old = 0;
    if (open_file_by_path(dst_vol, dst_path, &old, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
        old->Delete(old);
    }
    if (!open_file_by_path(dst_vol, dst_path, &dst,
                           EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0)) {
        src->Close(src);
        set_last_error("HEDEF YAZILAMAZ");
        return 0;
    }
    if (!preallocate_destination_file(dst_vol, dst, src_size)) {
        dst->Close(dst);
        src->Close(src);
        set_last_error("HEDEFTE ALAN AYRILAMADI");
        return 0;
    }
    for (;;) {
        UINTN read_sz = sizeof(g_io_buffer);
        if (src->Read(src, &read_sz, g_io_buffer) != EFI_SUCCESS || read_sz == 0) {
            break;
        }
        UINTN write_sz = read_sz;
        if (dst->Write(dst, &write_sz, g_io_buffer) != EFI_SUCCESS || write_sz != read_sz) {
            set_last_error("YAZMA HATASI");
            ok = 0;
            break;
        }
        dst_size += read_sz;
        g_transfer_done += read_sz;
        if (!g_transfer_is_dir) {
            /* Single-file mode: also accumulate total for accurate % */
        }
        /* Redraw every ~128KB */
        if ((g_transfer_done & 0x1FFFF) < (UINTN)sizeof(g_io_buffer)) {
            g_dirty = 1;
            render();
        }
    }
    if (ok && !set_file_size(dst, dst_size)) {
        set_last_error("BOYUT GUNCELLENEMEDI");
        ok = 0;
    }
    /* Replay source's original timestamps onto the freshly-written
     * destination.  We reuse the source's GetInfo blob but rewrite FileName
     * to the destination leaf and FileSize to the bytes actually written so
     * SetInfo only touches timestamps + size, not the name.                  */
    if (ok && have_src_info && src_info_size >= offsetof(EFI_FILE_INFO, FileName)) {
        EFI_FILE_INFO *si = (EFI_FILE_INFO *)src_info_buf;
        si->FileSize = dst_size;
        si->PhysicalSize = dst_size;
        UINTN cap = src_info_size > offsetof(EFI_FILE_INFO, FileName)
            ? (src_info_size - offsetof(EFI_FILE_INFO, FileName)) / sizeof(CHAR16)
            : 0;
        const CHAR16 *leaf = dst_path;
        for (const CHAR16 *p = dst_path; *p; p++) {
            if (*p == L'\\' || *p == L'/') leaf = p + 1;
        }
        if (cap) {
            uint32_t li = 0;
            while (li + 1 < cap && leaf[li]) {
                si->FileName[li] = leaf[li];
                li++;
            }
            si->FileName[li] = 0;
            si->Size = offsetof(EFI_FILE_INFO, FileName) + ((UINTN)li + 1) * sizeof(CHAR16);
            dst->SetInfo(dst, (EFI_GUID *)&FileInfoGuid, (UINTN)si->Size, src_info_buf);
        }
    }
    dst->Flush(dst);
    dst->Close(dst);
    if (!ok) {
        src->Close(src);
        return 0;
    }
    if (move_after) {
        EFI_STATUS del_st = src->Delete(src);
        if (del_st == EFI_WRITE_PROTECTED || del_st == EFI_ACCESS_DENIED) {
            set_last_error("KAYNAK SALT OKUNUR, KOPYALANDI");
        }
    } else {
        src->Close(src);
    }
    g_transfer_file_count++;
    g_dirty = 1;
    render();
    return 1;
}

/* Recursively copy a directory (src_dir → dst_dir), depth-limited for stack safety */
static void copy_dir_recursive(uint32_t src_vol, uint32_t dst_vol,
                                const CHAR16 *src_dir, const CHAR16 *dst_dir,
                                uint8_t move_after, uint32_t depth)
{
    if (depth > 12) return;
    /* Open source directory for enumeration AND grab its timestamps so we
     * can transplant them onto the freshly-created destination directory.   */
    EFI_FILE_PROTOCOL *dir = 0;
    if (!open_file_by_path(src_vol, src_dir, &dir, EFI_FILE_MODE_READ, 0)) {
        return;
    }
    uint8_t src_dir_info[sizeof(EFI_FILE_INFO) + 256];
    UINTN src_dir_info_size = sizeof(src_dir_info);
    int have_src_dir_info = (dir->GetInfo(dir, (EFI_GUID *)&FileInfoGuid,
                                          &src_dir_info_size, src_dir_info) == EFI_SUCCESS);
    /* Create destination directory */
    EFI_FILE_PROTOCOL *nd = 0;
    if (open_file_by_path(dst_vol, dst_dir, &nd,
                          EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
                          EFI_FILE_DIRECTORY)) {
        if (have_src_dir_info && src_dir_info_size >= offsetof(EFI_FILE_INFO, FileName)) {
            EFI_FILE_INFO *si = (EFI_FILE_INFO *)src_dir_info;
            UINTN cap = src_dir_info_size > offsetof(EFI_FILE_INFO, FileName)
                ? (src_dir_info_size - offsetof(EFI_FILE_INFO, FileName)) / sizeof(CHAR16)
                : 0;
            const CHAR16 *leaf = dst_dir;
            for (const CHAR16 *p = dst_dir; *p; p++) {
                if (*p == L'\\' || *p == L'/') leaf = p + 1;
            }
            if (cap) {
                uint32_t li = 0;
                while (li + 1 < cap && leaf[li]) {
                    si->FileName[li] = leaf[li];
                    li++;
                }
                si->FileName[li] = 0;
                si->Size = offsetof(EFI_FILE_INFO, FileName) + ((UINTN)li + 1) * sizeof(CHAR16);
                nd->SetInfo(nd, (EFI_GUID *)&FileInfoGuid, (UINTN)si->Size, src_dir_info);
            }
        }
        nd->Close(nd);
    }
    for (;;) {
        uint8_t info_buf[1024];
        UINTN sz = sizeof(info_buf);
        EFI_STATUS st = dir->Read(dir, &sz, info_buf);
        if (st != EFI_SUCCESS || sz == 0) break;
        EFI_FILE_INFO *info = (EFI_FILE_INFO *)info_buf;
        if (!info->FileName[0] ||
            (info->FileName[0] == L'.' &&
             (!info->FileName[1] || c16_is_dotdot(info->FileName)))) {
            continue;
        }
        CHAR16 child_src[256];
        CHAR16 child_dst[256];
        c16_join_path(child_src, sizeof(child_src) / sizeof(child_src[0]), src_dir, info->FileName);
        c16_join_path(child_dst, sizeof(child_dst) / sizeof(child_dst[0]), dst_dir, info->FileName);
        if (info->Attribute & EFI_FILE_DIRECTORY) {
            copy_dir_recursive(src_vol, dst_vol, child_src, child_dst, move_after, depth + 1);
        } else {
            c16_copy(g_transfer_src_name, info->FileName,
                     sizeof(g_transfer_src_name) / sizeof(g_transfer_src_name[0]));
            copy_single_file(src_vol, child_src, dst_vol, child_dst, move_after);
        }
    }
    dir->Close(dir);
    if (move_after) {
        EFI_FILE_PROTOCOL *sd = 0;
        if (open_file_by_path(src_vol, src_dir, &sd, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
            sd->Delete(sd);
        }
    }
}

static void copy_selected_to_other(uint8_t move_after_copy)
{
    explorer_window_t *srcw = &g_windows[g_active_window];
    explorer_window_t *dstw = 0;
    uint32_t dst_win_idx = 0;
    for (uint32_t i = 0; i < MAX_EXPLORER_WINDOWS; i++) {
        if (i != g_active_window && g_windows[i].visible && g_windows[i].mode == EXPLORER_MODE_FILES) {
            dstw = &g_windows[i];
            dst_win_idx = i;
            break;
        }
    }
    if (!dstw) {
        set_last_error("HEDEF DOSYA GEZGINI YOK");
        return;
    }
    if (srcw->mode != EXPLORER_MODE_FILES || srcw->selected >= srcw->entry_count) {
        return;
    }
    file_entry_t *sel = &srcw->entries[srcw->selected];
    if (c16_is_dotdot(sel->name)) {
        return;
    }
    CHAR16 src_path[256];
    CHAR16 dst_path[256];
    selected_full_path(srcw, src_path, sizeof(src_path) / sizeof(src_path[0]));
    c16_join_path(dst_path, sizeof(dst_path) / sizeof(dst_path[0]), dstw->path, sel->name);
    if (srcw->volume == dstw->volume && c16_equal(src_path, dst_path)) {
        return;
    }
    /* Check if destination already exists */
    EFI_FILE_PROTOCOL *existing = 0;
    int dst_exists = open_file_by_path(dstw->volume, dst_path, &existing, EFI_FILE_MODE_READ, 0);
    if (dst_exists) {
        existing->Close(existing);
        /* Ask user before overwriting */
        g_pending_src_win = g_active_window;
        g_pending_dst_win = dst_win_idx;
        g_pending_src_vol = srcw->volume;
        g_pending_dst_vol = dstw->volume;
        c16_copy(g_pending_src_path, src_path, sizeof(g_pending_src_path) / sizeof(g_pending_src_path[0]));
        c16_copy(g_pending_dst_path, dst_path, sizeof(g_pending_dst_path) / sizeof(g_pending_dst_path[0]));
        g_pending_is_dir = sel->is_dir ? 1 : 0;
        c16_to_confirm_msg(g_confirm_msg, sizeof(g_confirm_msg) / sizeof(g_confirm_msg[0]),
                           sel->name, move_after_copy ? L"TASI-UZERINE YAZ?" : L"KOPYALA-UZERINE YAZ?");
        g_confirm_action = move_after_copy ? CONFIRM_MOVE : CONFIRM_COPY;
        g_confirm_open = 1;
        return;
    }
    /* No conflict — start immediately */
    g_transfer_active = 1;
    g_transfer_is_move = move_after_copy;
    g_transfer_is_dir = sel->is_dir ? 1 : 0;
    g_transfer_done = 0;
    g_transfer_file_count = 0;
    c16_copy(g_transfer_src_name, sel->name,
             sizeof(g_transfer_src_name) / sizeof(g_transfer_src_name[0]));
    if (dstw->volume < g_volume_count) {
        c16_copy(g_transfer_dst_vol, g_volumes[dstw->volume].label,
                 sizeof(g_transfer_dst_vol) / sizeof(g_transfer_dst_vol[0]));
    } else {
        g_transfer_dst_vol[0] = 0;
    }
    if (sel->is_dir) {
        g_transfer_total = 0;
        g_dirty = 1;
        render();
        copy_dir_recursive(srcw->volume, dstw->volume, src_path, dst_path, move_after_copy, 0);
    } else {
        g_transfer_total = sel->size;
        if (g_transfer_total == 0) {
            EFI_FILE_PROTOCOL *probe = 0;
            if (open_file_by_path(srcw->volume, src_path, &probe, EFI_FILE_MODE_READ, 0)) {
                uint8_t fi_buf[sizeof(EFI_FILE_INFO) + 256];
                UINTN fi_sz = sizeof(fi_buf);
                if (probe->GetInfo(probe, (EFI_GUID *)&FileInfoGuid, &fi_sz, fi_buf) == EFI_SUCCESS) {
                    g_transfer_total = ((EFI_FILE_INFO *)fi_buf)->FileSize;
                }
                probe->Close(probe);
            }
        }
        g_dirty = 1;
        render();
        copy_single_file(srcw->volume, src_path, dstw->volume, dst_path, move_after_copy);
    }
    g_transfer_active = 0;
    load_window_entries(srcw);
    load_window_entries(dstw);
    g_dirty = 1;
}

/* Build a CHAR16 confirm message: "LABEL\nACTION" truncated to fit dialog */
static void c16_to_confirm_msg(CHAR16 *dst, uint32_t max, const CHAR16 *name, const CHAR16 *action)
{
    uint32_t ai = 0;
    while (action[ai] && ai + 1 < max) {
        dst[ai] = action[ai];
        ai++;
    }
    if (ai + 3 < max) { dst[ai++] = L' '; dst[ai++] = L'['; }
    uint32_t ni = 0;
    while (name[ni] && ai + 2 < max && ni < 30) {
        dst[ai++] = name[ni++];
    }
    if (ai + 1 < max) dst[ai++] = L']';
    dst[ai] = 0;
}

/* Recursively delete a directory and all its contents */
static void delete_recursive(uint32_t vol, const CHAR16 *path, uint32_t depth)
{
    if (depth > 12) return;
    EFI_FILE_PROTOCOL *dir = 0;
    if (!open_file_by_path(vol, path, &dir, EFI_FILE_MODE_READ, 0)) {
        return;
    }
    /* Enumerate children */
    for (;;) {
        uint8_t info_buf[1024];
        UINTN sz = sizeof(info_buf);
        if (dir->Read(dir, &sz, info_buf) != EFI_SUCCESS || sz == 0) break;
        EFI_FILE_INFO *info = (EFI_FILE_INFO *)info_buf;
        if (!info->FileName[0] ||
            (info->FileName[0] == L'.' && (!info->FileName[1] || c16_is_dotdot(info->FileName)))) {
            continue;
        }
        CHAR16 child[256];
        c16_join_path(child, sizeof(child) / sizeof(child[0]), path, info->FileName);
        if (info->Attribute & EFI_FILE_DIRECTORY) {
            dir->Close(dir);
            delete_recursive(vol, child, depth + 1);
            /* Reopen parent directory to continue enumeration */
            if (!open_file_by_path(vol, path, &dir, EFI_FILE_MODE_READ, 0)) {
                return;
            }
        } else {
            EFI_FILE_PROTOCOL *f = 0;
            if (open_file_by_path(vol, child, &f, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
                f->Delete(f);
            }
        }
    }
    dir->Close(dir);
    /* Delete now-empty directory */
    EFI_FILE_PROTOCOL *self = 0;
    if (open_file_by_path(vol, path, &self, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
        self->Delete(self);
    }
}

/* Called when user confirms the pending action */
static void execute_pending_confirm(void)
{
    if (g_confirm_action == CONFIRM_DELETE) {
        if (g_pending_is_dir) {
            delete_recursive(g_pending_src_vol, g_pending_src_path, 0);
        } else {
            EFI_FILE_PROTOCOL *f = 0;
            if (open_file_by_path(g_pending_src_vol, g_pending_src_path,
                                  &f, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
                EFI_STATUS st = f->Delete(f);
                if (st == EFI_WARN_DELETE_FAILURE || st == EFI_WRITE_PROTECTED) {
                    set_last_error("SILME ISLEMI BASARISIZ");
                }
            }
        }
        load_window_entries(&g_windows[g_pending_src_win]);
    } else {
        /* CONFIRM_COPY or CONFIRM_MOVE */
        explorer_window_t *srcw = &g_windows[g_pending_src_win];
        explorer_window_t *dstw = &g_windows[g_pending_dst_win];
        uint8_t is_move = (g_confirm_action == CONFIRM_MOVE) ? 1 : 0;
        /* Re-setup transfer overlay with stored params */
        g_transfer_active = 1;
        g_transfer_is_move = is_move;
        g_transfer_is_dir = g_pending_is_dir;
        g_transfer_done = 0;
        g_transfer_file_count = 0;
        /* src display name = last component of src path */
        const CHAR16 *slash = g_pending_src_path;
        for (const CHAR16 *p = g_pending_src_path; *p; p++) {
            if (*p == L'\\') slash = p + 1;
        }
        c16_copy(g_transfer_src_name, slash,
                 sizeof(g_transfer_src_name) / sizeof(g_transfer_src_name[0]));
        if (g_pending_dst_vol < g_volume_count) {
            c16_copy(g_transfer_dst_vol, g_volumes[g_pending_dst_vol].label,
                     sizeof(g_transfer_dst_vol) / sizeof(g_transfer_dst_vol[0]));
        } else {
            g_transfer_dst_vol[0] = 0;
        }
        if (g_pending_is_dir) {
            g_transfer_total = 0;
            g_dirty = 1;
            render();
            copy_dir_recursive(g_pending_src_vol, g_pending_dst_vol,
                               g_pending_src_path, g_pending_dst_path, is_move, 0);
        } else {
            g_transfer_total = 0;
            /* Query size */
            EFI_FILE_PROTOCOL *probe = 0;
            if (open_file_by_path(g_pending_src_vol, g_pending_src_path, &probe, EFI_FILE_MODE_READ, 0)) {
                uint8_t fi_buf[sizeof(EFI_FILE_INFO) + 256];
                UINTN fi_sz = sizeof(fi_buf);
                if (probe->GetInfo(probe, (EFI_GUID *)&FileInfoGuid, &fi_sz, fi_buf) == EFI_SUCCESS) {
                    g_transfer_total = ((EFI_FILE_INFO *)fi_buf)->FileSize;
                }
                probe->Close(probe);
            }
            g_dirty = 1;
            render();
            copy_single_file(g_pending_src_vol, g_pending_src_path,
                             g_pending_dst_vol, g_pending_dst_path, is_move);
        }
        g_transfer_active = 0;
        load_window_entries(srcw);
        load_window_entries(dstw);
        g_dirty = 1;
    }
}

static void delete_selected(void)
{
    explorer_window_t *win = &g_windows[g_active_window];
    CHAR16 path[256];
    if (!selected_full_path(win, path, sizeof(path) / sizeof(path[0]))) {
        return;
    }
    if (c16_is_dotdot(win->entries[win->selected].name)) {
        return;
    }
    /* Snapshot pending parameters and open confirm dialog */
    g_pending_src_win = g_active_window;
    c16_copy(g_pending_src_path, path, sizeof(g_pending_src_path) / sizeof(g_pending_src_path[0]));
    g_pending_src_vol = win->volume;
    g_pending_is_dir = win->entries[win->selected].is_dir;
    /* Build confirm message */
    if (g_pending_is_dir) {
        c16_to_confirm_msg(g_confirm_msg, sizeof(g_confirm_msg) / sizeof(g_confirm_msg[0]),
                           win->entries[win->selected].name, L"KLASORU SIL?");
    } else {
        c16_to_confirm_msg(g_confirm_msg, sizeof(g_confirm_msg) / sizeof(g_confirm_msg[0]),
                           win->entries[win->selected].name, L"DOSYAYI SIL?");
    }
    g_confirm_action = CONFIRM_DELETE;
    g_confirm_open = 1;
}

static void open_create_dialog_impl(uint32_t win_idx, uint8_t is_dir)
{
    explorer_window_t *win = &g_windows[win_idx];
    uint8_t writable = 0;
    if (win->mode == EXPLORER_MODE_FILES && win->volume < g_volume_count) {
        writable = (g_volumes[win->volume].firmware_fs && !g_volumes[win->volume].read_only) ||
                   ((g_volumes[win->volume].native_fs == NATIVE_FS_EXFAT ||
                     g_volumes[win->volume].native_fs == NATIVE_FS_NTFS) &&
                    g_volumes[win->volume].native_writable);
    }
    if (!writable) {
        set_last_error(is_dir ? "KLASOR ICIN YAZILABILIR BIRIM GEREKLI" : "DOSYA ICIN YAZILABILIR BIRIM GEREKLI");
        return;
    }
    g_create_win_idx = win_idx;
    g_create_is_dir  = is_dir;
    g_create_name[0] = 0;
    g_ctx_open = 0;
    g_create_open = 1;
}

static void open_create_dialog(void)
{
    open_create_dialog_impl(g_active_window, 0);
}

static void open_create_folder_dialog(void)
{
    open_create_dialog_impl(g_active_window, 1);
}

static void commit_create_file(void)
{
    if (!g_create_open || !g_create_name[0]) {
        g_create_open = 0;
        return;
    }
    explorer_window_t *win = &g_windows[g_create_win_idx];
    if (win->mode != EXPLORER_MODE_FILES) {
        g_create_open = 0;
        return;
    }
    CHAR16 full[256];
    c16_join_path(full, sizeof(full) / sizeof(full[0]), win->path, g_create_name);
    EFI_FILE_PROTOCOL *file = 0;
    uint64_t attr = g_create_is_dir ? EFI_FILE_DIRECTORY : 0;
    if (open_file_by_path(win->volume, full, &file,
                          EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, attr)) {
        file->Close(file);
        load_window_entries(win);
    } else {
        set_last_error(g_create_is_dir ? "KLASOR OLUSTURULAMADI" : "DOSYA OLUSTURULAMADI");
    }
    g_create_open = 0;
    g_create_name[0] = 0;
}

static void open_rename_dialog(uint32_t win_idx, uint32_t entry_idx)
{
    explorer_window_t *win = &g_windows[win_idx];
    if (win->mode != EXPLORER_MODE_FILES || entry_idx >= win->entry_count) return;
    file_entry_t *e = &win->entries[entry_idx];
    if (c16_is_dotdot(e->name)) return;
    g_rename_win_idx = win_idx;
    g_rename_vol = win->volume;
    /* Build old full path */
    c16_join_path(g_rename_old_path, sizeof(g_rename_old_path)/sizeof(g_rename_old_path[0]),
                  win->path, e->name);
    /* Pre-fill new name with current name */
    c16_copy(g_rename_name, e->name, sizeof(g_rename_name)/sizeof(g_rename_name[0]));
    g_rename_open = 1;
    g_ctx_open = 0;
}

static void commit_rename(void)
{
    if (!g_rename_open || !g_rename_name[0]) { g_rename_open = 0; return; }
    explorer_window_t *win = &g_windows[g_rename_win_idx];
    if (win->mode != EXPLORER_MODE_FILES) { g_rename_open = 0; return; }
    /* Build new path = parent dir + new name */
    CHAR16 new_path[256];
    /* Get parent dir of old path */
    CHAR16 parent[256];
    c16_copy(parent, g_rename_old_path, sizeof(parent)/sizeof(parent[0]));
    c16_parent(parent);
    c16_join_path(new_path, sizeof(new_path)/sizeof(new_path[0]), parent, g_rename_name);
    if (!c16_equal_ci(g_rename_old_path, new_path)) {
        EFI_FILE_PROTOCOL *existing = 0;
        if (open_file_by_path(g_rename_vol, new_path, &existing, EFI_FILE_MODE_READ, 0)) {
            existing->Close(existing);
            set_last_error("YENIDEN ADLANDIRMA: HEDEF VAR");
            g_rename_open = 0;
            return;
        }
    }
    /* Open old file with read+write */
    EFI_FILE_PROTOCOL *f = 0;
    if (!open_file_by_path(g_rename_vol, g_rename_old_path, &f,
                           EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
        set_last_error("YENIDEN ADLANDIRMA: ACMA HATASI");
        g_rename_open = 0;
        return;
    }
    /* Build EFI_FILE_INFO with new name */
    uint8_t fi_buf[sizeof(EFI_FILE_INFO) + 384];
    UINTN fi_sz = sizeof(fi_buf);
    if (f->GetInfo(f, (EFI_GUID *)&FileInfoGuid, &fi_sz, fi_buf) != EFI_SUCCESS) {
        f->Close(f);
        set_last_error("YENIDEN ADLANDIRMA: BILGI ALINAMADI");
        g_rename_open = 0;
        return;
    }
    EFI_FILE_INFO *info = (EFI_FILE_INFO *)fi_buf;
    /* Copy new name into FileName field */
    uint32_t ni = 0;
    while (g_rename_name[ni] && ni < 95) {
        info->FileName[ni] = g_rename_name[ni];
        ni++;
    }
    info->FileName[ni] = 0;
    UINTN new_fi_sz = (UINTN)offsetof(EFI_FILE_INFO, FileName) + (ni + 1) * sizeof(CHAR16);
    if (new_fi_sz > sizeof(fi_buf)) {
        f->Close(f);
        set_last_error("YENIDEN ADLANDIRMA: AD COK UZUN");
        g_rename_open = 0;
        return;
    }
    info->Size = new_fi_sz;
    EFI_STATUS st = f->SetInfo(f, (EFI_GUID *)&FileInfoGuid, new_fi_sz, fi_buf);
    f->Close(f);
    if (st == EFI_SUCCESS) {
        load_window_entries(win);
    } else {
        set_last_error("YENIDEN ADLANDIRMA BASARISIZ");
    }
    g_rename_open = 0;
    g_rename_name[0] = 0;
}

static void open_rename_from_active(void)
{
    explorer_window_t *win = &g_windows[g_active_window];
    if (win->mode == EXPLORER_MODE_FILES && win->entry_count > 0) {
        open_rename_dialog(g_active_window, win->selected);
    }
}

static void ctx_execute(uint32_t item)
{
    g_ctx_open = 0;
    if (g_ctx_mode == 1) {
        /* Background menu */
        set_active_window(g_ctx_win);
        open_create_dialog_impl(g_ctx_win, item == CTX_BG_NEW_FOLDER ? 1 : 0);
        return;
    }
    explorer_window_t *win = &g_windows[g_ctx_win];
    /* Temporarily make this window active so existing ops use it */
    uint32_t prev_active = g_active_window;
    g_active_window = g_ctx_win;
    /* Also select the entry the menu was opened on */
    win->selected = g_ctx_entry;
    switch (item) {
        case CTX_RENAME: open_rename_dialog(g_ctx_win, g_ctx_entry); break;
        case CTX_COPY:   copy_selected_to_other(0); break;
        case CTX_MOVE:   copy_selected_to_other(1); break;
        case CTX_DELETE: delete_selected(); break;
        default: break;
    }
    if (item != CTX_RENAME) {
        g_active_window = prev_active;
    }
}

static void set_active_window(uint32_t index)
{
    if (index >= MAX_EXPLORER_WINDOWS || !g_windows[index].visible) {
        return;
    }
    g_active_window = index;
    g_active_surface = ACTIVE_EXPLORER;
    for (uint32_t i = 0; i < MAX_EXPLORER_WINDOWS; i++) {
        g_windows[i].active = i == g_active_window;
    }
}

static void cycle_active_volume(void)
{
    if (!g_volume_count) {
        return;
    }
    explorer_window_t *win = &g_windows[g_active_window];
    win->volume = (win->volume + 1) % g_volume_count;
    win->path[0] = 0;
    win->selected = 0;
    win->scroll = 0;
    if (!volume_is_browsable(win->volume) && g_volumes[win->volume].native_fs != NATIVE_FS_NONE) {
        native_ensure_ready(win->volume);
    }
    win->mode = volume_is_browsable(win->volume) ? EXPLORER_MODE_FILES : EXPLORER_MODE_PART_INFO;
    if (win->mode == EXPLORER_MODE_FILES) {
        load_window_entries(win);
    } else {
        win->entry_count = 0;
    }
}

static void go_parent_or_stage(explorer_window_t *win)
{
    if (!win) {
        return;
    }
    if (win->mode == EXPLORER_MODE_FILES) {
        if (win->path[0]) {
            c16_parent(win->path);
            load_window_entries(win);
        } else {
            build_volume_map_for_disk(win);
            win->mode = EXPLORER_MODE_VOLUMES;
            win->selected = 0;
            win->scroll = 0;
        }
    } else if (win->mode == EXPLORER_MODE_PART_INFO) {
        build_volume_map_for_disk(win);
        win->mode = EXPLORER_MODE_VOLUMES;
        win->selected = 0;
        win->scroll = 0;
    } else if (win->mode == EXPLORER_MODE_VOLUMES) {
        win->mode = EXPLORER_MODE_DISKS;
        win->selected = win->disk;
        win->scroll = 0;
    }
}

static void open_new_explorer(void)
{
    for (uint32_t i = 0; i < MAX_EXPLORER_WINDOWS; i++) {
        if (!g_windows[i].visible) {
            g_windows[i].visible = 1;
            g_windows[i].mode = EXPLORER_MODE_DISKS;
            g_windows[i].disk = g_disk_count ? g_disk_map[0] : 0;
            g_windows[i].volume = g_volume_count ? 0 : 0;
            g_windows[i].path[0] = 0;
            g_windows[i].entry_count = 0;
            g_windows[i].selected = 0;
            g_windows[i].scroll = 0;
            g_windows[i].x = content_x() + (int)((20 + i * 18) * ui_scale());
            g_windows[i].y = content_y() + (int)((118 + i * 14) * ui_scale());
            g_windows[i].w = (int)(250 * ui_scale());
            g_windows[i].h = (int)(190 * ui_scale());
            set_active_window(i);
            return;
        }
    }
    set_last_error("MAKSIMUM GEZGIN PENCERESI ACILDI");
}

static void terminal_log(const char *text)
{
    if (g_terminal_line_count < sizeof(g_terminal_lines) / sizeof(g_terminal_lines[0])) {
        ascii_copy(g_terminal_lines[g_terminal_line_count++], text, sizeof(g_terminal_lines[0]));
        return;
    }
    for (uint32_t i = 1; i < sizeof(g_terminal_lines) / sizeof(g_terminal_lines[0]); i++) {
        ascii_copy(g_terminal_lines[i - 1], g_terminal_lines[i], sizeof(g_terminal_lines[0]));
    }
    ascii_copy(g_terminal_lines[(sizeof(g_terminal_lines) / sizeof(g_terminal_lines[0])) - 1], text, sizeof(g_terminal_lines[0]));
}

static void terminal_log_name(const char *prefix, const CHAR16 *name)
{
    char line[96];
    uint32_t p = 0;
    for (uint32_t i = 0; prefix && prefix[i] && p + 1 < sizeof(line); i++) {
        line[p++] = prefix[i];
    }
    char n[64];
    c16_to_ascii(n, name, sizeof(n));
    for (uint32_t i = 0; n[i] && p + 1 < sizeof(line); i++) {
        line[p++] = n[i];
    }
    line[p] = 0;
    terminal_log(line);
}

static void terminal_open(void)
{
    g_terminal_visible = 1;
    g_active_surface = ACTIVE_TERMINAL;
    if (!g_terminal_w) {
        uint32_t scale = ui_scale();
        g_terminal_w = (int)(360 * scale);
        g_terminal_h = (int)(170 * scale);
        g_terminal_x = content_x() + (int)(34 * scale);
        g_terminal_y = content_y() + (int)(126 * scale);
    }
    if (!g_terminal_line_count) {
        terminal_log("CaYaTerm hazir. help yazin.");
    }
}

static char *next_token(char **p, char *out, uint32_t max)
{
    uint32_t i = 0;
    char *s = *p;
    while (*s == ' ') {
        s++;
    }
    while (*s && *s != ' ' && i + 1 < max) {
        out[i++] = *s++;
    }
    out[i] = 0;
    while (*s == ' ') {
        s++;
    }
    *p = s;
    return out;
}

static int parse_path_token(const char *token, uint32_t *volume, CHAR16 *path, uint32_t max)
{
    uint32_t vol = g_terminal_volume;
    const char *p = token;
    if (!path || !volume || !max) {
        return 0;
    }
    c16_copy(path, g_terminal_path, max);
    if (!token || !token[0]) {
        *volume = vol;
        return 1;
    }
    if ((p[0] == 'v' || p[0] == 'V') && (p[1] == 'o' || p[1] == 'O') && (p[2] == 'l' || p[2] == 'L') && p[3] >= '0' && p[3] <= '9') {
        vol = (uint32_t)(p[3] - '0');
        p += 4;
        if (*p == ':') {
            p++;
        }
    } else if (p[0] >= '0' && p[0] <= '9' && p[1] == ':') {
        vol = (uint32_t)(p[0] - '0');
        p += 2;
    }
    if (vol >= g_volume_count) {
        return 0;
    }
    if (p[0] == '\\' || p[0] == '/') {
        path[0] = 0;
        while (*p == '\\' || *p == '/') {
            p++;
        }
    }
    if (p[0] == '.' && p[1] == '.' && !p[2]) {
        c16_parent(path);
        *volume = vol;
        return 1;
    }
    if (p[0] && !(p[0] == '.' && !p[1])) {
        CHAR16 rel[160];
        uint32_t i = 0;
        while (p[i] && i + 1 < sizeof(rel) / sizeof(rel[0])) {
            rel[i] = (p[i] == '/') ? L'\\' : (CHAR16)(uint8_t)p[i];
            i++;
        }
        rel[i] = 0;
        c16_join_path(path, max, path, rel);
    }
    *volume = vol;
    return 1;
}

static int terminal_path_is_dir(uint32_t volume, const CHAR16 *path)
{
    EFI_FILE_PROTOCOL *dir = 0;
    memset(&g_temp_window, 0, sizeof(g_temp_window));
    g_temp_window.volume = volume;
    g_temp_window.mode = EXPLORER_MODE_FILES;
    c16_copy(g_temp_window.path, path, sizeof(g_temp_window.path) / sizeof(g_temp_window.path[0]));
    if (open_window_dir(&g_temp_window, &dir)) {
        dir->Close(dir);
        return 1;
    }
    return 0;
}

static void terminal_dir(const char *arg)
{
    uint32_t vol = 0;
    CHAR16 path[256];
    if (!parse_path_token(arg, &vol, path, sizeof(path) / sizeof(path[0]))) {
        terminal_log("Birim bulunamadi.");
        return;
    }
    EFI_FILE_PROTOCOL *dir = 0;
    memset(&g_temp_window, 0, sizeof(g_temp_window));
    g_temp_window.volume = vol;
    g_temp_window.mode = EXPLORER_MODE_FILES;
    c16_copy(g_temp_window.path, path, sizeof(g_temp_window.path) / sizeof(g_temp_window.path[0]));
    if (!open_window_dir(&g_temp_window, &dir)) {
        terminal_log("Klasor acilamadi.");
        return;
    }
    terminal_log("DIR:");
    for (uint32_t shown = 0; shown < 7;) {
        uint8_t info_buf[1024];
        UINTN sz = sizeof(info_buf);
        EFI_STATUS st = dir->Read(dir, &sz, info_buf);
        if (st != EFI_SUCCESS || sz == 0) {
            break;
        }
        EFI_FILE_INFO *info = (EFI_FILE_INFO *)info_buf;
        if (!info->FileName[0] || (info->FileName[0] == L'.' && !info->FileName[1])) {
            continue;
        }
        terminal_log_name((info->Attribute & EFI_FILE_DIRECTORY) ? "[D] " : "    ", info->FileName);
        shown++;
    }
    dir->Close(dir);
}

static void terminal_open_file(const char *arg)
{
    uint32_t vol = 0;
    CHAR16 path[256];
    if (!parse_path_token(arg, &vol, path, sizeof(path) / sizeof(path[0]))) {
        terminal_log("Yol gecersiz.");
        return;
    }
    EFI_FILE_PROTOCOL *file = 0;
    if (!open_file_by_path(vol, path, &file, EFI_FILE_MODE_READ, 0)) {
        terminal_log("Dosya acilamadi.");
        return;
    }
    UINTN sz = sizeof(g_viewer_text) - 1;
    if (file->Read(file, &sz, g_viewer_text) == EFI_SUCCESS) {
        g_viewer_text[sz] = 0;
        for (UINTN i = 0; i < sz; i++) {
            uint8_t c = (uint8_t)g_viewer_text[i];
            if (c == '\r') {
                g_viewer_text[i] = '\n';
            } else if (c < 32 && c != '\n' && c != '\t') {
                g_viewer_text[i] = '.';
            }
        }
        c16_from_ascii(g_viewer_title, arg, sizeof(g_viewer_title) / sizeof(g_viewer_title[0]));
        g_viewer_vol = vol;
        c16_copy(g_viewer_path, path, sizeof(g_viewer_path) / sizeof(g_viewer_path[0]));
        g_viewer_cursor = (uint32_t)sz;
        g_viewer_scroll = 0;
        g_viewer_edit = 0;
        g_viewer_open = 1;
    }
    file->Close(file);
}

static void terminal_copy_move(const char *src_arg, const char *dst_arg, uint8_t move)
{
    uint32_t src_vol = 0, dst_vol = 0;
    CHAR16 src_path[256], dst_path[256];
    if (!parse_path_token(src_arg, &src_vol, src_path, sizeof(src_path) / sizeof(src_path[0])) ||
        !parse_path_token(dst_arg, &dst_vol, dst_path, sizeof(dst_path) / sizeof(dst_path[0]))) {
        terminal_log("Yol gecersiz.");
        return;
    }
    EFI_FILE_PROTOCOL *src = 0;
    EFI_FILE_PROTOCOL *dst = 0;
    uint64_t dst_size = 0;
    uint64_t src_size = 0;
    uint8_t ok = 1;
    if (!open_file_by_path(src_vol, src_path, &src, EFI_FILE_MODE_READ, 0)) {
        terminal_log("Kaynak acilamadi.");
        return;
    }
    get_file_size(src, &src_size);
    EFI_FILE_PROTOCOL *old = 0;
    if (open_file_by_path(dst_vol, dst_path, &old, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
        old->Delete(old);
    }
    if (!open_file_by_path(dst_vol, dst_path, &dst, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0)) {
        src->Close(src);
        terminal_log("Hedef acilamadi.");
        return;
    }
    if (!preallocate_destination_file(dst_vol, dst, src_size)) {
        dst->Close(dst);
        src->Close(src);
        terminal_log("Hedefte alan ayrilamadi.");
        return;
    }
    for (;;) {
        UINTN read_sz = sizeof(g_io_buffer);
        if (src->Read(src, &read_sz, g_io_buffer) != EFI_SUCCESS || read_sz == 0) {
            break;
        }
        UINTN write_sz = read_sz;
        if (dst->Write(dst, &write_sz, g_io_buffer) != EFI_SUCCESS || write_sz != read_sz) {
            terminal_log("Yazma hatasi.");
            ok = 0;
            break;
        }
        dst_size += read_sz;
    }
    if (ok && !set_file_size(dst, dst_size)) {
        terminal_log("Boyut guncellenemedi.");
        ok = 0;
    }
    dst->Flush(dst);
    dst->Close(dst);
    if (!ok) {
        src->Close(src);
        return;
    }
    if (move) {
        src->Delete(src);
    } else {
        src->Close(src);
    }
    detect_file_systems(g_image, 0);
    terminal_log(move ? "Tasi tamam." : "Kopya tamam.");
}

static void terminal_delete(const char *arg)
{
    uint32_t vol = 0;
    CHAR16 path[256];
    if (!parse_path_token(arg, &vol, path, sizeof(path) / sizeof(path[0]))) {
        terminal_log("Yol gecersiz.");
        return;
    }
    EFI_FILE_PROTOCOL *file = 0;
    if (open_file_by_path(vol, path, &file, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
        EFI_STATUS st = file->Delete(file);
        terminal_log(st == EFI_SUCCESS ? "Silindi." : "Silme basarisiz.");
        detect_file_systems(g_image, 0);
    } else {
        terminal_log("Dosya acilamadi.");
    }
}

static void terminal_execute(void)
{
    char command[16], a[96], b[96];
    char *p = g_terminal_input;
    next_token(&p, command, sizeof(command));
    next_token(&p, a, sizeof(a));
    next_token(&p, b, sizeof(b));
    if (!command[0]) {
        return;
    }
    terminal_log(g_terminal_input);
    if (ascii_eq(command, "help")) {
        terminal_log("dir cd copy move del open clear reboot shutdown");
    } else if (ascii_eq(command, "clear")) {
        g_terminal_line_count = 0;
    } else if (ascii_eq(command, "reboot") || ascii_eq(command, "restart")) {
        terminal_log("Yeniden baslatiliyor...");
        render();
        system_reset(EFI_RESET_COLD);
        terminal_log("Yeniden baslatma desteklenmiyor.");
    } else if (ascii_eq(command, "shutdown") || ascii_eq(command, "poweroff")) {
        terminal_log("Sistem kapatiliyor...");
        render();
        system_reset(EFI_RESET_SHUTDOWN);
        terminal_log("Kapatma desteklenmiyor.");
    } else if (ascii_eq(command, "dir") || ascii_eq(command, "ls")) {
        terminal_dir(a);
    } else if (ascii_eq(command, "cd")) {
        uint32_t vol = 0;
        CHAR16 path[256];
        if (parse_path_token(a, &vol, path, sizeof(path) / sizeof(path[0])) && terminal_path_is_dir(vol, path)) {
            g_terminal_volume = vol;
            c16_copy(g_terminal_path, path, sizeof(g_terminal_path) / sizeof(g_terminal_path[0]));
            terminal_log("Klasor degisti.");
        } else {
            terminal_log("Klasor bulunamadi.");
        }
    } else if (ascii_eq(command, "copy") || ascii_eq(command, "cp")) {
        terminal_copy_move(a, b, 0);
    } else if (ascii_eq(command, "move") || ascii_eq(command, "mv")) {
        terminal_copy_move(a, b, 1);
    } else if (ascii_eq(command, "del") || ascii_eq(command, "rm")) {
        terminal_delete(a);
    } else if (ascii_eq(command, "open")) {
        terminal_open_file(a);
    } else {
        terminal_log("Bilinmeyen komut.");
    }
    g_terminal_input[0] = 0;
}

static int top_h(void)
{
    return (int)(56 * ui_scale());
}

static int side_w(void)
{
    return (int)(188 * ui_scale());
}

static int content_x(void)
{
    return side_w() + (int)(22 * ui_scale());
}

static int content_y(void)
{
    return top_h() + (int)(22 * ui_scale());
}

static int content_w(void)
{
    int w = (int)g_w - content_x() - (int)(22 * ui_scale());
    return w > 80 ? w : 80;
}

static int content_h(void)
{
    int h = (int)g_h - content_y() - (int)(44 * ui_scale());
    return h > 80 ? h : 80;
}

static void draw_os_background(void)
{
    for (uint32_t y = 0; y < g_h; y++) {
        uint32_t shade = (y * 12) / (g_h ? g_h : 1);
        for (uint32_t x = 0; x < g_w; x++) {
            uint32_t side = x < (uint32_t)side_w() ? 2 : 0;
            g_backbuffer[y * g_w + x] = rgb((uint8_t)(7 + shade / 6 + side),
                                            (uint8_t)(11 + shade / 5 + side),
                                            (uint8_t)(24 + shade));
        }
    }
}

static void draw_logo(int x, int y, uint32_t scale)
{
    fill_rect(x - (int)(2 * scale), y - (int)(2 * scale), (int)(78 * scale), (int)(14 * scale), rgb(11, 16, 29));
    fill_rect(x, y + (int)(9 * scale), (int)(38 * scale), (int)(2 * scale), rgb(220, 39, 39));
    fill_rect(x + (int)(40 * scale), y + (int)(9 * scale), (int)(6 * scale), (int)(2 * scale), rgb(246, 247, 252));
    draw_text_scale(x, y, "CAYA", rgb(220, 39, 39), scale);
    draw_text_scale(x + (int)(25 * scale), y, "DEV", rgb(246, 247, 252), scale);
}

static void draw_top_bar(void)
{
    uint32_t scale = ui_scale();
    fill_rect(0, 0, (int)g_w, top_h(), rgb(10, 16, 30));
    fill_rect(0, top_h() - 1, (int)g_w, 1, rgb(42, 31, 49));
    draw_logo((int)(22 * scale), (int)(18 * scale), scale + 1);
    draw_text((int)(170 * scale), (int)(24 * scale), "CaYaBasicOS", rgb(235, 238, 245));
    draw_text((int)(g_w - 230 * scale), (int)(24 * scale), "UEFI X64", rgb(202, 209, 224));
    draw_text((int)(g_w - 120 * scale), (int)(24 * scale), "CAYADEV.COM", rgb(220, 39, 39));
}

static void draw_sidebar(void)
{
    static const char *items[] = {"GENEL", "İŞLEMCİ", "BELLEK", "DEPOLAMA", "EKRAN", "DOSYALAR"};
    uint32_t scale = ui_scale();
    int sw = side_w();
    fill_rect(0, top_h(), sw, (int)g_h - top_h(), rgb(9, 13, 25));
    draw_text((int)(22 * scale), top_h() + (int)(24 * scale), "KONTROL", rgb(126, 136, 158));
    for (uint32_t i = 0; i < 6; i++) {
        int y = top_h() + (int)((58 + i * 42) * scale);
        if (i == g_page) {
            fill_rect((int)(14 * scale), y - (int)(10 * scale), sw - (int)(28 * scale), (int)(30 * scale), rgb(39, 20, 35));
            fill_rect((int)(14 * scale), y - (int)(10 * scale), 3, (int)(30 * scale), rgb(220, 39, 39));
            draw_text((int)(28 * scale), y, items[i], rgb(250, 250, 252));
        } else {
            draw_text((int)(28 * scale), y, items[i], rgb(184, 194, 214));
        }
    }
    draw_text((int)(22 * scale), (int)g_h - (int)(58 * scale), "GELİŞTİREN", rgb(126, 136, 158));
    draw_text((int)(22 * scale), (int)g_h - (int)(38 * scale), "CAYADEV.COM", rgb(220, 39, 39));
}

static void draw_card(int x, int y, int w, int h, const char *title, const char *value, uint32_t accent)
{
    fill_rect(x, y, w, h, rgb(12, 18, 32));
    draw_rect(x, y, w, h, rgb(37, 46, 70));
    fill_rect(x, y, 3, h, accent);
    draw_text(x + (int)(14 * ui_scale()), y + (int)(14 * ui_scale()), title, rgb(139, 150, 174));
    draw_text_scale(x + (int)(14 * ui_scale()), y + (int)(36 * ui_scale()), value, rgb(246, 247, 252), ui_scale() + 1);
}

static void draw_info_row(int x, int *y, const char *label, const char *value)
{
    draw_text(x, *y, label, rgb(137, 148, 170));
    draw_text(x + (int)(160 * ui_scale()), *y, value, rgb(238, 241, 248));
    *y += (int)(18 * ui_scale());
}

static void draw_summary_cards(void)
{
    char mem[24], disks[24], volumes[24];
    u64_to_dec(g_memory_mb, mem);
    u64_to_dec(g_disk_count, disks);
    u64_to_dec(g_real_vol_count, volumes);
    /* Input type string */
    const char *input_str = g_abs_ptr_count ? "TOUCH" : (g_simple_ptr_count ? "FARE" : "YOK");
    if (g_abs_ptr_count && g_simple_ptr_count) input_str = "FARE+TOUCH";
    int x = content_x();
    int y = content_y();
    int gap = (int)(12 * ui_scale());
    int w = (content_w() - gap * 3) / 4;
    int h = (int)(76 * ui_scale());
    draw_card(x, y, w, h, "RAM MB", mem, rgb(220, 39, 39));
    draw_card(x + w + gap, y, w, h, "DISK", disks, rgb(30, 132, 212));
    draw_card(x + (w + gap) * 2, y, w, h, "BİRİM", volumes, rgb(30, 132, 212));
    draw_card(x + (w + gap) * 3, y, w, h, "GİRİŞ", input_str, rgb(220, 39, 39));
}

static void make_volume_path(explorer_window_t *win, CHAR16 *out, uint32_t max)
{
    if (!max) {
        return;
    }
    out[0] = 0;
    if (g_volume_count && win->volume < g_volume_count) {
        c16_copy(out, g_volumes[win->volume].label, max);
    } else {
        c16_from_ascii(out, "YOK", max);
    }
    c16_append_char(out, L':', max);
    c16_append_char(out, L'\\', max);
    c16_append(out, win->path, max);
}

static void draw_size_value(int x, int y, uint64_t bytes, uint32_t color)
{
    char num[24];
    const char *unit = "B";
    uint64_t value = bytes;
    if (bytes >= 1024ULL * 1024ULL) {
        value = bytes / (1024ULL * 1024ULL);
        unit = "MB";
    } else if (bytes >= 1024ULL) {
        value = bytes / 1024ULL;
        unit = "KB";
    }
    u64_to_dec(value, num);
    draw_text(x, y, num, color);
    draw_text(x + (int)(42 * ui_scale()), y, unit, color);
}

static void ensure_explorer_geometry(uint32_t index, int area_x, int area_y, int area_w, int area_h)
{
    explorer_window_t *win = &g_windows[index];
    if (win->w > 0 && win->h > 0) {
        return;
    }
    int gap = (int)(14 * ui_scale());
    int base_w = (area_w - gap) / 2;
    int base_h = area_h > (int)(210 * ui_scale()) ? (int)(210 * ui_scale()) : area_h;
    if (base_w < (int)(220 * ui_scale())) {
        base_w = area_w - (int)(20 * ui_scale());
    }
    win->x = area_x + (int)((index % 3) * 22 * ui_scale());
    win->y = area_y + (int)((index % 3) * 16 * ui_scale());
    if (index == 1) {
        win->x = area_x + base_w + gap;
        win->y = area_y;
    }
    win->w = base_w;
    win->h = base_h;
}

static void draw_explorer_window(uint32_t index)
{
    explorer_window_t *win = &g_windows[index];
    if (!win->visible) {
        return;
    }
    uint32_t scale = ui_scale();
    int x = win->x;
    int y = win->y;
    int w = win->w;
    int h = win->h;
    int header_h = (int)(30 * scale);
    int row_h = (int)(18 * scale);
    int row_y = y + header_h + (int)(8 * scale);
    int rows = row_h ? (h - header_h - (int)(18 * scale)) / row_h : 0;
    uint32_t active = (g_active_surface == ACTIVE_EXPLORER && index == g_active_window);
    uint32_t border = active ? rgb(220, 39, 39) : rgb(42, 50, 72);
    uint32_t list_count = win->mode == EXPLORER_MODE_DISKS ? g_disk_count : (win->mode == EXPLORER_MODE_VOLUMES ? win->vol_count : win->entry_count);

    fill_rect(x, y, w, h, rgb(12, 18, 32));
    draw_rect(x, y, w, h, border);
    fill_rect(x + 1, y + 1, w - 2, header_h - 1, active ? rgb(34, 22, 34) : rgb(16, 23, 39));
    draw_text(x + (int)(10 * scale), y + (int)(10 * scale), "GEZGIN", rgb(246, 247, 252));
    draw_text(x + (int)(58 * scale), y + (int)(10 * scale),
        win->mode == EXPLORER_MODE_DISKS    ? "DISK SEC" :
        win->mode == EXPLORER_MODE_VOLUMES  ? "BIRIM SEC" :
        win->mode == EXPLORER_MODE_PART_INFO ? "BOLUM BILGI" :
        "DOSYALAR", rgb(156, 168, 192));
    draw_text(x + w - (int)(18 * scale), y + (int)(10 * scale), "X", rgb(220, 39, 39));

    if (win->mode == EXPLORER_MODE_FILES) {
        CHAR16 path[320];
        make_volume_path(win, path, sizeof(path) / sizeof(path[0]));
        int path_px = w - (int)(160 * scale);
        draw_text16_limited(x + (int)(122 * scale), y + (int)(10 * scale), path, rgb(126, 136, 158), path_px > 0 ? (uint32_t)(path_px / (int)(6 * scale)) : 0);
    }

    if (win->mode == EXPLORER_MODE_VOLUMES && !win->vol_count) {
        uint32_t no_vol_max = (uint32_t)((w - (int)(28 * scale)) / (int)(6 * scale));
        if (g_volume_count) {
            draw_text_n(x + (int)(14 * scale), row_y, "DESTEKLENEN DOSYA SISTEMI YOK", rgb(220, 39, 39), no_vol_max);
        } else {
            draw_text_n(x + (int)(14 * scale), row_y, "UEFI DOSYA BIRIMI BULUNAMADI", rgb(184, 194, 214), no_vol_max);
        }
        return;
    }
    /* PART_INFO mode: show static partition details, no scrollable list */
    if (win->mode == EXPLORER_MODE_PART_INFO) {
        uint32_t vi = win->volume;
        uint32_t bi = vi < g_volume_count && g_volumes[vi].block_idx != 0xFFFFFFFFU ?
                      g_volumes[vi].block_idx :
                      (vi < g_volume_count ? find_block_idx_for_handle(g_volumes[vi].handle) : 0xFFFFFFFF);
        volume_t *vol = vi < g_volume_count ? &g_volumes[vi] : 0;
        block_summary_t *blk = (bi != 0xFFFFFFFF) ? &g_blocks[bi] : 0;
        char num[24];
        int ly = row_y;
        /* FS type */
        draw_text(x + (int)(14 * scale), ly, "DOSYA SISTEMI", rgb(126, 136, 158));
        draw_text(x + (int)(130 * scale), ly, blk ? blk->fs_name : "?", rgb(220, 39, 39));
        ly += row_h;
        /* Size */
        if (blk) {
            uint64_t bytes = (uint64_t)blk->blocks * blk->block_size;
            uint64_t gb_int = bytes / (1024ULL * 1024ULL * 1024ULL);
            uint64_t mb_rem = (bytes % (1024ULL * 1024ULL * 1024ULL)) / (1024ULL * 1024ULL);
            draw_text(x + (int)(14 * scale), ly, "BOYUT", rgb(126, 136, 158));
            u64_to_dec(gb_int, num);
            draw_text(x + (int)(130 * scale), ly, num, rgb(220, 226, 239));
            draw_text(x + (int)(166 * scale), ly, "GB", rgb(126, 136, 158));
            u64_to_dec(mb_rem, num);
            draw_text(x + (int)(196 * scale), ly, num, rgb(220, 226, 239));
            draw_text(x + (int)(232 * scale), ly, "MB", rgb(126, 136, 158));
        }
        ly += row_h;
        /* Block size */
        if (blk) {
            draw_text(x + (int)(14 * scale), ly, "BLOK BOYUTU", rgb(126, 136, 158));
            u64_to_dec((uint64_t)blk->block_size, num);
            draw_text(x + (int)(130 * scale), ly, num, rgb(220, 226, 239));
            draw_text(x + (int)(166 * scale), ly, "B", rgb(126, 136, 158));
        }
        ly += row_h;
        /* Removable / writable */
        if (blk) {
            draw_text(x + (int)(14 * scale), ly, "MEDYA", rgb(126, 136, 158));
            draw_text(x + (int)(130 * scale), ly, blk->removable ? "CIKARILABILIR" : "SABIT", rgb(220, 226, 239));
        }
        ly += row_h;
        if (blk) {
            draw_text(x + (int)(14 * scale), ly, "ERISIM", rgb(126, 136, 158));
            if (vol && vol->firmware_fs) {
                draw_text(x + (int)(130 * scale), ly, blk->readonly ? "SALT OKUNUR" : "OKU/YAZ", rgb(220, 226, 239));
            } else if (vol && vol->native_ready) {
                draw_text(x + (int)(130 * scale), ly, vol->native_writable ? "OKU/YAZ" : "OKUMA", rgb(46, 204, 113));
            } else if (vol && vol->native_fs != NATIVE_FS_NONE) {
                draw_text(x + (int)(130 * scale), ly, "OKUMA DENENIYOR", rgb(220, 180, 80));
            } else {
                draw_text(x + (int)(130 * scale), ly, "DESTEK YOK", rgb(180, 90, 60));
            }
        }
        ly += row_h;
        draw_text(x + (int)(14 * scale), ly, "SURUCU", rgb(126, 136, 158));
        if (vol && vol->firmware_fs) {
            draw_text(x + (int)(130 * scale), ly, "UEFI SIMPLEFS", rgb(46, 204, 113));
        } else if (vol && vol->native_ready) {
            draw_text(x + (int)(130 * scale), ly, native_fs_driver_name(vol->native_fs), rgb(46, 204, 113));
        } else if (vol && vol->native_fs != NATIVE_FS_NONE) {
            draw_text(x + (int)(130 * scale), ly, "NATIVE BASLAT HATASI", rgb(220, 180, 80));
        } else {
            draw_text(x + (int)(130 * scale), ly, "DESTEKLENMIYOR", rgb(180, 90, 60));
        }
        if (vol && vol->native_ready) {
            ly += row_h;
            draw_text(x + (int)(14 * scale), ly, "ENTER", rgb(126, 136, 158));
            draw_text(x + (int)(130 * scale), ly, "DOSYALARI AC", rgb(46, 204, 113));
        }
        draw_text_n(x + (int)(10 * scale), y + h - (int)(14 * scale), "BACKSPACE GERI",
                    rgb(126, 136, 158), (uint32_t)((w - (int)(20 * scale)) / (int)(6 * scale)));
        return;
    }
    if (rows < 1) {
        return;
    }
    if (win->selected >= list_count && list_count) {
        win->selected = list_count - 1;
    }
    if (!list_count || (uint32_t)rows >= list_count) {
        win->scroll = 0;
    } else if (win->scroll + (uint32_t)rows > list_count) {
        win->scroll = list_count - (uint32_t)rows;
    }

    for (int r = 0; r < rows; r++) {
        uint32_t entry_index = win->scroll + (uint32_t)r;
        if (entry_index >= list_count) {
            break;
        }
        int yy = row_y + r * row_h;
        uint32_t selected = entry_index == win->selected;
        if (selected) {
            fill_rect(x + (int)(8 * scale), yy - (int)(3 * scale), w - (int)(16 * scale), row_h, active ? rgb(69, 24, 37) : rgb(31, 39, 58));
        }
        if (win->mode == EXPLORER_MODE_DISKS) {
            uint32_t bi = entry_index < g_disk_count ? g_disk_map[entry_index] : entry_index;
            block_summary_t *b = &g_blocks[bi];
            char num[24];
            draw_text(x + (int)(14 * scale), yy, "DISK", rgb(220, 39, 39));
            u64_to_dec((uint64_t)bi, num);
            draw_text(x + (int)(68 * scale), yy, num, rgb(220, 226, 239));
            draw_size_value(x + (int)(106 * scale), yy, b->blocks * b->block_size, rgb(126, 136, 158));
            draw_text(x + w - (int)(70 * scale), yy, b->fs_name, rgb(220, 39, 39));
        } else if (win->mode == EXPLORER_MODE_VOLUMES) {
            char num[24];
            uint32_t actual_vol = entry_index < win->vol_count ? win->vol_map[entry_index] : entry_index;
            volume_t *vol = &g_volumes[actual_vol];
            uint32_t blk_idx = vol->block_idx != 0xFFFFFFFFU ? vol->block_idx : find_block_idx_for_handle(vol->handle);
            const char *fs_name = blk_idx != 0xFFFFFFFF ? g_blocks[blk_idx].fs_name : "?";
            uint8_t browsable = volume_is_browsable(actual_vol);
            u64_to_dec((uint64_t)actual_vol, num);
            draw_text(x + (int)(14 * scale), yy, "BIRIM", browsable ? rgb(30, 132, 212) : rgb(126, 136, 158));
            draw_text(x + (int)(72 * scale), yy, "VOL", rgb(220, 226, 239));
            draw_text(x + (int)(108 * scale), yy, num, rgb(220, 226, 239));
            draw_text(x + (int)(150 * scale), yy, fs_name, browsable ? rgb(46, 204, 113) : rgb(180, 90, 60));
        } else {
            file_entry_t *e = &win->entries[entry_index];
            draw_text(x + (int)(14 * scale), yy, e->is_dir ? "DIR" : "FILE", e->is_dir ? rgb(30, 132, 212) : rgb(184, 194, 214));
            int name_px = w - (int)(150 * scale);
            uint32_t name_chars = name_px > 0 ? (uint32_t)(name_px / (int)(6 * scale)) : 0;
            draw_text16_limited(x + (int)(52 * scale), yy, e->name, selected ? rgb(255, 255, 255) : rgb(220, 226, 239), name_chars);
            if (!e->is_dir) {
                draw_size_value(x + w - (int)(86 * scale), yy, e->size, rgb(126, 136, 158));
            }
        }
    }

    /* Corner resize handles — small L-shaped marks */
    {
        int cz = (int)(8 * scale);
        int ct = (int)(2 * scale) + 1;
        uint32_t hcol = rgb(90, 110, 150);
        /* Top-left */
        fill_rect(x + 1,       y + 1,       cz, ct, hcol);
        fill_rect(x + 1,       y + 1,       ct, cz, hcol);
        /* Top-right */
        fill_rect(x + w - cz - 1, y + 1,   cz, ct, hcol);
        fill_rect(x + w - ct - 1, y + 1,   ct, cz, hcol);
        /* Bottom-left */
        fill_rect(x + 1,       y + h - ct - 1, cz, ct, hcol);
        fill_rect(x + 1,       y + h - cz - 1, ct, cz, hcol);
        /* Bottom-right */
        fill_rect(x + w - cz - 1, y + h - ct - 1, cz, ct, hcol);
        fill_rect(x + w - ct - 1, y + h - cz - 1, ct, cz, hcol);
    }

    /* Bottom hint bar — clipped to window width */
    uint32_t hint_max = (uint32_t)((w - (int)(20 * scale)) / (int)(6 * scale));
    draw_text_n(x + (int)(10 * scale), y + h - (int)(14 * scale),
                "ENTER AC  GERI  C/M KOP/TAS  O DOSYA  D KLASOR",
                rgb(126, 136, 158), hint_max);
}

static void draw_storage_rows(int x, int y, int w, int h)
{
    uint32_t scale = ui_scale();
    int disk_row_h = (int)(24 * scale);
    int part_row_h = (int)(18 * scale);
    char num[24];
    if (!g_disk_count) {
        draw_text(x, y, "UEFI FIZIKSEL DISK BULUNAMADI", rgb(184, 194, 214));
        return;
    }
    int cy = y;
    int bottom = y + h - (int)(14 * scale);
    for (uint32_t di = 0; di < g_disk_count && cy < bottom; di++) {
        uint32_t bi = g_disk_map[di];
        block_summary_t *d = &g_blocks[bi];
        /* Disk header row */
        fill_rect(x, cy, w, disk_row_h - (int)(2 * scale), rgb(24, 12, 14));
        draw_rect(x, cy, w, disk_row_h - (int)(2 * scale), rgb(220, 39, 39));
        draw_text(x + (int)(8 * scale), cy + (int)(7 * scale), "DISK", rgb(220, 39, 39));
        u64_to_dec((uint64_t)di, num);
        draw_text(x + (int)(48 * scale), cy + (int)(7 * scale), num, rgb(246, 247, 252));
        draw_text(x + (int)(72 * scale), cy + (int)(7 * scale), d->removable ? "CIKARILABILIR" : "SABIT", rgb(156, 168, 192));
        /* Total size */
        {
            uint64_t bytes = (uint64_t)d->blocks * d->block_size;
            uint64_t gb = bytes / (1024ULL * 1024ULL * 1024ULL);
            if (gb) {
                u64_to_dec(gb, num);
                draw_text(x + (int)(190 * scale), cy + (int)(7 * scale), num, rgb(220, 226, 239));
                draw_text(x + (int)(226 * scale), cy + (int)(7 * scale), "GB", rgb(126, 136, 158));
            } else {
                u64_to_dec(bytes / (1024ULL * 1024ULL), num);
                draw_text(x + (int)(190 * scale), cy + (int)(7 * scale), num, rgb(220, 226, 239));
                draw_text(x + (int)(226 * scale), cy + (int)(7 * scale), "MB", rgb(126, 136, 158));
            }
        }
        draw_text(x + w - (int)(50 * scale), cy + (int)(7 * scale), d->readonly ? "SALT-OKU" : "OKU/YAZ", rgb(156, 168, 192));
        cy += disk_row_h;
        /* Partition rows for this disk */
        for (uint32_t pi = 0; pi < g_block_count && cy < bottom; pi++) {
            if (!g_blocks[pi].logical_partition) continue;
            if (g_blocks[pi].parent_disk_idx != bi) continue;
            block_summary_t *p = &g_blocks[pi];
            fill_rect(x + (int)(10 * scale), cy, w - (int)(10 * scale), part_row_h - (int)(2 * scale), rgb(12, 18, 32));
            draw_rect(x + (int)(10 * scale), cy, w - (int)(10 * scale), part_row_h - (int)(2 * scale), rgb(30, 60, 100));
            draw_text(x + (int)(18 * scale), cy + (int)(4 * scale), "BOLUM", rgb(80, 140, 200));
            /* FS name */
            draw_text(x + (int)(72 * scale), cy + (int)(4 * scale), p->fs_name, rgb(46, 204, 113));
            /* Size */
            {
                uint64_t bytes = (uint64_t)p->blocks * p->block_size;
                uint64_t mb = bytes / (1024ULL * 1024ULL);
                if (mb >= 1024) {
                    u64_to_dec(mb / 1024ULL, num);
                    draw_text(x + (int)(130 * scale), cy + (int)(4 * scale), num, rgb(220, 226, 239));
                    draw_text(x + (int)(166 * scale), cy + (int)(4 * scale), "GB", rgb(126, 136, 158));
                } else {
                    u64_to_dec(mb, num);
                    draw_text(x + (int)(130 * scale), cy + (int)(4 * scale), num, rgb(220, 226, 239));
                    draw_text(x + (int)(166 * scale), cy + (int)(4 * scale), "MB", rgb(126, 136, 158));
                }
            }
            draw_text(x + w - (int)(56 * scale), cy + (int)(4 * scale), p->readonly ? "SALT-OKU" : "OKU/YAZ", rgb(126, 136, 158));
            cy += part_row_h;
        }
        cy += (int)(4 * scale); /* gap between disks */
    }
}

static void draw_transfer_overlay(void)
{
    if (!g_transfer_active) {
        return;
    }
    uint32_t scale = ui_scale();
    int pw = (int)(340 * scale);
    int ph = (int)(120 * scale);
    int px = ((int)g_w - pw) / 2;
    int py = ((int)g_h - ph) / 2;
    /* Shadow */
    fill_rect(px + (int)(5 * scale), py + (int)(5 * scale), pw, ph, rgb(5, 8, 16));
    fill_rect(px, py, pw, ph, rgb(12, 18, 32));
    draw_rect(px, py, pw, ph, rgb(220, 39, 39));
    fill_rect(px + 1, py + 1, pw - 2, (int)(26 * scale), g_transfer_is_move ? rgb(24, 30, 50) : rgb(34, 22, 34));
    const char *title;
    if (g_transfer_is_dir) {
        title = g_transfer_is_move ? "KLASOR TASI" : "KLASOR KOPYALA";
    } else {
        title = g_transfer_is_move ? "DOSYA TASI" : "DOSYA KOPYALA";
    }
    draw_text(px + (int)(12 * scale), py + (int)(8 * scale), title, rgb(246, 247, 252));
    /* Source filename */
    draw_text(px + (int)(12 * scale), py + (int)(36 * scale), "KAYNAK", rgb(126, 136, 158));
    int name_max = (pw - (int)(90 * scale)) / (int)(6 * scale);
    draw_text16_limited(px + (int)(80 * scale), py + (int)(36 * scale), g_transfer_src_name,
                        rgb(220, 226, 239), name_max > 0 ? (uint32_t)name_max : 1);
    /* Destination volume */
    draw_text(px + (int)(12 * scale), py + (int)(52 * scale), "HEDEF", rgb(126, 136, 158));
    draw_text16_limited(px + (int)(80 * scale), py + (int)(52 * scale), g_transfer_dst_vol,
                        rgb(46, 204, 113), 24);
    /* Progress bar */
    int bar_x = px + (int)(12 * scale);
    int bar_y = py + (int)(72 * scale);
    int bar_w = pw - (int)(24 * scale);
    int bar_h = (int)(14 * scale);
    fill_rect(bar_x, bar_y, bar_w, bar_h, rgb(20, 28, 48));
    draw_rect(bar_x, bar_y, bar_w, bar_h, rgb(60, 72, 100));
    uint32_t pct = (g_transfer_total > 0)
        ? (uint32_t)((g_transfer_done * 100ULL) / g_transfer_total)
        : 0;
    if (pct > 100) pct = 100;
    int filled = g_transfer_is_dir
        ? 0   /* indeterminate for directory */
        : (bar_w * (int)pct) / 100;
    if (filled > 0) {
        fill_rect(bar_x, bar_y, filled, bar_h, g_transfer_is_move ? rgb(212, 130, 30) : rgb(30, 132, 212));
    }
    char num[16];
    if (g_transfer_is_dir) {
        /* Show file count in progress area */
        u64_to_dec((uint64_t)g_transfer_file_count, num);
        draw_text(bar_x + (int)(4 * scale), bar_y + (int)(2 * scale), "DOSYA:", rgb(126, 136, 158));
        draw_text(bar_x + (int)(52 * scale), bar_y + (int)(2 * scale), num, rgb(246, 247, 252));
    } else {
        /* Percentage */
        u64_to_dec((uint64_t)pct, num);
        draw_text(bar_x + bar_w / 2 - (int)(12 * scale), bar_y + (int)(2 * scale), num, rgb(246, 247, 252));
        draw_text(bar_x + bar_w / 2 + (int)(6 * scale), bar_y + (int)(2 * scale), "%", rgb(246, 247, 252));
    }
    /* Sizes */
    draw_size_value(px + (int)(12 * scale), py + ph - (int)(18 * scale), g_transfer_done, rgb(126, 136, 158));
    if (!g_transfer_is_dir && g_transfer_total > 0) {
        draw_text(px + (int)(72 * scale), py + ph - (int)(18 * scale), "/", rgb(80, 90, 110));
        draw_size_value(px + (int)(88 * scale), py + ph - (int)(18 * scale), g_transfer_total, rgb(156, 168, 192));
    }
}

static void draw_create_dialog(void)
{
    if (!g_create_open) {
        return;
    }
    uint32_t scale = ui_scale();
    int pw = (int)(320 * scale);
    int ph = (int)(90 * scale);
    int px = ((int)g_w - pw) / 2;
    int py = ((int)g_h - ph) / 2;
    fill_rect(px + (int)(4 * scale), py + (int)(4 * scale), pw, ph, rgb(5, 8, 16));
    fill_rect(px, py, pw, ph, rgb(12, 18, 32));
    draw_rect(px, py, pw, ph, rgb(46, 204, 113));
    fill_rect(px + 1, py + 1, pw - 2, (int)(26 * scale), rgb(14, 38, 22));
    draw_text(px + (int)(12 * scale), py + (int)(8 * scale),
              g_create_is_dir ? "YENİ KLASÖR OLUŞTUR" : "YENİ DOSYA OLUŞTUR", rgb(246, 247, 252));
    draw_text(px + (int)(12 * scale), py + (int)(36 * scale),
              g_create_is_dir ? "KLASÖR ADI:" : "AD+UZANTI:", rgb(126, 136, 158));
    /* Input box */
    int ix = px + (int)(98 * scale);
    int iy = py + (int)(32 * scale);
    int iw = pw - (int)(110 * scale);
    int ih = (int)(18 * scale);
    fill_rect(ix, iy, iw, ih, rgb(20, 28, 48));
    draw_rect(ix, iy, iw, ih, rgb(46, 204, 113));
    uint32_t name_chars = (uint32_t)(iw / (int)(6 * scale));
    uint32_t nlen = c16_len(g_create_name);
    /* Show last N chars if too long */
    const CHAR16 *show = g_create_name;
    if (nlen > name_chars && name_chars > 1) {
        show = g_create_name + nlen - (name_chars - 1);
    }
    draw_text16_limited(ix + (int)(3 * scale), iy + (int)(3 * scale), show, rgb(220, 226, 239), name_chars);
    /* Cursor blink using loop ticks */
    if ((g_loop_ticks / 4) & 1) {
        uint32_t shown_len = c16_len(show);
        int cx = ix + (int)(3 * scale) + (int)(shown_len * 6 * scale);
        fill_rect(cx, iy + (int)(2 * scale), (int)(1 * scale) + 1, ih - (int)(4 * scale), rgb(46, 204, 113));
    }
    draw_text(px + (int)(12 * scale), py + ph - (int)(16 * scale),
              "ENTER OLUSTUR   ESC IPTAL", rgb(126, 136, 158));
}

static void draw_rename_dialog(void)
{
    if (!g_rename_open) return;
    uint32_t scale = ui_scale();
    int pw = (int)(320 * scale);
    int ph = (int)(90 * scale);
    int px = ((int)g_w - pw) / 2;
    int py = ((int)g_h - ph) / 2;
    fill_rect(px + (int)(4 * scale), py + (int)(4 * scale), pw, ph, rgb(5, 8, 16));
    fill_rect(px, py, pw, ph, rgb(12, 18, 32));
    draw_rect(px, py, pw, ph, rgb(212, 130, 30));
    fill_rect(px + 1, py + 1, pw - 2, (int)(26 * scale), rgb(38, 22, 8));
    draw_text(px + (int)(12 * scale), py + (int)(8 * scale), "YENİDEN ADLANDIR", rgb(246, 247, 252));
    draw_text(px + (int)(12 * scale), py + (int)(36 * scale), "YENİ AD:", rgb(126, 136, 158));
    int ix = px + (int)(76 * scale);
    int iy = py + (int)(32 * scale);
    int iw = pw - (int)(88 * scale);
    int ih = (int)(18 * scale);
    fill_rect(ix, iy, iw, ih, rgb(20, 28, 48));
    draw_rect(ix, iy, iw, ih, rgb(212, 130, 30));
    uint32_t name_chars = (uint32_t)((uint32_t)iw / (int)(6 * scale));
    uint32_t nlen = c16_len(g_rename_name);
    const CHAR16 *show = g_rename_name;
    if (nlen > name_chars && name_chars > 1) show = g_rename_name + nlen - (name_chars - 1);
    draw_text16_limited(ix + (int)(3 * scale), iy + (int)(3 * scale), show, rgb(220, 226, 239), name_chars);
    if ((g_loop_ticks / 4) & 1) {
        uint32_t shown_len = c16_len(show);
        int cx = ix + (int)(3 * scale) + (int)(shown_len * 6 * (int)scale);
        fill_rect(cx, iy + (int)(2 * scale), (int)(1 * scale) + 1, ih - (int)(4 * scale), rgb(212, 130, 30));
    }
    draw_text(px + (int)(12 * scale), py + ph - (int)(16 * scale),
              "ENTER KAYDET   ESC İPTAL", rgb(126, 136, 158));
}

static void draw_context_menu(void)
{
    if (!g_ctx_open) return;
    uint32_t scale = ui_scale();
    int item_h = (int)(20 * scale);
    int menu_w = (int)(190 * scale);
    int item_count;
    const char *labels_file[CTX_ITEM_COUNT] = {
        "YENİDEN ADLANDIR [F2]",
        "KOPYALA [C]",
        "TAŞI [M]",
        "SİL [DEL]"
    };
    const char *labels_bg[CTX_BG_ITEM_COUNT] = {
        "YENİ DOSYA OLUŞTUR [O]",
        "YENİ KLASÖR OLUŞTUR"
    };
    const char **labels;
    if (g_ctx_mode == 1) {
        labels     = labels_bg;
        item_count = CTX_BG_ITEM_COUNT;
    } else {
        labels     = labels_file;
        item_count = CTX_ITEM_COUNT;
    }
    int menu_h = item_count * item_h + (int)(4 * scale);
    int mx = g_ctx_x;
    int my = g_ctx_y;
    if (mx + menu_w > (int)g_w) mx = (int)g_w - menu_w - (int)(4 * scale);
    if (my + menu_h > (int)g_h) my = (int)g_h - menu_h - (int)(4 * scale);
    fill_rect(mx + (int)(3 * scale), my + (int)(3 * scale), menu_w, menu_h, rgb(5, 8, 16));
    fill_rect(mx, my, menu_w, menu_h, rgb(18, 26, 44));
    draw_rect(mx, my, menu_w, menu_h, g_ctx_mode == 1 ? rgb(46, 120, 80) : rgb(60, 80, 120));
    for (int i = 0; i < item_count; i++) {
        int iy = my + (int)(2 * scale) + i * item_h;
        int hover = (i == (int)g_ctx_hover &&
                     g_mouse_x >= mx && g_mouse_x < mx + menu_w &&
                     g_mouse_y >= iy && g_mouse_y < iy + item_h);
        if (hover) fill_rect(mx + 1, iy, menu_w - 2, item_h,
                             g_ctx_mode == 1 ? rgb(30, 80, 50) : rgb(40, 60, 100));
        uint32_t col = (g_ctx_mode == 0 && i == CTX_DELETE) ? rgb(220, 80, 80) : rgb(210, 218, 235);
        draw_text(mx + (int)(10 * scale), iy + (int)(5 * scale), labels[i], col);
    }
}

static void draw_confirm_dialog(void)
{
    if (!g_confirm_open) {
        return;
    }
    uint32_t scale = ui_scale();
    int pw = (int)(340 * scale);
    int ph = (int)(112 * scale);
    int px = ((int)g_w - pw) / 2;
    int py = ((int)g_h - ph) / 2;
    /* Shadow */
    fill_rect(px + (int)(4 * scale), py + (int)(4 * scale), pw, ph, rgb(5, 8, 16));
    fill_rect(px, py, pw, ph, rgb(14, 18, 30));
    uint32_t border_col = (g_confirm_action == CONFIRM_DELETE) ? rgb(220, 39, 39) : rgb(212, 130, 30);
    draw_rect(px, py, pw, ph, border_col);
    fill_rect(px + 1, py + 1, pw - 2, (int)(26 * scale), rgb(34, 18, 18));
    /* Title */
    const char *title = (g_confirm_action == CONFIRM_DELETE) ? "! SILME UYARISI" : "! UZERINE YAZMA UYARISI";
    draw_text(px + (int)(12 * scale), py + (int)(8 * scale), title, rgb(246, 247, 252));
    /* Message */
    draw_text16_limited(px + (int)(12 * scale), py + (int)(38 * scale),
                        g_confirm_msg, rgb(220, 180, 80), 46);
    /* Buttons */
    int bw = (int)(118 * scale);
    int bh = (int)(24 * scale);
    int by = py + ph - (int)(34 * scale);
    int bx_evet  = px + (int)(12 * scale);
    int bx_hayir = px + pw - bw - (int)(12 * scale);
    /* Hover highlight */
    uint32_t evet_fill  = (g_mouse_x >= bx_evet  && g_mouse_x < bx_evet  + bw &&
                           g_mouse_y >= by && g_mouse_y < by + bh)
                          ? rgb(40, 180, 80) : rgb(20, 100, 40);
    uint32_t hayir_fill = (g_mouse_x >= bx_hayir && g_mouse_x < bx_hayir + bw &&
                           g_mouse_y >= by && g_mouse_y < by + bh)
                          ? rgb(180, 40, 40) : rgb(90, 20, 20);
    fill_rect(bx_evet,  by, bw, bh, evet_fill);
    draw_rect(bx_evet,  by, bw, bh, rgb(46, 204, 113));
    draw_text(bx_evet  + (int)(30 * scale), by + (int)(7 * scale), "E/ENTER EVET", rgb(240, 248, 240));
    fill_rect(bx_hayir, by, bw, bh, hayir_fill);
    draw_rect(bx_hayir, by, bw, bh, rgb(220, 60, 60));
    draw_text(bx_hayir + (int)(26 * scale), by + (int)(7 * scale), "ESC/H HAYIR", rgb(248, 220, 220));
}

static void save_viewer_file(void)
{
    if (!g_viewer_path[0]) return;
    EFI_FILE_PROTOCOL *f = 0;
    if (!open_file_by_path(g_viewer_vol, g_viewer_path, &f,
            EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0)) {
        set_last_error("DOSYA KAYDEDILEMEDI");
        return;
    }
    /* Truncate by setting position to 0 and writing */
    f->SetPosition(f, 0);
    UINTN len = 0;
    while (g_viewer_text[len]) len++;
    UINTN written = len;
    EFI_STATUS wr_st = f->Write(f, &written, g_viewer_text);
    if (wr_st != EFI_SUCCESS || written != len) {
        f->Close(f);
        set_last_error("DOSYA YAZILAMADI");
        return;
    }
    /* Truncate to new length via SetInfo to trim any old content */
    {
        uint8_t fi_buf2[sizeof(EFI_FILE_INFO) + 200];
        UINTN fi_sz2 = sizeof(fi_buf2);
        if (f->GetInfo(f, (EFI_GUID *)&FileInfoGuid, &fi_sz2, fi_buf2) == EFI_SUCCESS) {
            ((EFI_FILE_INFO *)fi_buf2)->FileSize = len;
            if (f->SetInfo(f, (EFI_GUID *)&FileInfoGuid, fi_sz2, fi_buf2) != EFI_SUCCESS) {
                f->Close(f);
                set_last_error("DOSYA BOYUTU GUNCELLENEMEDI");
                return;
            }
        }
    }
    f->Flush(f);
    f->Close(f);
    /* Refresh any open explorer window showing this file's directory */
    {
        CHAR16 parent[256];
        c16_copy(parent, g_viewer_path, sizeof(parent)/sizeof(parent[0]));
        c16_parent(parent);
        for (uint32_t wi = 0; wi < MAX_EXPLORER_WINDOWS; wi++) {
            explorer_window_t *win = &g_windows[wi];
            if (win->visible && win->mode == EXPLORER_MODE_FILES &&
                win->volume == g_viewer_vol && c16_equal(win->path, parent)) {
                load_window_entries(win);
            }
        }
    }
    set_last_error("KAYDEDILDI");
}

static void draw_viewer_overlay(void)
{
    if (!g_viewer_open) {
        return;
    }
    uint32_t scale = ui_scale();
    int w = (int)g_w - (int)(130 * scale);
    int h = (int)g_h - (int)(110 * scale);
    int x = ((int)g_w - w) / 2;
    int y = ((int)g_h - h) / 2;
    if (w < (int)(260 * scale) || h < (int)(160 * scale)) {
        x = (int)(20 * scale);
        y = (int)(20 * scale);
        w = (int)g_w - (int)(40 * scale);
        h = (int)g_h - (int)(40 * scale);
    }
    fill_rect(x - (int)(5 * scale), y - (int)(5 * scale), w + (int)(10 * scale), h + (int)(10 * scale), rgb(5, 8, 16));
    fill_rect(x, y, w, h, rgb(12, 18, 32));
    draw_rect(x, y, w, h, g_viewer_edit ? rgb(39, 160, 220) : rgb(220, 39, 39));
    fill_rect(x + 1, y + 1, w - 2, (int)(30 * scale), g_viewer_edit ? rgb(18, 34, 52) : rgb(34, 22, 34));
    draw_text(x + (int)(12 * scale), y + (int)(10 * scale), "NOT DEFTERİ", rgb(246, 247, 252));
    if (g_viewer_edit) {
        draw_text(x + (int)(12 * scale), y + (int)(10 * scale), "NOT DEFTERİ [DÜZENLEME]", rgb(246, 200, 80));
    }
    int title_px = w - (int)(240 * scale);
    draw_text16_limited(x + (int)(170 * scale), y + (int)(10 * scale), g_viewer_title, rgb(156, 168, 192), title_px > 0 ? (uint32_t)(title_px / (int)(6 * scale)) : 0);
    /* Text area */
    int ta_x = x + (int)(14 * scale);
    int ta_y = y + (int)(44 * scale);
    int ta_w = w - (int)(28 * scale);
    int ta_h = h - (int)(72 * scale);
    if (g_viewer_edit) {
        fill_rect(ta_x - 1, ta_y - 1, ta_w + 2, ta_h + 2, rgb(20, 30, 50));
    }
    /* Compute cursor logical row/col first; then auto-scroll so cursor is in view */
    int char_w = (int)(6 * scale);
    int line_h = (int)(9 * scale);
    int text_w = ta_w - 8;  /* leave gutter for scrollbar */
    if (text_w < char_w) text_w = char_w;
    int max_cols = char_w ? text_w / char_w : 1;
    if (max_cols < 1) max_cols = 1;
    int visible_rows = line_h ? ta_h / line_h : 1;
    if (visible_rows < 1) visible_rows = 1;
    int cur_col = 0, cur_row = 0;
    int total_rows = 0;
    {
        int col = 0;
        for (uint32_t ci = 0; ; ci++) {
            if (ci == g_viewer_cursor) { cur_col = col; cur_row = total_rows; }
            char c = g_viewer_text[ci];
            if (!c) break;
            if (c == '\n') { total_rows++; col = 0; }
            else { col++; if (col >= max_cols) { col = 0; total_rows++; } }
        }
        total_rows++;  /* account for last line */
    }
    if (g_viewer_edit && g_viewer_cursor != g_viewer_last_cursor_for_scroll) {
        if (cur_row < (int)g_viewer_scroll) g_viewer_scroll = (uint32_t)cur_row;
        if (cur_row >= (int)g_viewer_scroll + visible_rows)
            g_viewer_scroll = (uint32_t)(cur_row - visible_rows + 1);
        g_viewer_last_cursor_for_scroll = g_viewer_cursor;
    }
    /* Clamp scroll so we don't scroll past the end pointlessly */
    if (total_rows <= visible_rows) g_viewer_scroll = 0;
    else if ((int)g_viewer_scroll > total_rows - visible_rows)
        g_viewer_scroll = (uint32_t)(total_rows - visible_rows);
    /* Render visible rows starting from g_viewer_scroll */
    {
        int draw_row = 0;
        int col = 0;
        int dx = ta_x;
        int dy = ta_y;
        const char *p = g_viewer_text;
        while (*p && draw_row < (int)g_viewer_scroll) {
            uint16_t cp = utf8_next(&p);
            if (cp == '\n') { draw_row++; col = 0; }
            else { col++; if (col >= max_cols) { draw_row++; col = 0; } }
        }
        col = 0;
        int rows_drawn = 0;
        while (*p && rows_drawn < visible_rows) {
            uint16_t cp = utf8_next(&p);
            if (cp == '\n') {
                rows_drawn++; col = 0;
                dy += line_h; dx = ta_x;
                continue;
            }
            if (col >= max_cols) {
                rows_drawn++; col = 0;
                dy += line_h; dx = ta_x;
                if (rows_drawn >= visible_rows) break;
            }
            draw_char_cp(dx, dy, cp, rgb(220, 226, 239), scale);
            dx += char_w; col++;
        }
    }
    /* Draw cursor relative to scroll */
    if (g_viewer_edit) {
        int rel_row = cur_row - (int)g_viewer_scroll;
        if (rel_row >= 0 && rel_row < visible_rows) {
            int cx = ta_x + cur_col * char_w;
            int cy = ta_y + rel_row * line_h;
            fill_rect(cx, cy, (int)(2 * scale), line_h, rgb(80, 200, 255));
        }
    }
    /* Scroll indicator on right */
    if (total_rows > visible_rows) {
        int track_x = ta_x + ta_w - 4;
        int track_y = ta_y;
        int track_h = ta_h;
        fill_rect(track_x, track_y, 3, track_h, rgb(20, 28, 44));
        int thumb_h = (visible_rows * track_h) / total_rows;
        if (thumb_h < 8) thumb_h = 8;
        int max_scroll = total_rows - visible_rows;
        int thumb_y = track_y + ((int)g_viewer_scroll * (track_h - thumb_h)) / (max_scroll ? max_scroll : 1);
        fill_rect(track_x, thumb_y, 3, thumb_h, rgb(80, 130, 200));
    }
    /* Bottom bar */
    int by = y + h - (int)(20 * scale);
    if (g_viewer_edit) {
        /* Save button */
        int bx = x + (int)(14 * scale);
        fill_rect(bx, by - (int)(2 * scale), (int)(120 * scale), (int)(16 * scale), rgb(18, 80, 140));
        draw_text(bx + (int)(4 * scale), by, "KAYDET [ESC]", rgb(100, 220, 255));
    } else {
        /* Edit button */
        int bx = x + (int)(14 * scale);
        fill_rect(bx, by - (int)(2 * scale), (int)(90 * scale), (int)(16 * scale), rgb(30, 60, 30));
        draw_text(bx + (int)(4 * scale), by, "DÜZENLE [E]", rgb(100, 220, 100));
        draw_text(bx + (int)(100 * scale), by, "ESC KAPAT", rgb(126, 136, 158));
    }
}

static void draw_terminal_window(void)
{
    if (!g_terminal_visible) {
        return;
    }
    uint32_t scale = ui_scale();
    int x = g_terminal_x;
    int y = g_terminal_y;
    int w = g_terminal_w;
    int h = g_terminal_h;
    uint32_t active = g_active_surface == ACTIVE_TERMINAL;
    fill_rect(x, y, w, h, rgb(5, 8, 16));
    draw_rect(x, y, w, h, active ? rgb(220, 39, 39) : rgb(42, 50, 72));
    fill_rect(x + 1, y + 1, w - 2, (int)(28 * scale), active ? rgb(34, 22, 34) : rgb(16, 23, 39));
    draw_text(x + (int)(10 * scale), y + (int)(10 * scale), "CAYATERM", rgb(246, 247, 252));
    draw_text(x + w - (int)(18 * scale), y + (int)(10 * scale), "X", rgb(220, 39, 39));
    int yy = y + (int)(42 * scale);
    for (uint32_t i = 0; i < g_terminal_line_count; i++) {
        draw_text(x + (int)(12 * scale), yy, g_terminal_lines[i], rgb(184, 194, 214));
        yy += (int)(14 * scale);
        if (yy > y + h - (int)(34 * scale)) {
            break;
        }
    }
    fill_rect(x + (int)(8 * scale), y + h - (int)(28 * scale), w - (int)(16 * scale), (int)(20 * scale), rgb(12, 18, 32));
    draw_text(x + (int)(12 * scale), y + h - (int)(20 * scale), ">", rgb(220, 39, 39));
    draw_text(x + (int)(28 * scale), y + h - (int)(20 * scale), g_terminal_input, rgb(246, 247, 252));
}

static void draw_detail_panel(void)
{
    char buf[64];
    int x = content_x();
    int top_offset = (g_page == 5) ? 0 : (int)(98 * ui_scale());
    int y = content_y() + top_offset;
    int w = content_w();
    int h = content_h() - top_offset;
    fill_rect(x, y, w, h, rgb(15, 21, 36));
    draw_rect(x, y, w, h, rgb(42, 50, 72));
    int px = x + (int)(22 * ui_scale());
    int py = y + (int)(22 * ui_scale());

    if (g_page == 0) {
        /* ---- System Overview: 13 items ---- */
        draw_text_scale(px, py, "SİSTEM ÖZETİ", rgb(246, 247, 252), ui_scale() + 1);
        py += (int)(34 * ui_scale());

        /* Layout in two columns for more items */
        int col2 = px + (int)(280 * ui_scale());
        int ly = py;

        draw_info_row(px, &py, "BOOT MODU", "UEFI X64");
        draw_info_row(px, &py, "MİMARİ", "x86-64");

        /* Firmware vendor */
        char fwbuf[64];
        uint32_t fi = 0;
        while (g_firmware[fi] && fi < 63) { fwbuf[fi] = (char)(g_firmware[fi] & 0x7F); fi++; }
        fwbuf[fi] = 0;
        draw_info_row(px, &py, "FIRMWARE", fwbuf);

        /* UEFI revision (major.minor) */
        {
            char maj[16], min_s[16];
            u64_to_dec((g_uefi_rev >> 16) & 0xFFFF, maj);
            u64_to_dec(g_uefi_rev & 0xFFFF, min_s);
            char revbuf[32];
            uint32_t ri = 0;
            for (uint32_t j = 0; maj[j]; j++) revbuf[ri++] = maj[j];
            revbuf[ri++] = '.';
            for (uint32_t j = 0; min_s[j]; j++) revbuf[ri++] = min_s[j];
            revbuf[ri] = 0;
            draw_info_row(px, &py, "UEFI SURUM", revbuf);
        }

        /* Secure Boot */
        const char *sb_str = "BILINMIYOR";
        if (g_secure_boot == 1) sb_str = "AKTIF (ACIK)";
        else if (g_secure_boot == 2) sb_str = "PASIF (KAPALI)";
        else if (g_secure_boot == 3) sb_str = "SETUP MODU";
        draw_info_row(px, &py, "SECURE BOOT", sb_str);

        draw_info_row(px, &py, "ACPI", g_acpi_present ? "MEVCUT" : "YOK");

        /* Video */
        {
            char wb[16], hb[16];
            u64_to_dec(g_w, wb);
            u64_to_dec(g_h, hb);
            char vbuf[40];
            uint32_t vi = 0;
            for (uint32_t j = 0; wb[j]; j++) vbuf[vi++] = wb[j];
            vbuf[vi++] = 'x';
            for (uint32_t j = 0; hb[j]; j++) vbuf[vi++] = hb[j];
            vbuf[vi] = 0;
            draw_info_row(px, &py, "EKRAN COZUNURLUK", vbuf);
        }

        u64_to_dec(g_gop_modes, buf);
        draw_info_row(px, &py, "GOP MOD SAYISI", buf);

        /* CPU */
        if (g_cpu_brand[0]) draw_info_row(px, &py, "CPU", g_cpu_brand);
        else draw_info_row(px, &py, "CPU", g_cpu_vendor);

        /* RAM */
        u64_to_dec(g_memory_mb, buf);
        draw_info_row(px, &py, "RAM MB", buf);

        u64_to_dec(g_memory_conv_mb, buf);
        draw_info_row(px, &py, "KULLANILAB. MB", buf);

        /* Input devices */
        draw_info_row(px, &py, "GİRİŞ",
            g_abs_ptr_count ? "FARE + TOUCH" : (g_simple_ptr_count ? "FARE" : "KLAVYE"));

        /* Storage summary */
        u64_to_dec(g_real_vol_count, buf);
        draw_info_row(px, &py, "DOSYA BİRİMİ", buf);
        (void)ly; (void)col2;

    } else if (g_page == 1) {
        /* ---- CPU Detail: 20+ items ---- */
        uint32_t sig = g_cpu_sig;
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

        draw_text_scale(px, py, "İŞLEMCİ", rgb(246, 247, 252), ui_scale() + 1);
        py += (int)(34 * ui_scale());

        /* Split into two columns to fit all items */
        int left_x  = px;
        int right_x = px + (int)(240 * ui_scale());
        int ly = py;
        int ry = py;
        /* Left column */
        draw_info_row(left_x, &ly, "VENDOR", g_cpu_vendor);
        if (g_cpu_brand[0]) draw_info_row(left_x, &ly, "MARKA", g_cpu_brand);
        u64_to_dec(family,   buf); draw_info_row(left_x, &ly, "FAMILY", buf);
        u64_to_dec(model,    buf); draw_info_row(left_x, &ly, "MODEL",  buf);
        u64_to_dec(stepping, buf); draw_info_row(left_x, &ly, "STEPPING", buf);
        u64_to_dec(g_cpu_max_leaf, buf); draw_info_row(left_x, &ly, "CPUID MAX", buf);
        u64_to_dec(g_cpu_cores,   buf); draw_info_row(left_x, &ly, "FİZİKSEL ÇEK.", buf);
        u64_to_dec(g_cpu_threads, buf); draw_info_row(left_x, &ly, "MANTIKSAL ÇEK.", buf);
        if (g_cpu_cache_kb) {
            u64_to_dec(g_cpu_cache_kb, buf);
            draw_info_row(left_x, &ly, "L2 ÖNBELLEK KB", buf);
        }
        draw_info_row(left_x, &ly, "APIC", g_cpu_apic     ? "VAR" : "YOK");
        draw_info_row(left_x, &ly, "HYPERTHREADING", g_cpu_has_ht  ? "AKTIF" : "PASIF");

        /* Right column — feature flags */
        draw_info_row(right_x, &ry, "SSE",    (g_cpu_edx >> 25) & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "SSE2",   (g_cpu_edx >> 26) & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "SSE3",   (g_cpu_ecx)       & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "SSSE3",  (g_cpu_ecx >>  9) & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "SSE4.1", (g_cpu_ecx >> 19) & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "SSE4.2", (g_cpu_ecx >> 20) & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "AVX",    g_cpu_has_avx    ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "AES-NI", g_cpu_has_aes    ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "RDRAND", g_cpu_has_rdrand ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "NX / XD", g_cpu_has_nx    ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "VT-x/AMD-V", g_cpu_has_vt ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "POPCNT", (g_cpu_ecx >> 23) & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "HYPERVISOR", (g_cpu_ecx >> 31) & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "PAE",    (g_cpu_edx >>  6) & 1 ? "VAR" : "YOK");
        draw_info_row(right_x, &ry, "x2APIC", (g_cpu_ecx >> 21) & 1 ? "VAR" : "YOK");
        (void)ly;

    } else if (g_page == 2) {
        /* ---- Memory Detail ---- */
        draw_text_scale(px, py, "BELLEK", rgb(246, 247, 252), ui_scale() + 1);
        py += (int)(34 * ui_scale());

        u64_to_dec(g_memory_mb, buf);
        draw_info_row(px, &py, "TOPLAM MB", buf);
        u64_to_dec(g_memory_mb / 1024, buf);
        draw_info_row(px, &py, "TOPLAM GB (YAKLASIK)", buf);
        u64_to_dec(g_memory_conv_mb, buf);
        draw_info_row(px, &py, "KULLANILABILIR MB", buf);
        draw_info_row(px, &py, "KAYNAK", "UEFI MEMORY MAP");

        /* Framebuffer size */
        {
            uint64_t fb_kb = ((uint64_t)g_w * g_h * 4) / 1024;
            u64_to_dec(fb_kb, buf);
            draw_info_row(px, &py, "FRAMEBUFFER KB", buf);
        }

        /* Stride info */
        u64_to_dec(g_stride, buf);
        draw_info_row(px, &py, "GOP STRIDE (PX)", buf);

        /* Pixel format */
        const char *pf_str = "BILINMIYOR";
        if      (g_pixel_format == 0) pf_str = "RGBX 32-BIT";
        else if (g_pixel_format == 1) pf_str = "BGRX 32-BIT";
        else if (g_pixel_format == 2) pf_str = "BIT-MASK";
        else if (g_pixel_format == 3) pf_str = "BLT-ONLY";
        draw_info_row(px, &py, "PIKSEL FORMAT", pf_str);

        /* Memory type breakdown */
        py += (int)(8 * ui_scale());
        const char *type_names[] = {
            "RESERVED","LOADER CODE","LOADER DATA","BS CODE","BS DATA",
            "RT CODE","RT DATA","KONV. BELLEK","KULLAN.YOK","ACPI RECLAIM",
            "ACPI NVS","MMIO","MMIO PORT","PAL CODE","PERSIST.MEM"
        };
        for (uint32_t t = 0; t < 15; t++) {
            if (g_memory_types[t]) {
                uint64_t mb = ((uint64_t)g_memory_types[t] * 4096ULL) / (1024ULL * 1024ULL);
                if (mb > 0) {
                    u64_to_dec(mb, buf);
                    char lbuf[48];
                    uint32_t li = 0;
                    const char *tn = type_names[t];
                    while (tn[li] && li < 47) { lbuf[li] = tn[li]; li++; }
                    lbuf[li++] = ' '; lbuf[li++] = 'M'; lbuf[li++] = 'B'; lbuf[li] = 0;
                    draw_info_row(px, &py, lbuf, buf);
                    if (py > y + h - (int)(20 * ui_scale())) break;
                }
            }
        }

    } else if (g_page == 3) {
        draw_text_scale(px, py, "DEPOLAMA", rgb(246, 247, 252), ui_scale() + 1);
        py += (int)(34 * ui_scale());
        u64_to_dec(g_disk_count, buf);
        draw_info_row(px, &py, "FİZİKSEL DISK", buf);
        u64_to_dec(g_block_count, buf);
        draw_info_row(px, &py, "BLOCK DEVICE", buf);
        u64_to_dec(g_real_vol_count, buf);
        draw_info_row(px, &py, "DOSYA BİRİMİ", buf);
        py += (int)(12 * ui_scale());
        draw_storage_rows(px, py, w - (int)(44 * ui_scale()), h - (py - y) - (int)(18 * ui_scale()));
    } else if (g_page == 4) {
        /* ---- GPU / Display Adapters ---- */
        draw_text_scale(px, py, "EKRAN KARTI", rgb(246, 247, 252), ui_scale() + 1);
        py += (int)(34 * ui_scale());

        if (g_gpu_count == 0) {
            draw_info_row(px, &py, "EKRAN", "BULUNAMADI");
        }

        for (uint32_t gi = 0; gi < g_gpu_count; gi++) {
            gpu_info_t *g = &g_gpus[gi];

            /* Adapter header */
            char adapter_lbl[16];
            adapter_lbl[0] = 'E'; adapter_lbl[1] = 'K'; adapter_lbl[2] = 'R';
            adapter_lbl[3] = 'A'; adapter_lbl[4] = 'N'; adapter_lbl[5] = ' ';
            adapter_lbl[6] = (char)('1' + gi);
            adapter_lbl[7] = 0;

            uint32_t hdr_color = gi == 0 ? rgb(220, 39, 39) : rgb(30, 132, 212);
            draw_text(px, py, adapter_lbl, hdr_color);
            py += (int)(20 * ui_scale());

            int left_x  = px + (int)(8 * ui_scale());
            int right_x = px + (int)(248 * ui_scale());
            int ly = py;
            int ry = py;

            /* Resolution */
            {
                char wb[16], hb[16];
                u64_to_dec(g->width, wb);
                u64_to_dec(g->height, hb);
                char rbuf[40];
                uint32_t ri = 0;
                for (uint32_t j = 0; wb[j]; j++) rbuf[ri++] = wb[j];
                rbuf[ri++] = 'x';
                for (uint32_t j = 0; hb[j]; j++) rbuf[ri++] = hb[j];
                rbuf[ri] = 0;
                draw_info_row(left_x, &ly, "COZUNURLUK", rbuf);
            }

            /* Stride */
            u64_to_dec(g->stride, buf);
            draw_info_row(left_x, &ly, "STRIDE (PX)", buf);

            /* Pixel format */
            const char *pf_str = "BILINMIYOR";
            if      (g->pixel_format == 0) pf_str = "RGBX 32-BIT";
            else if (g->pixel_format == 1) pf_str = "BGRX 32-BIT";
            else if (g->pixel_format == 2) pf_str = "BIT-MASK";
            else if (g->pixel_format == 3) pf_str = "BLT-ONLY";
            draw_info_row(left_x, &ly, "PIKSEL FORMAT", pf_str);

            /* Framebuffer size */
            if (g->width && g->height) {
                uint64_t fb_kb = ((uint64_t)g->width * g->height * 4) / 1024;
                u64_to_dec(fb_kb, buf);
                draw_info_row(left_x, &ly, "FRAMEBUF. KB", buf);
            }

            /* Mode info */
            u64_to_dec(g->max_modes, buf);
            draw_info_row(left_x, &ly, "TOPLAM MOD", buf);
            u64_to_dec(g->cur_mode, buf);
            draw_info_row(left_x, &ly, "AKTIF MOD", buf);

            /* GOP protocol */
            draw_info_row(left_x, &ly, "PROTOKOL", "UEFI GOP");

            /* EDID info in right column */
            if (g->has_edid) {
                draw_info_row(right_x, &ry, "EDID", "MEVCUT");
                if (g->mfr_id[0]) draw_info_row(right_x, &ry, "URETICI KODU", g->mfr_id);
                if (g->monitor_name[0]) draw_info_row(right_x, &ry, "MONITOR", g->monitor_name);
                if (g->mfr_year > 1990 && g->mfr_year < 2050) {
                    u64_to_dec(g->mfr_year, buf);
                    draw_info_row(right_x, &ry, "URETIM YILI", buf);
                }
                {
                    char pc[12];
                    /* product code as hex */
                    static const char hex[] = "0123456789ABCDEF";
                    pc[0] = '0'; pc[1] = 'x';
                    pc[2] = hex[(g->product_code >> 12) & 0xF];
                    pc[3] = hex[(g->product_code >>  8) & 0xF];
                    pc[4] = hex[(g->product_code >>  4) & 0xF];
                    pc[5] = hex[ g->product_code        & 0xF];
                    pc[6] = 0;
                    draw_info_row(right_x, &ry, "URUN KODU", pc);
                }
            } else {
                draw_info_row(right_x, &ry, "EDID", "YOK");
                draw_info_row(right_x, &ry, "MONITOR BILGI", "BILINMIYOR");
            }

            py = (ly > ry ? ly : ry) + (int)(8 * ui_scale());
            if (py > y + h - (int)(30 * ui_scale())) break;
        }
    } else if (g_page == 5) {
        draw_text_scale(px, py, "DOSYA SİSTEMİ", rgb(246, 247, 252), ui_scale() + 1);
        draw_text(px + (int)(190 * ui_scale()), py + (int)(6 * ui_scale()), "[N] YENI GEZGIN", rgb(220, 39, 39));
        draw_text(px + (int)(330 * ui_scale()), py + (int)(6 * ui_scale()), "[T] TERMINAL", rgb(30, 132, 212));
        py += (int)(34 * ui_scale());
        int area_w = w - (int)(44 * ui_scale());
        int area_h = h - (py - y) - (int)(20 * ui_scale());
        for (uint32_t i = 0; i < MAX_EXPLORER_WINDOWS; i++) {
            if (g_windows[i].visible) {
                ensure_explorer_geometry(i, px, py, area_w, area_h);
                draw_explorer_window(i);
            }
        }
        draw_terminal_window();
        draw_text(px, y + h - (int)(20 * ui_scale()), "N GEZGIN  T TERMINAL  ENTER AC  DRAG BASLIK  WHEEL/UP/DOWN SCROLL", rgb(154, 166, 190));
    }
}

static void draw_cursor(void)
{
    uint32_t shadow = rgb(12, 12, 16);
    uint32_t fill = rgb(255, 255, 255);
    uint32_t edge = rgb(235, 36, 43);
    int x = g_mouse_x;
    int y = g_mouse_y;
    for (int i = 0; i < 18; i++) {
        put_pixel(x + 2, y + i + 2, shadow);
        put_pixel(x + i + 2, y + i + 2, shadow);
    }
    for (int i = 0; i < 18; i++) {
        put_pixel(x, y + i, edge);
        put_pixel(x + i, y + i, edge);
    }
    for (int i = 1; i < 14; i++) {
        for (int j = 1; j <= i / 2 + 1; j++) {
            put_pixel(x + j, y + i, fill);
        }
    }
    for (int i = 0; i < 8; i++) {
        put_pixel(x + 5 + i, y + 16, edge);
        put_pixel(x + 6 + i, y + 17, fill);
    }
}

static void flush_frame(void)
{
    if (!g_fb || !g_backbuffer) {
        return;
    }
    for (uint32_t y = 0; y < g_h; y++) {
        uint32_t *src = g_backbuffer + y * g_w;
        uint32_t *dst = g_fb + y * g_stride;
        for (uint32_t x = 0; x < g_w; x++) {
            dst[x] = src[x];
        }
    }
}

static void crash_screen(const char *detail, uint64_t code)
{
    if (!g_backbuffer || !g_fb) {
        for (;;) {
        }
    }
    draw_os_background();
    fill_rect(0, 0, (int)g_w, (int)g_h, rgb(7, 10, 20));
    int s = (int)ui_scale();
    int box_w = (int)g_w - (int)(120 * s);
    int box_h = (int)(190 * s);
    int x = ((int)g_w - box_w) / 2;
    int y = ((int)g_h - box_h) / 2;
    if (box_w < (int)(260 * s)) {
        box_w = (int)g_w - (int)(32 * s);
        x = (int)(16 * s);
    }
    fill_rect(x, y, box_w, box_h, rgb(12, 18, 32));
    draw_rect(x, y, box_w, box_h, rgb(220, 39, 39));
    draw_logo(x + (int)(20 * s), y + (int)(18 * s), (uint32_t)(s + 1));
    draw_text_scale(x + (int)(20 * s), y + (int)(62 * s), "SİSTEMDE HATA ÇIKTI", rgb(246, 247, 252), (uint32_t)(s + 1));
    draw_text(x + (int)(20 * s), y + (int)(100 * s), detail ? detail : "BILINMEYEN HATA", rgb(184, 194, 214));
    char num[24];
    u64_to_dec(code, num);
    draw_text(x + (int)(20 * s), y + (int)(128 * s), "HATA KODU", rgb(126, 136, 158));
    draw_text(x + (int)(110 * s), y + (int)(128 * s), num, rgb(220, 39, 39));
    draw_text(x + (int)(20 * s), y + box_h - (int)(24 * s), "CIHAZI YENIDEN BASLATIN", rgb(126, 136, 158));
    flush_frame();
    for (;;) {
        if (g_bs && g_bs->Stall) {
            g_bs->Stall(1000000);
        }
    }
}

/* ============================================================================
 * CYX runtime implementation
 * ============================================================================ */

static const uint32_t g_cyx_palette[16] = {
    0x000000, 0x081E5C, 0x2772E0, 0x2BAA42, 0x125A22, 0x35C6CC,
    0xE03030, 0xC036A8, 0x8C5A18, 0xC0C0C0, 0x707880, 0x66B0FF,
    0x6FE38B, 0x9CE8EC, 0xF1D540, 0xF6F7FC,
};

static int cyx_streq(const char *a, const char *b) {
    while (*a && *b) { if (*a != *b) return 0; a++; b++; }
    return *a == *b;
}

static int cyx_strieq(const char *a, const char *b) {
    while (*a && *b) {
        char ca = *a, cb = *b;
        if (ca >= 'a' && ca <= 'z') ca = (char)(ca - 32);
        if (cb >= 'a' && cb <= 'z') cb = (char)(cb - 32);
        if (ca != cb) return 0;
        a++; b++;
    }
    return *a == *b;
}

static void cyx_strcpy_n(char *dst, const char *src, uint32_t cap) {
    if (!cap) return;
    uint32_t i = 0;
    if (src) {
        for (; i + 1 < cap && src[i]; i++) dst[i] = src[i];
    }
    dst[i] = 0;
}

static uint32_t cyx_strlen(const char *s) {
    uint32_t n = 0; while (s[n]) n++; return n;
}

static void cyx_int_to_str(int32_t v, char *out) {
    char buf[16];
    int neg = v < 0;
    uint32_t u = neg ? (uint32_t)(-(int64_t)v) : (uint32_t)v;
    int n = 0;
    if (u == 0) buf[n++] = '0';
    else while (u) { buf[n++] = (char)('0' + (u % 10)); u /= 10; }
    if (neg) buf[n++] = '-';
    int j = 0;
    for (int i = n - 1; i >= 0; i--) out[j++] = buf[i];
    out[j] = 0;
}

static int cyx_parse_int(const char *s, int32_t *out) {
    if (!s || !*s) return 0;
    int neg = 0;
    if (*s == '-') { neg = 1; s++; if (!*s) return 0; }
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        s += 2;
        if (!*s) return 0;
        uint32_t v = 0;
        while (*s) {
            uint32_t d;
            if (*s >= '0' && *s <= '9') d = (uint32_t)(*s - '0');
            else if (*s >= 'a' && *s <= 'f') d = 10 + (uint32_t)(*s - 'a');
            else if (*s >= 'A' && *s <= 'F') d = 10 + (uint32_t)(*s - 'A');
            else return 0;
            v = v * 16 + d;
            s++;
        }
        *out = neg ? -(int32_t)v : (int32_t)v;
        return 1;
    }
    int32_t v = 0;
    int any = 0;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; any = 1; }
    if (!any || *s) return 0;
    *out = neg ? -v : v;
    return 1;
}

static uint32_t cyx_resolve_color(const char *s) {
    if (!s || !*s) return g_cyx_palette[15];
    /* Resolve $variable token to its value */
    char vbuf[32];
    if (s[0] == '$') {
        const char *name = s + 1;
        for (int i = 0; i < CYX_MAX_VARS; i++) {
            if (g_cyx_vars[i].used && cyx_streq(g_cyx_vars[i].name, name)) {
                if (g_cyx_vars[i].is_string) { s = g_cyx_vars[i].sval; }
                else { cyx_int_to_str(g_cyx_vars[i].ival, vbuf); s = vbuf; }
                break;
            }
        }
    }
    static const struct { const char *n; uint8_t idx; } names[] = {
        {"BLACK",0},{"NAVY",1},{"BLUE",2},{"GREEN",3},{"DGREEN",4},{"CYAN",5},
        {"RED",6},{"MAGENTA",7},{"BROWN",8},{"LGRAY",9},{"DGRAY",10},{"LBLUE",11},
        {"LGREEN",12},{"LCYAN",13},{"YELLOW",14},{"WHITE",15},
    };
    for (int i = 0; i < 16; i++) if (cyx_strieq(s, names[i].n)) return g_cyx_palette[names[i].idx];
    int32_t v;
    if (cyx_parse_int(s, &v)) {
        if (v >= 0 && v < 16) return g_cyx_palette[v];
        uint32_t u = (uint32_t)v;
        return rgb((uint8_t)((u >> 16) & 0xFF), (uint8_t)((u >> 8) & 0xFF), (uint8_t)(u & 0xFF));
    }
    return g_cyx_palette[15];
}

static int cyx_var_find(const char *name) {
    for (int i = 0; i < CYX_MAX_VARS; i++) {
        if (g_cyx_vars[i].used && cyx_streq(g_cyx_vars[i].name, name)) return i;
    }
    return -1;
}

static int cyx_var_alloc(const char *name) {
    int i = cyx_var_find(name);
    if (i >= 0) return i;
    for (i = 0; i < CYX_MAX_VARS; i++) {
        if (!g_cyx_vars[i].used) {
            cyx_strcpy_n(g_cyx_vars[i].name, name, sizeof(g_cyx_vars[i].name));
            g_cyx_vars[i].used = 1;
            g_cyx_vars[i].is_string = 0;
            g_cyx_vars[i].ival = 0;
            g_cyx_vars[i].sval[0] = 0;
            return i;
        }
    }
    return -1;
}

static int cyx_resolve_int(const char *t, int32_t *out) {
    if (!t || !*t) return 0;
    if (t[0] == '$') {
        int v = cyx_var_find(t + 1);
        if (v < 0) { *out = 0; return 1; }
        if (g_cyx_vars[v].is_string) {
            int32_t parsed = 0; cyx_parse_int(g_cyx_vars[v].sval, &parsed);
            *out = parsed; return 1;
        }
        *out = g_cyx_vars[v].ival;
        return 1;
    }
    if (t[0] == '@') {
        if (cyx_streq(t, "@x")) { *out = g_cyx_mx; return 1; }
        if (cyx_streq(t, "@y")) { *out = g_cyx_my; return 1; }
        if (cyx_streq(t, "@prevx")) { *out = g_cyx_have_prev ? g_cyx_prev_mx : g_cyx_mx; return 1; }
        if (cyx_streq(t, "@prevy")) { *out = g_cyx_have_prev ? g_cyx_prev_my : g_cyx_my; return 1; }
        if (cyx_streq(t, "@tick")) { *out = g_cyx_tick; return 1; }
        if (cyx_streq(t, "@width")) { *out = g_cyx_canvas_w; return 1; }
        if (cyx_streq(t, "@height")) { *out = g_cyx_canvas_h; return 1; }
        return 0;
    }
    return cyx_parse_int(t, out);
}

static void cyx_resolve_str(const char *t, uint8_t was_quoted, char *dst, uint32_t cap) {
    if (was_quoted) { cyx_strcpy_n(dst, t, cap); return; }
    if (!t || !*t) { dst[0] = 0; return; }
    if (t[0] == '$') {
        int v = cyx_var_find(t + 1);
        if (v < 0) { dst[0] = 0; return; }
        if (g_cyx_vars[v].is_string) cyx_strcpy_n(dst, g_cyx_vars[v].sval, cap);
        else { char buf[16]; cyx_int_to_str(g_cyx_vars[v].ival, buf); cyx_strcpy_n(dst, buf, cap); }
        return;
    }
    if (t[0] == '@') {
        if (cyx_streq(t, "@key")) { cyx_strcpy_n(dst, g_cyx_last_key, cap); return; }
        if (cyx_streq(t, "@click_btn")) { cyx_strcpy_n(dst, g_cyx_last_click_btn, cap); return; }
        int32_t v;
        if (cyx_resolve_int(t, &v)) { char buf[16]; cyx_int_to_str(v, buf); cyx_strcpy_n(dst, buf, cap); return; }
        dst[0] = 0;
        return;
    }
    cyx_strcpy_n(dst, t, cap);
}

static uint8_t cyx_tokenize(const char *line, char tok[CYX_MAX_TOKENS][CYX_TOK_LEN], uint8_t was_q[CYX_MAX_TOKENS]) {
    uint8_t count = 0;
    const char *p = line;
    while (*p && count < CYX_MAX_TOKENS) {
        while (*p == ' ' || *p == '\t') p++;
        if (!*p) break;
        was_q[count] = 0;
        uint32_t k = 0;
        if (*p == '"') {
            was_q[count] = 1;
            p++;
            while (*p && *p != '"' && k + 1 < CYX_TOK_LEN) tok[count][k++] = *p++;
            if (*p == '"') p++;
        } else {
            while (*p && *p != ' ' && *p != '\t' && k + 1 < CYX_TOK_LEN) tok[count][k++] = *p++;
        }
        tok[count][k] = 0;
        count++;
    }
    return count;
}

static const char *cyx_line(uint16_t i) { return &g_cyx_src[g_cyx_line_off[i]]; }

static void cyx_set_error(int32_t line, const char *msg) {
    if (g_cyx_has_error) return;
    g_cyx_has_error = 1;
    g_cyx_error_line = line;
    cyx_strcpy_n(g_cyx_error, msg, sizeof(g_cyx_error));
}

static void cyx_split_lines(void) {
    g_cyx_line_count = 0;
    if (!g_cyx_src_len) return;
    g_cyx_line_off[g_cyx_line_count++] = 0;
    uint32_t off = 0;
    while (off < g_cyx_src_len) {
        if (g_cyx_src[off] == '\n') {
            g_cyx_src[off] = 0;
            if (off + 1 < g_cyx_src_len && g_cyx_line_count < CYX_MAX_LINES) {
                g_cyx_line_off[g_cyx_line_count++] = (uint16_t)(off + 1);
            }
        } else if (g_cyx_src[off] == '\r') {
            g_cyx_src[off] = 0;
        }
        off++;
    }
    if (g_cyx_src_len < CYX_MAX_SRC) g_cyx_src[g_cyx_src_len] = 0;
}

static void cyx_parse(void) {
    g_cyx_handler_count = 0;
    g_cyx_label_count = 0;
    g_cyx_has_error = 0;
    g_cyx_error[0] = 0;
    g_cyx_error_line = -1;
    uint16_t cur = 0xFFFF;
    char tok[CYX_MAX_TOKENS][CYX_TOK_LEN];
    uint8_t wq[CYX_MAX_TOKENS];
    for (uint16_t i = 0; i < g_cyx_line_count; i++) {
        uint8_t n = cyx_tokenize(cyx_line(i), tok, wq);
        if (!n) continue;
        if (tok[0][0] == '#') continue;
        if (tok[0][0] == ':') {
            if (cur == 0xFFFF) { cyx_set_error(i, "LABEL OUTSIDE HANDLER"); continue; }
            if (g_cyx_label_count < CYX_MAX_LABELS_GOTO) {
                cyx_strcpy_n(g_cyx_labels[g_cyx_label_count].name, tok[0] + 1,
                             sizeof(g_cyx_labels[g_cyx_label_count].name));
                g_cyx_labels[g_cyx_label_count].line = i;
                g_cyx_label_count++;
            }
            continue;
        }
        if (cyx_strieq(tok[0], "ON")) {
            if (cur != 0xFFFF) { cyx_set_error(i, "NESTED ON BLOCK"); continue; }
            if (n < 2) { cyx_set_error(i, "ON NEEDS EVENT"); continue; }
            if (g_cyx_handler_count >= CYX_MAX_HANDLERS) { cyx_set_error(i, "TOO MANY HANDLERS"); continue; }
            cyx_handler_t *h = &g_cyx_handlers[g_cyx_handler_count];
            h->target[0] = 0;
            if      (cyx_strieq(tok[1], "START")) h->type = CYX_EV_START;
            else if (cyx_strieq(tok[1], "CLICK")) {
                h->type = CYX_EV_CLICK;
                if (n < 3) { cyx_set_error(i, "ON CLICK NEEDS BUTTON ID"); continue; }
                cyx_strcpy_n(h->target, tok[2], sizeof(h->target));
            }
            else if (cyx_strieq(tok[1], "KEY")) {
                h->type = CYX_EV_KEY;
                if (n >= 3) cyx_strcpy_n(h->target, tok[2], sizeof(h->target));
            }
            else if (cyx_strieq(tok[1], "DRAG")) h->type = CYX_EV_DRAG;
            else if (cyx_strieq(tok[1], "MOVE")) h->type = CYX_EV_MOVE;
            else if (cyx_strieq(tok[1], "TICK")) h->type = CYX_EV_TICK;
            else { cyx_set_error(i, "UNKNOWN EVENT"); continue; }
            h->start_line = (uint16_t)(i + 1);
            h->end_line = (uint16_t)(i + 1);
            cur = g_cyx_handler_count;
            g_cyx_handler_count++;
            continue;
        }
        if (cyx_strieq(tok[0], "END")) {
            if (cur == 0xFFFF) { cyx_set_error(i, "END WITHOUT ON"); continue; }
            g_cyx_handlers[cur].end_line = i;
            cur = 0xFFFF;
            continue;
        }
        if (cur == 0xFFFF) { cyx_set_error(i, "CODE OUTSIDE HANDLER"); continue; }
    }
    if (cur != 0xFFFF) cyx_set_error(g_cyx_line_count - 1, "MISSING END");
}

static void cyx_push_op(uint8_t op, int a, int b, int c, int d, uint32_t color, const char *text) {
    if (op == CYX_OP_FILL) g_cyx_op_count = 0;
    if (g_cyx_op_count >= CYX_MAX_OPS) return;
    cyx_op_t *o = &g_cyx_ops[g_cyx_op_count++];
    o->op = op;
    o->a = (int16_t)a; o->b = (int16_t)b; o->c = (int16_t)c; o->d = (int16_t)d;
    o->color = color;
    o->text_len = 0;
    if (text) {
        uint32_t k = 0;
        for (; text[k] && k + 1 < sizeof(o->text); k++) o->text[k] = text[k];
        o->text[k] = 0;
        o->text_len = (uint8_t)k;
    } else o->text[0] = 0;
}

static int cyx_btn_find(const char *id) {
    for (int i = 0; i < (int)g_cyx_btn_count; i++) if (cyx_streq(g_cyx_btns[i].id, id)) return i;
    return -1;
}
static int cyx_lab_find(const char *id) {
    for (int i = 0; i < (int)g_cyx_lab_count; i++) if (cyx_streq(g_cyx_labs[i].id, id)) return i;
    return -1;
}
static int cyx_inp_find(const char *id) {
    for (int i = 0; i < (int)g_cyx_inp_count; i++) if (cyx_streq(g_cyx_inps[i].id, id)) return i;
    return -1;
}

static uint16_t g_cyx_active_block_start;
static uint16_t g_cyx_active_block_end;

static int cyx_label_pos_for(const char *name, uint16_t *out) {
    /* Prefer labels within the active handler block; fall back to global */
    for (int i = 0; i < (int)g_cyx_label_count; i++) {
        if (g_cyx_labels[i].line >= g_cyx_active_block_start &&
            g_cyx_labels[i].line <  g_cyx_active_block_end &&
            cyx_streq(g_cyx_labels[i].name, name)) {
            *out = g_cyx_labels[i].line; return 1;
        }
    }
    for (int i = 0; i < (int)g_cyx_label_count; i++) {
        if (cyx_streq(g_cyx_labels[i].name, name)) { *out = g_cyx_labels[i].line; return 1; }
    }
    return 0;
}

static int cyx_path_to_c16(const char *src, CHAR16 *dst, uint32_t cap) {
    uint32_t k = 0;
    for (; src[k] && k + 1 < cap; k++) {
        char c = src[k];
        dst[k] = (c == '/') ? L'\\' : (CHAR16)(uint8_t)c;
    }
    dst[k] = 0;
    return 1;
}

static void cyx_run_file_op(uint16_t line_idx, const char *cmd,
                            char tok[CYX_MAX_TOKENS][CYX_TOK_LEN], uint8_t wq[CYX_MAX_TOKENS], uint8_t n) {
    if (cyx_strieq(cmd, "DELETE")) {
        if (n < 3) { cyx_set_error(line_idx, "DELETE disk \"path\""); return; }
        int32_t vol;
        if (!cyx_resolve_int(tok[1], &vol)) { cyx_set_error(line_idx, "BAD DISK"); return; }
        if (vol < 0 || (uint32_t)vol >= g_volume_count) { cyx_set_error(line_idx, "BAD DISK INDEX"); return; }
        char path[200]; cyx_resolve_str(tok[2], wq[2], path, sizeof(path));
        CHAR16 wp[256]; cyx_path_to_c16(path, wp, sizeof(wp) / sizeof(wp[0]));
        EFI_FILE_PROTOCOL *f = 0;
        if (!open_file_by_path((uint32_t)vol, wp, &f, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
            cyx_set_error(line_idx, "DELETE: FILE NOT OPEN"); return;
        }
        if (f->Delete(f) != EFI_SUCCESS) { cyx_set_error(line_idx, "DELETE FAILED"); return; }
        return;
    }
    /* COPY / MOVE */
    int is_move = cyx_strieq(cmd, "MOVE");
    if (n < 5) { cyx_set_error(line_idx, "COPY/MOVE src_disk \"src\" dst_disk \"dst\""); return; }
    int32_t sv, dv;
    if (!cyx_resolve_int(tok[1], &sv) || !cyx_resolve_int(tok[3], &dv)) { cyx_set_error(line_idx, "BAD DISK"); return; }
    if (sv < 0 || (uint32_t)sv >= g_volume_count || dv < 0 || (uint32_t)dv >= g_volume_count) {
        cyx_set_error(line_idx, "BAD DISK INDEX"); return;
    }
    char sp[200], dp[200];
    cyx_resolve_str(tok[2], wq[2], sp, sizeof(sp));
    cyx_resolve_str(tok[4], wq[4], dp, sizeof(dp));
    CHAR16 ws[256], wd[256];
    cyx_path_to_c16(sp, ws, sizeof(ws) / sizeof(ws[0]));
    cyx_path_to_c16(dp, wd, sizeof(wd) / sizeof(wd[0]));
    EFI_FILE_PROTOCOL *src = 0, *dst = 0, *old = 0;
    uint64_t src_size = 0;
    uint64_t src_mode = is_move ? (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE) : EFI_FILE_MODE_READ;
    if (!open_file_by_path((uint32_t)sv, ws, &src, src_mode, 0)) {
        if (!open_file_by_path((uint32_t)sv, ws, &src, EFI_FILE_MODE_READ, 0)) { cyx_set_error(line_idx, "SRC NOT FOUND"); return; }
        is_move = 0;
    }
    get_file_size(src, &src_size);
    if (open_file_by_path((uint32_t)dv, wd, &old, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) old->Delete(old);
    if (!open_file_by_path((uint32_t)dv, wd, &dst, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0)) {
        src->Close(src); cyx_set_error(line_idx, "DST CREATE FAILED"); return;
    }
    if (!preallocate_destination_file((uint32_t)dv, dst, src_size)) {
        dst->Close(dst); src->Close(src); cyx_set_error(line_idx, "DST PREALLOC FAILED"); return;
    }
    uint64_t total_written = 0;
    int ok = 1;
    for (;;) {
        UINTN rd = sizeof(g_io_buffer);
        if (src->Read(src, &rd, g_io_buffer) != EFI_SUCCESS || rd == 0) break;
        UINTN wr = rd;
        if (dst->Write(dst, &wr, g_io_buffer) != EFI_SUCCESS || wr != rd) { ok = 0; break; }
        total_written += rd;
    }
    if (ok) set_file_size(dst, total_written);
    dst->Flush(dst);
    dst->Close(dst);
    if (!ok) { src->Close(src); cyx_set_error(line_idx, "WRITE FAILED"); return; }
    if (is_move) src->Delete(src);
    else src->Close(src);
}

static void cyx_exec(uint16_t line_idx) {
    char tok[CYX_MAX_TOKENS][CYX_TOK_LEN];
    uint8_t wq[CYX_MAX_TOKENS];
    uint8_t n = cyx_tokenize(cyx_line(line_idx), tok, wq);
    if (!n || tok[0][0] == '#' || tok[0][0] == ':') return;
    if (cyx_strieq(tok[0], "ON") || cyx_strieq(tok[0], "END")) return;
    const char *cmd = tok[0];

    if (cyx_strieq(cmd, "WINDOW")) {
        if (n < 3) { cyx_set_error(line_idx, "WINDOW W H \"title\""); return; }
        int32_t w, h;
        if (!cyx_resolve_int(tok[1], &w) || !cyx_resolve_int(tok[2], &h)) { cyx_set_error(line_idx, "BAD WINDOW SIZE"); return; }
        if (w < 120) w = 120; if (w > 760) w = 760;
        if (h < 80) h = 80;   if (h > 520) h = 520;
        g_cyx_canvas_w = (int16_t)w;
        g_cyx_canvas_h = (int16_t)h;
        if (n >= 4) {
            char s[48]; cyx_resolve_str(tok[3], wq[3], s, sizeof(s));
            cyx_strcpy_n(g_cyx_title, s, sizeof(g_cyx_title));
        }
        return;
    }
    if (cyx_strieq(cmd, "TITLE")) {
        if (n < 2) { cyx_set_error(line_idx, "TITLE NEEDS TEXT"); return; }
        char s[48]; cyx_resolve_str(tok[1], wq[1], s, sizeof(s));
        cyx_strcpy_n(g_cyx_title, s, sizeof(g_cyx_title));
        return;
    }
    if (cyx_strieq(cmd, "EXIT")) { g_cyx_did_exit = 1; return; }

    if (cyx_strieq(cmd, "FILL")) {
        if (n < 2) { cyx_set_error(line_idx, "FILL COLOR"); return; }
        cyx_push_op(CYX_OP_FILL, 0, 0, g_cyx_canvas_w, g_cyx_canvas_h, cyx_resolve_color(tok[1]), 0);
        return;
    }
    if (cyx_strieq(cmd, "CLEAR")) {
        cyx_push_op(CYX_OP_FILL, 0, 0, g_cyx_canvas_w, g_cyx_canvas_h, g_cyx_palette[0], 0);
        return;
    }
    if (cyx_strieq(cmd, "PIXEL")) {
        if (n < 4) { cyx_set_error(line_idx, "PIXEL X Y COLOR"); return; }
        int32_t x, y;
        if (!cyx_resolve_int(tok[1], &x) || !cyx_resolve_int(tok[2], &y)) { cyx_set_error(line_idx, "BAD PIXEL ARGS"); return; }
        cyx_push_op(CYX_OP_PIXEL, x, y, 0, 0, cyx_resolve_color(tok[3]), 0);
        return;
    }
    if (cyx_strieq(cmd, "LINE")) {
        if (n < 6) { cyx_set_error(line_idx, "LINE X1 Y1 X2 Y2 COLOR"); return; }
        int32_t a,b,c,d;
        if (!cyx_resolve_int(tok[1],&a)||!cyx_resolve_int(tok[2],&b)||!cyx_resolve_int(tok[3],&c)||!cyx_resolve_int(tok[4],&d)) { cyx_set_error(line_idx,"BAD LINE"); return; }
        cyx_push_op(CYX_OP_LINE, a, b, c, d, cyx_resolve_color(tok[5]), 0);
        return;
    }
    if (cyx_strieq(cmd, "RECT")) {
        if (n < 6) { cyx_set_error(line_idx, "RECT X Y W H COLOR"); return; }
        int32_t a,b,c,d;
        if (!cyx_resolve_int(tok[1],&a)||!cyx_resolve_int(tok[2],&b)||!cyx_resolve_int(tok[3],&c)||!cyx_resolve_int(tok[4],&d)) { cyx_set_error(line_idx,"BAD RECT"); return; }
        cyx_push_op(CYX_OP_RECT, a, b, c, d, cyx_resolve_color(tok[5]), 0);
        return;
    }
    if (cyx_strieq(cmd, "FILLRECT")) {
        if (n < 6) { cyx_set_error(line_idx, "FILLRECT X Y W H COLOR"); return; }
        int32_t a,b,c,d;
        if (!cyx_resolve_int(tok[1],&a)||!cyx_resolve_int(tok[2],&b)||!cyx_resolve_int(tok[3],&c)||!cyx_resolve_int(tok[4],&d)) { cyx_set_error(line_idx,"BAD FILLRECT"); return; }
        cyx_push_op(CYX_OP_FILLRECT, a, b, c, d, cyx_resolve_color(tok[5]), 0);
        return;
    }
    if (cyx_strieq(cmd, "TEXT")) {
        if (n < 5) { cyx_set_error(line_idx, "TEXT X Y COLOR \"...\""); return; }
        int32_t x, y;
        if (!cyx_resolve_int(tok[1], &x) || !cyx_resolve_int(tok[2], &y)) { cyx_set_error(line_idx, "BAD TEXT POS"); return; }
        char s[16]; cyx_resolve_str(tok[4], wq[4], s, sizeof(s));
        cyx_push_op(CYX_OP_TEXT, x, y, 0, 0, cyx_resolve_color(tok[3]), s);
        return;
    }

    if (cyx_strieq(cmd, "BUTTON")) {
        if (n < 7) { cyx_set_error(line_idx, "BUTTON ID X Y W H \"label\""); return; }
        int idx = cyx_btn_find(tok[1]);
        if (idx < 0) {
            if (g_cyx_btn_count >= CYX_MAX_BUTTONS) { cyx_set_error(line_idx, "TOO MANY BUTTONS"); return; }
            idx = g_cyx_btn_count++;
            cyx_strcpy_n(g_cyx_btns[idx].id, tok[1], sizeof(g_cyx_btns[idx].id));
        }
        int32_t x,y,w,h;
        if (!cyx_resolve_int(tok[2],&x)||!cyx_resolve_int(tok[3],&y)||!cyx_resolve_int(tok[4],&w)||!cyx_resolve_int(tok[5],&h)) { cyx_set_error(line_idx,"BAD BUTTON GEOM"); return; }
        g_cyx_btns[idx].x = (int16_t)x; g_cyx_btns[idx].y = (int16_t)y;
        g_cyx_btns[idx].w = (int16_t)w; g_cyx_btns[idx].h = (int16_t)h;
        char s[40]; cyx_resolve_str(tok[6], wq[6], s, sizeof(s));
        cyx_strcpy_n(g_cyx_btns[idx].text, s, sizeof(g_cyx_btns[idx].text));
        return;
    }
    if (cyx_strieq(cmd, "LABEL")) {
        if (n < 6) { cyx_set_error(line_idx, "LABEL ID X Y COLOR \"text\""); return; }
        int idx = cyx_lab_find(tok[1]);
        if (idx < 0) {
            if (g_cyx_lab_count >= CYX_MAX_LABELS) { cyx_set_error(line_idx, "TOO MANY LABELS"); return; }
            idx = g_cyx_lab_count++;
            cyx_strcpy_n(g_cyx_labs[idx].id, tok[1], sizeof(g_cyx_labs[idx].id));
        }
        int32_t x, y;
        if (!cyx_resolve_int(tok[2], &x) || !cyx_resolve_int(tok[3], &y)) { cyx_set_error(line_idx, "BAD LABEL POS"); return; }
        g_cyx_labs[idx].x = (int16_t)x; g_cyx_labs[idx].y = (int16_t)y;
        g_cyx_labs[idx].color = cyx_resolve_color(tok[4]);
        char s[64]; cyx_resolve_str(tok[5], wq[5], s, sizeof(s));
        cyx_strcpy_n(g_cyx_labs[idx].text, s, sizeof(g_cyx_labs[idx].text));
        return;
    }
    if (cyx_strieq(cmd, "INPUT")) {
        if (n < 6) { cyx_set_error(line_idx, "INPUT ID X Y W H"); return; }
        int idx = cyx_inp_find(tok[1]);
        if (idx < 0) {
            if (g_cyx_inp_count >= CYX_MAX_INPUTS) { cyx_set_error(line_idx, "TOO MANY INPUTS"); return; }
            idx = g_cyx_inp_count++;
            cyx_strcpy_n(g_cyx_inps[idx].id, tok[1], sizeof(g_cyx_inps[idx].id));
            g_cyx_inps[idx].text[0] = 0; g_cyx_inps[idx].cursor = 0; g_cyx_inps[idx].focused = 0;
        }
        int32_t x,y,w,h;
        if (!cyx_resolve_int(tok[2],&x)||!cyx_resolve_int(tok[3],&y)||!cyx_resolve_int(tok[4],&w)||!cyx_resolve_int(tok[5],&h)) { cyx_set_error(line_idx,"BAD INPUT GEOM"); return; }
        g_cyx_inps[idx].x = (int16_t)x; g_cyx_inps[idx].y = (int16_t)y;
        g_cyx_inps[idx].w = (int16_t)w; g_cyx_inps[idx].h = (int16_t)h;
        return;
    }
    if (cyx_strieq(cmd, "SET_LABEL")) {
        if (n < 3) { cyx_set_error(line_idx, "SET_LABEL ID TEXT"); return; }
        int idx = cyx_lab_find(tok[1]);
        if (idx < 0) { cyx_set_error(line_idx, "UNKNOWN LABEL"); return; }
        char s[64]; cyx_resolve_str(tok[2], wq[2], s, sizeof(s));
        cyx_strcpy_n(g_cyx_labs[idx].text, s, sizeof(g_cyx_labs[idx].text));
        return;
    }
    if (cyx_strieq(cmd, "SET_INPUT")) {
        if (n < 3) { cyx_set_error(line_idx, "SET_INPUT ID TEXT"); return; }
        int idx = cyx_inp_find(tok[1]);
        if (idx < 0) { cyx_set_error(line_idx, "UNKNOWN INPUT"); return; }
        char s[64]; cyx_resolve_str(tok[2], wq[2], s, sizeof(s));
        cyx_strcpy_n(g_cyx_inps[idx].text, s, sizeof(g_cyx_inps[idx].text));
        g_cyx_inps[idx].cursor = (uint16_t)cyx_strlen(g_cyx_inps[idx].text);
        return;
    }
    if (cyx_strieq(cmd, "GET_INPUT")) {
        if (n < 3 || tok[2][0] != '$') { cyx_set_error(line_idx, "GET_INPUT ID $var"); return; }
        int idx = cyx_inp_find(tok[1]);
        if (idx < 0) { cyx_set_error(line_idx, "UNKNOWN INPUT"); return; }
        int v = cyx_var_alloc(tok[2] + 1);
        if (v < 0) { cyx_set_error(line_idx, "TOO MANY VARS"); return; }
        g_cyx_vars[v].is_string = 1;
        cyx_strcpy_n(g_cyx_vars[v].sval, g_cyx_inps[idx].text, sizeof(g_cyx_vars[v].sval));
        return;
    }

    if (cyx_strieq(cmd, "SET")) {
        if (n < 3 || tok[1][0] != '$') { cyx_set_error(line_idx, "SET $var value"); return; }
        int v = cyx_var_alloc(tok[1] + 1);
        if (v < 0) { cyx_set_error(line_idx, "TOO MANY VARS"); return; }
        int32_t val;
        if (!cyx_resolve_int(tok[2], &val)) { cyx_set_error(line_idx, "BAD INT VALUE"); return; }
        g_cyx_vars[v].is_string = 0; g_cyx_vars[v].ival = val;
        return;
    }
    if (cyx_strieq(cmd, "SETSTR")) {
        if (n < 3 || tok[1][0] != '$') { cyx_set_error(line_idx, "SETSTR $var TEXT"); return; }
        int v = cyx_var_alloc(tok[1] + 1);
        if (v < 0) { cyx_set_error(line_idx, "TOO MANY VARS"); return; }
        char s[CYX_VAR_STR_LEN]; cyx_resolve_str(tok[2], wq[2], s, sizeof(s));
        g_cyx_vars[v].is_string = 1;
        cyx_strcpy_n(g_cyx_vars[v].sval, s, sizeof(g_cyx_vars[v].sval));
        return;
    }
    if (cyx_strieq(cmd, "APPEND")) {
        if (n < 3 || tok[1][0] != '$') { cyx_set_error(line_idx, "APPEND $var TEXT"); return; }
        int v = cyx_var_find(tok[1] + 1);
        if (v < 0) {
            v = cyx_var_alloc(tok[1] + 1);
            if (v < 0) { cyx_set_error(line_idx, "TOO MANY VARS"); return; }
            g_cyx_vars[v].is_string = 1; g_cyx_vars[v].sval[0] = 0;
        }
        if (!g_cyx_vars[v].is_string) {
            char buf[16]; cyx_int_to_str(g_cyx_vars[v].ival, buf);
            g_cyx_vars[v].is_string = 1;
            cyx_strcpy_n(g_cyx_vars[v].sval, buf, sizeof(g_cyx_vars[v].sval));
        }
        char s[CYX_VAR_STR_LEN]; cyx_resolve_str(tok[2], wq[2], s, sizeof(s));
        uint32_t curlen = cyx_strlen(g_cyx_vars[v].sval);
        for (uint32_t i = 0; s[i] && curlen + 1 < sizeof(g_cyx_vars[v].sval); i++) {
            g_cyx_vars[v].sval[curlen++] = s[i];
        }
        g_cyx_vars[v].sval[curlen] = 0;
        return;
    }

    if (cyx_strieq(cmd, "ADD") || cyx_strieq(cmd, "SUB") || cyx_strieq(cmd, "MUL") || cyx_strieq(cmd, "DIV") || cyx_strieq(cmd, "MOD")) {
        if (n < 3 || tok[1][0] != '$') { cyx_set_error(line_idx, "MATH NEEDS $var value"); return; }
        int v = cyx_var_alloc(tok[1] + 1);
        if (v < 0) { cyx_set_error(line_idx, "TOO MANY VARS"); return; }
        int32_t val;
        if (!cyx_resolve_int(tok[2], &val)) { cyx_set_error(line_idx, "BAD INT VALUE"); return; }
        if (g_cyx_vars[v].is_string) {
            int32_t cur = 0; cyx_parse_int(g_cyx_vars[v].sval, &cur);
            g_cyx_vars[v].ival = cur; g_cyx_vars[v].is_string = 0;
        }
        if      (cyx_strieq(cmd, "ADD")) g_cyx_vars[v].ival += val;
        else if (cyx_strieq(cmd, "SUB")) g_cyx_vars[v].ival -= val;
        else if (cyx_strieq(cmd, "MUL")) g_cyx_vars[v].ival *= val;
        else if (cyx_strieq(cmd, "DIV")) { if (!val) { cyx_set_error(line_idx, "DIV BY ZERO"); return; } g_cyx_vars[v].ival /= val; }
        else                              { if (!val) { cyx_set_error(line_idx, "MOD BY ZERO"); return; } g_cyx_vars[v].ival %= val; }
        return;
    }

    if (cyx_strieq(cmd, "TOSTR")) {
        if (n < 3 || tok[1][0] != '$') { cyx_set_error(line_idx, "TOSTR $dst src"); return; }
        int dst = cyx_var_alloc(tok[1] + 1);
        if (dst < 0) { cyx_set_error(line_idx, "TOO MANY VARS"); return; }
        int32_t v;
        if (!cyx_resolve_int(tok[2], &v)) { cyx_set_error(line_idx, "BAD INT"); return; }
        char buf[16]; cyx_int_to_str(v, buf);
        g_cyx_vars[dst].is_string = 1;
        cyx_strcpy_n(g_cyx_vars[dst].sval, buf, sizeof(g_cyx_vars[dst].sval));
        return;
    }
    if (cyx_strieq(cmd, "TOINT")) {
        if (n < 3 || tok[1][0] != '$') { cyx_set_error(line_idx, "TOINT $dst src"); return; }
        int dst = cyx_var_alloc(tok[1] + 1);
        if (dst < 0) { cyx_set_error(line_idx, "TOO MANY VARS"); return; }
        char s[CYX_VAR_STR_LEN]; cyx_resolve_str(tok[2], wq[2], s, sizeof(s));
        int32_t v = 0; cyx_parse_int(s, &v);
        g_cyx_vars[dst].is_string = 0; g_cyx_vars[dst].ival = v;
        return;
    }

    if (cyx_strieq(cmd, "GOTO")) {
        if (n < 2) { cyx_set_error(line_idx, "GOTO label"); return; }
        uint16_t t;
        if (!cyx_label_pos_for(tok[1], &t)) { cyx_set_error(line_idx, "UNKNOWN LABEL"); return; }
        g_cyx_jump_target = t; g_cyx_did_goto = 1;
        return;
    }
    if (cyx_strieq(cmd, "IF")) {
        if (n < 6 || !cyx_strieq(tok[4], "GOTO")) { cyx_set_error(line_idx, "IF a OP b GOTO label"); return; }
        int32_t a, b;
        if (!cyx_resolve_int(tok[1], &a) || !cyx_resolve_int(tok[3], &b)) { cyx_set_error(line_idx, "BAD IF OPERANDS"); return; }
        const char *op = tok[2];
        int truth = 0;
        if      (cyx_streq(op, "==")) truth = (a == b);
        else if (cyx_streq(op, "!=")) truth = (a != b);
        else if (cyx_streq(op, "<"))  truth = (a < b);
        else if (cyx_streq(op, ">"))  truth = (a > b);
        else if (cyx_streq(op, "<=")) truth = (a <= b);
        else if (cyx_streq(op, ">=")) truth = (a >= b);
        else { cyx_set_error(line_idx, "BAD IF OP"); return; }
        if (!truth) return;
        uint16_t t;
        if (!cyx_label_pos_for(tok[5], &t)) { cyx_set_error(line_idx, "UNKNOWN LABEL"); return; }
        g_cyx_jump_target = t; g_cyx_did_goto = 1;
        return;
    }

    if (cyx_strieq(cmd, "PRINT")) {
        if (n < 2) { g_cyx_status[0] = 0; return; }
        cyx_resolve_str(tok[1], wq[1], g_cyx_status, sizeof(g_cyx_status));
        return;
    }
    if (cyx_strieq(cmd, "LIST_DISKS")) {
        if (n < 2 || tok[1][0] != '$') { cyx_set_error(line_idx, "LIST_DISKS $count"); return; }
        int v = cyx_var_alloc(tok[1] + 1);
        if (v < 0) { cyx_set_error(line_idx, "TOO MANY VARS"); return; }
        g_cyx_vars[v].is_string = 0;
        g_cyx_vars[v].ival = (int32_t)g_volume_count;
        return;
    }
    if (cyx_strieq(cmd, "COPY") || cyx_strieq(cmd, "MOVE") || cyx_strieq(cmd, "DELETE")) {
        cyx_run_file_op(line_idx, cmd, tok, wq, n);
        return;
    }

    cyx_set_error(line_idx, "UNKNOWN COMMAND");
}

static void cyx_run_block(uint16_t start, uint16_t end) {
    uint16_t pc = start;
    int budget = 50000;
    g_cyx_active_block_start = start;
    g_cyx_active_block_end = end;
    while (pc < end && !g_cyx_has_error && !g_cyx_did_exit && budget-- > 0) {
        g_cyx_did_goto = 0;
        cyx_exec(pc);
        if (g_cyx_did_goto) pc = g_cyx_jump_target;
        else pc++;
    }
    if (budget <= 0) cyx_set_error(pc, "INFINITE LOOP");
}

static int cyx_dispatch(uint8_t event_type, const char *target) {
    if (!g_cyx_running || g_cyx_has_error || g_cyx_did_exit) return 0;
    int found = 0;
    for (uint16_t i = 0; i < g_cyx_handler_count; i++) {
        if (g_cyx_handlers[i].type != event_type) continue;
        if (event_type == CYX_EV_CLICK || event_type == CYX_EV_KEY) {
            if (g_cyx_handlers[i].target[0]) {
                if (!cyx_streq(g_cyx_handlers[i].target, target)) continue;
            }
        }
        cyx_run_block(g_cyx_handlers[i].start_line, g_cyx_handlers[i].end_line);
        found = 1;
        if (g_cyx_did_exit || g_cyx_has_error) break;
    }
    return found;
}

/* Reset all CYX runtime state for a fresh run */
static void cyx_reset_runtime(void) {
    g_cyx_canvas_w = 480; g_cyx_canvas_h = 320;
    cyx_strcpy_n(g_cyx_title, "CYX UYGULAMA", sizeof(g_cyx_title));
    g_cyx_status[0] = 0;
    g_cyx_op_count = 0;
    g_cyx_btn_count = 0; g_cyx_lab_count = 0; g_cyx_inp_count = 0;
    g_cyx_handler_count = 0; g_cyx_label_count = 0;
    g_cyx_did_exit = 0; g_cyx_did_goto = 0;
    g_cyx_has_error = 0; g_cyx_error[0] = 0; g_cyx_error_line = -1;
    g_cyx_tick = 0; g_cyx_last_tick_at = 0;
    g_cyx_mouse_in_canvas = 0; g_cyx_left_was_down = 0;
    g_cyx_last_key[0] = 0; g_cyx_last_click_btn[0] = 0;
    for (int i = 0; i < CYX_MAX_VARS; i++) {
        g_cyx_vars[i].used = 0;
        g_cyx_vars[i].name[0] = 0;
        g_cyx_vars[i].sval[0] = 0;
        g_cyx_vars[i].ival = 0;
        g_cyx_vars[i].is_string = 0;
    }
}

/* Read .cyx file into g_cyx_src. Returns 1 on success. */
static int cyx_load_source(uint32_t vol, const CHAR16 *path) {
    EFI_FILE_PROTOCOL *f = 0;
    if (!open_file_by_path(vol, path, &f, EFI_FILE_MODE_READ, 0)) return 0;
    UINTN sz = sizeof(g_cyx_src) - 1;
    EFI_STATUS st = f->Read(f, &sz, g_cyx_src);
    f->Close(f);
    if (st != EFI_SUCCESS) return 0;
    g_cyx_src[sz] = 0;
    g_cyx_src_len = (uint32_t)sz;
    return 1;
}

/* Detect .cyx file extension on a CHAR16 name */
static int cyx_name_has_ext(const CHAR16 *name) {
    if (!name) return 0;
    uint32_t len = c16_len(name);
    if (len < 4) return 0;
    CHAR16 a = name[len - 4], b = name[len - 3], c = name[len - 2], d = name[len - 1];
    if (a != '.') return 0;
    CHAR16 b2 = (b >= 'a' && b <= 'z') ? (CHAR16)(b - 32) : b;
    CHAR16 c2 = (c >= 'a' && c <= 'z') ? (CHAR16)(c - 32) : c;
    CHAR16 d2 = (d >= 'a' && d <= 'z') ? (CHAR16)(d - 32) : d;
    return (b2 == 'C' && c2 == 'Y' && d2 == 'X');
}

/* Open Run/Edit chooser for a .cyx file */
static void cyx_open_chooser(uint32_t vol, const CHAR16 *path, const CHAR16 *name) {
    g_cyx_choose_vol = vol;
    c16_copy(g_cyx_choose_path, path, sizeof(g_cyx_choose_path) / sizeof(g_cyx_choose_path[0]));
    c16_copy(g_cyx_choose_name, name, sizeof(g_cyx_choose_name) / sizeof(g_cyx_choose_name[0]));
    g_cyx_choose_hover = 0;
    g_cyx_choose_open = 1;
}

/* Start running an app from current chooser selection */
static void cyx_start_run(void) {
    cyx_reset_runtime();
    g_cyx_src_vol = g_cyx_choose_vol;
    c16_copy(g_cyx_src_path, g_cyx_choose_path, sizeof(g_cyx_src_path) / sizeof(g_cyx_src_path[0]));
    c16_copy(g_cyx_src_name, g_cyx_choose_name, sizeof(g_cyx_src_name) / sizeof(g_cyx_src_name[0]));
    if (!cyx_load_source(g_cyx_src_vol, g_cyx_src_path)) {
        set_last_error("CYX: KAYNAK OKUNAMADI");
        return;
    }
    cyx_split_lines();
    cyx_parse();
    g_cyx_running = 1;
    cyx_dispatch(CYX_EV_START, "");
    /* Center the window now that canvas size is known */
    int cw = g_cyx_canvas_w + 14;
    int ch = g_cyx_canvas_h + 60;
    g_cyx_win_x = (int16_t)(((int)g_w - cw) / 2);
    g_cyx_win_y = (int16_t)(((int)g_h - ch) / 2);
    if (g_cyx_win_x < 8) g_cyx_win_x = 8;
    if (g_cyx_win_y < 30) g_cyx_win_y = 30;
}

/* Open file as editor (re-uses viewer in edit mode) */
static void cyx_start_edit(void) {
    EFI_FILE_PROTOCOL *file = 0;
    if (!open_file_by_path(g_cyx_choose_vol, g_cyx_choose_path, &file, EFI_FILE_MODE_READ, 0)) {
        set_last_error("CYX: KAYNAK ACILAMADI");
        return;
    }
    UINTN sz = sizeof(g_viewer_text) - 1;
    EFI_STATUS st = file->Read(file, &sz, g_viewer_text);
    file->Close(file);
    if (st != EFI_SUCCESS) { set_last_error("CYX: OKUMA HATASI"); return; }
    g_viewer_text[sz] = 0;
    for (UINTN i = 0; i < sz; i++) {
        uint8_t c = (uint8_t)g_viewer_text[i];
        if (c == '\r') g_viewer_text[i] = '\n';
        else if (c < 32 && c != '\n' && c != '\t') g_viewer_text[i] = '.';
    }
    c16_copy(g_viewer_title, g_cyx_choose_name, sizeof(g_viewer_title) / sizeof(g_viewer_title[0]));
    g_viewer_vol = g_cyx_choose_vol;
    c16_copy(g_viewer_path, g_cyx_choose_path, sizeof(g_viewer_path) / sizeof(g_viewer_path[0]));
    g_viewer_cursor = 0;
    g_viewer_scroll = 0;
    g_viewer_edit = 1;
    g_viewer_open = 1;
}

/* ---- CYX rendering ---- */

static void cyx_clip_rect(int *x, int *y, int *w, int *h, int max_w, int max_h) {
    if (*x < 0) { *w += *x; *x = 0; }
    if (*y < 0) { *h += *y; *y = 0; }
    if (*x + *w > max_w) *w = max_w - *x;
    if (*y + *h > max_h) *h = max_h - *y;
}

static void cyx_draw_canvas_line(int origin_x, int origin_y, int x0, int y0, int x1, int y1, uint32_t color, int cw, int ch) {
    /* Bresenham, clipped to canvas */
    int dx = x1 - x0; if (dx < 0) dx = -dx;
    int dy = y1 - y0; if (dy < 0) dy = -dy;
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int safety = 4000;
    while (safety-- > 0) {
        if (x0 >= 0 && x0 < cw && y0 >= 0 && y0 < ch) put_pixel(origin_x + x0, origin_y + y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
}

static void cyx_replay_canvas(int origin_x, int origin_y, int cw, int ch) {
    fill_rect(origin_x, origin_y, cw, ch, g_cyx_palette[0]);
    for (uint16_t i = 0; i < g_cyx_op_count; i++) {
        cyx_op_t *o = &g_cyx_ops[i];
        switch (o->op) {
            case CYX_OP_FILL: {
                fill_rect(origin_x, origin_y, cw, ch, o->color);
                break;
            }
            case CYX_OP_PIXEL: {
                if (o->a >= 0 && o->a < cw && o->b >= 0 && o->b < ch)
                    put_pixel(origin_x + o->a, origin_y + o->b, o->color);
                break;
            }
            case CYX_OP_LINE: {
                cyx_draw_canvas_line(origin_x, origin_y, o->a, o->b, o->c, o->d, o->color, cw, ch);
                break;
            }
            case CYX_OP_RECT: {
                int x = o->a, y = o->b, w = o->c, h = o->d;
                cyx_clip_rect(&x, &y, &w, &h, cw, ch);
                if (w > 0 && h > 0) draw_rect(origin_x + x, origin_y + y, w, h, o->color);
                break;
            }
            case CYX_OP_FILLRECT: {
                int x = o->a, y = o->b, w = o->c, h = o->d;
                cyx_clip_rect(&x, &y, &w, &h, cw, ch);
                if (w > 0 && h > 0) fill_rect(origin_x + x, origin_y + y, w, h, o->color);
                break;
            }
            case CYX_OP_TEXT: {
                if (o->a >= 0 && o->a < cw && o->b >= 0 && o->b < ch)
                    draw_text(origin_x + o->a, origin_y + o->b, o->text, o->color);
                break;
            }
        }
    }
}

static void draw_cyx_app_window(void) {
    if (!g_cyx_running) return;
    int cw = g_cyx_canvas_w;
    int ch = g_cyx_canvas_h;
    int title_h = 22;
    int status_h = 22;
    int margin = 7;
    int win_w = cw + margin * 2;
    int win_h = ch + title_h + status_h + margin;
    int x = g_cyx_win_x;
    int y = g_cyx_win_y;
    /* Drop-shadow + frame */
    fill_rect(x - 2, y - 2, win_w + 4, win_h + 4, rgb(5, 8, 16));
    fill_rect(x, y, win_w, win_h, rgb(12, 18, 32));
    draw_rect(x, y, win_w, win_h, rgb(39, 160, 220));
    /* Title bar */
    fill_rect(x + 1, y + 1, win_w - 2, title_h, rgb(18, 34, 52));
    draw_text(x + 8, y + 7, "CYX:", rgb(156, 168, 192));
    draw_text(x + 38, y + 7, g_cyx_title, rgb(246, 247, 252));
    draw_text(x + win_w - 60, y + 7, "[ESC] KAPAT", rgb(220, 60, 60));
    /* Canvas origin */
    int ox = x + margin;
    int oy = y + title_h + 2;
    cyx_replay_canvas(ox, oy, cw, ch);
    /* Track mouse-in-canvas */
    g_cyx_mouse_in_canvas = (g_mouse_x >= ox && g_mouse_x < ox + cw &&
                             g_mouse_y >= oy && g_mouse_y < oy + ch);
    g_cyx_mx = (int16_t)(g_mouse_x - ox);
    g_cyx_my = (int16_t)(g_mouse_y - oy);
    /* Labels */
    for (uint16_t i = 0; i < g_cyx_lab_count; i++) {
        cyx_lab_t *l = &g_cyx_labs[i];
        if (l->x >= 0 && l->x < cw && l->y >= 0 && l->y < ch)
            draw_text(ox + l->x, oy + l->y, l->text, l->color);
    }
    /* Inputs */
    for (uint16_t i = 0; i < g_cyx_inp_count; i++) {
        cyx_inp_t *in = &g_cyx_inps[i];
        int ix = ox + in->x, iy = oy + in->y, iw = in->w, ih = in->h;
        fill_rect(ix, iy, iw, ih, rgb(30, 40, 58));
        draw_rect(ix, iy, iw, ih, in->focused ? rgb(246, 200, 80) : rgb(70, 90, 120));
        draw_text(ix + 4, iy + (ih - 8) / 2, in->text, rgb(232, 238, 248));
        if (in->focused) {
            int char_w = 6;
            int cx = ix + 4 + (int)in->cursor * char_w;
            if (cx < ix + iw - 2)
                fill_rect(cx, iy + 3, 1, ih - 6, rgb(246, 200, 80));
        }
    }
    /* Buttons */
    for (uint16_t i = 0; i < g_cyx_btn_count; i++) {
        cyx_btn_t *b = &g_cyx_btns[i];
        int bx = ox + b->x, by = oy + b->y, bw = b->w, bh = b->h;
        int hover = (g_mouse_x >= bx && g_mouse_x < bx + bw &&
                     g_mouse_y >= by && g_mouse_y < by + bh);
        uint32_t fill = hover ? rgb(40, 90, 140) : rgb(28, 56, 92);
        fill_rect(bx, by, bw, bh, fill);
        draw_rect(bx, by, bw, bh, rgb(80, 130, 200));
        int tw = (int)cyx_strlen(b->text) * 6;
        int tx = bx + (bw - tw) / 2;
        if (tx < bx + 3) tx = bx + 3;
        draw_text(tx, by + (bh - 8) / 2, b->text, rgb(240, 246, 252));
    }
    /* Status bar */
    int sy_y = y + title_h + ch + 4;
    fill_rect(x + 1, sy_y, win_w - 2, status_h - 2, rgb(8, 14, 24));
    if (g_cyx_has_error) {
        char prefix[16];
        cyx_int_to_str(g_cyx_error_line + 1, prefix);
        fill_rect(x + 1, sy_y, win_w - 2, status_h - 2, rgb(80, 16, 16));
        draw_text(x + 8, sy_y + 7, "HATA SAT", rgb(255, 200, 200));
        draw_text(x + 60, sy_y + 7, prefix, rgb(255, 220, 100));
        draw_text(x + 90, sy_y + 7, ":", rgb(255, 200, 200));
        draw_text(x + 100, sy_y + 7, g_cyx_error, rgb(255, 230, 230));
    } else if (g_cyx_status[0]) {
        draw_text(x + 8, sy_y + 7, g_cyx_status, rgb(180, 200, 230));
    } else {
        draw_text(x + 8, sy_y + 7, "HAZIR", rgb(120, 140, 170));
    }
}

static void draw_cyx_chooser_dialog(void) {
    if (!g_cyx_choose_open) return;
    uint32_t scale = ui_scale();
    int pw = (int)(360 * scale);
    int ph = (int)(150 * scale);
    int px = ((int)g_w - pw) / 2;
    int py = ((int)g_h - ph) / 2;
    fill_rect(px - 4, py - 4, pw + 8, ph + 8, rgb(5, 8, 16));
    fill_rect(px, py, pw, ph, rgb(14, 22, 38));
    draw_rect(px, py, pw, ph, rgb(39, 160, 220));
    fill_rect(px + 1, py + 1, pw - 2, (int)(28 * scale), rgb(18, 34, 52));
    draw_text(px + (int)(12 * scale), py + (int)(10 * scale), "CYX UYGULAMA", rgb(246, 247, 252));
    draw_text16_limited(px + (int)(140 * scale), py + (int)(10 * scale),
                        g_cyx_choose_name, rgb(156, 168, 192),
                        (uint32_t)((pw - (int)(150 * scale)) / (int)(6 * scale)));
    draw_text(px + (int)(12 * scale), py + (int)(44 * scale),
              "BU DOSYAYI NASIL ACMAK ISTERSINIZ?", rgb(184, 194, 214));
    int bw = (int)(150 * scale);
    int bh = (int)(36 * scale);
    int by = py + ph - (int)(48 * scale);
    int bx_run = px + (int)(20 * scale);
    int bx_edit = px + pw - bw - (int)(20 * scale);
    int hover_run = (g_mouse_x >= bx_run && g_mouse_x < bx_run + bw &&
                     g_mouse_y >= by && g_mouse_y < by + bh);
    int hover_edit = (g_mouse_x >= bx_edit && g_mouse_x < bx_edit + bw &&
                      g_mouse_y >= by && g_mouse_y < by + bh);
    uint32_t run_fill  = (hover_run  || g_cyx_choose_hover == 0) ? rgb(40, 130, 90) : rgb(20, 80, 60);
    uint32_t edit_fill = (hover_edit || g_cyx_choose_hover == 1) ? rgb(50, 110, 180) : rgb(30, 70, 130);
    fill_rect(bx_run, by, bw, bh, run_fill);
    draw_rect(bx_run, by, bw, bh, rgb(80, 200, 130));
    draw_text(bx_run + (int)(10 * scale), by + (int)(8 * scale),  "[C] CALISTIR", rgb(240, 248, 240));
    draw_text(bx_run + (int)(10 * scale), by + (int)(20 * scale), "Uygulama olarak ac",  rgb(180, 220, 200));
    fill_rect(bx_edit, by, bw, bh, edit_fill);
    draw_rect(bx_edit, by, bw, bh, rgb(120, 170, 240));
    draw_text(bx_edit + (int)(10 * scale), by + (int)(8 * scale),  "[D] DUZENLE", rgb(240, 248, 252));
    draw_text(bx_edit + (int)(10 * scale), by + (int)(20 * scale), "Kod editorunde ac",  rgb(190, 210, 240));
}

/* ---- CYX input handling ---- */

static void cyx_keyname_for(EFI_INPUT_KEY *k, char *out) {
    out[0] = 0;
    if (k->ScanCode == 1) { cyx_strcpy_n(out, "UP", 16); return; }
    if (k->ScanCode == 2) { cyx_strcpy_n(out, "DOWN", 16); return; }
    if (k->ScanCode == 3) { cyx_strcpy_n(out, "RIGHT", 16); return; }
    if (k->ScanCode == 4) { cyx_strcpy_n(out, "LEFT", 16); return; }
    if (k->ScanCode == 23) { cyx_strcpy_n(out, "ESC", 16); return; }
    if (k->UnicodeChar == ' ') { cyx_strcpy_n(out, "SPACE", 16); return; }
    if (k->UnicodeChar == '\r' || k->UnicodeChar == '\n') { cyx_strcpy_n(out, "ENTER", 16); return; }
    if (k->UnicodeChar >= 32 && k->UnicodeChar < 127) {
        char c = (char)(k->UnicodeChar & 0x7F);
        if (c >= 'a' && c <= 'z') c = (char)(c - 32);
        out[0] = c; out[1] = 0;
    }
}

static int cyx_chooser_handle_key(EFI_INPUT_KEY *k) {
    if (!g_cyx_choose_open) return 0;
    if (k->ScanCode == 23 || k->UnicodeChar == 27) {
        g_cyx_choose_open = 0; return 1;
    }
    if (k->UnicodeChar == 'c' || k->UnicodeChar == 'C' || k->UnicodeChar == '\r' || k->UnicodeChar == '\n') {
        g_cyx_choose_open = 0;
        cyx_start_run();
        return 1;
    }
    if (k->UnicodeChar == 'd' || k->UnicodeChar == 'D') {
        g_cyx_choose_open = 0;
        cyx_start_edit();
        return 1;
    }
    if (k->ScanCode == 4) { g_cyx_choose_hover = 0; return 1; }
    if (k->ScanCode == 3) { g_cyx_choose_hover = 1; return 1; }
    return 1;
}

static int cyx_chooser_handle_click(void) {
    if (!g_cyx_choose_open) return 0;
    uint32_t scale = ui_scale();
    int pw = (int)(360 * scale);
    int ph = (int)(150 * scale);
    int px = ((int)g_w - pw) / 2;
    int py = ((int)g_h - ph) / 2;
    int bw = (int)(150 * scale);
    int bh = (int)(36 * scale);
    int by = py + ph - (int)(48 * scale);
    int bx_run = px + (int)(20 * scale);
    int bx_edit = px + pw - bw - (int)(20 * scale);
    if (g_mouse_x >= bx_run && g_mouse_x < bx_run + bw &&
        g_mouse_y >= by && g_mouse_y < by + bh) {
        g_cyx_choose_open = 0; cyx_start_run(); return 1;
    }
    if (g_mouse_x >= bx_edit && g_mouse_x < bx_edit + bw &&
        g_mouse_y >= by && g_mouse_y < by + bh) {
        g_cyx_choose_open = 0; cyx_start_edit(); return 1;
    }
    if (g_mouse_x < px || g_mouse_x >= px + pw ||
        g_mouse_y < py || g_mouse_y >= py + ph) {
        g_cyx_choose_open = 0;
    }
    return 1;
}

static int cyx_app_handle_key(EFI_INPUT_KEY *k) {
    if (!g_cyx_running) return 0;
    if (k->ScanCode == 23 || k->UnicodeChar == 27) {
        g_cyx_running = 0;
        return 1;
    }
    /* If an error is set, ESC closes; any other key clears error and tries to continue */
    if (g_cyx_has_error) {
        if (k->UnicodeChar == 'e' || k->UnicodeChar == 'E') {
            /* Open editor on the failing source */
            g_cyx_running = 0;
            g_cyx_choose_vol = g_cyx_src_vol;
            c16_copy(g_cyx_choose_path, g_cyx_src_path, sizeof(g_cyx_choose_path) / sizeof(g_cyx_choose_path[0]));
            c16_copy(g_cyx_choose_name, g_cyx_src_name, sizeof(g_cyx_choose_name) / sizeof(g_cyx_choose_name[0]));
            cyx_start_edit();
            return 1;
        }
        return 1;
    }
    /* Focused input field gets typed characters */
    for (uint16_t i = 0; i < g_cyx_inp_count; i++) {
        if (!g_cyx_inps[i].focused) continue;
        cyx_inp_t *in = &g_cyx_inps[i];
        uint32_t len = cyx_strlen(in->text);
        if (k->UnicodeChar == '\b') {
            if (in->cursor > 0) {
                for (uint32_t j = in->cursor - 1; j < len; j++) in->text[j] = in->text[j + 1];
                in->cursor--;
            }
            return 1;
        }
        if (k->UnicodeChar >= 32 && k->UnicodeChar < 127 && len + 1 < sizeof(in->text)) {
            for (uint32_t j = len + 1; j > in->cursor; j--) in->text[j] = in->text[j - 1];
            in->text[in->cursor] = (char)(k->UnicodeChar & 0x7F);
            in->cursor++;
            return 1;
        }
        if (k->UnicodeChar == '\r' || k->UnicodeChar == '\n') {
            cyx_keyname_for(k, g_cyx_last_key);
            cyx_dispatch(CYX_EV_KEY, "ENTER");
            return 1;
        }
    }
    cyx_keyname_for(k, g_cyx_last_key);
    if (g_cyx_last_key[0]) cyx_dispatch(CYX_EV_KEY, g_cyx_last_key);
    return 1;
}

static int cyx_app_handle_click(void) {
    if (!g_cyx_running) return 0;
    /* Window drag from title bar */
    int cw = g_cyx_canvas_w, ch = g_cyx_canvas_h;
    int title_h = 22, margin = 7;
    int win_w = cw + margin * 2;
    int x = g_cyx_win_x, y = g_cyx_win_y;
    /* ESC button area in title bar */
    if (g_mouse_x >= x + win_w - 64 && g_mouse_x < x + win_w - 4 &&
        g_mouse_y >= y + 4 && g_mouse_y < y + title_h) {
        g_cyx_running = 0;
        return 1;
    }
    int ox = x + margin;
    int oy = y + title_h + 2;
    /* Inputs: focus on click */
    int focused_one = -1;
    for (uint16_t i = 0; i < g_cyx_inp_count; i++) {
        cyx_inp_t *in = &g_cyx_inps[i];
        int ix = ox + in->x, iy = oy + in->y, iw = in->w, ih = in->h;
        if (g_mouse_x >= ix && g_mouse_x < ix + iw &&
            g_mouse_y >= iy && g_mouse_y < iy + ih) {
            in->focused = 1; focused_one = i;
        }
    }
    if (focused_one >= 0) {
        for (uint16_t i = 0; i < g_cyx_inp_count; i++)
            if ((int)i != focused_one) g_cyx_inps[i].focused = 0;
        return 1;
    }
    /* Buttons */
    for (uint16_t i = 0; i < g_cyx_btn_count; i++) {
        cyx_btn_t *b = &g_cyx_btns[i];
        int bx = ox + b->x, by = oy + b->y, bw = b->w, bh = b->h;
        if (g_mouse_x >= bx && g_mouse_x < bx + bw &&
            g_mouse_y >= by && g_mouse_y < by + bh) {
            for (uint16_t j = 0; j < g_cyx_inp_count; j++) g_cyx_inps[j].focused = 0;
            cyx_strcpy_n(g_cyx_last_click_btn, b->id, sizeof(g_cyx_last_click_btn));
            cyx_dispatch(CYX_EV_CLICK, b->id);
            return 1;
        }
    }
    /* Click on canvas: blur inputs */
    if (g_mouse_x >= ox && g_mouse_x < ox + cw &&
        g_mouse_y >= oy && g_mouse_y < oy + ch) {
        for (uint16_t i = 0; i < g_cyx_inp_count; i++) g_cyx_inps[i].focused = 0;
        return 1;
    }
    return 1;
}

/* Per-frame: dispatch DRAG / MOVE / TICK */
static void cyx_per_frame(void) {
    if (!g_cyx_running || g_cyx_has_error) return;
    int left_now = (g_mouse_buttons & 1) ? 1 : 0;
    /* Track previous mouse position so paint-style apps can use LINE @prevx @prevy @x @y */
    if (g_cyx_mouse_in_canvas) {
        if (left_now) {
            /* If we just started dragging or weren't on canvas last frame, no prev */
            if (!g_cyx_left_was_down) g_cyx_have_prev = 0;
            cyx_dispatch(CYX_EV_DRAG, "");
            g_cyx_prev_mx = g_cyx_mx;
            g_cyx_prev_my = g_cyx_my;
            g_cyx_have_prev = 1;
        } else {
            cyx_dispatch(CYX_EV_MOVE, "");
            g_cyx_have_prev = 0;
        }
    } else {
        g_cyx_have_prev = 0;
    }
    g_cyx_left_was_down = (uint8_t)left_now;
    /* TICK every ~4 polled frames (~62/sec at 4ms stall) */
    if (g_loop_ticks - g_cyx_last_tick_at >= 4) {
        g_cyx_last_tick_at = g_loop_ticks;
        g_cyx_tick++;
        cyx_dispatch(CYX_EV_TICK, "");
    }
}

static void render(void)
{
    draw_os_background();
    draw_top_bar();
    draw_sidebar();
    if (g_page != 5) draw_summary_cards();
    draw_detail_panel();
    fill_rect(side_w(), (int)g_h - (int)(26 * ui_scale()), (int)g_w - side_w(), (int)(26 * ui_scale()), rgb(12, 18, 31));
    draw_text(side_w() + (int)(18 * ui_scale()), (int)g_h - (int)(17 * ui_scale()), "1-6 SAYFA   UP/DOWN SEÇİM   R YENİLE   FARE/TOUCH TIKLAMA", rgb(154, 166, 190));
    draw_viewer_overlay();
    draw_transfer_overlay();
    draw_create_dialog();
    draw_rename_dialog();
    draw_confirm_dialog();
    draw_context_menu();
    draw_cyx_app_window();
    draw_cyx_chooser_dialog();
    if (g_last_error[0]) {
        fill_rect(side_w() + (int)(18 * ui_scale()), top_h() + (int)(4 * ui_scale()), (int)(360 * ui_scale()), (int)(20 * ui_scale()), rgb(34, 22, 34));
        draw_text(side_w() + (int)(26 * ui_scale()), top_h() + (int)(10 * ui_scale()), g_last_error, rgb(246, 247, 252));
    }
    draw_cursor();
    flush_frame();
    g_dirty = 0;
}

static void move_active_selection(int delta)
{
    explorer_window_t *win = &g_windows[g_active_window];
    uint32_t count = win->mode == EXPLORER_MODE_DISKS ? g_disk_count : (win->mode == EXPLORER_MODE_VOLUMES ? win->vol_count : win->entry_count);
    if (!win->visible || !count) {
        return;
    }
    if (delta < 0) {
        if (win->selected > 0) {
            win->selected--;
        }
    } else if (win->selected + 1 < count) {
        win->selected++;
    }
    uint32_t scale = ui_scale();
    int row_h = (int)(18 * scale);
    int rows = row_h ? (win->h - (int)(30 * scale) - (int)(18 * scale)) / row_h : 0;
    if (rows < 1) {
        rows = 1;
    }
    if (win->selected < win->scroll) {
        win->scroll = win->selected;
    } else if (win->selected >= win->scroll + (uint32_t)rows) {
        win->scroll = win->selected - (uint32_t)rows + 1;
    }
}

static void scroll_storage(int delta)
{
    if (delta < 0) {
        if (g_storage_scroll > 0) {
            g_storage_scroll--;
        }
    } else if (g_storage_scroll + 1 < g_block_count) {
        g_storage_scroll++;
    }
}

static void scroll_active_window(int delta)
{
    explorer_window_t *win = &g_windows[g_active_window];
    uint32_t count = win->mode == EXPLORER_MODE_DISKS ? g_disk_count : (win->mode == EXPLORER_MODE_VOLUMES ? win->vol_count : win->entry_count);
    if (!win->visible || !count) {
        return;
    }
    if (delta < 0) {
        if (win->scroll > 0) {
            win->scroll--;
        }
    } else if (win->scroll + 1 < count) {
        win->scroll++;
    }
}

static int terminal_key(EFI_INPUT_KEY *key)
{
    uint32_t len = ascii_len(g_terminal_input);
    if (key->ScanCode == 23 || key->UnicodeChar == 27) {
        g_active_surface = ACTIVE_EXPLORER;
        return 1;
    }
    if (key->UnicodeChar == '\r' || key->UnicodeChar == '\n') {
        terminal_execute();
        return 1;
    }
    if (key->UnicodeChar == '\b') {
        if (len) {
            g_terminal_input[len - 1] = 0;
        }
        return 1;
    }
    if (key->UnicodeChar >= 32 && key->UnicodeChar < 127 && len + 1 < sizeof(g_terminal_input)) {
        g_terminal_input[len] = (char)key->UnicodeChar;
        g_terminal_input[len + 1] = 0;
        return 1;
    }
    return 0;
}

static int poll_keyboard(void)
{
    int changed = 0;
    EFI_INPUT_KEY key;
    while (g_in && g_in->ReadKeyStroke(g_in, &key) == EFI_SUCCESS) {
        if (g_cyx_choose_open) {
            cyx_chooser_handle_key(&key);
            changed = 1;
            continue;
        }
        if (g_cyx_running) {
            cyx_app_handle_key(&key);
            changed = 1;
            continue;
        }
        if (g_viewer_open) {
            if (g_viewer_edit) {
                if (key.ScanCode == 23 || key.UnicodeChar == 27) {
                    /* ESC in edit mode: save and exit edit mode */
                    save_viewer_file();
                    g_viewer_edit = 0;
                } else if (key.UnicodeChar == '\b') {
                    /* Backspace: delete char before cursor */
                    if (g_viewer_cursor > 0) {
                        g_viewer_cursor--;
                        uint32_t len = 0;
                        while (g_viewer_text[len]) len++;
                        for (uint32_t ci = g_viewer_cursor; ci < len; ci++) {
                            g_viewer_text[ci] = g_viewer_text[ci + 1];
                        }
                    }
                } else if (key.UnicodeChar == '\r' || key.UnicodeChar == '\n') {
                    /* Insert newline at cursor */
                    uint32_t len = 0;
                    while (g_viewer_text[len]) len++;
                    if (len + 1 < sizeof(g_viewer_text) - 1) {
                        for (uint32_t ci = len + 1; ci > g_viewer_cursor; ci--) {
                            g_viewer_text[ci] = g_viewer_text[ci - 1];
                        }
                        g_viewer_text[g_viewer_cursor] = '\n';
                        g_viewer_cursor++;
                    }
                } else if (key.ScanCode == 3) {
                    /* Right arrow */
                    if (g_viewer_text[g_viewer_cursor]) g_viewer_cursor++;
                } else if (key.ScanCode == 4) {
                    /* Left arrow */
                    if (g_viewer_cursor > 0) g_viewer_cursor--;
                } else if (key.ScanCode == 1) {
                    /* Up arrow: move cursor up one line */
                    if (g_viewer_cursor > 0) {
                        /* find start of current line */
                        uint32_t cur = g_viewer_cursor;
                        while (cur > 0 && g_viewer_text[cur - 1] != '\n') cur--;
                        uint32_t col = g_viewer_cursor - cur;
                        /* find start of previous line */
                        if (cur > 0) {
                            cur--;
                            while (cur > 0 && g_viewer_text[cur - 1] != '\n') cur--;
                            uint32_t prev_len = 0;
                            while (g_viewer_text[cur + prev_len] && g_viewer_text[cur + prev_len] != '\n') prev_len++;
                            g_viewer_cursor = cur + (col < prev_len ? col : prev_len);
                        }
                    }
                } else if (key.ScanCode == 2) {
                    /* Down arrow: move cursor down one line */
                    uint32_t cur = g_viewer_cursor;
                    while (cur > 0 && g_viewer_text[cur - 1] != '\n') cur--;
                    uint32_t col = g_viewer_cursor - cur;
                    /* skip to next line */
                    while (g_viewer_text[cur] && g_viewer_text[cur] != '\n') cur++;
                    if (g_viewer_text[cur] == '\n') {
                        cur++;
                        uint32_t next_len = 0;
                        while (g_viewer_text[cur + next_len] && g_viewer_text[cur + next_len] != '\n') next_len++;
                        g_viewer_cursor = cur + (col < next_len ? col : next_len);
                    }
                } else if (key.UnicodeChar >= 32 && key.UnicodeChar < 127) {
                    /* Printable ASCII: insert at cursor */
                    uint32_t len = 0;
                    while (g_viewer_text[len]) len++;
                    if (len + 1 < sizeof(g_viewer_text) - 1) {
                        for (uint32_t ci = len + 1; ci > g_viewer_cursor; ci--) {
                            g_viewer_text[ci] = g_viewer_text[ci - 1];
                        }
                        g_viewer_text[g_viewer_cursor] = (char)(key.UnicodeChar & 0x7F);
                        g_viewer_cursor++;
                    }
                }
            } else {
                if (key.ScanCode == 23 || key.UnicodeChar == 27) {
                    g_viewer_open = 0;
                    g_viewer_edit = 0;
                } else if (key.UnicodeChar == 'e' || key.UnicodeChar == 'E') {
                    g_viewer_edit = 1;
                } else if (key.ScanCode == 1) {
                    /* Up arrow: scroll up */
                    if (g_viewer_scroll > 0) g_viewer_scroll--;
                } else if (key.ScanCode == 2) {
                    /* Down arrow: scroll down (clamped in renderer) */
                    g_viewer_scroll++;
                } else if (key.ScanCode == 9) {
                    /* PageUp */
                    if (g_viewer_scroll > 10) g_viewer_scroll -= 10; else g_viewer_scroll = 0;
                } else if (key.ScanCode == 10) {
                    /* PageDown */
                    g_viewer_scroll += 10;
                }
            }
            changed = 1;
            continue;
        }
        /* Confirm dialog intercepts all keys */
        if (g_confirm_open) {
            if (key.ScanCode == 23 || key.UnicodeChar == 27 ||
                key.UnicodeChar == 'h' || key.UnicodeChar == 'H' ||
                key.UnicodeChar == 'n' || key.UnicodeChar == 'N') {
                /* HAYIR / ESC — cancel */
                g_confirm_open = 0;
            } else if (key.UnicodeChar == 'e' || key.UnicodeChar == 'E' ||
                       key.UnicodeChar == 'y' || key.UnicodeChar == 'Y' ||
                       key.UnicodeChar == '\r' || key.UnicodeChar == '\n') {
                /* EVET / Enter — execute */
                g_confirm_open = 0;
                execute_pending_confirm();
            }
            changed = 1;
            continue;
        }
        /* Create dialog intercepts all keys */
        if (g_create_open) {
            if (key.ScanCode == 23 || key.UnicodeChar == 27) {
                g_create_open = 0;
            } else if (key.UnicodeChar == '\r' || key.UnicodeChar == '\n') {
                commit_create_file();
            } else if (key.UnicodeChar == '\b') {
                uint32_t nlen = c16_len(g_create_name);
                if (nlen > 0) {
                    g_create_name[nlen - 1] = 0;
                }
            } else if (key.UnicodeChar >= 32 && key.UnicodeChar < 127) {
                uint32_t nlen = c16_len(g_create_name);
                if (nlen + 1 < sizeof(g_create_name) / sizeof(g_create_name[0])) {
                    g_create_name[nlen] = key.UnicodeChar;
                    g_create_name[nlen + 1] = 0;
                }
            }
            changed = 1;
            continue;
        }
        /* Rename dialog intercepts all keys */
        if (g_rename_open) {
            if (key.ScanCode == 23 || key.UnicodeChar == 27) {
                g_rename_open = 0;
            } else if (key.UnicodeChar == '\r' || key.UnicodeChar == '\n') {
                commit_rename();
            } else if (key.UnicodeChar == '\b') {
                uint32_t nlen = c16_len(g_rename_name);
                if (nlen > 0) { g_rename_name[nlen - 1] = 0; }
            } else if (key.UnicodeChar >= 32 && key.UnicodeChar < 127) {
                uint32_t nlen = c16_len(g_rename_name);
                if (nlen + 1 < sizeof(g_rename_name) / sizeof(g_rename_name[0])) {
                    g_rename_name[nlen] = key.UnicodeChar;
                    g_rename_name[nlen + 1] = 0;
                }
            }
            changed = 1;
            continue;
        }
        /* Context menu: ESC closes it */
        if (g_ctx_open) {
            if (key.ScanCode == 23 || key.UnicodeChar == 27) {
                g_ctx_open = 0;
                changed = 1;
            }
            continue;
        }
        if (g_page == 5 && g_terminal_visible && g_active_surface == ACTIVE_TERMINAL) {
            changed |= terminal_key(&key);
            continue;
        }
        if (key.UnicodeChar >= '1' && key.UnicodeChar <= '6') {
            uint32_t next = (uint32_t)(key.UnicodeChar - '1');
            if (g_page != next) {
                g_page = next;
                changed = 1;
            }
        } else if (g_page == 5 && key.UnicodeChar == '\t') {
            for (uint32_t i = 1; i <= MAX_EXPLORER_WINDOWS; i++) {
                uint32_t next = (g_active_window + i) % MAX_EXPLORER_WINDOWS;
                if (g_windows[next].visible) {
                    set_active_window(next);
                    break;
                }
            }
            changed = 1;
        } else if (g_page == 5 && (key.UnicodeChar == 'n' || key.UnicodeChar == 'N')) {
            open_new_explorer();
            changed = 1;
        } else if (g_page == 5 && (key.UnicodeChar == 't' || key.UnicodeChar == 'T')) {
            terminal_open();
            changed = 1;
        } else if (g_page == 5 && (key.UnicodeChar == 'v' || key.UnicodeChar == 'V')) {
            cycle_active_volume();
            changed = 1;
        } else if (g_page == 5 && (key.UnicodeChar == 'c' || key.UnicodeChar == 'C')) {
            copy_selected_to_other(0);
            changed = 1;
        } else if (g_page == 5 && (key.UnicodeChar == 'm' || key.UnicodeChar == 'M')) {
            copy_selected_to_other(1);
            changed = 1;
        } else if (g_page == 5 && (key.UnicodeChar == 'o' || key.UnicodeChar == 'O')) {
            open_create_dialog();
            changed = 1;
        } else if (g_page == 5 && (key.UnicodeChar == 'd' || key.UnicodeChar == 'D')) {
            open_create_folder_dialog();
            changed = 1;
        } else if (key.UnicodeChar == 'r' || key.UnicodeChar == 'R') {
            g_storage_refresh_needed = 1;
            g_fs_refresh_needed = 1;
            set_last_error("CIHAZLAR YENILENIYOR");
            changed = 1;
        } else if (g_page == 5 && key.ScanCode == 8) {
            delete_selected();
            changed = 1;
        } else if (g_page == 5 && key.ScanCode == 12) {
            /* F2 — rename selected */
            open_rename_from_active();
            changed = 1;
        } else if (g_page == 5 && (key.UnicodeChar == '\r' || key.UnicodeChar == '\n')) {
            open_selected_entry(&g_windows[g_active_window]);
            changed = 1;
        } else if (g_page == 5 && key.UnicodeChar == '\b') {
            go_parent_or_stage(&g_windows[g_active_window]);
            changed = 1;
        } else if (key.ScanCode == 1) {
            if (g_page == 5) {
                move_active_selection(-1);
            } else if (g_page == 3) {
                scroll_storage(-1);
            } else if (g_page > 0) {
                g_page--;
            }
            changed = 1;
        } else if (key.ScanCode == 2) {
            if (g_page == 5) {
                move_active_selection(1);
            } else if (g_page == 3) {
                scroll_storage(1);
            } else if (g_page < 5) {
                g_page++;
            }
            changed = 1;
        } else if (g_page == 5 && key.ScanCode == 3) {
            for (uint32_t i = 1; i <= MAX_EXPLORER_WINDOWS; i++) {
                uint32_t next = (g_active_window + MAX_EXPLORER_WINDOWS - i) % MAX_EXPLORER_WINDOWS;
                if (g_windows[next].visible) {
                    set_active_window(next);
                    break;
                }
            }
            changed = 1;
        } else if (g_page == 5 && key.ScanCode == 4) {
            for (uint32_t i = 1; i <= MAX_EXPLORER_WINDOWS; i++) {
                uint32_t next = (g_active_window + i) % MAX_EXPLORER_WINDOWS;
                if (g_windows[next].visible) {
                    set_active_window(next);
                    break;
                }
            }
            changed = 1;
        }
    }
    return changed;
}

static void clamp_pointer(void)
{
    if (g_mouse_fx < 0) {
        g_mouse_fx = 0;
    }
    if (g_mouse_fy < 0) {
        g_mouse_fy = 0;
    }
    int64_t max_x = ((int64_t)g_w - 1) << 16;
    int64_t max_y = ((int64_t)g_h - 1) << 16;
    if (g_mouse_fx > max_x) {
        g_mouse_fx = max_x;
    }
    if (g_mouse_fy > max_y) {
        g_mouse_fy = max_y;
    }
    g_mouse_x = (int)(g_mouse_fx >> 16);
    g_mouse_y = (int)(g_mouse_fy >> 16);
}

static int64_t relative_to_fp(int32_t delta, uint64_t resolution, uint32_t axis_pixels)
{
    if (delta == 0) {
        return 0;
    }
    if (resolution) {
        int64_t v = ((int64_t)delta * (int64_t)axis_pixels * 65536) / ((int64_t)resolution * 50);
        if (v == 0) {
            return delta > 0 ? 65536 : -65536;
        }
        return v;
    }
    return (int64_t)delta * 65536;
}

static void update_buttons(int buttons)
{
    int old = g_mouse_buttons;
    g_mouse_buttons = buttons;
    if ((buttons & 1) && !(old & 1)) {
        g_mouse_click = 1;
    }
    if ((buttons & 2) && !(old & 2)) {
        g_mouse_right_click = 1;
    }
}

static int poll_simple_pointers(void)
{
    int changed = 0;
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    g_simple_ptr_count = 0;
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&PointerGuid, 0, &count, &handles) != EFI_SUCCESS) {
        return 0;
    }
    for (UINTN i = 0; i < count && g_simple_ptr_count < MAX_SIMPLE_POINTERS; i++) {
        EFI_SIMPLE_POINTER_PROTOCOL *p = 0;
        EFI_STATUS st = g_bs->OpenProtocol(handles[i], (EFI_GUID *)&PointerGuid, (void **)&p, g_image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
        if (st != EFI_SUCCESS) {
            st = g_bs->HandleProtocol(handles[i], (EFI_GUID *)&PointerGuid, (void **)&p);
        }
        if (st != EFI_SUCCESS || !p) {
            continue;
        }
        g_simple_ptr_count++;
        EFI_SIMPLE_POINTER_STATE s;
        st = p->GetState(p, &s);
        if (st == EFI_NOT_READY) {
            continue;
        }
        if (st == EFI_DEVICE_ERROR) {
            set_last_error("FARE CIHAZI DEGISTI, GIRIS YENILENIYOR");
            changed = 1;
            continue;
        }
        uint64_t rx = p->Mode ? p->Mode->ResolutionX : 0;
        uint64_t ry = p->Mode ? p->Mode->ResolutionY : 0;
        if (s.RelativeMovementZ > 0) {
            g_wheel_delta++;
        } else if (s.RelativeMovementZ < 0) {
            g_wheel_delta--;
        }
        g_mouse_fx += relative_to_fp(s.RelativeMovementX, rx, g_w);
        g_mouse_fy += relative_to_fp(s.RelativeMovementY, ry, g_h);
        clamp_pointer();
        update_buttons((s.LeftButton ? 1 : 0) | (s.RightButton ? 2 : 0));
        changed = 1;
    }
    g_bs->FreePool(handles);
    return changed;
}

static int poll_absolute_pointers(void)
{
    int changed = 0;
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    g_abs_ptr_count = 0;
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&AbsolutePointerGuid, 0, &count, &handles) != EFI_SUCCESS) {
        return 0;
    }
    for (UINTN i = 0; i < count && g_abs_ptr_count < MAX_ABSOLUTE_POINTERS; i++) {
        EFI_ABSOLUTE_POINTER_PROTOCOL *p = 0;
        EFI_STATUS st = g_bs->OpenProtocol(handles[i], (EFI_GUID *)&AbsolutePointerGuid, (void **)&p, g_image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
        if (st != EFI_SUCCESS) {
            st = g_bs->HandleProtocol(handles[i], (EFI_GUID *)&AbsolutePointerGuid, (void **)&p);
        }
        if (st != EFI_SUCCESS || !p || !p->Mode) {
            continue;
        }
        g_abs_ptr_count++;
        EFI_ABSOLUTE_POINTER_STATE s;
        st = p->GetState(p, &s);
        if (st == EFI_NOT_READY) {
            continue;
        }
        if (st == EFI_DEVICE_ERROR) {
            set_last_error("DOKUNMATIK GIRIS DEGISTI, YENILENIYOR");
            changed = 1;
            continue;
        }
        EFI_ABSOLUTE_POINTER_MODE *m = p->Mode;
        if (m->AbsoluteMaxX != m->AbsoluteMinX) {
            uint64_t x = s.CurrentX < m->AbsoluteMinX ? m->AbsoluteMinX : s.CurrentX;
            if (x > m->AbsoluteMaxX) {
                x = m->AbsoluteMaxX;
            }
            g_mouse_fx = (int64_t)(((x - m->AbsoluteMinX) * (uint64_t)(g_w - 1) * 65536) / (m->AbsoluteMaxX - m->AbsoluteMinX));
        }
        if (m->AbsoluteMaxY != m->AbsoluteMinY) {
            uint64_t y = s.CurrentY < m->AbsoluteMinY ? m->AbsoluteMinY : s.CurrentY;
            if (y > m->AbsoluteMaxY) {
                y = m->AbsoluteMaxY;
            }
            g_mouse_fy = (int64_t)(((y - m->AbsoluteMinY) * (uint64_t)(g_h - 1) * 65536) / (m->AbsoluteMaxY - m->AbsoluteMinY));
        }
        clamp_pointer();
        update_buttons((s.ActiveButtons & (EFI_ABSP_TOUCH_ACTIVE | EFI_ABSP_ALT_ACTIVE)) ? 1 : 0);
        changed = 1;
    }
    g_bs->FreePool(handles);
    return changed;
}

static int poll_pointer(void)
{
    int changed = 0;
    changed |= poll_simple_pointers();
    changed |= poll_absolute_pointers();
    if (g_drag_kind && (g_mouse_buttons & 1)) {
        if (g_drag_kind == 1 && g_drag_index >= 0 && (uint32_t)g_drag_index < MAX_EXPLORER_WINDOWS) {
            explorer_window_t *win = &g_windows[g_drag_index];
            win->x = g_mouse_x - g_drag_dx;
            win->y = g_mouse_y - g_drag_dy;
            changed = 1;
        } else if (g_drag_kind == 2) {
            g_terminal_x = g_mouse_x - g_drag_dx;
            g_terminal_y = g_mouse_y - g_drag_dy;
            changed = 1;
        } else if (g_drag_kind == 3 && g_drag_index >= 0 && (uint32_t)g_drag_index < MAX_EXPLORER_WINDOWS) {
            explorer_window_t *win = &g_windows[g_drag_index];
            int min_w = (int)(140 * ui_scale());
            int min_h = (int)(90 * ui_scale());
            int mdx = g_mouse_x - g_drag_dx; /* mouse delta from drag start */
            int mdy = g_mouse_y - g_drag_dy;
            int nx = g_drag_ox, ny = g_drag_oy;
            int nw = g_drag_ow, nh = g_drag_oh;
            switch (g_resize_corner) {
                case 0: nx = g_drag_ox + mdx; ny = g_drag_oy + mdy; nw = g_drag_ow - mdx; nh = g_drag_oh - mdy; break;
                case 1: ny = g_drag_oy + mdy; nw = g_drag_ow + mdx; nh = g_drag_oh - mdy; break;
                case 2: nx = g_drag_ox + mdx; nw = g_drag_ow - mdx; nh = g_drag_oh + mdy; break;
                case 3: nw = g_drag_ow + mdx; nh = g_drag_oh + mdy; break;
                default: break;
            }
            if (nw < min_w) {
                if (g_resize_corner == 0 || g_resize_corner == 2) nx = g_drag_ox + g_drag_ow - min_w;
                nw = min_w;
            }
            if (nh < min_h) {
                if (g_resize_corner == 0 || g_resize_corner == 1) ny = g_drag_oy + g_drag_oh - min_h;
                nh = min_h;
            }
            win->x = nx; win->y = ny; win->w = nw; win->h = nh;
            changed = 1;
        }
    } else if (!(g_mouse_buttons & 1)) {
        g_drag_kind = 0;
        g_drag_index = -1;
    }
    return changed;
}

static int handle_wheel_scroll(void)
{
    if (!g_wheel_delta) {
        return 0;
    }
    int delta = g_wheel_delta;
    g_wheel_delta = 0;
    /* Viewer scroll wins when open */
    if (g_viewer_open) {
        int step = (delta > 0) ? 3 : -3;
        if (delta < 0) {
            if ((int)g_viewer_scroll + step < 0) g_viewer_scroll = 0;
            else g_viewer_scroll = (uint32_t)((int)g_viewer_scroll + step);
        } else {
            g_viewer_scroll += (uint32_t)step;
        }
        return 1;
    }
    if (g_page == 3) {
        scroll_storage(delta);
        return 1;
    }
    if (g_page == 5) {
        for (uint32_t i = 0; i < MAX_EXPLORER_WINDOWS; i++) {
            explorer_window_t *win = &g_windows[i];
            if (win->visible && g_mouse_x >= win->x && g_mouse_x < win->x + win->w &&
                g_mouse_y >= win->y && g_mouse_y < win->y + win->h) {
                set_active_window(i);
                scroll_active_window(delta);
                return 1;
            }
        }
    }
    return 0;
}

static int refresh_devices_if_needed(void)
{
    int changed = 0;
    g_loop_ticks++;
    if ((g_loop_ticks % 84U) == 0) {
        connect_all_controllers();
        changed = 1;
    }
    if (g_storage_refresh_needed || g_fs_refresh_needed) {
        load_external_fs_drivers();
        changed = 1;
    }
    if (g_storage_refresh_needed) {
        detect_storage(g_image);
        changed = 1;
    }
    if (g_fs_refresh_needed) {
        detect_file_systems(g_image, 0);
        changed = 1;
    }
    return changed;
}

static int handle_right_click(void)
{
    if (!g_mouse_right_click) return 0;
    g_mouse_right_click = 0;
    /* Close any open context menu first */
    if (g_ctx_open) { g_ctx_open = 0; return 1; }
    /* Only open context menu on page 5, file mode explorer */
    if (g_page != 5) return 0;
    uint32_t scale = ui_scale();
    for (int wi = MAX_EXPLORER_WINDOWS - 1; wi >= 0; wi--) {
        explorer_window_t *win = &g_windows[wi];
        if (!win->visible || win->mode != EXPLORER_MODE_FILES) continue;
        if (g_mouse_x >= win->x && g_mouse_x < win->x + win->w &&
            g_mouse_y >= win->y && g_mouse_y < win->y + win->h) {
            int row_h = (int)(18 * scale);
            int row_y = win->y + (int)(38 * scale);
            if (row_h && g_mouse_y >= row_y) {
                uint32_t idx = win->scroll + (uint32_t)((g_mouse_y - row_y) / row_h);
                if (idx < win->entry_count && !c16_is_dotdot(win->entries[idx].name)) {
                    /* Right-clicked on a file/folder entry */
                    set_active_window((uint32_t)wi);
                    win->selected = idx;
                    g_ctx_win   = (uint32_t)wi;
                    g_ctx_entry = idx;
                    g_ctx_x     = g_mouse_x;
                    g_ctx_y     = g_mouse_y;
                    g_ctx_hover = 0;
                    g_ctx_mode  = 0;
                    g_ctx_open  = 1;
                    return 1;
                }
            }
            /* Clicked on empty area inside window — background menu */
            if (win->volume < g_volume_count &&
                ((g_volumes[win->volume].firmware_fs && !g_volumes[win->volume].read_only) ||
                 ((g_volumes[win->volume].native_fs == NATIVE_FS_EXFAT ||
                   g_volumes[win->volume].native_fs == NATIVE_FS_NTFS) &&
                  g_volumes[win->volume].native_writable))) {
                set_active_window((uint32_t)wi);
                g_ctx_win   = (uint32_t)wi;
                g_ctx_x     = g_mouse_x;
                g_ctx_y     = g_mouse_y;
                g_ctx_hover = 0;
                g_ctx_mode  = 1;
                g_ctx_open  = 1;
            }
            return 1;
        }
    }
    return 0;
}

static int handle_click(void)
{
    if (!g_mouse_click) {
        return 0;
    }
    g_mouse_click = 0;
    if (g_cyx_choose_open) {
        cyx_chooser_handle_click();
        return 1;
    }
    if (g_cyx_running) {
        cyx_app_handle_click();
        return 1;
    }
    /* Context menu click handling */
    if (g_ctx_open) {
        uint32_t scale = ui_scale();
        int item_h = (int)(20 * scale);
        int menu_w = (int)(190 * scale);
        int item_count = (g_ctx_mode == 1) ? CTX_BG_ITEM_COUNT : CTX_ITEM_COUNT;
        int menu_h = item_count * item_h + (int)(4 * scale);
        int mx = g_ctx_x;
        int my = g_ctx_y;
        if (mx + menu_w > (int)g_w) mx = (int)g_w - menu_w - (int)(4 * scale);
        if (my + menu_h > (int)g_h) my = (int)g_h - menu_h - (int)(4 * scale);
        if (g_mouse_x >= mx && g_mouse_x < mx + menu_w &&
            g_mouse_y >= my && g_mouse_y < my + menu_h) {
            int rel = g_mouse_y - (my + (int)(2 * scale));
            if (rel >= 0) {
                int item = rel / item_h;
                if (item >= 0 && item < item_count) {
                    ctx_execute((uint32_t)item);
                    return 1;
                }
            }
        }
        g_ctx_open = 0;
        return 1;
    }
    if (g_viewer_open) {
        uint32_t scale = ui_scale();
        int vw = (int)g_w - (int)(130 * scale);
        int vh = (int)g_h - (int)(110 * scale);
        int vx = ((int)g_w - vw) / 2;
        int vy = ((int)g_h - vh) / 2;
        if (vw < (int)(260 * scale) || vh < (int)(160 * scale)) {
            vx = (int)(20 * scale);
            vy = (int)(20 * scale);
            vw = (int)g_w - (int)(40 * scale);
            vh = (int)g_h - (int)(40 * scale);
        }
        int inside = (g_mouse_x >= vx && g_mouse_x < vx + vw && g_mouse_y >= vy && g_mouse_y < vy + vh);
        if (inside) {
            /* Check DÜZENLE / KAYDET buttons in bottom bar */
            int by = vy + vh - (int)(20 * scale);
            int bx = vx + (int)(14 * scale);
            if (!g_viewer_edit) {
                /* DÜZENLE button area */
                if (g_mouse_x >= bx && g_mouse_x < bx + (int)(90 * scale) &&
                    g_mouse_y >= by - (int)(2 * scale) && g_mouse_y < by + (int)(14 * scale)) {
                    g_viewer_edit = 1;
                }
            } else {
                /* KAYDET button area */
                if (g_mouse_x >= bx && g_mouse_x < bx + (int)(120 * scale) &&
                    g_mouse_y >= by - (int)(2 * scale) && g_mouse_y < by + (int)(14 * scale)) {
                    save_viewer_file();
                    g_viewer_edit = 0;
                }
            }
        } else {
            /* Click outside viewer: only close if not in edit mode */
            if (!g_viewer_edit) {
                g_viewer_open = 0;
                g_viewer_edit = 0;
            }
        }
        return 1;
    }
    if (g_confirm_open) {
        uint32_t scale = ui_scale();
        int pw = (int)(340 * scale);
        int ph = (int)(112 * scale);
        int px = ((int)g_w - pw) / 2;
        int py = ((int)g_h - ph) / 2;
        int bw = (int)(118 * scale);
        int bh = (int)(24 * scale);
        int by = py + ph - (int)(34 * scale);
        int bx_evet  = px + (int)(12 * scale);
        int bx_hayir = px + pw - bw - (int)(12 * scale);
        if (g_mouse_x >= bx_evet && g_mouse_x < bx_evet + bw &&
            g_mouse_y >= by && g_mouse_y < by + bh) {
            g_confirm_open = 0;
            execute_pending_confirm();
            return 1;
        }
        if (g_mouse_x >= bx_hayir && g_mouse_x < bx_hayir + bw &&
            g_mouse_y >= by && g_mouse_y < by + bh) {
            g_confirm_open = 0;
            return 1;
        }
        /* Click outside dialog = cancel */
        if (g_mouse_x < px || g_mouse_x >= px + pw ||
            g_mouse_y < py || g_mouse_y >= py + ph) {
            g_confirm_open = 0;
        }
        return 1;
    }
    uint32_t scale = ui_scale();
    for (uint32_t i = 0; i < 6; i++) {
        int y = top_h() + (int)((58 + i * 42) * scale);
        if (g_mouse_x >= (int)(14 * scale) && g_mouse_x < side_w() - (int)(14 * scale) &&
            g_mouse_y >= y - (int)(10 * scale) && g_mouse_y < y + (int)(20 * scale)) {
            if (g_page != i) {
                g_page = i;
                return 1;
            }
            return 0;
        }
    }
    if (g_page == 5) {
        int panel_x = content_x();
        int panel_y = content_y();  /* page 5 panel now starts at content_y() */
        int toolbar_y = panel_y + (int)(22 * scale);
        if (g_mouse_y >= toolbar_y && g_mouse_y < toolbar_y + (int)(24 * scale)) {
            if (g_mouse_x >= panel_x + (int)(205 * scale) && g_mouse_x < panel_x + (int)(330 * scale)) {
                open_new_explorer();
                return 1;
            }
            if (g_mouse_x >= panel_x + (int)(345 * scale) && g_mouse_x < panel_x + (int)(455 * scale)) {
                terminal_open();
                return 1;
            }
        }
        if (g_terminal_visible && g_mouse_x >= g_terminal_x && g_mouse_x < g_terminal_x + g_terminal_w &&
            g_mouse_y >= g_terminal_y && g_mouse_y < g_terminal_y + g_terminal_h) {
            g_active_surface = ACTIVE_TERMINAL;
            if (g_mouse_y < g_terminal_y + (int)(28 * scale)) {
                if (g_mouse_x > g_terminal_x + g_terminal_w - (int)(28 * scale)) {
                    g_terminal_visible = 0;
                    g_active_surface = ACTIVE_EXPLORER;
                } else {
                    g_drag_kind = 2;
                    g_drag_index = -1;
                    g_drag_dx = g_mouse_x - g_terminal_x;
                    g_drag_dy = g_mouse_y - g_terminal_y;
                }
            }
            return 1;
        }
        for (int wi = MAX_EXPLORER_WINDOWS - 1; wi >= 0; wi--) {
            explorer_window_t *win = &g_windows[wi];
            if (!win->visible) {
                continue;
            }
            if (g_mouse_x >= win->x && g_mouse_x < win->x + win->w &&
                g_mouse_y >= win->y && g_mouse_y < win->y + win->h) {
                set_active_window((uint32_t)wi);
                /* Corner resize grab — check before title-bar drag */
                {
                    int cz = (int)(14 * scale);
                    int corner = -1;
                    if (g_mouse_x < win->x + cz && g_mouse_y < win->y + cz)              corner = 0; /* TL */
                    else if (g_mouse_x >= win->x + win->w - cz && g_mouse_y < win->y + cz) corner = 1; /* TR */
                    else if (g_mouse_x < win->x + cz && g_mouse_y >= win->y + win->h - cz) corner = 2; /* BL */
                    else if (g_mouse_x >= win->x + win->w - cz && g_mouse_y >= win->y + win->h - cz) corner = 3; /* BR */
                    if (corner >= 0) {
                        g_drag_kind      = 3;
                        g_drag_index     = wi;
                        g_drag_dx        = g_mouse_x;    /* initial mouse x */
                        g_drag_dy        = g_mouse_y;    /* initial mouse y */
                        g_drag_ox        = win->x;
                        g_drag_oy        = win->y;
                        g_drag_ow        = win->w;
                        g_drag_oh        = win->h;
                        g_resize_corner  = corner;
                        return 1;
                    }
                }
                if (g_mouse_y < win->y + (int)(30 * scale)) {
                    if (g_mouse_x > win->x + win->w - (int)(28 * scale)) {
                        win->visible = 0;
                        for (uint32_t i = 0; i < MAX_EXPLORER_WINDOWS; i++) {
                            if (g_windows[i].visible) {
                                set_active_window(i);
                                break;
                            }
                        }
                    } else {
                        g_drag_kind = 1;
                        g_drag_index = wi;
                        g_drag_dx = g_mouse_x - win->x;
                        g_drag_dy = g_mouse_y - win->y;
                    }
                    return 1;
                }
                int row_h = (int)(18 * scale);
                int row_y = win->y + (int)(38 * scale);
                uint32_t count = win->mode == EXPLORER_MODE_DISKS ? g_disk_count : (win->mode == EXPLORER_MODE_VOLUMES ? win->vol_count : win->entry_count);
                if (row_h && g_mouse_y >= row_y) {
                    uint32_t idx = win->scroll + (uint32_t)((g_mouse_y - row_y) / row_h);
                    if (idx < count) {
                        if (win->selected == idx && g_last_click_window == (uint32_t)wi && g_last_click_entry == idx) {
                            open_selected_entry(win);
                            g_last_click_window = 0xFFFFFFFFU;
                            g_last_click_entry = 0xFFFFFFFFU;
                        } else {
                            win->selected = idx;
                            g_last_click_window = (uint32_t)wi;
                            g_last_click_entry = idx;
                        }
                    }
                }
                return 1;
            }
        }
    }
    return 1;
}

static void detect_simple_pointers(EFI_HANDLE image)
{
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    g_simple_ptr_count = 0;
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&PointerGuid, 0, &count, &handles) != EFI_SUCCESS) {
        return;
    }
    for (UINTN i = 0; i < count; i++) {
        EFI_SIMPLE_POINTER_PROTOCOL *ptr = 0;
        EFI_STATUS st = g_bs->OpenProtocol(handles[i], (EFI_GUID *)&PointerGuid, (void **)&ptr, image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
        if (st != EFI_SUCCESS) {
            st = g_bs->HandleProtocol(handles[i], (EFI_GUID *)&PointerGuid, (void **)&ptr);
        }
        if (st == EFI_SUCCESS && ptr) {
            ptr->Reset(ptr, 0);
            g_simple_ptr_count++;
        }
    }
    g_bs->FreePool(handles);
}

static void detect_absolute_pointers(EFI_HANDLE image)
{
    EFI_HANDLE *handles = 0;
    UINTN count = 0;
    g_abs_ptr_count = 0;
    if (g_bs->LocateHandleBuffer(BY_PROTOCOL, (EFI_GUID *)&AbsolutePointerGuid, 0, &count, &handles) != EFI_SUCCESS) {
        return;
    }
    for (UINTN i = 0; i < count; i++) {
        EFI_ABSOLUTE_POINTER_PROTOCOL *ptr = 0;
        EFI_STATUS st = g_bs->OpenProtocol(handles[i], (EFI_GUID *)&AbsolutePointerGuid, (void **)&ptr, image, 0, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
        if (st != EFI_SUCCESS) {
            st = g_bs->HandleProtocol(handles[i], (EFI_GUID *)&AbsolutePointerGuid, (void **)&ptr);
        }
        if (st == EFI_SUCCESS && ptr) {
            ptr->Reset(ptr, 0);
            g_abs_ptr_count++;
        }
    }
    g_bs->FreePool(handles);
}

static void copy_firmware_name(void)
{
    uint32_t i = 0;
    if (!g_st->FirmwareVendor) {
        g_firmware[0] = 0;
        return;
    }
    while (g_st->FirmwareVendor[i] && i + 1 < sizeof(g_firmware) / sizeof(g_firmware[0])) {
        g_firmware[i] = g_st->FirmwareVendor[i];
        i++;
    }
    g_firmware[i] = 0;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    g_st = SystemTable;
    g_bs = SystemTable->BootServices;
    g_image = ImageHandle;
    g_in = SystemTable->ConIn;
    if (g_bs->SetWatchdogTimer) {
        g_bs->SetWatchdogTimer(0, 0, 0, 0);
    }

    copy_firmware_name();
    connect_all_controllers();
    load_external_fs_drivers();
    detect_cpu();
    detect_memory();
    detect_storage(ImageHandle);
    detect_file_systems(ImageHandle, 1);

    if (g_bs->LocateProtocol((EFI_GUID *)&GopGuid, 0, (void **)&g_gop) != EFI_SUCCESS || !g_gop || !g_gop->Mode) {
        CHAR16 msg[] = L"CaYa UEFI booted, but GOP framebuffer was not found.\r\n";
        if (SystemTable->ConOut && SystemTable->ConOut->OutputString) {
            SystemTable->ConOut->OutputString(SystemTable->ConOut, msg);
        }
        for (;;) {
        }
    }

    g_w = g_gop->Mode->Info->HorizontalResolution;
    g_h = g_gop->Mode->Info->VerticalResolution;
    g_stride = g_gop->Mode->Info->PixelsPerScanLine;
    g_pixel_format = g_gop->Mode->Info->PixelFormat;
    g_red_mask = g_gop->Mode->Info->PixelInformation[0];
    g_green_mask = g_gop->Mode->Info->PixelInformation[1];
    g_blue_mask = g_gop->Mode->Info->PixelInformation[2];
    g_fb = (uint32_t *)(uintptr_t)g_gop->Mode->FrameBufferBase;
    if (g_bs->AllocatePool(EfiLoaderData, (UINTN)g_w * (UINTN)g_h * 4, (void **)&g_backbuffer) != EFI_SUCCESS || !g_backbuffer) {
        CHAR16 msg[] = L"CaYa UEFI booted, but framebuffer backbuffer allocation failed.\r\n";
        if (SystemTable->ConOut && SystemTable->ConOut->OutputString) {
            SystemTable->ConOut->OutputString(SystemTable->ConOut, msg);
        }
        for (;;) {
        }
    }
    if (!g_w || !g_h || g_stride < g_w) {
        crash_screen("GOP FRAMEBUFFER BILGISI GECERSIZ", 1001);
    }
    g_mouse_x = (int)(g_w / 2);
    g_mouse_y = (int)(g_h / 2);
    g_mouse_fx = (int64_t)g_mouse_x << 16;
    g_mouse_fy = (int64_t)g_mouse_y << 16;
    detect_simple_pointers(ImageHandle);
    detect_absolute_pointers(ImageHandle);
    detect_hw_extended();
    detect_gpu();

    for (;;) {
        int changed = 0;
        changed |= refresh_devices_if_needed();
        changed |= poll_keyboard();
        changed |= poll_pointer();
        changed |= handle_wheel_scroll();
        changed |= handle_click();
        changed |= handle_right_click();
        if (g_cyx_running && !g_cyx_has_error) {
            cyx_per_frame();
            changed = 1;  /* keep frame fresh for animations */
        }
        if (changed || g_dirty) {
            render();
        }
        g_bs->Stall(4000);
    }
}
