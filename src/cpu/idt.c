#include "idt.h"

idt_register_t idt_register;
idt_entry_t    idt_entries[IDT_ENTRIES];

void set_idt()
{
    idt_register.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_register.base = (uint32) &idt_entries;

    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_register));
}

void set_idt_gate(uint8 index, uint32 irq_address)
{
    idt_entries[index].offset_low = irq_address & 0xffff;
    idt_entries[index].segment_selector = KERNEL_CODE_SEGMENT;
    idt_entries[index]._always_0 = 0;
    idt_entries[index].flags = 0x8e;
    idt_entries[index].offset_high = (irq_address >> 16) & 0xffff;
}
