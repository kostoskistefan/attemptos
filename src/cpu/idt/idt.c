#include "idt.h"

idt_register_t idt_register;
idt_entry_t    idt_entries[IDT_ENTRIES];

void set_idt()
{
    idt_register.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_register.base = (uint32_t) &idt_entries;

    asm volatile("lidt %0" : : "m" (idt_register));
    asm volatile("sti");
}

void set_idt_gate(uint8_t index, uint32_t irq_address)
{
    idt_entries[index].offset_low = irq_address & 0x0000ffff;
    idt_entries[index].segment_selector = KERNEL_CODE_SEGMENT;
    idt_entries[index]._always_0 = 0;
    idt_entries[index].flags = 0x8e;
    idt_entries[index].offset_high = (irq_address & 0xffff0000) >> 16;
}
