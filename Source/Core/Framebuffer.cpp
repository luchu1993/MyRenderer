//
// Created by luchu on 2022/3/16.
//
#include <cstdlib>
#include <cassert>

#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height)
    : width_(width)
    , height_(height)
{
    int colorBufferSize = width * height * 4;
    int depthBufferSize = sizeof (float) * width * height;

    Vector4 defaultColor(0, 0, 0, 1);
    float defaultDepth = 1.0f;

    assert(width > 0 && height > 0);

    colorBuffer_ = (unsigned char*) malloc(colorBufferSize);
    depthBuffer_ = (float *) malloc(depthBufferSize);

    ClearColorBuffer(defaultColor);
    ClearDepthBuffer(defaultDepth);
}

Framebuffer::~Framebuffer()
{
    free(colorBuffer_);
    free(depthBuffer_);
}

void Framebuffer::ClearColorBuffer(const Vector4& color)
{
    int numPixels = width_ * height_;
    for (int i = 0; i < numPixels; ++i)
    {
        colorBuffer_[i * 4 + 0] = FloatToUChar(color.x_);
        colorBuffer_[i * 4 + 1] = FloatToUChar(color.y_);
        colorBuffer_[i * 4 + 2] = FloatToUChar(color.z_);
        colorBuffer_[i * 4 + 3] = FloatToUChar(color.w_);
    }
}

void Framebuffer::ClearDepthBuffer(float depth)
{
    int numPixels = width_ * height_;
    for (int i = 0; i < numPixels; ++i)
    {
        depthBuffer_[i] = depth;
    }
}