//
// Created by luchu on 2022/3/16.
//

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <direct.h>

#include "../Core/Image.h"
#include "../Core/Platform.h"
#include "../Core/Macro.h"

#ifdef UNICODE
    static const wchar_t *const WINDOW_CLASS_NAME = L"Class";
    static const wchar_t *const WINDOW_ENTRY_NAME = L"Entry";
#else
    static const char *const WINDOW_CLASS_NAME = "Class";
    static const char *const WINDOW_ENTRY_NAME = "Entry";
#endif

static LRESULT CALLBACK ProcessWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static void RegisterWindowClass()
{
    ATOM classAtom;
    WNDCLASS wndClass;

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = ProcessWndMessage;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = GetModuleHandle(nullptr);
    wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = nullptr;
    wndClass.lpszClassName = WINDOW_CLASS_NAME;

    classAtom = RegisterClass(&wndClass);
    assert(classAtom != 0);
    UNUSED_VAR(classAtom);
}

static void UnRegisterWindowClass()
{
    UnregisterClass(WINDOW_CLASS_NAME, GetModuleHandle(nullptr));
}

static void InitializePath()
{
#ifdef UNICODE
    wchar_t path[MAX_PATH];
    GetModuleFileName(nullptr, path, MAX_PATH);
    *wcsrchr(path, L'\\') = L'\0';
    _wchdir(path);
    _wchdir(L"Assets");
#else
    char path[MAX_PATH];
    GetModuleFileName(nullptr, path, MAX_PATH);
    *strrchr(path, '\\') = '\0';
    _chdir(path);
    _chdir("Assets");
#endif
}

static double GetNativeTime()
{
    static double period = -1;
    LARGE_INTEGER counter;
    if (period < 0)
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        period = 1 / (double)frequency.QuadPart;
    }
    QueryPerformanceCounter(&counter);
    return counter.QuadPart * period;
}

Platform Platform::instance_;


void Platform::Initialize()
{
    assert(!initialized_);

    initialized_ = true;
    RegisterWindowClass();
    InitializePath();

    srand((unsigned) time(nullptr));
}

void Platform::Terminate()
{
    assert(initialized_);

    UnRegisterWindowClass();
    initialized_ = false;
}

class Window
{
public:
    Window (const char* title, int width, int height)
    {
        DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
        RECT rect;

        rect.left = 0;
        rect.top = 0;
        rect.right = width;
        rect.bottom = height;
        AdjustWindowRect(&rect, style, 0);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;

        handle_ = CreateWindow(WINDOW_CLASS_NAME, title, style, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                               nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
        assert(handle_ != nullptr);

        width_ = width;
        height_ = height;

        CreateSurface();

        ShowWindow(handle_, SW_SHOW);
    }

    void SetShouldClose(bool shouldClose) { shouldClose_ = shouldClose; }
    bool ShouldClose() const { return shouldClose_; }

    void HandleKeyMessage(WPARAM virtualKey, bool pressed)
    {
        KeyCode key;
        switch (virtualKey)
        {
            case 'A': key = KEY_A; break;
            case 'D': key = KEY_D; break;
            case 'W': key = KEY_W; break;
            case 'S': key = KEY_S; break;
            case VK_SPACE: key = KEY_SPACE; break;
            case VK_ESCAPE: key= KEY_ESCAPE; break;
            default: key = KEY_NUM; break;
        }

        if (key < KEY_NUM)
        {
            keys_[key] = pressed;
            auto const& callbacks = Platform::Get().keycallbacks_;
            if (!callbacks.empty())
            {
                for (auto const& cb : callbacks)
                    cb(key, pressed);
            }
        }
    }

    void HandleButtonMessage(Button button, bool pressed)
    {
        buttons_[button] = pressed;

        auto const& callbacks = Platform::Get().buttoncallbacks_;
        if (!callbacks.empty())
        {
            for (auto const& cb : callbacks)
                cb(button, pressed);
        }
    }

    void HandleScrollMessage(float offset)
    {
        auto const& callbacks = Platform::Get().scrollcallbacks_;
        if (!callbacks.empty())
        {
            for (auto const& cb : callbacks)
                cb(offset);
        }
    }

private:

    void CreateSurface()
    {
        surface_ = new Image(width_, height_, 4, FMT_LDR);

        HDC windowDC = GetDC(handle_);
        memoryDC_ = CreateCompatibleDC(windowDC);
        ReleaseDC(handle_, windowDC);

        BITMAPINFOHEADER biHeader;
        memset(&biHeader, 0, sizeof(BITMAPINFOHEADER));
        biHeader.biSize = sizeof(BITMAPINFOHEADER);
        biHeader.biWidth = width_;
        biHeader.biHeight = -height_;  /* top-down */
        biHeader.biPlanes = 1;
        biHeader.biBitCount = 32;
        biHeader.biCompression = BI_RGB;

        unsigned char* bufferAddress;
        HBITMAP dibBitmap = CreateDIBSection(memoryDC_, (BITMAPINFO*)&biHeader,DIB_RGB_COLORS, (void**)&bufferAddress, nullptr, 0);
        surface_->SetLDRBuffer(bufferAddress);

        assert(dibBitmap != nullptr);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memoryDC_, dibBitmap);
        DeleteObject(oldBitmap);
    }

    HWND handle_;
    HDC memoryDC_{};
    Image* surface_{};

    bool shouldClose_{};
    bool keys_[KEY_NUM]{};
    bool buttons_[BUTTON_NUM]{};

    int width_;
    int height_;
};

void Platform::OpenWindow(const char* title, int width, int height)
{
    window_ = new Window(title, width, height);
}

bool Platform::WindowShouldClose() const
{
    return window_ && window_->ShouldClose();
}

void Platform::SetWindowShouldClose(bool close)
{
    if (window_)
        window_->SetShouldClose(true);
}

float Platform::GetTime()
{
    if (initialTime_ < 0)
    {
        initialTime_ = GetNativeTime();
    }
    return (float)(GetNativeTime() - initialTime_);
}

void Platform::PollInputEvents()
{
    MSG message;
    while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

static LRESULT CALLBACK ProcessWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window* window = Platform::Get().GetWindow();
    if (window == nullptr)
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    switch (uMsg)
    {
        case WM_CLOSE:
            window->SetShouldClose(true);
            return 0;

        case WM_KEYDOWN:
            window->HandleKeyMessage(wParam, true);
            return 0;

        case WM_KEYUP:
            window->HandleKeyMessage(wParam, false);
            return 0;

        case WM_LBUTTONDOWN:
            window->HandleButtonMessage(BUTTON_L, true);
            return 0;

        case WM_RBUTTONDOWN:
            window->HandleButtonMessage(BUTTON_R, true);
            return 0;

        case WM_LBUTTONUP:
            window->HandleButtonMessage(BUTTON_L, false);
            return 0;

        case WM_RBUTTONUP:
            window->HandleButtonMessage(BUTTON_R, false);
            return 0;

        case WM_MOUSEHWHEEL:
            float offset = GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
            window->HandleScrollMessage(offset);
            return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}