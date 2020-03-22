#include "Application.h"

#include <glad/glad.h>

#include "Logger.h"

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

        this->Update();
        //while (_running)
        //{
        //    this->Update();

        //    _running = _window->OnUpdate();
        //}

        PENGINE_INFO("--- Run end ---");
    }
}
