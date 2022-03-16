//
// Created by luchu on 2022/3/16.
//

#pragma once

#include <vector>
#include "../Math/Vector.h"

class Framebuffer;
class Texture;
class Model;


class Scene
{
public:
    void Load(const char* name);

private:
    Color background_;
    Model* skybox_;
    std::vector<Model*> models_;

    float ambientIntensity_;
    float punctualIntensity_;

    Framebuffer* shadowBuffer_;
    Texture* shadowMap_;
};
