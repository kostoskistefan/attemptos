#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void memory_set(uint8 *destination, uint8 value, uint32 length);
void memory_copy(uint8 *source, uint8 *destination, int no_bytes);

#endif