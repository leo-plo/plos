#include <common/logging.h>
#include <memory/vmm.h>
#include <interrupts/isr.h>
#include <cpu.h>

// Main interrupt handler, each interrupt arrives here
void interrupt_handler(struct isr_context *context)
{
    log_log_line(LOG_DEBUG, "Interrupt fired: 0x%llx error code: 0x%llx", context->vector_number, context->error_code);
    switch(context->vector_number)
    {
        // Page fault
        case 14:
            vmm_page_fault_handler(context);
        break;
    }
}