//
// Created by luchu on 2022/3/17.
//
#include <cassert>
#include <cstdlib>
#include "Image.h"
#include "Texture.h"


Texture::Texture(int width, int height)
    : width_(width)
    , height_(height)
{
    unsigned buffSize = sizeof(Color) * width * height;
    assert(width > 0 && height > 0);

    buffer_ = (Color*) malloc(buffSize);
}

Texture::~Texture()
{
    free(buffer_);
    buffer_ = nullptr;
}

void Texture::SetDataFromLDRImage(const Image &image)
{
    int numPixels = image.Width() * image.Height();

    unsigned char* ldrBuffer = image.GetLDRBuffer();

    for (int i = 0; i < numPixels; ++i)
    {
        unsigned char* pixel = &ldrBuffer[i * image.Channels()];
        Color texel(0, 0, 0, 1);

        // Luminance
        if (image.Channels() == 1)
        {
            texel.x_ = texel.y_ = texel.z_ = UCharToFloat(pixel[0]);
        }
        // Luminance alpha
        else if (image.Channels() == 2)
        {
            texel.x_ = texel.y_ = texel.z_ = UCharToFloat(pixel[0]);
            texel.w_ = UCharToFloat(pixel[1]);
        }
        // RGB
        else if (image.Channels() == 3)
        {
            texel.x_ = UCharToFloat(pixel[0]);
            texel.y_ = UCharToFloat(pixel[1]);
            texel.z_ = UCharToFloat(pixel[2]);
        }
        // RGBA
        else
        {
            texel.x_ = UCharToFloat(pixel[0]);
            texel.y_ = UCharToFloat(pixel[1]);
            texel.z_ = UCharToFloat(pixel[2]);
            texel.w_ = UCharToFloat(pixel[3]);
        }

        buffer_[i] = texel;
    }
}