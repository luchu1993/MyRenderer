//
// Created by luchu on 2022/3/16.
//

#pragma once
#include <vector>
#include <functional>

class Window;

enum KeyCode
{
    KEY_A,
    KEY_D,
    KEY_S,
    KEY_W,
    KEY_SPACE,
    KEY_ESCAPE,
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
    friend class Window;

    using KeyCallback = std::function<void(const KeyCode&, bool)>;
    using ButtonCallback = std::function<void(const Button&, bool)>;
    using ScrollCallback = std::function<void(float)>;
public:
    void Initialize();

    void Terminate();

    void OpenWindow(const char* title, int width, int height);

    bool WindowShouldClose() const;

    void SetWindowShouldClose(bool close);

    float GetTime();

    void PollInputEvents();

    Window* GetWindow() const { return window_; }

    void RegisterKeyCallback( const KeyCallback& callback) { keycallbacks_.emplace_back(callback); }

    void RegisterButtonCallback( const ButtonCallback& callback) { buttoncallbacks_.emplace_back(callback); }

    void RegisterScrollCallback( const ScrollCallback & callback) { scrollcallbacks_.emplace_back(callback); }

    static Platform& Get() { return instance_; }

private:
    bool initialized_ {};
    Window* window_ {};
    double initialTime_ = -1;

    std::vector<KeyCallback> keycallbacks_;
    std::vector<ButtonCallback> buttoncallbacks_;
    std::vector<ScrollCallback> scrollcallbacks_;

    static Platform instance_;
};
