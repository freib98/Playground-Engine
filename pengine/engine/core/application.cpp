#include "application.h"

#include <iostream>

#include "platform/windows/window_win32.h"

namespace PEngine
{
    Application::Application()
    {
        m_window = std::unique_ptr<Window>(Window::Create());
    }

    void Application::Run()
    {
        std::cout << "Hello World" << std::endl;
    }
}
