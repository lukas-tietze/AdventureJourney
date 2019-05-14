#include "Objects.hpp"
#include "data/Io.hpp"

#include <cstdio>

#define STBI_WINDOWS_UTF8
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace
{
constexpr uint32_t WRAP_R = 0;
constexpr uint32_t WRAP_S = 1;
constexpr uint32_t WRAP_T = 2;
constexpr uint32_t FILTER_MIN = 0;
constexpr uint32_t FILTER_MAG = 1;

} // namespace

glutil::Texture::Texture() : format(GL_RGBA),
                             internalFormat(GL_RGBA),
                             target(GL_TEXTURE_2D),
                             width(0),
                             height(0),
                             wrapModes{GL_REPEAT, GL_REPEAT, GL_REPEAT},
                             filterModes{GL_LINEAR, GL_LINEAR},
                             createMipmaps(false),
                             maxAnisotropy(0),
                             tex(0)
{
}

glutil::Texture::~Texture()
{
    this->DestroyGlObjects();
}

void glutil::Texture::DestroyGlObjects()
{
    if (this->tex)
    {
        glDeleteTextures(1, &this->tex);
        this->tex = 0;
    }
}

void glutil::Texture::PrepareLoad()
{
    this->DestroyGlObjects();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &this->tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(this->target, this->tex);
}

void glutil::Texture::SetTextureParameters()
{
    glTexParameteri(this->target, GL_TEXTURE_WRAP_R, this->wrapModes[WRAP_R]);
    glTexParameteri(this->target, GL_TEXTURE_WRAP_S, this->wrapModes[WRAP_S]);
    glTexParameteri(this->target, GL_TEXTURE_WRAP_T, this->wrapModes[WRAP_T]);
    glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, this->filterModes[FILTER_MIN]);
    glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, this->filterModes[FILTER_MAG]);
    glTexParameterf(this->target, GL_TEXTURE_MAX_ANISOTROPY, this->maxAnisotropy);

    if (this->createMipmaps)
        glGenerateMipmap(this->target);
}

int glutil::Texture::GetChannelCountFromFormat()
{
    switch (this->format)
    {
    case GL_DEPTH_COMPONENT:
    case GL_RED:
        return 1;
    case GL_DEPTH_STENCIL:
    case GL_RG:
        return 2;
    case GL_RGB:
    case GL_BGR:
        return 3;
    case GL_RGBA:
    case GL_BGRA:
        return 4;
    }
}

GLenum glutil::Texture::GetFormatFromChannelCount(int n)
{
    switch (n)
    {
    case 1:
        return GL_RED;
    case 2:
        return GL_RG;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    }
}

bool glutil::Texture::CreateBuffer()
{
    this->PrepareLoad();

    glTexImage2D(this->target, 0, this->internalFormat,
                 this->width, this->height, 0,
                 this->format, GL_UNSIGNED_BYTE, nullptr);

    this->SetTextureParameters();
}

bool glutil::Texture::CreateAsStencilBuffer()
{
    this->format = GL_STENCIL_INDEX;
    this->internalFormat = GL_STENCIL_INDEX;

    this->CreateBuffer();
}

bool glutil::Texture::CreateAsDepthBuffer()
{
    this->format = GL_DEPTH_COMPONENT;
    this->internalFormat = GL_DEPTH_COMPONENT;

    this->CreateBuffer();
}

bool glutil::Texture::CreateAsStencilAndDepthBuffer()
{
    this->format = GL_DEPTH_STENCIL;
    this->internalFormat = GL_DEPTH24_STENCIL8;

    this->CreateBuffer();
}

bool glutil::Texture::LoadDataFromMemory(void *data)
{
    this->PrepareLoad();

    glTexImage2D(this->target, 0, this->internalFormat,
                 this->width, this->height, 0,
                 this->format, GL_UNSIGNED_BYTE, data);

    this->SetTextureParameters();

    return true;
}

bool glutil::Texture::LoadData(const std::string &path, ImageFormat format)
{
    if (!this->format || !this->internalFormat || !this->target)
        return false;

    auto file = std::fopen(path.c_str(), "r");
    ;

    if (!file)
    {
        util::dbg.WriteLine("Failed to load texture from %. Could not open file!", path);

        return false;
    }

    int nChannels;

    auto pixels = stbi_load_from_file(file, &this->width, &this->height, &nChannels, 0);

    this->format = this->GetFormatFromChannelCount(nChannels);

    if (!pixels)
    {
        util::dbg.WriteLine("Failed to load texture from %. Error while reading data! Message: %", path, stbi_failure_reason());

        return false;
    }

    auto res = this->LoadDataFromMemory(pixels);

    stbi_image_free(pixels);

    return res;
}

bool glutil::Texture::LoadCubeMap(const std::string &directory, const std::initializer_list<std::string> &files)
{
    return false;
}

bool glutil::Texture::LoadCubeMap(const std::initializer_list<std::string> &files)
{
    return false;
}

bool glutil::Texture::LoadCubeMap(const std::vector<std::string> &paths)
{
    return false;
}

bool glutil::Texture::LoadCubeMap(const std::string &directory, const std::vector<std::string> &files)
{
    return false;
}

bool glutil::Texture::LoadCubeMapFromMemory(const void **)
{
    return false;
}

void glutil::Texture::Bind(GLuint textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(this->target, this->tex);
}

void glutil::Texture::SetFormat(int fromat)
{
    this->format = format;
}

void glutil::Texture::SetInternalFormat(int internalFormat)
{
    this->internalFormat = internalFormat;
}

void glutil::Texture::SetDataType(int type)
{
    this->dataType = type;
}

void glutil::Texture::SetTarget(int target)
{
    this->target = target;
}

void glutil::Texture::SetSize(int w, int h)
{
    this->width = w;
    this->height = h;
}

void glutil::Texture::SetWidth(int w)
{
    this->width = w;
}

void glutil::Texture::SetHeight(int h)
{
    this->height = h;
}

void glutil::Texture::SetMipmapsEnabled(bool enabled)
{
    this->createMipmaps = enabled;
}

void glutil::Texture::SetFilterMode(GLenum filterMode)
{
    this->filterModes[FILTER_MIN] = filterMode;
    this->filterModes[FILTER_MAG] = filterMode;
}

void glutil::Texture::SetMinFilterMode(GLenum filterMode)
{
    this->filterModes[FILTER_MIN] = filterMode;
}

void glutil::Texture::SetMagFilterMode(GLenum filterMode)
{
    this->filterModes[FILTER_MAG] = filterMode;
}

void glutil::Texture::SetWrapMode(GLenum wrapMode)
{
    this->wrapModes[WRAP_R] = wrapMode;
    this->wrapModes[WRAP_S] = wrapMode;
    this->wrapModes[WRAP_T] = wrapMode;
}

void glutil::Texture::SetWrapModeR(GLenum wrapMode)
{
    this->wrapModes[WRAP_R] = wrapMode;
}

void glutil::Texture::SetWrapModeS(GLenum wrapMode)
{
    this->wrapModes[WRAP_S] = wrapMode;
}

void glutil::Texture::SetWrapModeT(GLenum wrapMode)
{
    this->wrapModes[WRAP_T] = wrapMode;
}

void glutil::Texture::SetMaxAnisotropy(double maxAnisotropy)
{
    this->maxAnisotropy = maxAnisotropy;
}

void glutil::Texture::SetAnisotropicFilterDisabled()
{
    this->maxAnisotropy = 0;
}

GLuint glutil::Texture::GetId() const
{
    return this->tex;
}
