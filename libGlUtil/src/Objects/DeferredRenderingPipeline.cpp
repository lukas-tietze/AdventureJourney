#include "Objects.hpp"
#include "data/Io.hpp"

namespace
{
constexpr int ALBEDO = 0;
constexpr int NORMAL = 1;
constexpr int MATERIAL = 2;
constexpr int DEPTH_STENCIL = 3;
} // namespace

glutil::DeferredRenderingPipeline::DeferredRenderingPipeline() : textures{0, 0, 0, 0},
                                                                 targets{
                                                                     GL_TEXTURE0,
                                                                     GL_TEXTURE1,
                                                                     GL_TEXTURE2,
                                                                     GL_TEXTURE3,
                                                                 }
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
    glGenTextures(4, this->textures);

    util::dbg.WriteLine("Created textures a=%, n=%, m=%, ds=%",
                        this->textures[ALBEDO],
                        this->textures[NORMAL],
                        this->textures[MATERIAL],
                        this->textures[DEPTH_STENCIL]);

    glBindTexture(GL_TEXTURE_2D, this->textures[ALBEDO]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->GetWidth(), this->GetHeight(), 0, GL_RGB, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textures[ALBEDO], 0);

    glBindTexture(GL_TEXTURE_2D, this->textures[NORMAL]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->GetWidth(), this->GetHeight(), 0, GL_RGB, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->textures[NORMAL], 0);

    glBindTexture(GL_TEXTURE_2D, this->textures[MATERIAL]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->GetWidth(), this->GetHeight(), 0, GL_RGB, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->textures[MATERIAL], 0);

    glBindTexture(GL_TEXTURE_2D, this->textures[DEPTH_STENCIL]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->GetWidth(), this->GetHeight(), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->textures[DEPTH_STENCIL], 0);

    unsigned int attachements[3] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
    };

    glDrawBuffers(3, attachements);
}

void glutil::DeferredRenderingPipeline::BeginRender()
{
    glActiveTexture(this->targets[ALBEDO]);

    glBindTexture(GL_TEXTURE_2D, this->textures[ALBEDO]);
    glActiveTexture(this->targets[NORMAL]);
    glBindTexture(GL_TEXTURE_2D, this->textures[NORMAL]);
    glActiveTexture(this->targets[MATERIAL]);
    glBindTexture(GL_TEXTURE_2D, this->textures[MATERIAL]);
    glActiveTexture(this->targets[DEPTH_STENCIL]);
    glBindTexture(GL_TEXTURE_2D, this->textures[DEPTH_STENCIL]);
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
    this->targets[DEPTH_STENCIL] = value;
}

glutil::DeferredRenderingPipeline &glutil::DeferredRenderingPipeline::operator=(DeferredRenderingPipeline &&other)
{
    this->TransferFrom(other);

    return *this;
}
