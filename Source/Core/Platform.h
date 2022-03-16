//
// Created by luchu on 2022/3/16.
//

#pragma once

class Window;

enum KeyCode
{
    KEY_A,
    KEY_D,
    KEY_S,
    KEY_W,
    KEY_SPACE,
    KEY_NUM
};

enum Button
{
    BUTTON_L,
    BUTTON_R,
    BUTTON_NUM
};

class Platform
{
public:
    void Initialize();

    void Terminate();

    void OpenWindow(const char* title, int width, int height);

    bool WindowShouldClose();

    float GetTime();

    static Platform& Get() { return instance_; }

private:
    bool initialized_ {};
    Window* window_ {};
    double initialTime_ = -1;

    static Platform instance_;
};
