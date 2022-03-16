//
// Created by luchu on 2022/3/16.
//

#pragma once
#include "Vector.h"

class Quat;
class Matrix4;

class Matrix3
{
public:
    Matrix3()
        : m00_(1.0f)
        , m01_(0.0f)
        , m02_(0.0f)
        , m10_(0.0f)
        , m11_(1.0f)
        , m12_(0.0f)
        , m20_(0.0f)
        , m21_(0.0f)
        , m22_(1.0f)
    {
    }

    Matrix3(float v00, float v01, float v02,
            float v10, float v11, float v12,
            float v20, float v21, float v22)
        : m00_(v00)
        , m01_(v01)
        , m02_(v02)
        , m10_(v10)
        , m11_(v11)
        , m12_(v12)
        , m20_(v20)
        , m21_(v21)
        , m22_(v22)
    {
    }

    Matrix3(const Vector3& c0, const Vector3& c1, const Vector3 c2)
        : m00_(c0.x_)
        , m01_(c1.x_)
        , m02_(c2.x_)
        , m10_(c0.y_)
        , m11_(c1.y_)
        , m12_(c2.y_)
        , m20_(c0.z_)
        , m21_(c1.z_)
        , m22_(c2.z_)
    {
    }

    Matrix3 operator+(const Matrix3& m) const;

    Matrix3 operator-(const Matrix3& v) const;

    Matrix3 operator*(float factor) const;

    Vector3 operator*(const Vector3& v) const;

    Matrix3 operator*(const Matrix3& m) const;

    Matrix3 Transpose() const;

    Matrix3 Inverse() const;


    explicit Matrix3(const Matrix4& m);

    float m00_;
    float m01_;
    float m02_;
    float m10_;
    float m11_;
    float m12_;
    float m20_;
    float m21_;
    float m22_;

    const static Matrix3 Identify;
};

Matrix3 Combine(const Matrix3 mat[3], const Vector3& weight);


class Matrix4
{
public:
public:
    Matrix4()
        : m00_(1.0f)
        , m01_(0.0f)
        , m02_(0.0f)
        , m03_(0.0f)
        , m10_(0.0f)
        , m11_(1.0f)
        , m12_(0.0f)
        , m13_(0.0f)
        , m20_(0.0f)
        , m21_(0.0f)
        , m22_(1.0f)
        , m23_(0.0f)
        , m30_(0.0f)
        , m31_(0.0f)
        , m32_(0.0f)
        , m33_(1.0f)
    {
    }

    explicit Matrix4(const Matrix3& matrix)
        : m00_(matrix.m00_)
        , m01_(matrix.m01_)
        , m02_(matrix.m02_)
        , m03_(0.0f)
        , m10_(matrix.m10_)
        , m11_(matrix.m11_)
        , m12_(matrix.m12_)
        , m13_(0.0f)
        , m20_(matrix.m20_)
        , m21_(matrix.m21_)
        , m22_(matrix.m22_)
        , m23_(0.0f)
        , m30_(0.0f)
        , m31_(0.0f)
        , m32_(0.0f)
        , m33_(1.0f)
    {
    }

    Matrix4(float v00, float v01, float v02, float v03,
            float v10, float v11, float v12, float v13,
            float v20, float v21, float v22, float v23,
            float v30, float v31, float v32, float v33) noexcept
        : m00_(v00)
        , m01_(v01)
        , m02_(v02)
        , m03_(v03)
        , m10_(v10)
        , m11_(v11)
        , m12_(v12)
        , m13_(v13)
        , m20_(v20)
        , m21_(v21)
        , m22_(v22)
        , m23_(v23)
        , m30_(v30)
        , m31_(v31)
        , m32_(v32)
        , m33_(v33)
    {
    }

    Matrix4 operator+(const Matrix4& v) const;

    Matrix4 operator-(const Matrix4& v) const;

    Matrix4 operator*(const Matrix4& m) const;

    Vector4 operator*(const Vector4& v) const;

    Matrix4 operator*(float factor) const;

    Matrix4 Inverse() const;

    Matrix4 Transpose() const;

    static Matrix4 FromTranslate(Vector3 const& translate);

    static Matrix4 FromRotation(const Quat& rotation);

    static Matrix4 FromScale(const Vector3& scale);

    static Matrix4 FromTRS(Vector3 const& translate, const Quat& rotation, const Vector3& scale);

    static Matrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

    static Matrix4 Orthographic(float right, float top, float near, float far);

    static Matrix4 Perspective(float yFov, float aspect, float near, float far);
    
    float m00_;
    float m01_;
    float m02_;
    float m03_;
    float m10_;
    float m11_;
    float m12_;
    float m13_;
    float m20_;
    float m21_;
    float m22_;
    float m23_;
    float m30_;
    float m31_;
    float m32_;
    float m33_;

    const static Matrix4 Identify;
};

Matrix4 Combine(const Matrix4 mat[3], const Vector4& weight);
