#ifndef STRING_H
#define STRING_H

#include "stdint.h"

short strlen(char* str) {
    short out = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        out++;
    }
    return out;
}

const char* inttostr(int value) {
    static char buffer[12];
    char* ptr = buffer + sizeof(buffer) - 1;
    *ptr = '\0';

    bool isNegative = value < 0;
    unsigned int absValue = isNegative ? -value : value;

    do {
        *--ptr = '0' + (absValue % 10);
        absValue /= 10;
    } while (absValue > 0);

    if (isNegative) {
        *--ptr = '-';
    }

    return ptr;
}

const char* shorttostr(short value) {
    return inttostr(static_cast<int>(value));
}

#endif