#ifndef VMM_H
#define VMM_H

#define VMM_PAGE_SIZE 4096

// Flags for PML4, PDPR, PD entries
#define PDE_FLAG_EXEC       (1ull << 63)
#define PDE_FLAG_ACCESSED   (1ull << 5)
#define PDE_FLAG_PCD        (1ull << 4)
#define PDE_FLAG_PWT        (1ull << 3)
#define PDE_FLAG_US         (1ull << 2)
#define PDE_FLAG_RW         (1ull << 1)
#define PDE_FLAG_PRESENT    (1ull << 0)

// Flags for Page tables
#define PTE_FLAG_EXEC       (1ull << 63)
#define PTE_FLAG_GLOABL     (1ull << 8)
#define PTE_FLAG_PAT        (1ull << 7)
#define PTE_FLAG_DIRTY      (1ull << 6)
#define PTE_FLAG_ACCESSED   (1ull << 5)
#define PTE_FLAG_PCD        (1ull << 4)
#define PTE_FLAG_PWT        (1ull << 3)
#define PTE_FLAG_US         (1ull << 2)
#define PTE_FLAG_RW         (1ull << 1)
#define PTE_FLAG_PRESENT    (1ull << 0)

// Those indexes are 9bit wide that's why we use 0x1FF mask
#define VMM_GET_PML4INDEX(virtAddress)      (((virtAddress) >> 39) & 0x1FF)
#define VMM_GET_PDPRINDEX(virtAddress)      (((virtAddress) >> 30) & 0x1FF)
#define VMM_GET_PDINDEX(virtAddress)        (((virtAddress) >> 21) & 0x1FF)
#define VMM_GET_PTINDEX(virtAddress)        (((virtAddress) >> 12) & 0x1FF)
#define VMM_GET_FRAME_OFFSET(virtAddress)   ((virtAddress) & 0xFFF)

#define VMM_PTE_ADDR_MASK 0x000FFFFFFFFFF000

#endif // VMM_H