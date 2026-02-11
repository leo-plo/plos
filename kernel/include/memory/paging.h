#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stdbool.h>
#include <interrupts/isr.h>

#define PAGING_PAGE_SIZE       4096
#define PAGING_HUGE_PAGE_SIZE  0x200000

// Flags for Page tables and directories
#define PTE_FLAG_NO_EXEC    (1ull << 63)
#define PTE_FLAG_GLOBAL     (1ull << 8)
#define PTE_FLAG_PS         (1ull << 7)
#define PTE_FLAG_PAT        (1ull << 7)
#define PTE_FLAG_DIRTY      (1ull << 6)
#define PTE_FLAG_ACCESSED   (1ull << 5)
#define PTE_FLAG_PCD        (1ull << 4)
#define PTE_FLAG_PWT        (1ull << 3)
#define PTE_FLAG_US         (1ull << 2)
#define PTE_FLAG_RW         (1ull << 1)
#define PTE_FLAG_PRESENT    (1ull << 0)

// Those indexes are 9bit wide that's why we use 0x1FF mask
#define PAGING_GET_PML4INDEX(virtAddress)      (((virtAddress) >> 39) & 0x1FF)
#define PAGING_GET_PDPRINDEX(virtAddress)      (((virtAddress) >> 30) & 0x1FF)
#define PAGING_GET_PDINDEX(virtAddress)        (((virtAddress) >> 21) & 0x1FF)
#define PAGING_GET_PTINDEX(virtAddress)        (((virtAddress) >> 12) & 0x1FF)
#define PAGING_GET_FRAME_OFFSET(virtAddress)   ((virtAddress) & 0xFFF)

#define PAGING_PTE_ADDR_MASK 0x000FFFFFFFFFF000

void paging_init(void);
void paging_map_page(uint64_t *pml4_root, uint64_t virt_addr, uint64_t phys_addr, uint64_t flags, bool isHugePage);
void paging_map_region(uint64_t *pml4_root, uint64_t virt_addr, uint64_t phys_addr, uint64_t size, uint64_t flags, bool isHugePage);
void paging_unmap_page(uint64_t *pml4_root, uint64_t virt_addr, bool isHugePage);
inline void paging_switch_context(uint64_t *kernel_pml4_phys);
uint64_t *paging_getKernelRoot(void);

#endif // PAGING_H