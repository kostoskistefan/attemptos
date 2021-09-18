#include "screen.h"
#include "../../cpu/types.h"
#include "../../cpu/ports/ports.h"
#include "../../libraries/mem.h"

// -------------------------- Function declaration --------------------------

int get_cursor();
void set_cursor(int offset);
int print_char(char character, int row, int col, char attribute_byte);

int get_row_offset(int offset);
int get_col_offset(int offset);
int get_screen_offset(int row, int col);
int handle_scrolling(int cursor_offset);

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
    uint8 *video_memory = (uint8 *)VIDEO_ADDRESS;

    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++)
    {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = WHITE_ON_BLACK;
    }

    set_cursor(get_screen_offset(0, 0));
}

int print_char(char character, int row, int col, char attribute_byte)
{
    uint8 *video_memory = (uint8 *)VIDEO_ADDRESS;

    if (!attribute_byte)
        attribute_byte = WHITE_ON_BLACK;

    int offset;

    if (row >= 0 && col >= 0)
        offset = get_screen_offset(row, col);

    else
        offset = get_cursor();

    if (character == '\n')
    {
        int rows = get_row_offset(offset);
        offset = get_screen_offset(rows + 1, 0);
    }

    else if(character == '\b')
    {
        if(row >= 0 && col > 0)
        {
            int cols = get_col_offset(offset);
            offset = get_screen_offset(row, cols - 1);

            video_memory[offset] = ' ';
            video_memory[offset + 1] = attribute_byte;
        }
    }

    else
    {
        video_memory[offset] = character;
        video_memory[offset + 1] = attribute_byte;
        offset += 2;
    }

    offset = handle_scrolling(offset);

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

int handle_scrolling(int cursor_offset)
{
    if(cursor_offset < MAX_ROWS * MAX_COLS * 2)
        return cursor_offset;

    for (int i = 1; i < MAX_ROWS; i++)
    {
        memory_copy((uint8*)(get_screen_offset(i, 0) + VIDEO_ADDRESS),
                (uint8*)(get_screen_offset(i - 1, 0) + VIDEO_ADDRESS),
                MAX_COLS * 2);
    }

    char *last_line = (char*) (get_screen_offset(MAX_ROWS - 1, 0) + VIDEO_ADDRESS);
    
    for (int i = 0; i < MAX_COLS * 2; i++)
        last_line[i] = 0;

    cursor_offset -= 2 * MAX_COLS;

    return cursor_offset;
}
