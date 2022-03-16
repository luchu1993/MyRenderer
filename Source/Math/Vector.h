//
// Created by luchu on 2022/3/16.
//

#pragma once

#include "Math.h"

class Vector3;
class Vector4;

using Color = Vector4;

class Vector2
{
public:
    Vector2() = default;

    Vector2(float x, float y)
        : x_(x)
        , y_(y)
    {
    }

    Vector2 operator+(const Vector2& v) const;

    Vector2 operator-(const Vector2& v) const;

    Vector2 operator*(float factor) const;

    Vector2 operator/(float divisor) const;

    Vector2 operator-() const;

    float Length() const;

    float SquareLength() const;

    void Normalize();

    Vector2 Normalized() const;

    float x_ {};
    float y_ {};
};


Vector2 Min(const Vector2& a, const Vector2& b);

Vector2 Max(const Vector2& a, const Vector2& b);

Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

// ----------------------------------------------------------
class Vector3
{
public:
    Vector3() = default;

    Vector3(float x, float y, float z)
        : x_(x)
        , y_(y)
        , z_(z)
    {
    }

    explicit Vector3(const Vector4& v);

    Vector3 operator+(const Vector3& v) const;

    Vector3 operator-(const Vector3& v) const;

    Vector3 operator*(float factor) const;

    Vector3 operator*(const Vector3& v) const;

    Vector3 operator/(float divisor) const;

    Vector3 operator-() const;

    float Length() const;

    float SquareLength() const;

    void Normalize();

    Vector3 Normalized() const;

    float Dot(const Vector3& v) const;

    Vector3 Cross(const Vector3& v) const;

    Vector3 Saturate() const;

    float x_ {};
    float y_ {};
    float z_ {};

    const static Vector3 Up;
};

Vector3 Min(const Vector3& a, const Vector3& b);

Vector3 Max(const Vector3& a, const Vector3& b);

Vector3 Lerp(const Vector3& a, const Vector3& b, float t);


// ----------------------------------------------------------
class Vector4
{
public:
    Vector4() = default;

    Vector4(float x, float y, float z, float w)
        : x_(x)
        , y_(y)
        , z_(z)
        , w_(w)
    {
    }

    explicit Vector4(const Vector3& v)
        : x_(v.x_)
        , y_(v.y_)
        , z_(v.z_)
        , w_(0)
    {
    }

    Vector4 operator+(const Vector4& v) const;

    Vector4 operator-(const Vector4& v) const;

    Vector4 operator*(const Vector4& v) const;

    Vector4 operator*(float factor) const;

    Vector4 operator/(float divisor) const;

    Vector4 Saturate() const;

    float x_ {};
    float y_ {};
    float z_ {};
    float w_ {};

    static const Vector4 Zero;
};

Vector4 Lerp(const Vector4& a, const Vector4& b, float t);