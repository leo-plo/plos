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