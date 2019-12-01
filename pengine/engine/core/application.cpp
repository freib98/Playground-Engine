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
            if (!m_window->OnUpdate())
            {
                m_running = false;
            }
        }
        //if (!gladLoadGL())
        //{
        //    printf("Something went wrong!\n");
        //    exit(-1);
        //}
        //printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

        std::cout << "Run end" << std::endl;
    }
}
