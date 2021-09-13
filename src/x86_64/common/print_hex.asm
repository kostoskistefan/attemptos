HEX_OUT:
    db '0x0000', 0

print_hex:
    pusha
    mov si, HEX_OUT + 2
    mov cx, 0

next_character:
    inc cx

    mov bx, dx
    and bx, 0xf000
    shr bx, 4

    add bh, 0x30

    cmp bh, 0x39
    jg add_39

add_character_hex:
    mov [si], bh

    inc si

    shl dx, 4

    cmp cx, 4
    jnz next_character

    jmp _done_hex

add_39:
    add bh, 0x27
    jmp add_character_hex

_done_hex:
    mov bx, HEX_OUT
    call print_string
    
    popa
    ret
