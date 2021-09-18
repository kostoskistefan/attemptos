#include "string.h"

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

void append(char str[], char character) {
    int len = strlen(str);
    str[len] = character;
    str[len+1] = '\0';
}