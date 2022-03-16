//
// Created by luchu on 2022/3/16.
//

#pragma once

#include "../Math/Vector.h"
#include "../Math/Matrix.h"


class Camera
{
public:
    Camera(const Vector3& position, const Vector3& target, float aspect);

    void SetTransform(const Vector3& position, const Vector3& target);

    Vector3 GetPosition() const { return position_; }

    float GetAspect() const { return aspect_;}

    Vector3 GetForward() const;

    Matrix4 GetViewMatrix() const;

    Matrix4 GetProjectionMatrix() const;

    void UpdateTransform();

private:
    Vector3 position_;
    Vector3 target_;
    float aspect_;
};
