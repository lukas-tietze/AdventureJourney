#include "Objects.hpp"

namespace
{
constexpr int ALBEDO = 0;
constexpr int NORMAL = 1;
constexpr int MATERIAL = 2;
constexpr int DEPTH = 3;

// constexpr GLenum FORMATS[4] = {
//     GL_SRGB8,
//     GL_RG16,
//     GL_RGB5_A1,
//     GL_DEPTH_COMPONENT24,
// };

constexpr GLenum FORMATS[4] = {
    GL_RGB,
    GL_RGB,
    GL_RGBA,
    GL_DEPTH_COMPONENT24,
};
} // namespace

glutil::DeferredRenderingPipeline::DeferredRenderingPipeline() : textures{0, 0, 0, 0},
                                                                 targets{
                                                                     GL_TEXTURE0,
                                                                     GL_TEXTURE1,
                                                                     GL_TEXTURE2,
                                                                     GL_TEXTURE3}
{
}

glutil::DeferredRenderingPipeline::DeferredRenderingPipeline(DeferredRenderingPipeline &&other)
{
    this->TransferFrom(other);
}

glutil::DeferredRenderingPipeline::~DeferredRenderingPipeline()
{
    this->DestroyGlObjects();
}

void glutil::DeferredRenderingPipeline::DestroyGlObjects()
{
    glDeleteTextures(4, this->textures);

    for (int i = 0; i < 4; i++)
        this->textures[i] = 0;
}

void glutil::DeferredRenderingPipeline::TransferFrom(DeferredRenderingPipeline &other)
{
    this->RenderToTextureBase::TransferFrom(other);

    for (int i = 0; i < 4; i++)
    {
        this->textures[i] = other.textures[i];
        other.textures[i] = 0;
        this->targets[i] = other.targets[i];
    }
}

void glutil::DeferredRenderingPipeline::FillFrameBuffer()
{
    this->DestroyGlObjects();

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(4, &this->textures[0]);

    for (int i = 0; i < 4; i++)
    {
        glBindTexture(GL_TEXTURE_2D, this->textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, FORMATS[i], this->GetWidth(), this->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textures[ALBEDO], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->textures[NORMAL], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->textures[MATERIAL], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->textures[DEPTH], 0);
}

void glutil::DeferredRenderingPipeline::BeginRender()
{
    unsigned int attachements[3] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
    };

    glDrawBuffers(3, attachements);
    glActiveTexture(this->targets[ALBEDO]);
    glBindTexture(GL_TEXTURE_2D, this->textures[ALBEDO]);
    glActiveTexture(this->targets[NORMAL]);
    glBindTexture(GL_TEXTURE_2D, this->textures[NORMAL]);
    glActiveTexture(this->targets[MATERIAL]);
    glBindTexture(GL_TEXTURE_2D, this->targets[MATERIAL]);
}

void glutil::DeferredRenderingPipeline::EndRender()
{
}

void glutil::DeferredRenderingPipeline::SetNormalTexureBindingTarget(GLuint value)
{
    this->targets[NORMAL] = value;
}

void glutil::DeferredRenderingPipeline::SetMaterialTexureBindingTarget(GLuint value)
{
    this->targets[MATERIAL] = value;
}

void glutil::DeferredRenderingPipeline::SetAlbedoTexureBindingTarget(GLuint value)
{
    this->targets[ALBEDO] = value;
}

void glutil::DeferredRenderingPipeline::SetDepthTexureBindingTarget(GLuint value)
{
    this->targets[DEPTH] = value;
}

glutil::DeferredRenderingPipeline &glutil::DeferredRenderingPipeline::operator=(DeferredRenderingPipeline &&other)
{
    this->TransferFrom(other);

    return *this;
}
