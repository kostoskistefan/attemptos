#include "timer.h"
#include "../isr/isr.h"
#include "../ports/ports.h"
#include "../../libraries/function.h"

uint32 tick = 0;

void timer_callback(registers_t reg)
{
    UNUSED(reg);
    tick++;
}

void init_timer(uint32 frequency)
{
    register_interrupt_handler(IRQ0, timer_callback);

    uint32 divisor = 1193180 / frequency;
    uint8 low = (uint8) (divisor & 0xff);
    uint8 high = (uint8) ((divisor >> 8) & 0xff);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
