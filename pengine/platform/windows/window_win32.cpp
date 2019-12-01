#include "window_win32.h"

namespace PEngine
{
    Window* Window::Create(const WindowProps& props)
    {
        return new Win32Window(props);
    }

    Win32Window::Win32Window(const WindowProps& props)
    {
        Win32Window::Init(props);
    }

    void Win32Window::Init(const WindowProps& props)
    {
        const auto hInstance = GetModuleHandleW(nullptr);

        const auto className = reinterpret_cast<LPCSTR>("PEngine");

        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = className;
        //wc.style = CS_OWNDC;

        RegisterClass(&wc);

        const auto hwnd = CreateWindowEx(
            0,
            className,
            reinterpret_cast<LPCSTR>(props.Title.c_str()),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            props.Width,
            props.Height,
            nullptr,
            nullptr,
            hInstance,
            nullptr);

        if (hwnd == nullptr)
        {
            return;
        }

        ShowWindow(hwnd, SW_SHOW);
    }

    bool Win32Window::OnUpdate()
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return true;
    }

    LRESULT CALLBACK WindowProc(const HWND hwnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:;
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
