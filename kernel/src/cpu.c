#include <stdint.h>
#include <stdbool.h>
#include <cpu.h>
#include <memory/gdt/gdt.h>
#include <interrupts/idt.h>

__attribute__((noreturn)) void hcf(void)
{
    for(;;)
    {
        asm("hlt");
    }
}

void cpu_getMSR(uint32_t msr, uint32_t *lo, uint32_t *hi)
{
   asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}

void cpu_setMSR(uint32_t msr, uint32_t lo, uint32_t hi)
{
   asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}