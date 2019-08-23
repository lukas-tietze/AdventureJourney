#include "Objects.hpp"
#include "RenderUtils.hpp"

glutil::SkyBox::SkyBox() : program(nullptr),
                           texture(nullptr),
                           textureUnit(0)
{
}

void glutil::SkyBox::SetProgram(Program *program)
{
    this->program = program;
}

void glutil::SkyBox::SetTexture(Texture *texture, GLuint unit)
{
    this->texture = texture;
    this->textureUnit = unit;
}

void glutil::SkyBox::Render()
{
    if (this->texture)
        this->texture->Bind(this->textureUnit);

    if (this->program)
        this->program->Use();

    glDepthFunc(GL_LEQUAL);

    renderUtil::RenderNdcBox();
}
