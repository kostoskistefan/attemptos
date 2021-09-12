[org 0x7c00]

section .text
    global _start

_start:
    mov bx, label
    call print_string

    mov dx, 0x1234
    call print_hex

    jmp $

    label: db 'Booting AttemptOS...', 0

    %include "print_string.asm"
    %include "print_hex.asm"

    ; Padding and magic BIOS number
    times 510-($-$$) db 0
    dw 0xaa55
