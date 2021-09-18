#ifndef IDT_H
#define IDT_H

#include "../types.h"

#define IDT_ENTRIES 256
#define KERNEL_CODE_SEGMENT 0x08

typedef struct
{
    uint16 offset_low;
    uint16 segment_selector;
    uint8  _always_0;
    uint8  flags;
    uint16 offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct
{
    uint16 limit;
    uint32 base;
} __attribute__((packed)) idt_register_t;

void set_idt();
void set_idt_gate(uint8 index, uint32 irq_address);

extern void idt_load();

#endif
