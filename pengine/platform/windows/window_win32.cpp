#include "window_win32.h"

#include <iostream>
#include <glad/glad.h>

#pragma comment(lib, "opengl32.lib")

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
        wc.style = CS_OWNDC;

        RegisterClass(&wc);

        const auto hWnd = CreateWindowEx(
            0,
            className,
            reinterpret_cast<LPCSTR>(props.Title.c_str()),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<int>(props.Width),
            static_cast<int>(props.Height),
            nullptr,
            nullptr,
            hInstance,
            nullptr);

        if (hWnd == nullptr)
        {
            return;
        }

        ShowWindow(hWnd, SW_SHOW);
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

    void Win32Window::OnDestroy()
    {
    }

    LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_CREATE: {
            PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
                PFD_TYPE_RGBA, // The kind of framebuffer. RGBA or palette.
                32, // Colordepth of the framebuffer.
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                24, // Number of bits for the depthbuffer
                8, // Number of bits for the stencilbuffer
                0, // Number of Aux buffers in the framebuffer.
                PFD_MAIN_PLANE,
                0,
                0,
                0,
                0
            };

            const auto hdc = GetDC(hWnd);

            const auto pixelFormat = ChoosePixelFormat(hdc, &pfd);
            SetPixelFormat(hdc, pixelFormat, &pfd);

            const auto tempContext = wglCreateContext(hdc);
            wglMakeCurrent(hdc, tempContext);

            if (!gladLoadGL())
            {
                std::cout << "Unable to load OpenGL" << std::endl;
            }

            std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

            wglDeleteContext(tempContext);
        }
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }
}
