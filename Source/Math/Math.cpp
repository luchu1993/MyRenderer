//
// Created by luchu on 2022/3/16.
//

#include "Math.h"

float Min(float a, float b) { return a < b ? a : b; }

float Max(float a, float b) { return a > b ? a : b; }

float Lerp(float a, float b, float t) { return a + (b - a) * t; }

float Clamp(float f, float min, float max)
{
    return f < min ? min : (f > max ? max : f);
}

float Saturate(float f)
{
    return f < 0 ? 0 : (f > 1 ? 1 : f);
}

unsigned char FloatToUChar(float value)
{
    return (unsigned char )(value * 255);
}

float UCharToFloat(unsigned char value)
{
    return value / 255.0f;
}

float SrgbToLinear(float value)
{
    return powf(value, 2.2f);
}

float LineaToSrgb(float value)
{
    return powf(value, 1 / 2.2f);
}