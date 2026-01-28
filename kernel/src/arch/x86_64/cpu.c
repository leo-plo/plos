#include <hal/cpu.h>
#include <stdbool.h>
#include "gdt/gdt.h"
#include "idt/idt.h"

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
    idt_initialize_idtTable();
}

void cpu_getMSR(uint32_t msr, uint32_t *lo, uint32_t *hi)
{
   asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}

void cpu_setMSR(uint32_t msr, uint32_t lo, uint32_t hi)
{
   asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}