#pragma once
#include <string>

#include "../Core/Api.h"

struct FrameInfo
{
    float frameTime_;
    float deltaTime_;
    Vector3 lightDir_;
};

class Blinn
{
public:
    explicit Blinn(const char* scene);

    void Initialize();
    void MainLoop();
    void Terminate();

private:
    void RenderOneFrame(const FrameInfo& frameInfo);
    void Present();
    void Update();

private:
    const char* sceneName_;
    Framebuffer* framebuffer_;
    Camera* camera_;
};