//
// Created by luchu on 2022/3/16.
//

#include "Vector.h"

// ---------------------------------------------
Vector2 Vector2::operator+(const Vector2 &v) const
{
    return Vector2(x_ + v.x_, y_ + v.y_);
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
    return Vector2(x_ - v.x_, y_ - v.y_);
}

Vector2 Vector2::operator*(float factor) const
{
    return Vector2(x_ * factor, y_ * factor);
}

Vector2 Vector2::operator/(float divisor) const
{
    float factor = 1.0f / divisor;
    return Vector2(x_ * factor, y_ * factor);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x_, -y_);
}

float Vector2::Length() const
{
    return sqrtf(SquareLength());
}

float Vector2::SquareLength() const
{
    return x_ * x_ + y_ * y_;
}

void Vector2::Normalize()
{
    float length = Length();
    x_ /= length;
    y_ /= length;
}

Vector2 Vector2::Normalized() const
{
    float length = Length();
    return Vector2(x_ / length, y_ / length);
}

Vector2 Min(const Vector2& a, const Vector2& b)
{
    return Vector2(Min(a.x_, b.x_), Min(a.y_, b.y_));
}

Vector2 Max(const Vector2& a, const Vector2& b)
{
    return Vector2(Max(a.x_, b.x_), Max(a.y_, b.y_));
}

Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
{
    return Vector2(Lerp(a.x_, b.x_, t), Lerp(a.y_, b.y_, t));
}

// ---------------------------------------------------------------

const Vector3 Vector3::Up(0, 1, 0);

Vector3::Vector3(const Vector4 &v)
    :   x_(v.x_)
    , y_(v.y_)
    , z_(v.z_)
{
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}

Vector3 Vector3::operator*(const Vector3 &v) const
{
    return Vector3(x_ * v.x_, y_ * v.y_, z_ * v.z_);
}

Vector3 Vector3::operator*(float factor) const
{
    return Vector3(x_ * factor, y_ * factor, z_ * factor);
}

Vector3 Vector3::operator/(float divisor) const
{
    float factor = 1.0f / divisor;
    return Vector3(x_ * factor, y_ * factor, z_ * factor);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x_, -y_, -z_);
}

float Vector3::Length() const
{
    return sqrtf(SquareLength());
}

float Vector3::SquareLength() const
{
    return x_ * x_ + y_ * y_ + z_ * z_;
}

void Vector3::Normalize()
{
    float length = Length();
    x_ /= length;
    y_ /= length;
    z_ /= length;
}

Vector3 Vector3::Normalized() const
{
    float length = Length();
    return Vector3(x_ / length, y_ / length, z_ / length);
}

float Vector3::Dot(const Vector3 &v) const
{
    return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

Vector3 Vector3::Cross(const Vector3 &v) const
{
    return Vector3(
        y_ * v.z_ - z_ * v.y_,
        z_ * v.x_ - x_ * v.z_,
        x_ * v.y_ - y_ * v.x_
    );
}

Vector3 Vector3::Saturate() const
{
    return Vector3(::Saturate(x_), ::Saturate(y_), ::Saturate(z_));
}

Vector3 Min(const Vector3& a, const Vector3& b)
{
    return Vector3(Min(a.x_, b.x_), Min(a.y_, b.y_), Min(a.z_, b.z_));
}

Vector3 Max(const Vector3& a, const Vector3& b)
{
    return Vector3(Max(a.x_, b.x_), Max(a.y_, b.y_), Max(a.z_, b.z_));
}

Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
{
    return Vector3(
        Lerp(a.x_, b.x_, t),
        Lerp(a.y_, b.y_, t),
        Lerp(a.z_, b.z_, t)
    );
}

// ----------------------------------------------------------

const Vector4 Vector4::Zero;

Vector4 Vector4::operator+(const Vector4 &v) const
{
    return Vector4(x_ + v.x_, y_ + v.y_, z_ + v.z_, w_ + v.w_);
}

Vector4 Vector4::operator-(const Vector4 &v) const
{
    return Vector4(x_ - v.x_, y_ - v.y_, z_ - v.z_, w_ - v.w_);
}

Vector4 Vector4::operator*(const Vector4 &v) const
{
    return Vector4(x_ * v.x_, y_ * v.y_, z_ * v.z_, w_ * v.w_);
}

Vector4 Vector4::operator*(float factor) const
{
    return Vector4(x_ * factor, y_ * factor, z_ * factor, w_ * factor);
}

Vector4 Vector4::operator/ (float divisor) const
{
    float factor = 1.0f / divisor;
    return Vector4(x_ * factor, y_ * factor, z_ * factor, w_ * factor);
}

Vector4 Vector4::Saturate() const
{
    return Vector4(::Saturate(x_), ::Saturate(y_), ::Saturate(z_), ::Saturate(w_));
}

Vector4 Lerp(const Vector4& a, const Vector4& b, float t)
{
    return Vector4(
        Lerp(a.x_, b.x_, t),
        Lerp(a.y_, b.y_, t),
        Lerp(a.z_, b.z_, t),
        Lerp(a.w_, b.w_, t)
    );
}

