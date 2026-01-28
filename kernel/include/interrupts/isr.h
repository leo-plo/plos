#ifndef ISR_H
#define ISR_H

#include <stdint.h>

struct isr_context
{
    uint64_t general_purpose_registers[16];

    uint64_t vector_number;
    uint64_t error_code;

    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((packed));

void interrupt_handler(struct isr_context *context);

#endif // ISR_H