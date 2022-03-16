//
// Created by luchu on 2022/3/16.
//

#include <cassert>
#include "Matrix.h"
#include "Quat.h"

const Matrix3 Matrix3::Identify;

Matrix3::Matrix3(const Matrix4 &m)
    : m00_(m.m00_)
    , m01_(m.m01_)
    , m02_(m.m02_)
    , m10_(m.m10_)
    , m11_(m.m11_)
    , m12_(m.m12_)
    , m20_(m.m20_)
    , m21_(m.m21_)
    , m22_(m.m22_)
{
}

Matrix3 Matrix3::operator +(const Matrix3& m) const
{
    return Matrix3(
        m00_ + m.m00_,
        m01_ + m.m01_,
        m02_ + m.m02_,
        m10_ + m.m10_,
        m11_ + m.m11_,
        m12_ + m.m12_,
        m20_ + m.m20_,
        m21_ + m.m21_,
        m22_ + m.m22_
    );
}

Matrix3 Matrix3::operator -(const Matrix3& v) const
{
    return Matrix3(
        m00_ - v.m00_,
        m01_ - v.m01_,
        m02_ - v.m02_,
        m10_ - v.m10_,
        m11_ - v.m11_,
        m12_ - v.m12_,
        m20_ - v.m20_,
        m21_ - v.m21_,
        m22_ - v.m22_
    );
}

Matrix3 Matrix3::operator*(float factor) const
{
    return Matrix3(
        m00_ * factor,
        m01_ * factor,
        m02_ * factor,
        m10_ * factor,
        m11_ * factor,
        m12_ * factor,
        m20_ * factor,
        m21_ * factor,
        m22_ * factor
    );
}

Matrix3 Matrix3::operator*(const Matrix3& m) const
{
    return Matrix3(
        m00_ * m.m00_ + m01_ * m.m10_ + m02_ * m.m20_,
        m00_ * m.m01_ + m01_ * m.m11_ + m02_ * m.m21_,
        m00_ * m.m02_ + m01_ * m.m12_ + m02_ * m.m22_,
        m10_ * m.m00_ + m11_ * m.m10_ + m12_ * m.m20_,
        m10_ * m.m01_ + m11_ * m.m11_ + m12_ * m.m21_,
        m10_ * m.m02_ + m11_ * m.m12_ + m12_ * m.m22_,
        m20_ * m.m00_ + m21_ * m.m10_ + m22_ * m.m20_,
        m20_ * m.m01_ + m21_ * m.m11_ + m22_ * m.m21_,
        m20_ * m.m02_ + m21_ * m.m12_ + m22_ * m.m22_
    );
}

Vector3 Matrix3::operator*(const Vector3 &v) const
{
    return Vector3(
        m00_ * v.x_ + m01_ * v.y_ + m02_ * v.z_,
        m10_ * v.x_ + m11_ * v.y_ + m12_ * v.z_,
        m20_ * v.x_ + m21_ * v.y_ + m22_ * v.z_
    );
}

Matrix3 Matrix3::Transpose() const
{
    return Matrix3(
        m00_,m10_,m20_,
        m01_,m11_,m21_,
        m02_,m12_,m22_
    );
}

Matrix3 Matrix3::Inverse() const
{
    float det = m00_ * m11_ * m22_ +
                m10_ * m21_ * m02_ +
                m20_ * m01_ * m12_ -
                m20_ * m11_ * m02_ -
                m10_ * m01_ * m22_ -
                m00_ * m21_ * m12_;

    float invDet = 1.0f / det;

    return Matrix3(
        (m11_ * m22_ - m21_ * m12_) * invDet,
        -(m01_ * m22_ - m21_ * m02_) * invDet,
        (m01_ * m12_ - m11_ * m02_) * invDet,
        -(m10_ * m22_ - m20_ * m12_) * invDet,
        (m00_ * m22_ - m20_ * m02_) * invDet,
        -(m00_ * m12_ - m10_ * m02_) * invDet,
        (m10_ * m21_ - m20_ * m11_) * invDet,
        -(m00_ * m21_ - m20_ * m01_) * invDet,
        (m00_ * m11_ - m10_ * m01_) * invDet
    );
}

Matrix3 Combine(const Matrix3 mat[3], const Vector3& weight)
{
    return mat[0] * weight.x_ + mat[1] * weight.y_ + mat[2] * weight.z_;
}

// -------------------------------------------------------------------------------------

const Matrix4 Matrix4::Identify;

Matrix4 Matrix4::FromScale(const Vector3 &scale)
{
    Matrix4 mat;
    assert(scale.x_ != 0 && scale.y_ != 0 && scale.z_ != 0);
    mat.m00_ = scale.x_;
    mat.m11_ = scale.y_;
    mat.m22_ = scale.z_;

    return mat;
}

Matrix4 Matrix4::FromRotation(const Quat &rotation)
{
    return Matrix4(rotation.RotationMatrix());
}

Matrix4 Matrix4::FromTranslate(const Vector3 &translate)
{
    Matrix4 mat;
    mat.m03_ = translate.x_;
    mat.m13_ = translate.y_;
    mat.m23_ = translate.z_;
    return mat;
}

Matrix4 Matrix4::FromTRS(const Vector3 &translate, const Quat &rotation, const Vector3 &scale)
{
    Matrix4 T = Matrix4::FromTranslate(translate);
    Matrix4 R = Matrix4::FromRotation(rotation);
    Matrix4 S = Matrix4::FromScale(scale);

    return T * R * S;
}

Matrix4 Matrix4::LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
{
    Vector3 zAxis = (eye - target).Normalized();
    Vector3 xAxis = up.Cross(zAxis).Normalized();
    Vector3 yAxis = zAxis.Cross(xAxis);

    Matrix4 mat;
    mat.m00_ = xAxis.x_;
    mat.m01_ = xAxis.y_;
    mat.m02_ = xAxis.z_;

    mat.m10_ = yAxis.x_;
    mat.m11_ = yAxis.y_;
    mat.m12_ = yAxis.z_;

    mat.m10_ = zAxis.x_;
    mat.m11_ = zAxis.y_;
    mat.m12_ = zAxis.z_;

    mat.m03_ = -xAxis.Dot(eye);
    mat.m13_ = -yAxis.Dot(eye);
    mat.m23_ = -zAxis.Dot(eye);

    return mat;
}

Matrix4 Matrix4::Orthographic(float right, float top, float near, float far)
{
    float zRange = far - near;
    Matrix4 mat;
    assert(right > 0 && top > 0 && zRange > 0);

    mat.m00_ = 1 / right;
    mat.m11_ = 1 / top;
    mat.m22_ = -2 / zRange;
    mat.m23_ = -(far + near) / zRange;

    return mat;
}

Matrix4 Matrix4::Perspective(float yFov, float aspect, float near, float far)
{
    float zRange = far - near;
    Matrix4 mat;
    assert(yFov > 0 && aspect > 0);
    assert(near > 0 && far > 0 && zRange > 0);

    mat.m11_ = 1 / tanf(yFov / 2);
    mat.m00_ = mat.m11_ / aspect;
    mat.m22_ = -(near + far) / zRange;
    mat.m23_ = -2 * far * near / zRange;
    mat.m32_ = -1;
    mat.m33_ = 0;

    return mat;
}

Matrix4 Matrix4::operator+(const Matrix4 &v) const
{
    return Matrix4(
        m00_ + v.m00_,
        m01_ + v.m01_,
        m02_ + v.m02_,
        m03_ + v.m03_,
        m10_ + v.m10_,
        m11_ + v.m11_,
        m12_ + v.m12_,
        m13_ + v.m13_,
        m20_ + v.m20_,
        m21_ + v.m21_,
        m22_ + v.m22_,
        m23_ + v.m23_,
        m30_ + v.m30_,
        m31_ + v.m31_,
        m32_ + v.m32_,
        m33_ + v.m33_
    );
}

Matrix4 Matrix4::operator -(const Matrix4& v) const
{
    return Matrix4(
        m00_ - v.m00_,
        m01_ - v.m01_,
        m02_ - v.m02_,
        m03_ - v.m03_,
        m10_ - v.m10_,
        m11_ - v.m11_,
        m12_ - v.m12_,
        m13_ - v.m13_,
        m20_ - v.m20_,
        m21_ - v.m21_,
        m22_ - v.m22_,
        m23_ - v.m23_,
        m30_ - v.m30_,
        m31_ - v.m31_,
        m32_ - v.m32_,
        m33_ - v.m33_
    );
}

Matrix4 Matrix4::operator *(float factor) const
{
    return Matrix4(
        m00_ * factor,
        m01_ * factor,
        m02_ * factor,
        m03_ * factor,
        m10_ * factor,
        m11_ * factor,
        m12_ * factor,
        m13_ * factor,
        m20_ * factor,
        m21_ * factor,
        m22_ * factor,
        m23_ * factor,
        m30_ * factor,
        m31_ * factor,
        m32_ * factor,
        m33_ * factor
    );
}

Matrix4 Matrix4::operator *(const Matrix4& m) const
{
    return Matrix4(
        m00_ * m.m00_ + m01_ * m.m10_ + m02_ * m.m20_ + m03_ * m.m30_,
        m00_ * m.m01_ + m01_ * m.m11_ + m02_ * m.m21_ + m03_ * m.m31_,
        m00_ * m.m02_ + m01_ * m.m12_ + m02_ * m.m22_ + m03_ * m.m32_,
        m00_ * m.m03_ + m01_ * m.m13_ + m02_ * m.m23_ + m03_ * m.m33_,
        m10_ * m.m00_ + m11_ * m.m10_ + m12_ * m.m20_ + m13_ * m.m30_,
        m10_ * m.m01_ + m11_ * m.m11_ + m12_ * m.m21_ + m13_ * m.m31_,
        m10_ * m.m02_ + m11_ * m.m12_ + m12_ * m.m22_ + m13_ * m.m32_,
        m10_ * m.m03_ + m11_ * m.m13_ + m12_ * m.m23_ + m13_ * m.m33_,
        m20_ * m.m00_ + m21_ * m.m10_ + m22_ * m.m20_ + m23_ * m.m30_,
        m20_ * m.m01_ + m21_ * m.m11_ + m22_ * m.m21_ + m23_ * m.m31_,
        m20_ * m.m02_ + m21_ * m.m12_ + m22_ * m.m22_ + m23_ * m.m32_,
        m20_ * m.m03_ + m21_ * m.m13_ + m22_ * m.m23_ + m23_ * m.m33_,
        m30_ * m.m00_ + m31_ * m.m10_ + m32_ * m.m20_ + m33_ * m.m30_,
        m30_ * m.m01_ + m31_ * m.m11_ + m32_ * m.m21_ + m33_ * m.m31_,
        m30_ * m.m02_ + m31_ * m.m12_ + m32_ * m.m22_ + m33_ * m.m32_,
        m30_ * m.m03_ + m31_ * m.m13_ + m32_ * m.m23_ + m33_ * m.m33_
    );
}

Vector4 Matrix4::operator *(const Vector4& v) const
{
    return Vector4(
        m00_ * v.x_ + m01_ * v.y_ + m02_ * v.z_ + m03_ * v.w_,
        m10_ * v.x_ + m11_ * v.y_ + m12_ * v.z_ + m13_ * v.w_,
        m20_ * v.x_ + m21_ * v.y_ + m22_ * v.z_ + m23_ * v.w_,
        m30_ * v.x_ + m31_ * v.y_ + m32_ * v.z_ + m33_ * v.w_
    );
}

Matrix4 Matrix4::Inverse() const
{
    float v0 = m20_ * m31_ - m21_ * m30_;
    float v1 = m20_ * m32_ - m22_ * m30_;
    float v2 = m20_ * m33_ - m23_ * m30_;
    float v3 = m21_ * m32_ - m22_ * m31_;
    float v4 = m21_ * m33_ - m23_ * m31_;
    float v5 = m22_ * m33_ - m23_ * m32_;

    float i00 = (v5 * m11_ - v4 * m12_ + v3 * m13_);
    float i10 = -(v5 * m10_ - v2 * m12_ + v1 * m13_);
    float i20 = (v4 * m10_ - v2 * m11_ + v0 * m13_);
    float i30 = -(v3 * m10_ - v1 * m11_ + v0 * m12_);

    float invDet = 1.0f / (i00 * m00_ + i10 * m01_ + i20 * m02_ + i30 * m03_);

    i00 *= invDet;
    i10 *= invDet;
    i20 *= invDet;
    i30 *= invDet;

    float i01 = -(v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
    float i11 = (v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
    float i21 = -(v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
    float i31 = (v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;

    v0 = m10_ * m31_ - m11_ * m30_;
    v1 = m10_ * m32_ - m12_ * m30_;
    v2 = m10_ * m33_ - m13_ * m30_;
    v3 = m11_ * m32_ - m12_ * m31_;
    v4 = m11_ * m33_ - m13_ * m31_;
    v5 = m12_ * m33_ - m13_ * m32_;

    float i02 = (v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
    float i12 = -(v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
    float i22 = (v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
    float i32 = -(v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;

    v0 = m21_ * m10_ - m20_ * m11_;
    v1 = m22_ * m10_ - m20_ * m12_;
    v2 = m23_ * m10_ - m20_ * m13_;
    v3 = m22_ * m11_ - m21_ * m12_;
    v4 = m23_ * m11_ - m21_ * m13_;
    v5 = m23_ * m12_ - m22_ * m13_;

    float i03 = -(v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
    float i13 = (v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
    float i23 = -(v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
    float i33 = (v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;

    return Matrix4(
        i00, i01, i02, i03,
        i10, i11, i12, i13,
        i20, i21, i22, i23,
        i30, i31, i32, i33);
}

Matrix4 Matrix4::Transpose() const
{
    return Matrix4(
        m00_, m10_, m20_, m30_,
        m01_, m11_, m21_, m31_,
        m02_, m12_, m22_, m32_,
        m03_, m13_, m23_, m33_
    );
}

Matrix4 Combine(const Matrix4 mat[3], const Vector4& weight)
{
    return mat[0] * weight.x_ + mat[1] * weight.y_ + mat[2] * weight.z_ + mat[3] * weight.z_;
}
