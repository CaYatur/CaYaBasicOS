[bits 32]

global _start
extern kmain
extern __bss_start
extern __bss_end

section .text

_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, stack_top

    ; Preserve stage16 arguments while clearing C .bss.
    mov edx, eax
    mov esi, ebx

    mov edi, __bss_start
    mov ecx, __bss_end
    sub ecx, edi
    xor eax, eax
    cld
    rep stosb

    ; stage16 passes boot drive in EAX and boot_info physical pointer in EBX.
    mov eax, edx
    mov ebx, esi
    push ebx
    push eax
    call kmain

.halt:
    hlt
    jmp .halt

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
