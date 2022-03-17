//
// Created by luchu on 2022/3/16.
//

#include "Blinn.h"

static const char *const WINDOW_TITLE = "Viewer";
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

Blinn::Blinn(const char *scene)
    : sceneName_(scene)
{
}

void Blinn::Initialize()
{
    Platform::Get().OpenWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    framebuffer_ = new Framebuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

    Platform::Get().RegisterKeyCallback([](const KeyCode& key, bool pressed)
    {
        Platform::Get().SetWindowShouldClose(key == KEY_ESCAPE);
    });
}

void Blinn::MainLoop()
{
    int frameCount = 0;
    float prevTime = Platform::Get().GetTime();

    while (!Platform::Get().WindowShouldClose())
    {
        float currentTime = Platform::Get().GetTime();
        float deltaTime = currentTime - prevTime;

        Update();

        FrameInfo frameInfo;
        frameInfo.frameTime_ = currentTime;
        frameInfo.deltaTime_ = deltaTime;

        RenderOneFrame(frameInfo);
        Present();

        frameCount += 1;
        prevTime = currentTime;

        Platform::Get().PollInputEvents();
    }
}

void Blinn::Update()
{

}

void Blinn::RenderOneFrame(const FrameInfo &frameInfo)
{

}

void Blinn::Present()
{

}

void Blinn::Terminate()
{

}
