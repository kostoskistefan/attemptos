#include "keyboard.h"
#include "../screen/screen.h"
#include "../../cpu/isr/isr.h"
#include "../../cpu/ports/ports.h"
#include "../../libraries/function.h"
#include "../../system/shell/shell.h"

static char key_buffer[256];
static mod_key_t modifier_keys;

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
    0};

const uint8_t scancode_set_2[128] = {
    0,
    27,
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')',
    '_',
    '+',
    '\b',
    '\t',
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '{',
    '}',
    '\n',
    0,
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ':',
    '"',
    '~',
    0,
    '|',
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    '<',
    '>',
    '?',
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
    0};

void handle_modifier_keys(uint16_t scancode)
{
    if (scancode & 0x80)
    {
        if (scancode == LSHIFT_KEY + 128 || scancode == RSHIFT_KEY + 128)
            modifier_keys.shiftIsPressed = 0;

        if (scancode == LCTRL_KEY + 128 || scancode == RCTRL_KEY + 128)
            modifier_keys.ctrlIsPressed = 0;
        
        if (scancode == LALT_KEY + 128 || scancode == RALT_KEY + 128)
            modifier_keys.ctrlIsPressed = 1;
    }

    else
    {
        if (scancode == LSHIFT_KEY || scancode == RSHIFT_KEY)
            modifier_keys.shiftIsPressed = 1;

        if (scancode == LCTRL_KEY || scancode == RCTRL_KEY)
            modifier_keys.ctrlIsPressed = 1;

        if (scancode == LALT_KEY || scancode == RALT_KEY)
            modifier_keys.ctrlIsPressed = 1;
    }
}

static void keyboard_callback(registers_t *reg)
{
    UNUSED(reg);

    uint16_t scancode = port_byte_in(0x60);

    handle_modifier_keys(scancode);

    if(!(scancode & 0x80))
    {
        if (scancode == ENTER_KEY)
        {
            print("\n");
            execute(key_buffer);
            key_buffer[0] = 0;
        }

        else if (scancode == BACKSPACE_KEY)
        {
            key_buffer[strlen(key_buffer) - 1] = '\0';
            delete_last_character();
        }

        else
        {
            if(modifier_keys.ctrlIsPressed && scancode == 0x2E) // Ctrl+C is pressed
            {
                key_buffer[0] = 0;
                execute("");
                return;
            }

            if (!modifier_keys.shiftIsPressed)
            {
                append(key_buffer, scancode_set_1[scancode]);
                printf("%s", toString(scancode_set_1[scancode]));
            }

            else
            {
                append(key_buffer, scancode_set_2[scancode]);
                printf("%s", toString(scancode_set_2[scancode]));
            }
        }
    }
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}