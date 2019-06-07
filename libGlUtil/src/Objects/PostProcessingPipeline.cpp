#include "Objects.hpp"

#include "data/Io.hpp"

glutil::PostProcessingPipeline::PostProcessingPipeline() : RenderToTextureBase(),
                                                           requireColors(true),
                                                           requireDepthStencil(false),
                                                           colorTextureTarget(GL_TEXTURE0),
                                                           depthStencilTextureTarget(GL_TEXTURE1),
                                                           colorTexture(0),
                                                           depthStencilTexture(0),
                                                           rbo(0)
{
}

glutil::PostProcessingPipeline::PostProcessingPipeline(PostProcessingPipeline &&other)
{
    this->TransferFrom(other);
}

glutil::PostProcessingPipeline::~PostProcessingPipeline()
{
    this->DestroyGlObjects();
}

void glutil::PostProcessingPipeline::DestroyGlObjects()
{
    if (this->colorTexture)
    {
        glDeleteTextures(1, &this->colorTexture);
        this->colorTexture = 0;
    }

    if (this->depthStencilTexture)
    {
        glDeleteTextures(1, &this->depthStencilTexture);
        this->depthStencilTexture = 0;
    }

    if (this->rbo)
    {
        glDeleteRenderbuffers(1, &this->rbo);
        this->rbo = 0;
    }
}

void glutil::PostProcessingPipeline::FillFrameBuffer()
{
    this->DestroyGlObjects();

    if (this->requireColors)
    {
        glGenTextures(1, &this->colorTexture);
        glBindTexture(GL_TEXTURE_2D, this->colorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->GetWidth(), this->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorTexture, 0);

        util::dbg.WriteLine("\tCreated color attachment!");
    }

    if (this->requireDepthStencil)
    {
        glGenTextures(1, &this->depthStencilTexture);
        glBindTexture(GL_TEXTURE_2D, this->depthStencilTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->GetWidth(), this->GetHeight(), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->depthStencilTexture, 0);

        util::dbg.WriteLine("\tCreated depth & stencil attachment!");
    }
    else
    {
        glGenRenderbuffers(1, &this->rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->GetWidth(), this->GetHeight());
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);

        util::dbg.WriteLine("\tCreated renderbuffer for depth and stencil buffers!");
    }
}

void glutil::PostProcessingPipeline::BeginRender()
{
    if (this->requireColors)
    {
        glActiveTexture(this->colorTextureTarget);
        glBindTexture(GL_TEXTURE_2D, this->colorTexture);
    }

    if (this->requireDepthStencil)
    {
        glActiveTexture(this->depthStencilTextureTarget);
        glBindTexture(GL_TEXTURE_2D, this->depthStencilTexture);
    }
}

void glutil::PostProcessingPipeline::EndRender()
{
}

void glutil::PostProcessingPipeline::TransferFrom(PostProcessingPipeline &other)
{
    this->PostProcessingPipeline::TransferFrom(other);

    this->requireColors = other.requireColors;
    this->colorTextureTarget = other.colorTextureTarget;
    this->depthStencilTextureTarget = other.depthStencilTextureTarget;
    this->requireDepthStencil = other.requireDepthStencil;
    this->colorTexture = other.colorTexture;
    this->depthStencilTexture = other.depthStencilTexture;

    other.colorTexture = 0;
    other.depthStencilTexture = 0;
}

void glutil::PostProcessingPipeline::SetColorsEnabled(bool enabled)
{
    if (this->requireColors != enabled)
    {
        this->requireColors = enabled;
        this->SetFrameBufferDirty();
    }
}

void glutil::PostProcessingPipeline::SetDepthAndStencilEnabled(bool enabled)
{
    if (this->requireDepthStencil != enabled)
    {
        this->requireDepthStencil = enabled;
        this->SetFrameBufferDirty();
    }
}

void glutil::PostProcessingPipeline::SetColorBufferTextureTarget(GLenum target)
{
    if (this->colorTextureTarget != target)
    {
        this->colorTextureTarget = target;
        this->SetFrameBufferDirty();
    }
}

void glutil::PostProcessingPipeline::SetDepthStencilBufferTextureTarget(GLenum target)
{
    if (this->depthStencilTextureTarget != target)
    {
        this->depthStencilTextureTarget = target;
        this->SetFrameBufferDirty();
    }
}

glutil::PostProcessingPipeline &glutil::PostProcessingPipeline::operator=(PostProcessingPipeline &&other)
{
    this->TransferFrom(other);

    return *this;
}