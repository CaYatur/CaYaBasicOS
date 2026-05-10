%ifndef KERNEL_SECTORS
%define KERNEL_SECTORS 128
%endif

[bits 16]
org 0x7C00

    jmp short start
    nop

; Minimal FAT-like BPB so the El Torito floppy image is conventional.
    db 'CAYAOS  '
    dw 512
    db 1
    dw 1
    db 2
    dw 224
    dw 2880
    db 0xF0
    dw 9
    dw 18
    dw 2
    dd 0
    dd 0
    db 0
    db 0
    db 0x29
    dd 0x20260503
    db 'CAYABASICOS'
    db 'RAWBOOT '

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov [boot_drive], dl
    mov si, msg_loading
    call print

    xor ah, ah
    mov dl, [boot_drive]
    int 0x13

    mov ax, 0x1000
    mov es, ax
    xor bx, bx
    mov word [lba], 1
    mov cx, KERNEL_SECTORS

load_loop:
    push cx
    mov ax, [lba]
    call lba_to_chs

.retry:
    mov ah, 0x02
    mov al, 0x01
    mov dl, [boot_drive]
    int 0x13
    jnc .loaded

    xor ah, ah
    mov dl, [boot_drive]
    int 0x13
    jmp .retry

.loaded:
    add bx, 512
    jnc .same_segment
    mov ax, es
    add ax, 0x1000
    mov es, ax
.same_segment:
    inc word [lba]
    pop cx
    loop load_loop

    mov dl, [boot_drive]
    jmp 0x1000:0x0000

; Convert 1.44 MB floppy LBA to CHS.
; In: AX = LBA. Out: CH, CL, DH.
lba_to_chs:
    xor dx, dx
    mov bx, 18
    div bx
    mov cl, dl
    inc cl

    xor dx, dx
    mov bx, 2
    div bx
    mov ch, al
    mov dh, dl
    and ah, 0x03
    shl ah, 6
    or cl, ah
    ret

print:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0
    mov bl, 0x07
    int 0x10
    jmp print
.done:
    ret

boot_drive db 0
lba dw 0
msg_loading db 'CaYaBasicOS loading...', 13, 10, 0

times 510 - ($ - $$) db 0
dw 0xAA55
