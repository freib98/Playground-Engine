#pragma once

#include <string>
#include <utility>

namespace PEngine
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(std::string title = "Playground Engine - PEngine",
                    const unsigned int width = 1280,
                    const unsigned int height = 720) :
            Title(std::move(title)),
            Width(width),
            Height(height) {}
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        // virtual void OnUpdate() = 0;

        // virtual unsigned int GetWidth() const = 0;
        // virtual unsigned int GetHeight() const = 0;

        static Window* Create(const WindowProps& props = WindowProps());
    };
}
