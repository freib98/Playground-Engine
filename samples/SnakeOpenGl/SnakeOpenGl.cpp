#define PENGINE_OPENGL_API

#include <pengine.h>

class SnakeOpenGl : public PEngine::Application
{
public:
    SnakeOpenGl() = default;
    ~SnakeOpenGl() = default;

    void Update() override;
};

void SnakeOpenGl::Update()
{
}

PEngine::Application* PEngine::CreateApplication()
{
    return new SnakeOpenGl();
}
