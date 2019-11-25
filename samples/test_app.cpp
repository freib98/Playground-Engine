#include <pengine.h>

class TestApp : public PEngine::Application
{
public:
    TestApp() = default;
    ~TestApp() = default;
};

PEngine::Application* PEngine::CreateApplication()
{
    return new TestApp();
}
