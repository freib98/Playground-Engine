#include "window_win32.h"

#include <glad/glad_wgl.h>

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

    bool Win32Window::OnUpdate()
    {
        SwapBuffers(GetDC(_hwnd));
        // Todo - investigate SwapBuffers without glFinish
        glFinish();

        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return false;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        return true;
    }

    void Win32Window::OnDestroy()
    {
    }

    void Win32Window::Init(const WindowProps& props)
    {
        RegisterWindowClass();

        CreateHelperWindow();

        CreateNativeWindow(props);

        InitWgl();

        CreateContextWgl();

        ShowWindow(_hwnd, SW_SHOW);
    }

    void Win32Window::RegisterWindowClass() const
    {
        WNDCLASSEXW wc = {};
        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = static_cast<WNDPROC>(WindowProc);
        wc.hInstance = GetModuleHandleW(nullptr);
        wc.lpszClassName = _wndClassName;

        // Todo - check register return value
        RegisterClassExW(&wc);
    }

    void Win32Window::CreateHelperWindow()
    {
        _helperHwnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,
                                      _wndClassName,
                                      L"helper window",
                                      WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                                      0,
                                      0,
                                      1,
                                      1,
                                      nullptr,
                                      nullptr,
                                      GetModuleHandleW(nullptr),
                                      nullptr);

        // Todo - check hwnd

        ShowWindow(_helperHwnd, SW_HIDE);

        MSG msg;

        while (PeekMessageW(&msg, _helperHwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    void Win32Window::CreateNativeWindow(const WindowProps& props)
    {
        const auto wTitle = WideStringFromUtf8(props.Title);

        _hwnd = CreateWindowExW(
            0,
            _wndClassName,
            wTitle.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<int>(props.Width),
            static_cast<int>(props.Height),
            nullptr,
            nullptr,
            GetModuleHandleW(nullptr),
            nullptr);

        // Todo - check hwnd
    }

    void Win32Window::InitWgl() const
    {
        // Creating a dummy context to load the real OpenGL context

        const auto dc = GetDC(_helperHwnd);

        PIXELFORMATDESCRIPTOR pfd;
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 24;

        SetPixelFormat(dc, ChoosePixelFormat(dc, &pfd), &pfd);

        const auto rc = wglCreateContext(dc);

        const auto pdc = wglGetCurrentDC();
        const auto prc = wglGetCurrentContext();

        if (!wglMakeCurrent(dc, rc))
        {
            wglMakeCurrent(pdc, prc);
            wglDeleteContext(rc);
            return;
        }

        gladLoadWGL(dc);

        wglMakeCurrent(pdc, prc);
        wglDeleteContext(rc);

        ReleaseDC(_helperHwnd, dc);
        //DestroyWindow(_helperHwnd);

        // Todo - check all function return values
    }

    void Win32Window::CreateContextWgl() const
    {
        const auto dc = GetDC(_hwnd);

        // clang-format off
        const int attributesAttribs[] = {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
            WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
            WGL_COLOR_BITS_ARB, 32,
            WGL_ALPHA_BITS_ARB, 8,
            WGL_DEPTH_BITS_ARB, 24,
            WGL_STENCIL_BITS_ARB, 8,
            WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
            WGL_SAMPLES_ARB, 4,
            0
        };
        // clang-format on

        int pixelFormat;
        UINT numFormats;

        const auto status = wglChoosePixelFormatARB(dc, attributesAttribs, nullptr, 1, &pixelFormat, &numFormats);

        if (status == false || numFormats == 0)
        {
            // Todo - error
            return;
        }

        PIXELFORMATDESCRIPTOR pfd;
        DescribePixelFormat(dc, pixelFormat, sizeof(pfd), &pfd);
        SetPixelFormat(dc, pixelFormat, &pfd);

        // clang-format off
        GLint contextAttributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 5,
            WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        // clang-format on

        const auto rc = wglCreateContextAttribsARB(dc, nullptr, contextAttributes);

        wglMakeCurrent(dc, rc);

        if (wglSwapIntervalEXT)
        {
            wglSwapIntervalEXT(1);
        }

        gladLoadGL();
    }

    std::wstring Win32Window::WideStringFromUtf8(const std::string& source)
    {
        const auto slength = static_cast<int>(source.length()) + 1;
        const auto len = MultiByteToWideChar(CP_ACP, 0, source.c_str(), slength, nullptr, 0);
        const auto buf = new wchar_t[len];

        MultiByteToWideChar(CP_ACP, 0, source.c_str(), slength, buf, len);

        std::wstring r(buf);

        delete[] buf;
        return r;
    }

    LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }
}
