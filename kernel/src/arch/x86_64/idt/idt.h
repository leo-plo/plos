#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_NUM_ENTRIES 256

#define IDT_GATE_INTERRUPT_TYPE 0b1110
#define IDT_GATE_TRAP_TYPE 0b1111

struct idt_descriptor
{
    uint16_t offset_1;
    uint16_t segment_selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t reserved;
} __attribute__((packed));

struct idtr
{
    uint16_t size;
    uintptr_t offset;
} __attribute__((packed));

extern void idt_load(struct idtr* idtr);
void idt_initialize_idtTable(void);

#endif // IDT_H