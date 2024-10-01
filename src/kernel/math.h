#ifndef MATH_H
#define MATH_H

int clamp(int value, int min, int max)
{
    if (value < min) value = min;
    if (value > max) value = max;
}

#endif