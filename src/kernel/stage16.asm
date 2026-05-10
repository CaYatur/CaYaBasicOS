%ifndef STAGE16_BASE
%define STAGE16_BASE 0x10000
%endif

%ifndef KERNEL32_ADDR
%define KERNEL32_ADDR 0x11000
%endif

[bits 16]
org 0

stage16_start:
    cli
    mov [cs:boot_drive8], dl

    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0xFFFE
    sti

    call collect_boot_info

    mov ax, 0x0013
    int 0x10

    cli
    call enable_a20
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp dword 0x08:(STAGE16_BASE + protected_start)

collect_boot_info:
    int 0x12
    mov [boot_info + 0], ax

    mov ax, 0xE801
    int 0x15
    jc .skip_e801
    mov [boot_info + 2], ax
    mov [boot_info + 4], bx
.skip_e801:
    ret

enable_a20:
    in al, 0x92
    or al, 0x02
    out 0x92, al
    ret

[bits 32]
protected_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    movzx eax, byte [STAGE16_BASE + boot_drive8]
    mov ebx, STAGE16_BASE + boot_info
    jmp dword 0x08:KERNEL32_ADDR

align 8
gdt_start:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd STAGE16_BASE + gdt_start

boot_drive8 db 0
align 4
boot_info:
    dw 0
    dw 0
    dw 0
    times 58 db 0
