#include "../cpu/isr/isr.h"
#include "../drivers/screen/screen.h"

void kernel_main()
{
    clear_screen();
    isr_install();
    irq_install();
    printf("%s %d\n", "Test", 123);
}