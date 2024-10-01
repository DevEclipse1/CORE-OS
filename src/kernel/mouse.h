#ifndef MOUSE_H
#define MOUSE_H

#include "libs/stdint.h"
#include "ports.h"

int mouse_x = 40;
int mouse_y = 12;
int mouse_buttons = 0;

void init_mouse() {
    
    outb(0x64, 0xA8);
    
    outb(0x64, 0x20);  
    uint8_t status = inb(0x60);
    status |= 2;  
    outb(0x64, 0x60);  
    outb(0x60, status);
    
    outb(0x64, 0xD4);  
    outb(0x60, 0xF4);  
}

typedef struct {
    int8_t x_movement;
    int8_t y_movement;
    uint8_t buttons;
} mouse_input;

mouse_input read_mouse_input()
{
    mouse_input in;
    int8_t x_movement = 0, y_movement = 0;

    if (inb(0x64) & 1) { in.buttons = inb(0x60); }
    if (inb(0x64) & 1) { x_movement = inb(0x60); }
    if (inb(0x64) & 1) { y_movement = inb(0x60); }

    in.x_movement = x_movement;
    in.y_movement = -y_movement;

    return in;
}

void update_mouse()
{
    mouse_input in = read_mouse_input();
    if (in.x_movement != 0 || in.y_movement != 0 || in.buttons != 0)
    {
        mouse_x += in.x_movement;
        mouse_y += in.y_movement;

        if (mouse_x < 0) mouse_x = 0;
        if (mouse_x > 79) mouse_x = 79;
        if (mouse_y < 0) mouse_y = 0;
        if (mouse_y > 24) mouse_y = 24;

        mouse_buttons = in.buttons;
    }
}

#endif