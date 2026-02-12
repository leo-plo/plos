#ifndef KHEAP_H
#define KHEAP_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// The starting size of our kernel heap (1MB)
#define KHEAP_STARTING_SIZE 0x100000
#define KHEAP_MIN_SPLITTING_SIZE 16
#define KHEAP_BLOCK_SIZE 16
#define KHEAP_EXTENDING_AMOUNT 0x100000

// The fundamental block of our heap
struct kheap_node
{
    // The size of the region EXCLUDING its header size
    uint64_t size;
    bool isFree;
    struct kheap_node *next;
};

void kheap_init(void);
bool kheap_extend(size_t size);
void* kmalloc(size_t size);
void kfree(void *ptr);
void kheap_print_nodes();

#endif // KHEAP_H