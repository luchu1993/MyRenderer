//
// Created by luchu on 2022/3/16.
//

#include "Quat.h"

Quat Quat::operator+(const Quat& q) const
{
    return Quat(x_ + q.x_, y_ + q.y_, z_ + q.z_, w_ + q.w_);
}

Quat Quat::operator*(float factor) const
{
    return Quat(x_ * factor, y_ * factor, z_ * factor, w_ * factor);
}

Quat Quat::operator-() const
{
    return Quat(-x_, -y_, -z_, -w_);
}

float Quat::Dot(const Quat &q) const
{
    return x_ * q.x_ + y_ * q.y_ + z_ * q.z_ + w_ * q.w_;
}

Matrix3 Quat::RotationMatrix() const
{
    return Matrix3(
        1.0f - 2.0f * y_ * y_ - 2.0f * z_ * z_,
        2.0f * x_ * y_ - 2.0f * w_ * z_,
        2.0f * x_ * z_ + 2.0f * w_ * y_,
        2.0f * x_ * y_ + 2.0f * w_ * z_,
        1.0f - 2.0f * x_ * x_ - 2.0f * z_ * z_,
        2.0f * y_ * z_ - 2.0f * w_ * x_,
        2.0f * x_ * z_ - 2.0f * w_ * y_,
        2.0f * y_ * z_ + 2.0f * w_ * x_,
        1.0f - 2.0f * x_ * x_ - 2.0f * y_ * y_
    );
}

Quat Quat::Normalized() const
{
    float factor = 1.0f / Length();
    return Quat(x_ * factor, y_ * factor, z_ * factor, w_ * factor);
}

float Quat::Length() const
{
    return sqrtf(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
}

Quat Lerp(const Quat& a, const Quat& b, float t)
{
    return Quat(
        Lerp(a.x_, b.x_, t),
        Lerp(a.y_, b.y_, t),
        Lerp(a.z_, b.z_, t),
        Lerp(a.w_, b.w_, t)
    );
}

Quat Slerp(const Quat& from, const Quat& to, float t)
{
    Quat a = from;
    Quat b = to;

    float cosAngle = a.Dot(b);
    if (cosAngle < 0)
    {
        b = -b;
        cosAngle = -cosAngle;
    }

    if (cosAngle > 1 - EPSILON)
    {
        return Lerp(from, to, t);
    }
    else
    {
        float angle = acosf(cosAngle);
        float sinAngle = sinf(angle);

        float angleA = (1-t) * angle;
        float angleB = t * angle;
        float factorA = sinf(angleA) / sinAngle;
        float factorB = sinf(angleB) / sinAngle;

        return a * factorA + b * factorB;
    }
}