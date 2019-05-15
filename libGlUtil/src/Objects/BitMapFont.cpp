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
}

void glutil::BitMapFont::SetStridePx(int x, int y)
{
}

void glutil::BitMapFont::SetCharSizePx(int w, int h)
{
}

void glutil::BitMapFont::Load(const std::string &path)
{
}

void glutil::BitMapFont::Bind(GLenum target)
{
}

glm::vec2 glutil::BitMapFont::GetTexCoords(char c)
{
}

glutil::BitMapFont &glutil::BitMapFont::operator=(BitMapFont &&other)
{
    this->TransferFrom(other);

    return *this;
}
