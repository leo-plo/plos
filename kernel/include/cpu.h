#ifndef CPU_H
#define CPU_H

#include <stdint.h>

// Halt and catch fire function.
__attribute__((noreturn)) void hcf(void);
void cpu_getMSR(uint32_t msr, uint32_t *lo, uint32_t *hi);
void cpu_setMSR(uint32_t msr, uint32_t lo, uint32_t hi);
void cpu_cpuid(uint32_t leaf, uint32_t subleaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

#endif // CPU_H