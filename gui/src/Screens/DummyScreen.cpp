#include "GlScreens.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"

gui::DummyScreen::DummyScreen() : vao(0),
                                  ibo(0),
                                  vbo(0)
{
    glEnable(GL_DEPTH_TEST);

    pId = glutil::CreateProgram("assets/shaders/example.vs.glsl",
                                "assets/shaders/example.fs.glsl");
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(gui::models::Vertex_XYZ_RGB), gui::models::cubeData, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLubyte), gui::models::cubeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gui::models::Vertex_XYZ_RGB), (void *)offsetof(gui::models::Vertex_XYZ_RGB, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(gui::models::Vertex_XYZ_RGB), (void *)offsetof(gui::models::Vertex_XYZ_RGB, color));
    glEnableVertexAttribArray(1);

    this->eyePos = glm::vec3(3.f, 3.f, 3.f);
}

gui::DummyScreen::~DummyScreen()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteProgram(pId);
}

void gui::DummyScreen::Render()
{
    glUseProgram(pId);
    glBindVertexArray(vao);
    glUniformMatrix4fv(0, 1, GL_FALSE, &(this->modelViewProjectionMat[0][0]));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (void *)0);
}

void gui::DummyScreen::Update(double delta)
{
    this->rotation += delta * 0.3;

    auto projection = glm::perspective(glm::radians(60.f), 1.f, 0.1f, 100.f);
    auto view = glm::lookAt(this->eyePos, glutil::ORIGIN, glutil::AXIS_Y);
    auto model = glm::rotate(this->rotation, glutil::AXIS_Y);

    this->modelViewProjectionMat = projection * view * model;

    if (glutil::IsKeyDown(GLFW_KEY_ESCAPE) || glutil::IsKeyDown(GLFW_KEY_Q))
        glutil::Quit();
    if (glutil::IsKeyDown(GLFW_KEY_W))
        this->eyePos[0] += delta * 0.8;
    if (glutil::IsKeyDown(GLFW_KEY_S))
        this->eyePos[0] -= delta * 0.8;
    if (glutil::IsKeyDown(GLFW_KEY_A))
        this->eyePos[1] += delta * 0.8;
    if (glutil::IsKeyDown(GLFW_KEY_D))
        this->eyePos[1] -= delta * 0.8;
}