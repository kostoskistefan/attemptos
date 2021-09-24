#include "mem.h"

uint32_t free_memory_address = 0x10000;

void memory_set(uint8_t *destination, uint8_t value, uint32_t length)
{
    uint8_t* temp = (uint8_t *) destination;
    for(; length != 0; length--)
        *temp++ = value;
}

void memory_copy(uint8_t * source, uint8_t * destination, int no_bytes)
{
    for (int i = 0; i < no_bytes; i++) 
        *(destination + i) = *(source + i);
}

uint32_t malloc(uint32_t size, int align, uint32_t* physical_address)
{
    if (align == 1 && (free_memory_address & 0xFFFFF000)) {
        free_memory_address &= 0xFFFFF000;
        free_memory_address += 0x1000;
    }
    
    if (physical_address) 
        *physical_address = free_memory_address;

    uint32_t ret = free_memory_address;
    
    free_memory_address += size;

    return ret;
}