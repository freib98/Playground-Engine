#include "application.h"

#include <glad/glad.h>

#include "logger.h"

namespace PEngine
{
    Application::Application()
    {
        Logger::Init();

        _window = std::unique_ptr<Window>(Window::Create());
    }

    void Application::Run()
    {
        PENGINE_INFO("OpenGL Info:");
        PENGINE_INFO("  Vendor: {}", glGetString(GL_VENDOR));
        PENGINE_INFO("  Renderer: {}", glGetString(GL_RENDERER));
        PENGINE_INFO("  Version: {}", glGetString(GL_VERSION));

        PENGINE_INFO("--- Run start ---");

        while (_running)
        {
            glClearColor(0.129f, 0.586f, 0.949f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            _running = _window->OnUpdate();
        }

        PENGINE_INFO("--- Run end ---");
    }
}
