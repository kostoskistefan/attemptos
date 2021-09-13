[org 0x7c00]

section .text
    global _start

_start:
    call clear_screen

    mov bx, label
    call print_string

    mov dx, 0x1a3f
    call print_hex

    jmp $

    label: db 'Booting AttemptOS...', 0

    %include "x86_64/common/print_string.asm"
    %include "x86_64/common/print_hex.asm"
    %include "x86_64/common/screen_utilities.asm"

    ; Padding and magic BIOS number
    times 510-($-$$) db 0
    dw 0xaa55
