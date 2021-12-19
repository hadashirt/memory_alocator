#include <stdio.h>

void mem_init(unsigned char *my_memory, unsigned int my_mem_size)
{
    /*How do i initialize ? What am I initializing? */
    /*need to define a maz number for memory */
    char free_list[my_mem_size];
    int free = 1;
    char nextt = NULL;
}
void *my_malloc(unsigned size)
{
    /*test if the memory we are accessing is past what we have*/
    void *mem;

    if (sizeof my_memory - nextt < size)
        return NULL;

    mem = &my_memory[nextt];
    next += size;
    return mem;
}

void my_free(void *mem_pointer) void mem_get_stats(mem_stats_ptr mem_stats_ptr) * /
