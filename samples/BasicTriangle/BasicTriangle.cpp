#define PENGINE_OPENGL_API

#include <pengine.h>

#include <chrono>
#include <iostream>

class BasicTriangle : public PEngine::Application
{
public:
    BasicTriangle() = default;
    ~BasicTriangle() = default;

    void Update() override;

private:
    static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    static unsigned int CompileShader(const unsigned int type, const std::string& source);
};

void BasicTriangle::Update()
{
    PEngineEnableVsync();

    // clang-format off
	float positions[] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};
    // clang-format on

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //const std::string vertexShader =
    //    "#version 330 core\n"
    //    "\n"
    //    "layout(location = 0) in vex4 position;\n"
    //    "\n"
    //    "void main()\n"
    //    "{\n"
    //    "   gl_Position = position;\n"
    //    "}\n";

    //const std::string fragmentShader =
    //    "#version 330 core\n"
    //    "\n"
    //    "layout(location = 0) out vex4 color;\n"
    //    "\n"
    //    "void main()\n"
    //    "{\n"
    //    "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    //    "}\n";

    //const auto shader = CreateShader(vertexShader, fragmentShader);
    //glUseProgram(shader);

    unsigned int frames = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (PEngineIsRunning())
    {
        frames++;

        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start) >= std::chrono::seconds{ 1 })
        {
            std::cout << frames << std::endl;
            start = std::chrono::high_resolution_clock::now();
            frames = 0;
        }

        //glClearColor(0.129f, 0.586f, 0.949f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        PEngineSwap();
    }

    //glDeleteProgram(shader);
}

int BasicTriangle::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    const auto program = glCreateProgram();
    const auto vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    const auto fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int BasicTriangle::CompileShader(const unsigned int type, const std::string& source)
{
    const auto id = glCreateShader(type);
    const auto src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        return 0;
    }

    return id;
}

PEngine::Application* PEngine::CreateApplication()
{
    return new BasicTriangle();
}
