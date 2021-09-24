#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define LALT_KEY 0x38
#define RALT_KEY 0x57B8

#define LCTRL_KEY 0x1D
#define RCTRL_KEY 0x579D

#define LSHIFT_KEY 0x2A
#define RSHIFT_KEY 0x36

#define ENTER_KEY 0x1C
#define BACKSPACE_KEY 0x0E

typedef struct 
{
    uint8_t shiftIsPressed;
    uint8_t ctrlIsPressed;
    uint8_t altIsPressed;
} mod_key_t;

void init_keyboard();

#endif
