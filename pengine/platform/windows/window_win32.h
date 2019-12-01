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
        void OnDestroy() override;

    private:
        virtual void Init(const WindowProps& props);
    };

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}
