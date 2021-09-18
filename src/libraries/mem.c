#include "mem.h"

void memory_set(uint8 *destination, uint8 value, uint32 length)
{
    uint8* temp = (uint8 *) destination;
    for(; length != 0; length--)
        *temp++ = value;
}

void memory_copy(uint8 * source, uint8 * destination, int no_bytes)
{
    for (int i = 0; i < no_bytes; i++) 
        *(destination + i) = *(source + i);
}