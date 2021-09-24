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
    while (str[i] != '\0')
        i++;
    return i;
}

void append(char str[], char character)
{
    int len = strlen(str);
    str[len] = character;
    str[len + 1] = '\0';
}

char *itoa(int number)
{
    static char str[50];

    int sign;

    if ((sign = number) < 0)
        number = -number;

    int i = 0;

    do
    {
        str[i++] = number % 10 + '0';
    } while ((number /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';

    str[i] = '\0';

    reverse(str);

    return str;
}

char *toString(char letter)
{
    static char out[2] = "\0";
    out[0] = letter;
    return out;
}

int strcmp(char str1[], char str2[])
{
    int i;

    for (i = 0; str1[i] == str2[i]; i++)
        if (str1[i] == '\0')
            return 0;

    return str1[i] - str2[i];
}

uint8_t contains(char *string, char *toFind)
{
    uint8_t slen = strlen(string);
    uint8_t tFlen = strlen(toFind);
    uint8_t found = 0;

    if (slen >= tFlen)
    {
        for (uint8_t s = 0, t = 0; s < slen; s++)
        {
            do
            {
                if (string[s] == toFind[t])
                {
                    if (++found == tFlen)
                        return 1;
                    s++;
                    t++;
                }

                else
                {
                    s -= found;
                    found = 0;
                    t = 0;
                }
            } while (found);
        }
        return 0;
    }

    else
        return 0;
}