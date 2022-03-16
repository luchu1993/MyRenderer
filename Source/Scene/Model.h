//
// Created by luchu on 2022/3/16.
//

#pragma once
#include "../Math/Matrix.h"

class Mesh;
class Skeleton;


class Model
{
public:
    void Update();

    void Render(bool shadowPass);


private:
    Mesh* mesh_;
    Skeleton* skeleton_;
    Matrix4 transform_;

    bool opaque_;
    float distance_;
};
