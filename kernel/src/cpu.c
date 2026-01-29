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

void cpu_cpuid(uint32_t leaf, uint32_t subleaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) 
{
    uint32_t rax, rbx, rcx, rdx;

    __asm__ volatile (
    "cpuid"
    : "=a"(rax), "=b"(rbx), "=c"(rcx), "=d"(rdx)
    : "a"(leaf), "c"(subleaf)
    : "memory"
    );

    if (eax) *eax = rax;
    if (ebx) *ebx = rbx;
    if (ecx) *ecx = rcx;
    if (edx) *edx = rdx;
}