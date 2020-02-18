#pragma once

#include <windows.h>

#include "core/Window.h"

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

        void RegisterWindowClass() const;
        void CreateHelperWindow();
        void CreateNativeWindow(const WindowProps& props);

        void InitWgl() const;
        void CreateContextWgl() const;

        static std::wstring WideStringFromUtf8(const std::string& source);

        const LPCWSTR _wndClassName = L"PEngine";

        HWND _hwnd{};
        HWND _helperHwnd{};
    };

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}
