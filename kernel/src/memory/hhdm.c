#include <common/logging.h>
#include <memory/hhdm.h>
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

extern struct limine_hhdm_request hhdm_request;

void* hhdm_physToVirt(void *physical_addr)
{
    return (void *)((uint64_t )physical_addr + hhdm_request.response->offset);
}

void* hhdm_virtToPhys(void *virtual_addr)
{
    return (void *)((uint64_t )virtual_addr - hhdm_request.response->offset);
}

void printMemmap(struct limine_memmap_response *memmap)
{
    log_logLine(LOG_DEBUG, "%s: Printing system memory map: ", __FUNCTION__);
    for(size_t i = 0; i < memmap->entry_count; i++)
    {
        struct limine_memmap_entry *entry = memmap->entries[i];
        if(entry->type == LIMINE_MEMMAP_USABLE)
        {
            log_logLine(LOG_DEBUG, "%d) Usable region; Phys range: 0x%llx - 0x%llx; Length: %llu bytes", i+1, entry->base, entry->base + entry->length, entry->length);
        }
    }
}