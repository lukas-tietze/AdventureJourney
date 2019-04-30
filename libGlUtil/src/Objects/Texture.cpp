#include "Objects.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

glutil::Texture::Texture() : format(GL_RGBA),
                             internalFormat(GL_RGBA),
                             target(GL_TEXTURE_2D),
                             width(),
                             height(),
                             tex()
{
}

glutil::Texture::~Texture()
{
}

void glutil::Texture::DestroyGlObjects()
{
    if (this->tex)
        glDeleteTextures(1, &this->tex);
}

bool glutil::Texture::LoadDataFromMemory(void *data)
{
    this->DestroyGlObjects();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &this->tex);
    glBindTexture(this->target, this->tex);
    glTexImage2D(this->target, 0, this->internalFormat,
                 this->width, this->height, 0,
                 this->format, GL_UNSIGNED_BYTE, data);
}

bool glutil::Texture::LoadDataFromFunction(int (*func)(float x, float y))
{
    auto pixels = new unsigned char[this->width * this->height];
}

bool glutil::Texture::LoadData(const std::string &path, TextureFormat format)
{
    if (!this->format || !this->internalFormat || !this->target)
        return false;

    auto file = std::fopen(path.c_str(), "r");

    if (!file)
        return false;

    auto pixels = stbi_load_from_file(file, &this->width, &height, nullptr, this->internalFormat);

    if (!pixels)
        return false;

    this->LoadDataFromMemory(pixels);

    stbi_image_free(pixels);
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

void glutil::Texture::SetWidth(int w)
{
    this->width = w;
}

void glutil::Texture::SetHeight(int h)
{
    this->height = h;
}

void glutil::Texture::Bind(uint textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(this->target, this->tex);
}