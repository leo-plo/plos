#ifndef HHDM_H
#define HHDM_H

#include <stdint.h>
#include <limine.h>

void* hhdm_physToVirt(void *physical_addr);
void* hhdm_virtToPhys(void *virtual_addr);
void printMemmap(struct limine_memmap_response *memmap);

#endif // HHDM_H