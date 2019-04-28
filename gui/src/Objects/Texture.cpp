#include "Objects.hpp"
#include "stab.h"

glutil::Texture::Texture()
{
}

glutil::Texture::~Texture()
{
}

bool glutil::Texture::LoadData(const std::string &path, TextureFormat format = TextureFormat::FromFileExtension)
{

}

void glutil::Texture::SetFormat(int fromat) 
{
    this->format = format;
}

void glutil::Texture::SetInternalFormat(int internalFormat)
{
    this->internalFormat = internalFormat;
}

void glutil::Texture::SetTarget(int target)
{
    this->target = target;
}

void glutil::Texture::SetTextureUnit(int unit)
{
    this->textureUnit = unit;
}

void glutil::Texture::SetWidth(int w)
{
    this->width = w;
}

void glutil::Texture::SetHeight(int h)
{
    this->height = h;
}