#include "stdint.h"

static inline void outb(uint16 port, uint8 value)
{
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8 inb(uint16 port)
{
    uint8 ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

char read_key()
{
    uint8 scancode = inb(0x60);
    if (scancode < 0x80)
    {
        char c = 0;
        switch (scancode)
        {
            case 0x1E: c = 'a'; break;
            case 0x30: c = 'b'; break;
            case 0x2E: c = 'c'; break;
            case 0x20: c = 'd'; break;
            case 0x12: c = 'e'; break;
            case 0x21: c = 'f'; break;
            case 0x22: c = 'g'; break;
            case 0x23: c = 'h'; break;
            case 0x17: c = 'i'; break;
            case 0x24: c = 'j'; break;
            case 0x25: c = 'k'; break;
            case 0x26: c = 'l'; break;
            case 0x32: c = 'm'; break;
            case 0x31: c = 'n'; break;
            case 0x18: c = 'o'; break;
            case 0x19: c = 'p'; break;
            case 0x10: c = 'q'; break;
            case 0x13: c = 'r'; break;
            case 0x14: c = 's'; break;
            case 0x27: c = 't'; break;
            case 0x16: c = 'u'; break;
            case 0x2F: c = 'v'; break;
            case 0x11: c = 'w'; break;
            case 0x2D: c = 'x'; break;
            case 0x15: c = 'y'; break;
            case 0x2C: c = 'z'; break;
            case 0x39: c = ' '; break;
            case 0x0C: c = '0'; break;
            case 0x0B: c = '1'; break;
            case 0x0A: c = '2'; break;
            case 0x09: c = '3'; break;
            case 0x08: c = '4'; break;
            case 0x07: c = '5'; break;
            case 0x06: c = '6'; break;
            case 0x05: c = '7'; break;
            case 0x04: c = '8'; break;
            case 0x03: c = '9'; break;
            case 0x1C: c = '\n'; break;
            case 0x0E: c = '\r'; break;
        }
        return c;
    }
    return 0;
}

void init_mouse() {
    
    outb(0x64, 0xA8);
    
    outb(0x64, 0x20);  
    uint8 status = inb(0x60);
    status |= 2;  
    outb(0x64, 0x60);  
    outb(0x60, status);
    
    outb(0x64, 0xD4);  
    outb(0x60, 0xF4);  
}

typedef struct {
    int8 x_movement;
    int8 y_movement;
    uint8 buttons;
} MousePacket;

MousePacket read_mouse() {
    MousePacket packet;

    while (!(inb(0x64) & 1));  
    packet.buttons = inb(0x60);  
    
    while (!(inb(0x64) & 1));  
    int8 x_movement = inb(0x60);  

    while (!(inb(0x64) & 1));  
    int8 y_movement = inb(0x60);

    packet.x_movement = x_movement;
    packet.y_movement = -y_movement;

    return packet;
}
