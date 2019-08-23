#include "RenderUtils.hpp"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace
{
bool ready = false;

constexpr int BUFFER_OFFSET = 0;
constexpr int BUFFER_COUNT = 3;
constexpr int VAO_OFFSET = BUFFER_COUNT;
constexpr int VAO_COUNT = 2;

constexpr int QUAD_VBO = 0;
constexpr int BOX_VBO = 1;
constexpr int BOX_IBO = 2;
constexpr int QUAD_VAO = 3;
constexpr int BOX_VAO = 4;

GLuint buffers[BUFFER_COUNT + VAO_COUNT];

static const glm::vec2 quadData[] = {
    {-1.f, 1.f},
    {-1.f, -1.f},
    {1.f, 1.f},
    {1.f, -1.f},
};

const glm::vec3 boxData[8] = {
    {-1.f, -1.f, -1.f}, //0
    {1.f, -1.f, -1.f},  //1
    {1.f, 1.f, -1.f},   //2
    {-1.f, 1.f, -1.f},  //3
    {-1.f, -1.f, 1.f},  //4
    {1.f, -1.f, 1.f},   //5
    {1.f, 1.f, 1.f},    //6
    {-1.f, 1.f, 1.f},   //7
};

const GLubyte boxIndices[36] = {
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

void glutil::renderUtil::RenderNdcBox()
{
    if (!ready)
        Init();

    glBindVertexArray(buffers[BOX_VAO]);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
}

void glutil::renderUtil::RenderNdcRect()
{
    if (!ready)
        Init();

    glBindVertexArray(buffers[QUAD_VAO]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool glutil::renderUtil::Init()
{
    if (ready)
        return true;

    glGenBuffers(BUFFER_COUNT, &buffers[BUFFER_OFFSET]);
    glGenVertexArrays(VAO_COUNT, &buffers[VAO_OFFSET]);

    glBindVertexArray(buffers[QUAD_VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[QUAD_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), &quadData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(buffers[BOX_VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[BOX_VBO]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BOX_IBO]);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), &boxData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLubyte), &boxIndices[0], GL_STATIC_DRAW);

    ready = true;
}

void glutil::renderUtil::Destroy()
{
    if (!ready)
        return;

    //TODO: Threadsicherheit!

    glDeleteBuffers(BUFFER_COUNT, &buffers[BUFFER_OFFSET]);
    glDeleteVertexArrays(VAO_COUNT, &buffers[BUFFER_COUNT]);

    ready = false;
}