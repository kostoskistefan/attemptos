#ifndef STRINGS_H
#define STRINGS_H

#include <stdint.h>

int strlen(char str[]);
char* itoa(int number);
void reverse(char str[]);
char* toString(char letter);
void append(char s[], char n);
int strcmp(char str1[], char str2[]);
uint8_t contains(char *string, char *toFind);

#endif