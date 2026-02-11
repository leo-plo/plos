#ifndef VMM_H
#define VMM_H

#include <interrupts/isr.h>

void vmm_page_fault_handler(struct isr_context *context);

#endif // VMM_H