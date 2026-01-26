#include "isr.h"
#include <hal/cpu.h>
#include <hal/devices.h>

void interrupt_handler(struct isr_context *context)
{
    switch (context->vector_number) {
        case 0:
            log_to_serial("[DEBUG] Divide by 0 interrupt\n");
            hal_hcf();
            break;
        default:
            log_to_serial("[DEBUG] Interrupt fired\n");
            break;
    }
}