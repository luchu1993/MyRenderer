//
// Created by luchu on 2022/3/16.
//

#pragma once
#include <cmath>

#define EPSILON 1e-5f
#define PI 3.1415927f

#define TO_RADIANS(degrees) ((PI / 180) * (degrees))
#define TO_DEGREES(radians) ((180 / PI) * (radians))

float Min(float a, float b);

float Max(float a, float b);

float Lerp(float a, float b, float t);

float Clamp(float f, float min, float max);

float Saturate(float f);

unsigned char FloatToUChar(float value);

float UCharToFloat(unsigned char value);

float SrgbToLinear(float value);

float LineaToSrgb(float value);