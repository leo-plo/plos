#include <stdint.h>
#include "idt.h"
#include "../gdt/gdt.h"

// Aligned for performance
__attribute__((aligned(0x10))) 
struct idt_descriptor idt[IDT_NUM_ENTRIES];

void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags)
{
    struct idt_descriptor *currentDescriptor = &idt[vector];
    
    currentDescriptor->offset_1 = (uintptr_t)isr & 0xffff;
    currentDescriptor->segment_selector = GDT_KERNEL_CS * sizeof(uintptr_t);
    currentDescriptor->ist = 0;
    currentDescriptor->flags = flags;
    currentDescriptor->offset_2 = ((uintptr_t)isr >> 16) & 0xffff;
    currentDescriptor->offset_3 = (uintptr_t)isr >> 32;
}

void idt_initialize_idtTable(void)
{
    struct idtr idtr;
    idtr.offset = (uintptr_t)idt;
    idtr.size = sizeof(idt) - 1;
    
    idt_load(&idtr);
}