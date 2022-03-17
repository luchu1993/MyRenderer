//
// Created by luchu on 2022/3/17.
//

#pragma once
#include "../Math/Vector.h"

class Image;

class Texture
{
public:
    Texture(int width, int height);

    ~Texture();

    void SetDataFromLDRImage(const Image& image);

    void SetDataFromHDRImage(const Image& image);

private:
    int width_;
    int height_;
    Color* buffer_;
};


class CubeMap
{
public:

private:
    Texture* faces_[6];
};

