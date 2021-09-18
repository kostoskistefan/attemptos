#include "../cpu/isr/isr.h"
#include "../drivers/screen/screen.h"

void main()
{
    clear_screen();
    isr_install();
    irq_install();
}
