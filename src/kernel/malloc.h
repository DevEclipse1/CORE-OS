#include "stdint.h"

void* malloc(size s) 
{
    static uint8 memory[1024 * 1024]; 
    static size allocated = 0;

    if (allocated + s > sizeof(memory)) 
        return NULL;

    void* ptr = &memory[allocated];
    allocated += s;
    return ptr;
}
