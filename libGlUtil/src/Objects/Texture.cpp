#include "Objects.hpp"

#define __STDC_WANT_LIB_EXT1__ 1
#include <cstdio>

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

    return true;
}

bool glutil::Texture::LoadDataFromFunction(uint32_t (*func)(float x, float y))
{
    auto pixels = new unsigned char[static_cast<size_t>(this->width) * static_cast<size_t>(this->height)];

    return false;
}

bool glutil::Texture::LoadData(const std::string &path, TextureFormat format)
{
    if (!this->format || !this->internalFormat || !this->target)
        return false;

    std::FILE *file;

    file = std::fopen(path.c_str(), "r");

    if (!file)
        return false;

    auto pixels = stbi_load_from_file(file, &this->width, &this->height, nullptr, this->internalFormat);

    if (!pixels)
        return false;

    this->LoadDataFromMemory(pixels);

    stbi_image_free(pixels);

    return true;
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

void glutil::Texture::Bind(GLuint textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(this->target, this->tex);
}