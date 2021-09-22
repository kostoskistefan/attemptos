#include "mem.h"

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