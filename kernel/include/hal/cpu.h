#ifndef CPU_H
#define CPU_H

// Halt and catch fire function.
__attribute__((noreturn)) void hal_hcf(void);
void hal_initialize_cpu(void);

#endif // CPU_H