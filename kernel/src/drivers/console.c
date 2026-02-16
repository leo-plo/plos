#include "flanterm.h"
#include "flanterm_backends/fb.h"
#include <cpu.h>
#include <drivers/console.h>
#include <memory/hhdm.h>
#include <memory/kheap.h>
#include <memory/paging.h>
#include <memory/vmm.h>
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

extern struct limine_framebuffer_request framebuffer_request;
static struct flanterm_context *ft_ctx = NULL;

static void flanterm_kfree_wrapper(void *ptr, size_t size)
{
    (void) size;
    kfree(ptr);
}

/**
 * @brief Initializes the terminal emulator
 */
void console_init()
{
    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];

    // Calculate the total size that we need to map
    uint64_t fb_size = fb->height * fb->pitch;
    if(fb_size % PAGING_PAGE_SIZE) fb_size += PAGING_PAGE_SIZE - (fb_size % PAGING_PAGE_SIZE);

    // Map the framebuffer location
    void *virt_fb = vmm_alloc(vmm_get_kernel_vas(),
        fb_size,
        VMM_FLAGS_MMIO | VMM_FLAGS_READ | VMM_FLAGS_WRITE | VMM_FLAGS_WC,
        (uint64_t)hhdm_virtToPhys(fb->address));
    
    // Panic!
    if(!virt_fb)
    {
        hcf();
    }

    // Initializing flanterm
    ft_ctx = flanterm_fb_init(
        kmalloc, flanterm_kfree_wrapper, 
        virt_fb, 
        fb->width, fb->height, fb->pitch, 
        fb->red_mask_size, fb->red_mask_shift, 
        fb->green_mask_size, fb->green_mask_shift, 
        fb->blue_mask_size, fb->blue_mask_shift,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        0, 0, 1, 0, 
        0, 0, 0);

}

/**
 * @brief Wrapper for writing to console
 * 
 * @param str Pointer to the string that will be printed
 * @param len 
 */
void console_write_str(const char *str, size_t len) 
{
    if (ft_ctx) {
        flanterm_write(ft_ctx, str, len);
    }
}