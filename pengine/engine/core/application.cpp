#include "application.h"

#include <iostream>
#include <glad/glad.h>

#include "platform/windows/window_win32.h"

namespace PEngine
{
    Application::Application()
    {
        _window = std::unique_ptr<Window>(Window::Create());
    }

    void Application::Run()
    {
        std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

        std::cout << "Run start" << std::endl;

        while (_running)
        {
            glClearColor(0.129f, 0.586f, 0.949f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            _running = _window->OnUpdate();
        }

        std::cout << "Run end" << std::endl;
    }
}
