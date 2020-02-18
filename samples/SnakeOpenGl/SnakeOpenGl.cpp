#include <pengine.h>
#include <glad/glad.h>

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
