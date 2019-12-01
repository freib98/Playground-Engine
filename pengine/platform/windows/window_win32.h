#pragma once

#include <windows.h>

#include "engine/core/window.h"

namespace PEngine
{
    class Win32Window : public Window
    {
    public:
        Win32Window(const WindowProps& props);
        ~Win32Window() = default;

        bool OnUpdate() override;

    private:
        virtual void Init(const WindowProps& props);

        HWND m_handle{};
    };

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}
