#pragma once

#pragma warning(push)
#pragma warning(disable : 4251)

#include <memory>

#include "Window.h"

namespace PEngine
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();

        virtual void Update() = 0;

    private:
        std::unique_ptr<Window> _window;

        bool _running = true;
    };

    Application* CreateApplication();

}

#pragma warning(pop)
