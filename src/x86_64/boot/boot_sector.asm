[org 0x7c00]

section .text
    global _start

_start:
    call clear_screen

    mov bx, BOOT_LABEL
    call print_string

    mov [BOOT_DRIVE], dl

    mov bp, 0x8000
    mov sp, bp

    mov bx, 0x9000
    mov dh, 5
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov bx, [0x9000]
    call print_hex

    mov bx, [0x9000 + 512]
    call print_hex

    jmp $


; Global variables
BOOT_LABEL: db 'Booting AttemptOS...', 0
BOOT_DRIVE: db 0


; Common procedures and routine imports
%include "x86_64/boot/disk_logic.asm"
%include "x86_64/common/print_string.asm"
%include "x86_64/common/print_hex.asm"
%include "x86_64/common/screen_utilities.asm"
    

; Boot sector padding and magic BIOS number
times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface