#include "screen.h"
#include "ports.h"

// -------------------------- Function declaration --------------------------

int get_cursor();
void set_cursor(int offset);
int get_screen_offset(int row, int col);
int get_row_offset(int offset);
int get_col_offset(int offset);
int print_char(char character, int row, int col, char attribute_byte);

// ------------------------ Function implementations ------------------------

void print(char *text)
{
    print_at(text, -1, -1);
}

void print_at(char *text, int row, int col)
{
    int offset;
    
    if (col >= 0 && row >= 0)
        offset = get_screen_offset(col, row);
    
    else 
    {
        offset = get_cursor();
        row = get_row_offset(offset);
        col = get_col_offset(offset);
    }

    for (int i = 0; text[i] != 0; i++)
    {
        offset = print_char(text[i], row, col, WHITE_ON_BLACK); 
        row = get_row_offset(offset);
        col = get_col_offset(offset);
    }
}

void clear_screen()
{
    unsigned char *video_memory = (unsigned char *)VIDEO_ADDRESS;

    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++)
    {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = WHITE_ON_BLACK;
    }

    set_cursor(get_screen_offset(0, 0));
}

int print_char(char character, int row, int col, char attribute_byte)
{
    unsigned char *video_memory = (unsigned char *)VIDEO_ADDRESS;

    if (!attribute_byte)
        attribute_byte = WHITE_ON_BLACK;

    int offset;

    if (row >= 0 && col >= 0)
        offset = get_screen_offset(row, col);

    else
        offset = get_cursor();

    if (character == '\n')
    {
        int row = offset / (2 * MAX_COLS);
        offset = get_screen_offset(0, row + 1);
    }

    else
    {
        video_memory[offset] = character;
        video_memory[offset + 1] = attribute_byte;
        offset += 2;
    }

    set_cursor(offset);
    return offset;
}

int get_cursor()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    return offset * 2;
}

void set_cursor(int offset)
{
    offset /= 2;

    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_screen_offset(int row, int col)
{
    return 2 * (row * MAX_COLS + col);
}

int get_row_offset(int offset)
{
    return offset / (2 * MAX_COLS);
}

int get_col_offset(int offset)
{
    return (offset - (get_row_offset(offset) * 2 * MAX_COLS)) / 2;
}