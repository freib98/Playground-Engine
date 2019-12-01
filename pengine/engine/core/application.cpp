#include "application.h"

#include <iostream>
#include <glad/glad.h>

#include "platform/windows/window_win32.h"

namespace PEngine
{
    Application::Application()
    {
        m_window = std::unique_ptr<Window>(Window::Create());
    }

    void Application::Run()
    {
        std::cout << "Run start" << std::endl;

        while (m_running)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_running = m_window->OnUpdate();
        }

        std::cout << "Run end" << std::endl;
    }
}
