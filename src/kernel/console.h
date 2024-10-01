#include "libs/stdint.h"
#include "ports.h"
#include "mouse.h"
#include "libs/string.h"

short cursor_x = 0;
short cursor_y = 0;

void disable_cursor() {
    outb(0x3D4, 0x0A);  
    outb(0x3D5, 0x20);  
}

void enable_cursor() {
    outb(0x3D4, 0x0A);  
    outb(0x3D5, 0x0E);  
}

void cursor_pos(int x = 0, int y = 0)
{
    unsigned short pos = y * 80 + x;
    outb(0x3D4, 0x0E);
    outb(0x3D5, (pos >> 8) & 0xFF);
    outb(0x3D4, 0x0F);
    outb(0x3D5, pos & 0xFF);
    cursor_x = x;
    cursor_y = y;
}

void clear()
{
    unsigned short* vid_mem = (unsigned short*)0xB8000;
    unsigned short attribute = 0x0F00; 
    for(int i = 0; i < 80 * 25; ++i)
    {
        vid_mem[i] = attribute | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

void printf(const char* str, int color = 0x0F)
{
    unsigned short* vid_mem = (unsigned short*)0xB8000;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == '\n') { cursor_y++; }
        else
        {
            if (cursor_x >= 80) { cursor_x = 0; cursor_y++; }
            if (cursor_y >= 25) { clear(); cursor_y = 0; cursor_x = 0; }

            vid_mem[cursor_y * 80 + cursor_x] = (color << 8) | str[i];
            cursor_x++;
        }
    }

    cursor_pos(cursor_x, cursor_y);
}

void printf_button(const char* text, int x, int y, void (*callback)(), int color = 0xF0)
{
    cursor_pos(x, y);
    printf(text, color);

    if (mouse_buttons & 0x01 && mouse_x >= x && mouse_x <= strlen(const_cast<char*>(text)) && mouse_y == y)
    {
        callback();
    }
}