#pragma once

#pragma warning(push)
#pragma warning(disable : 4251)

#include <memory>

#include "window.h"

namespace PEngine
{
    class __declspec(dllexport) Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();

    private:
        std::unique_ptr<Window> m_window;

        bool m_running = true;
    };

    Application* CreateApplication();

}

#pragma warning(pop)
