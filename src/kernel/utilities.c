#include "utilities.h"

void memory_set(uint8 *destination, uint8 value, uint32 length)
{
    uint8* temp = (uint8 *) destination;
    for(; length != 0; length--)
        *temp++ = value;
}

void memory_copy(uint8 * source, uint8 * destination, uint32 no_bytes)
{
    for (int i = 0; i < no_bytes; i++) 
        *(destination + i) = *(source + i);
}

void reverse(char str[])
{
    for (int i = 0, j = strlen(str) - 1; i < j; i++, j--)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int strlen(char str[])
{
    int i = 0;
    while(str[i] != '\0') i++;
    return i;
}

void int_to_string(int n, char str[]) 
{
    int i, sign;

    if ((sign = n) < 0) 
        n = -n;

    i = 0;

    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';

    str[i] = '\0';

    reverse(str);
}
