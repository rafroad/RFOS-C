#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096  // Example page size
#define MAX_PAGES 1024  // Example maximum number of pages

static volatile int interrupts_enabled = 1; // Flag for interrupt state
static char memory_pool[MAX_PAGES * PAGE_SIZE]; // Memory pool for allocation
static int pages_allocated = 0; // Track the number of pages currently allocated

/** Disable interrupts on i386 */
static inline void disable_interrupts() {
    asm volatile ("cli"); // Clear interrupt flag (disable interrupts)
    interrupts_enabled = 0;
}

/** Enable interrupts on i386 */
static inline void enable_interrupts() {
    asm volatile ("sti"); // Set interrupt flag (enable interrupts)
    interrupts_enabled = 1;
}

/** This function locks the memory data structures. */
int liballoc_lock() {
    disable_interrupts(); // Lock by disabling interrupts
    return 0; // Success
}

/** This function unlocks what was previously locked. */
int liballoc_unlock() {
    enable_interrupts(); // Unlock by enabling interrupts
    return 0; // Success
}

/** This function allocates memory pages. */
void* liballoc_alloc(int num_pages) {
    if (num_pages <= 0 || pages_allocated + num_pages > MAX_PAGES) {
        return NULL; // Allocation failed
    }

    void* allocated_memory = (void*)(memory_pool + (pages_allocated * PAGE_SIZE));
    pages_allocated += num_pages; // Update the count of allocated pages
    return allocated_memory; // Return the pointer to the allocated memory
}

/** This function frees previously allocated memory. */
int liballoc_free(void* ptr, int num_pages) {
    // In this simple example, we do not track which pages are free.
    // This function could be expanded to manage a free list if needed.
    if (ptr < (void*)memory_pool || ptr >= (void*)(memory_pool + sizeof(memory_pool))) {
        return -1; // Invalid pointer
    }

    pages_allocated -= num_pages; // Update the count of allocated pages
    return 0; // Success
}
void liballoc_init() {
    // Reset the memory pool to zero
    for (int i = 0; i < sizeof(memory_pool); i++) {
        memory_pool[i] = 0; // Initialize all bytes to zero
    }

    // Initialize the page allocation tracker
    pages_allocated = 0;
}
