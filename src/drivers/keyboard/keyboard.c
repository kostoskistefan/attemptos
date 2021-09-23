#include "keyboard.h"
#include "../screen/screen.h"
#include "../../cpu/isr/isr.h"
#include "../../cpu/ports/ports.h"
#include "../../libraries/function.h"

const uint8_t scancode_set_1[128] = {
    0,
    27,
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\b',
    '\t',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '\n',
    0,
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '`',
    0,
    '\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    0,
    '*',
    0,
    ' ',
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0
};

static void keyboard_callback(registers_t *reg)
{
    UNUSED(reg);

    uint8_t scancode = port_byte_in(0x60);
    char letter[2] = {scancode_set_1[scancode], '\0'};

    // On key release
    if(scancode & 0x80)
        print("");

    // On key press
    else
        print(letter);
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}