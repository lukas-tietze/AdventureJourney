#include "Objects.hpp"

glutil::DeferredRenderingPipeline::DeferredRenderingPipeline() : positionTex(0),
                                                                 positionTarget(GL_TEXTURE0),
                                                                 normalTex(0),
                                                                 normalTarget(GL_TEXTURE1),
                                                                 colorTex(0),
                                                                 colorTarget(GL_TEXTURE2),
                                                                 rbo(0)
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
    if (this->positionTex)
    {
        glDeleteTextures(1, &this->positionTex);
        this->positionTex = 0;
    }

    if (this->normalTex)
    {
        glDeleteTextures(1, &this->normalTex);
        this->normalTex = 0;
    }

    if (this->colorTex)
    {
        glDeleteTextures(1, &this->colorTex);
        this->colorTex = 0;
    }

    if (this->rbo)
    {
        glDeleteRenderbuffers(1, &this->rbo);
        this->rbo = 0;
    }
}

void glutil::DeferredRenderingPipeline::TransferFrom(DeferredRenderingPipeline &other)
{
    this->RenderToTextureBase::TransferFrom(other);

    this->positionTex = other.positionTex;
    this->positionTarget = other.positionTarget;
    this->normalTex = other.normalTex;
    this->normalTarget = other.normalTarget;
    this->colorTex = other.colorTex;
    this->colorTarget = other.colorTarget;
    this->rbo = other.rbo;

    other.positionTex = 0;
    other.normalTex = 0;
    other.colorTex = 0;
    other.rbo = 0;
}

void glutil::DeferredRenderingPipeline::FillFrameBuffer()
{
    this->DestroyGlObjects();

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &this->positionTex);
    glBindTexture(GL_TEXTURE_2D, this->positionTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->GetWidth(), this->GetHeight(), 0, GL_RGB, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorTex, 0);

    glGenTextures(1, &this->normalTex);
    glBindTexture(GL_TEXTURE_2D, this->normalTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->GetWidth(), this->GetHeight(), 0, GL_RGB, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->normalTex, 0);

    glGenTextures(1, &this->colorTex);
    glBindTexture(GL_TEXTURE_2D, this->colorTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->GetWidth(), this->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->colorTex, 0);

    glGenRenderbuffers(1, &this->rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->GetWidth(), this->GetHeight());
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);
}

void glutil::DeferredRenderingPipeline::BeginRender()
{
    unsigned int attachements[3] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
    };

    glDrawBuffers(3, attachements);
    glActiveTexture(this->positionTarget);
    glBindTexture(GL_TEXTURE_2D, this->positionTex);
    glActiveTexture(this->normalTarget);
    glBindTexture(GL_TEXTURE_2D, this->normalTex);
    glActiveTexture(this->colorTarget);
    glBindTexture(GL_TEXTURE_2D, this->colorTex);
}

void glutil::DeferredRenderingPipeline::EndRender()
{
}

void glutil::DeferredRenderingPipeline::SetPositionTex(GLuint value)
{
    if (this->positionTex != value)
    {
        this->positionTex = value;
        this->SetFrameBufferDirty();
    }
}

void glutil::DeferredRenderingPipeline::SetPositionTarget(GLuint value)
{
    if (this->positionTarget != value)
    {
        this->positionTarget = value;
        this->SetFrameBufferDirty();
    }
}

void glutil::DeferredRenderingPipeline::SetNormalTex(GLuint value)
{
    if (this->normalTex != value)
    {
        this->normalTex = value;
        this->SetFrameBufferDirty();
    }
}

void glutil::DeferredRenderingPipeline::SetNormalTarget(GLuint value)
{
    if (this->normalTarget != value)
    {
        this->normalTarget = value;
        this->SetFrameBufferDirty();
    }
}

void glutil::DeferredRenderingPipeline::SetColorTex(GLuint value)
{
    if (this->colorTex != value)
    {
        this->colorTex = value;
        this->SetFrameBufferDirty();
    }
}

void glutil::DeferredRenderingPipeline::SetColorTarget(GLuint value)
{
    if (this->colorTarget != value)
    {
        this->colorTarget = value;
        this->SetFrameBufferDirty();
    }
}

glutil::DeferredRenderingPipeline &glutil::DeferredRenderingPipeline::operator=(DeferredRenderingPipeline &&other)
{
    this->TransferFrom(other);

    return *this;
}
