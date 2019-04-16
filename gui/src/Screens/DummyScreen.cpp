#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "GlScreens.hpp"

namespace
{
struct Vertex
{
    GLfloat position[3];
    GLubyte color[3];
};

/*
         *   3-------2
         *  /|      /|
         * 7-+-----6 |
         * | |     | |
         * | 0-----+-1
         * |/      |/
         * 4-------5
         * */
Vertex cubeData[8] = {
    {{-1, -1, -1}, {0, 0, 0}},    //0
    {{1, -1, -1}, {255, 0, 0}},   //1
    {{1, 1, -1}, {255, 255, 0}},  //2
    {{-1, 1, -1}, {0, 255, 0}},   //3
    {{-1, -1, 1}, {0, 0, 255}},   //4
    {{1, -1, 1}, {255, 0, 255}},  //5
    {{1, 1, 1}, {255, 255, 255}}, //6
    {{-1, 1, 1}, {0, 255, 255}},  //7
};

GLuint indices[36] = {
    0, 2, 1,
    3, 2, 0,
    4, 5, 6,
    7, 4, 6,
    5, 1, 2,
    2, 6, 5,
    0, 4, 7,
    7, 3, 0,
    5, 4, 1,
    0, 1, 4,
    7, 6, 2,
    7, 2, 3};
} // namespace

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

    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), cubeData, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
}

gui::DummyScreen::~DummyScreen()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void gui::DummyScreen::Render()
{
    glUseProgram(pId);
    glBindVertexArray(vao);
    glUniformMatrix4fv(0, 1, GL_FALSE, &(this->modelViewProjectionMat[0][0]));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)0);
}

void gui::DummyScreen::Update(double delta)
{
    this->rotation += delta * 0.3;

    this->modelViewProjectionMat = glm::perspective(glm::radians(60.f), 1.f, 0.1f, 100.f) *
                                   glm::lookAt(this->eyePos, glutil::ORIGIN, glutil::AXIS_Y) *
                                   glm::rotate(static_cast<float>(this->rotation), glutil::AXIS_Y);

    if (glutil::IsKeyDown(GLFW_KEY_ESCAPE))
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

void gui::DummyScreen::OnShow()
{
}

void gui::DummyScreen::OnHide()
{
}
