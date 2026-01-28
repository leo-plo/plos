#ifndef CPU_H
#define CPU_H

#include <stdint.h>

// Halt and catch fire function.
__attribute__((noreturn)) void hcf(void);
void cpu_getMSR(uint32_t msr, uint32_t *lo, uint32_t *hi);
void cpu_setMSR(uint32_t msr, uint32_t lo, uint32_t hi);

#endif // CPU_H