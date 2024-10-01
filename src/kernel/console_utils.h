#include "stdint.h"
#include "driver.h"

unsigned int current_x = 0;
unsigned int current_y = 0;

void set_cursor_position(int x, int y)
{
    current_x = x;
    current_y = y;
    unsigned short pos = y * 80 + x;
    outb(0x3D4, 0x0E);
    outb(0x3D5, (pos >> 8) & 0xFF);
    outb(0x3D4, 0x0F);
    outb(0x3D5, pos & 0xFF);
}

void clear()
{
    unsigned short* vid_mem = (unsigned short*)0xB8000;
    unsigned short attribute = 0x0F00; 
    for(int i = 0; i < 80 * 25; ++i)
    {
        vid_mem[i] = attribute | ' ';
    }
    set_cursor_position(0, 0);
}

void printf(const char* str, int color, char arg_char = 0)
{
    unsigned short* vid_mem = (unsigned short*)0xB8000;
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '%')
        {
            i++;
            if (str[i] == 'c')
            {
                vid_mem[current_y * 80 + current_x] = (color << 8) | (arg_char & 0xFF);
                current_x++;
            }
        }
        else
        {
            vid_mem[current_y * 80 + current_x] = (color << 8) | (str[i] & 0xFF);
            current_x++;
        }

        if (current_x >= 80)
        {
            current_x = 0;
            current_y++;
        }

        if (current_y >= 25)
        {
            current_y = 0; 
            clear();
        }

        i++;
    }

    set_cursor_position(current_x, current_y);
}

void printf_at(const char* str, int x, int y, int color)
{
    set_cursor_position(x, y);
    unsigned short* vid_mem = (unsigned short*)0xB8000;
    int i = 0;
    while(str[i] != '\0')
    {
        vid_mem[(y * 80) + x + i] = (color << 8) | (str[i] & 0xFF);
        i++;
    }
    set_cursor_position(x + i, y);
}

const char* int8_to_string(int8 value)
{
    static char buffer[5];
    char *ptr = buffer + sizeof(buffer) - 1;
    int is_negative = (value < 0);
    
    *ptr = '\0';

    if (is_negative) value = -value;

    do {
        *--ptr = (value % 10) + '0';
        value /= 10;
    } while (value);

    if (is_negative) *--ptr = '-';

    return ptr;
}

void printf_button(const char text[], int x, int y, int width, int color, void (*func)(), int mouse_x, int mouse_y, int buttons)
{
    printf_at(text, x, y, color);
    
    if (buttons & 0x01 && mouse_x >= x && mouse_x <= x + width && mouse_y == y)
    {
        func();
    }
}

void delete_char(int x, int y)
{
    unsigned short* vid_mem = (unsigned short*)0xB8000;
    unsigned short attribute = 0x0F00;
    vid_mem[y * 80 + x] = attribute | ' ';
}

void disable_cursor() {
    outb(0x3D4, 0x0A);  
    outb(0x3D5, 0x20);  
}

void enable_cursor() {
    outb(0x3D4, 0x0A);  
    outb(0x3D5, 0x0E);  
}
