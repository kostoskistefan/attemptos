#ifndef MEM_H
#define MEM_H

#include <stdint.h>

void memory_set(uint8_t *destination, uint8_t value, uint32_t length);
void memory_copy(uint8_t *source, uint8_t *destination, int no_bytes);

#endif