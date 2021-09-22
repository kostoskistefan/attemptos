#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256
#define KERNEL_CODE_SEGMENT 0x08

typedef struct
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t  _always_0;
    uint8_t  flags;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

void set_idt();
void set_idt_gate(uint8_t index, uint32_t irq_address);

extern void idt_load();

#endif
