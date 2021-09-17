#include "timer.h"
#include "isr.h"
#include "../kernel/utilities.h"
#include "../drivers/screen/screen.h"
#include "../drivers/ports/ports.h"

uint32 tick = 0;

void timer_callback(registers_t reg)
{
    tick++;

    print("Tick: ");

    char tick_ascii[256];
    int_to_string(tick, tick_ascii);

    print(tick_ascii);
    print("\n");
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
