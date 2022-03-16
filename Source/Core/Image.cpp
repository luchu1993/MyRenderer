//
// Created by luchu on 2022/3/16.
//
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "Image.h"

template <typename T>
static void Swap(T& a, T&b)
{
    T t = a;
    a = b;
    b = t;
}

Image::Image(int width, int height, int channels, Format format)
    : width_(width)
    , height_(height)
    , channels_(channels)
    , format_(format)
{
    assert(width > 0 && height > 0 && channels >= 1 && channels <= 4);
    assert(format == FMT_LDR || format == FMT_HDR);

    int numElems = width + height * channels;

    if (format_ == FMT_LDR)
    {
        int size = sizeof(unsigned char) * numElems;
        ldrBuffer_ = (unsigned char*) malloc(size);
        memset(ldrBuffer_, 0, size);
    }
    else
    {
        int size = sizeof(float) * numElems;
        hdrBuffer_ = (float*) malloc(size);
        memset(hdrBuffer_, 0, size);
    }
}

void Image::Load(const char *filename)
{

}

void Image::Save(const char *name)
{

}

void Image::SetLDRBuffer(unsigned char *buffer)
{
    if (ldrBuffer_ != nullptr)
    {
        free(ldrBuffer_);
        ldrBuffer_ = nullptr;
    }

    ldrBuffer_ = buffer;
}

Image::~Image()
{
    free(ldrBuffer_);
    free(hdrBuffer_);
}

unsigned char* Image::GetLDRPixel(int row, int col)
{
    int index = (row * width_ + col) * channels_;
    return &ldrBuffer_[index];
}

float* Image::GetHDRPixel(int row, int col)
{
    int index = (row * width_ + col) * channels_;
    return &hdrBuffer_[index];
}

void Image::FlipH()
{
    int halfWidth = width_ / 2;
    for (int r = 0; r < height_; ++r)
    {
        for (int c = 0; c < halfWidth; ++c)
        {
            int flippedCol = width_ - 1 - c;
            if (format_ == FMT_LDR)
            {
                unsigned char* pixel1 = GetLDRPixel(r, c);
                unsigned char* pixel2 = GetLDRPixel(r, flippedCol);
                for (int k = 0; k < channels_; ++k)
                    Swap(pixel1[k], pixel2[k]);
            }
            else
            {
                float * pixel1 = GetHDRPixel(r, c);
                float * pixel2 = GetHDRPixel(r, flippedCol);
                for (int k = 0; k < channels_; ++k)
                    Swap(pixel1[k], pixel2[k]);
            }
        }
    }
}

void Image::FlipV()
{
    int halfHeight = height_ / 2;
    for (int r = 0; r < halfHeight; r++)
    {
        for (int c = 0; c < width_; c++)
        {
            int flippedRow = height_ - 1 - r;
            if (format_ == FMT_LDR)
            {
                unsigned char *pixel1 = GetLDRPixel(r, c);
                unsigned char *pixel2 = GetLDRPixel(flippedRow, c);
                for (int k = 0; k < channels_; k++)
                    Swap(pixel1[k], pixel2[k]);
            }
            else
            {
                float *pixel1 = GetHDRPixel(r, c);
                float *pixel2 = GetHDRPixel(flippedRow, c);
                for (int k = 0; k < channels_; k++)
                    Swap(pixel1[k], pixel2[k]);
            }
        }
    }
}
