//
// Created by luchu on 2022/3/16.
//

#pragma once

#include <vector>
#include "../Math/Vector.h"
#include "../Math/Matrix.h"

class VertexShader;
class PixelShader;
class Texture;

struct BlinnAttribs
{
    Vector3 position_;
    Vector3 texcoord_;
    Vector3 normal_;
    Vector4 joint_;
    Vector4 weight_;
};

struct BlinnVaryings
{
    Vector3 worldPosition_;
    Vector3 depthPosition;
    Vector2 texcoord_;
    Vector3 normal_;
};

struct BlinnUniforms
{
    Vector3 lightDir_;
    Vector3 cameraPos;
    Matrix4 modelMatrix_;
    Matrix3 normalMatrix_;
    Matrix4 lightVPMatrix;
    Matrix4 cameraVPMatrix;
    std::vector<Matrix4> jointMatrices_;
    std::vector<Matrix3> jointNormalMatrices_;
    Texture* shadowMap_;

    // surface parameters
    Vector4 baseColor_;
    float shininess_;
    Texture* diffuseMap_;
    Texture* specularMap_;
    Texture* emissionMap_;

    // render control
    float alphaCutoff_;
    bool shadowPass_;
};

class BlinnProgram
{
    BlinnProgram(VertexShader* vertexShader, PixelShader* pixelShader);

    ~BlinnProgram();

private:
    VertexShader* vertexShader_;
    PixelShader* pixelShader_;
    BlinnAttribs* attribs_[3];
    BlinnVaryings* varyings_;
    BlinnUniforms* uniforms_;
};
