//
// Created by luchu on 2022/3/16.
//

#include "Camera.h"

static const float NEAR = 0.1f;
static const float FAR = 10000;
static const float FOV = TO_RADIANS(60);

Camera::Camera(const Vector3 &position, const Vector3 &target, float aspect)
    : position_(position)
    , target_(target)
    , aspect_(aspect)
{
}


void Camera::SetTransform(const Vector3 &position, const Vector3 &target)
{
    position_ = position;
    target_ = target;
}

void Camera::UpdateTransform()
{
    Vector3 fromTarget = position_ - target_;
    Vector3 fromCamera = -fromTarget;
}


Vector3 Camera::GetForward() const
{
    return (target_ - position_).Normalized();
}

Matrix4 Camera::GetViewMatrix() const
{
    return Matrix4::LookAt(position_, target_, Vector3::Up);
}

Matrix4 Camera::GetProjectionMatrix() const
{
    return Matrix4::Perspective(FOV, aspect_, NEAR, FAR);
}