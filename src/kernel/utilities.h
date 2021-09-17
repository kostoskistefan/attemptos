#ifndef UTILITIES_H
#define UTILITIES_H

#include "../cpu/types.h"

int strlen(char str[]);
void reverse(char str[]);
void int_to_string(int n, char str[]);
void memory_set(uint8 *destination, uint8 value, uint32 length);
void memory_copy(uint8 *source, uint8 *destination, uint32 no_bytes);

#endif
