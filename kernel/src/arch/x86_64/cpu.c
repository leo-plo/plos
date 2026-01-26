#include <hal/cpu.h>
#include "gdt/gdt.h"

__attribute__((noreturn)) void hal_hcf(void)
{
    for(;;)
    {
        asm("hlt");
    }
}

void hal_initialize_cpu(void)
{
    gdt_initialize_gdtTable();
}