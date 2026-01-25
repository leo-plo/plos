#include <hal/cpu.h>

__attribute__((noreturn)) void hal_hcf(void)
{
    for(;;)
    {
        asm("wfi");
    }
}