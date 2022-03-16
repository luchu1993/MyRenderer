//
// Created by luchu on 2022/3/16.
//

#pragma once

enum Format
{
    FMT_LDR,
    FMT_HDR
};

class Image
{
public:
    Image(int width, int height, int channels, Format format);

    ~Image();

    void Load(const char* filename);

    void Save(const char* name);

    void FlipH();

    void FlipV();

    void SetLDRBuffer(unsigned char* buffer);

    unsigned char* GetLDRPixel(int row, int col);

    float* GetHDRPixel(int row, int col);

private:
    int width_;
    int height_;
    int channels_;
    Format format_;
    unsigned char* ldrBuffer_ {};
    float* hdrBuffer_ {};
};
