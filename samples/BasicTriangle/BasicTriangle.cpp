#include <pengine.h>
#include <glad/glad.h>

class BasicTriangle : public PEngine::Application
{
public:
    BasicTriangle() = default;
    ~BasicTriangle() = default;

    void Update() override;
};

void BasicTriangle::Update()
{
    glClearColor(0.129f, 0.586f, 0.949f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int vertexArray, vertexBuffer, indexBuffer;

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // clang-format off
    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f ,0.0f,
         0.0f,  0.5f, 0.0f,
    };
    // clang-format on

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    unsigned int indices[3] = { 0, 1, 2 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}


PEngine::Application* PEngine::CreateApplication()
{
    return new BasicTriangle();
}
