[extern isr_handler]
[extern irq_handler]

isr_common_stub:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8
    sti
    iret

irq_common_stub:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop ebx
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8
    sti
    iret

%macro ISR_NOERRCODE 1
[global isr%1]
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
[global isr%1]
isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

%macro IRQ 2
[global irq%1]
irq%1:
	cli
	push byte %1
	push byte %2
	jmp irq_common_stub
%endmacro

%assign i 0
%rep    33
    %if i >= 15
        ISR_NOERRCODE i
    %elif i >= 10
        ISR_ERRCODE i
    %elif i == 8
        ISR_ERRCODE i
    %else
        ISR_NOERRCODE i
    %endif
%assign i i+1 
%endrep

%assign i 0 
%rep    16 
   IRQ i, i+32 
%assign i i+1 
%endrep
