#pragma once

#include "Application.h"

extern PEngine::Application* PEngine::CreateApplication();

int main(int argc, char** argv)
{
    auto app = PEngine::CreateApplication();

    app->Run();

    delete app;
}
