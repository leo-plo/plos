#include <interrupts/isr.h>
#include <memory/vmm.h>
#include <common/logging.h>
#include <cpu.h>

void vmm_page_fault_handler(struct isr_context *context)
{
    uint64_t cr2;
    asm volatile("mov %%cr2, %0" : "=r"(cr2));
    uint64_t rip = context->rip;

    log_log_line(LOG_ERROR, "PAGE FAULT! CR2 (Addr): 0x%llx | RIP (Code): 0x%llx | Error: 0x%x", cr2, rip, context->error_code);

    hcf();
}