#include "utilities.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/screen/screen.h"

int main()
{
    isr_install();

    clear_screen();

    asm volatile ("sti");
    init_timer(50);
}
