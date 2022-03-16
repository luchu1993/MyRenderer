//
// Created by luchu on 2022/3/16.
//

#pragma once

#include "Matrix.h"

class Quat
{
public:
    Quat(float x, float y, float z, float w)
        : x_(x)
        , y_(y)
        , z_(z)
        , w_(w)
    {
    }

    Quat operator+(const Quat& q) const;

    Quat operator*(float factor) const;

    Quat operator-() const;

    float Dot(const Quat& q) const;

    float Length() const;

    Quat Normalized() const;

    Matrix3 RotationMatrix() const;

    float x_;
    float y_;
    float z_;
    float w_;
};

Quat Lerp(const Quat& a, const Quat& b, float t);
Quat Slerp(const Quat& a, const Quat& b, float t);
