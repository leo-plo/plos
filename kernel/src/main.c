#include <drivers/console.h>
#include <flanterm.h>
#include <memory/kheap.h>
#include <memory/paging.h>
#include <memory/vmm.h>
#include <stdbool.h>
#include <limine.h>
#include <cpu.h>
#include <drivers/acpi.h>
#include <memory/gdt/gdt.h>
#include <interrupts/idt.h>
#include <drivers/serial.h>
#include <memory/pmm.h>
#include <libk/string.h>
#include <common/logging.h>
#include <limine_requests.h>
#include <memory/hhdm.h>

// This is our kernel's entry point.
void kmain(void) {

    limine_verify_requests();
    
    gdt_init();
    idt_init();

    pmm_printUsableRegions();
    pmm_init();
    pmm_dump_state();
    paging_init();
    kheap_init();
    vmm_init();

    console_init();

    if(!acpi_set_correct_RSDT())
    {
        log_line(LOG_ERROR, "Error, cannot initialize RSDT");
        hcf();
    }

    // We're done, just hang...
    hcf();
}
