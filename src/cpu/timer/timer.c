#include "timer.h"
#include "../isr/isr.h"
#include "../ports/ports.h"
#include "../../drivers/screen/screen.h"
#include "../../libraries/function.h"

uint32_t tick = 0;

static void timer_callback(registers_t *reg)
{
    UNUSED(reg);
    tick++;
}

void init_timer(uint32_t frequency)
{
    register_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = 1193180 / frequency;

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, divisor & 0xff);
    port_byte_out(0x40, divisor >> 8);
}
