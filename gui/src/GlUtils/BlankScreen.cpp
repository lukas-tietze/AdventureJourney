#include "GlUtils.hpp"

void glutil::BlankScreen::Render()
{
    glClearColor(this->clearColor[0],
                 this->clearColor[1],
                 this->clearColor[2],
                 this->clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void glutil::BlankScreen::SetClearColor(float r, float g, float b, float a)
{
    this->clearColor[0] = r;
    this->clearColor[1] = g;
    this->clearColor[2] = b;
    this->clearColor[3] = a;
}
