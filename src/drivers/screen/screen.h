#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stdarg.h>
#include "../../libraries/string.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

// Screen I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void clear_screen();
void print(char *text);
void delete_last_character();
void printf(char *format, ...);
void print_at(char *text, int col, int row);

#endif