//
// Created by luchu on 2022/3/16.
//

#pragma once

#include "../Math/Vector.h"

class Framebuffer
{
public:
    Framebuffer(int width, int height);

    ~Framebuffer();

    void ClearColorBuffer(Color const& color);

    void ClearDepthBuffer(float depth);

private:
    int width_;
    int height_;
    unsigned char* colorBuffer_;
    float* depthBuffer_;
};
