print_string:
    pusha

start:
    mov al, [bx]

    cmp al, 0
    je _done_string
    
    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp start

_done_string:
    mov al, 0x0d
    int 0x10

    mov al, 0x0a
    int 0x10

    popa
    ret
