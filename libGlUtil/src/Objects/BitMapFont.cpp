#include "Objects.hpp"

glutil::BitMapFont::BitMapFont()
{
}

glutil::BitMapFont::BitMapFont(BitMapFont &&other)
{
    this->TransferFrom(other);
}

glutil::BitMapFont::~BitMapFont()
{
    this->DestroyGlObjects();
}

void glutil::BitMapFont::DestroyGlObjects()
{
    if (this->tex)
    {
        glDeleteTextures(1, &this->tex);
        this->tex = 0;
    }
}

void glutil::BitMapFont::TransferFrom(BitMapFont &other)
{
    this->data = other.data;
}

void glutil::BitMapFont::SetOffsetPx(int x, int y)
{
    if (this->offsetX != x || this->offsetY != y)
    {
        this->offsetX = x;
        this->offsetY = y;
        this->data.offset = glm::vec2(x, y);

        this->SetDirty();
    }
}

void glutil::BitMapFont::SetStridePx(int x, int y)
{
    if (this->strideX != x || this->strideY != y)
    {
        this->strideX = x;
        this->strideY = y;
        this->data.stride = glm::vec2(x, y);

        this->SetDirty();
    }
}

void glutil::BitMapFont::SetCharSizePx(int w, int h)
{
    if (this->charWidth != w || this->charHeight != h)
    {
        this->charWidth = w;
        this->charHeight = h;
        this->data.charSize = glm::vec2(w, h);

        this->SetDirty();
    }
}

void glutil::BitMapFont::Load(const std::string &path)
{
}

void glutil::BitMapFont::Bind(GLenum target)
{
    glBindTexture(this->tex, target);
}

glm::vec4 glutil::BitMapFont::GetTexCoords(char c)
{
}

glutil::BitMapFont &glutil::BitMapFont::operator=(BitMapFont &&other)
{
    this->TransferFrom(other);

    return *this;
}
