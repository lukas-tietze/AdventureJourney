#include "Objects.hpp"

#include "data/Io.hpp"

glutil::PostProcessingPipeLine::PostProcessingPipeLine() : dirty(true),
                                                           ready(false),
                                                           autoUpdate(true),
                                                           requireColors(true),
                                                           requireDepthStencil(false),
                                                           colorTextureTarget(GL_TEXTURE0),
                                                           depthStencilTextureTarget(GL_TEXTURE1),
                                                           quadVao(0),
                                                           quadVbo(0),
                                                           colorTexture(0),
                                                           depthStencilTexture(0),
                                                           fbo(0),
                                                           rbo(0),
                                                           w(0),
                                                           h(0)
{
}

glutil::PostProcessingPipeLine::PostProcessingPipeLine(PostProcessingPipeLine &&other)
{
    this->TransferFrom(other);
}

glutil::PostProcessingPipeLine::~PostProcessingPipeLine()
{
    this->DestroyGlObjects();
}

void glutil::PostProcessingPipeLine::DestroyGlObjects()
{
    if (this->quadVao)
        glDeleteVertexArrays(1, &this->quadVao);

    if (this->quadVbo)
        glDeleteBuffers(1, &this->quadVbo);

    if (this->colorTexture)
        glDeleteTextures(1, &this->colorTexture);

    if (this->depthStencilTexture)
        glDeleteTextures(1, &this->depthStencilTexture);

    if (this->fbo)
        glDeleteFramebuffers(1, &this->fbo);

    if (this->rbo)
        glDeleteRenderbuffers(1, &this->rbo);
}

void glutil::PostProcessingPipeLine::Recreate()
{
    this->DestroyGlObjects();

    glGenVertexArrays(1, &this->quadVao);
    glBindVertexArray(this->quadVao);

    glGenBuffers(1, &this->quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->quadVbo);

    const float data[] = {
        -1.f,
        1.f,
        -1.f,
        -1.f,
        1.f,
        1.f,
        1.f,
        -1.f,
    };

    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (this->fbo)
        glDeleteFramebuffers(1, &this->fbo);

    glGenFramebuffers(1, &this->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

    if (this->requireColors)
    {
        glGenTextures(1, &this->colorTexture);
        glBindTexture(GL_TEXTURE_2D, this->colorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->w, this->h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorTexture, 0);
    }

    if (this->requireDepthStencil)
    {
        glGenTextures(1, &this->depthStencilTexture);
        glBindTexture(GL_TEXTURE_2D, this->depthStencilTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->w, this->h, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->depthStencilTexture, 0);
    }
    else
    {
        glGenRenderbuffers(1, &this->rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);
    }

    this->ready = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

    if (this->ready)
        util::dbg.WriteLine("Created Framebuffer!");
    else
        util::dbg.WriteLine("Failed to create Framebuffer!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    this->dirty = false;
}

void glutil::PostProcessingPipeLine::TransferFrom(PostProcessingPipeLine &other)
{
    this->autoUpdate = other.autoUpdate;
    this->requireColors = other.requireColors;
    this->colorTextureTarget = other.colorTextureTarget;
    this->depthStencilTextureTarget = other.depthStencilTextureTarget;
    this->requireDepthStencil = other.requireDepthStencil;
    this->w = other.w;
    this->h = other.h;
    this->quadVao = other.quadVao;
    this->quadVbo = other.quadVbo;
    this->colorTexture = other.colorTexture;
    this->depthStencilTexture = other.depthStencilTexture;
    this->dirty = other.dirty;

    other.quadVao = 0;
    other.quadVbo = 0;
    other.colorTexture = 0;
    other.depthStencilTexture = 0;
    other.dirty = true;
}

void glutil::PostProcessingPipeLine::SetColorsEnabled(bool enabled)
{
    if (this->requireColors != enabled)
    {
        this->requireColors = enabled;
        this->dirty = true;
    }
}

void glutil::PostProcessingPipeLine::SetDepthAndStencilEnabled(bool enabled)
{
    if (this->requireDepthStencil != enabled)
    {
        this->requireDepthStencil = enabled;
        this->dirty = true;
    }
}

void glutil::PostProcessingPipeLine::SetColorBufferTextureTarget(GLenum target)
{
    if (this->colorTextureTarget != target)
    {
        this->colorTextureTarget = target;
        this->dirty = true;
    }
}

void glutil::PostProcessingPipeLine::SetDepthStencilBufferTextureTarget(GLenum target)
{
    if (this->depthStencilTextureTarget != target)
    {
        this->depthStencilTextureTarget = target;
        this->dirty = true;
    }
}

void glutil::PostProcessingPipeLine::SetSize(int w, int h)
{
    if (this->w != w || this->h != h)
    {
        this->w = w;
        this->h = h;
        this->dirty = true;
    }
}

void glutil::PostProcessingPipeLine::StartRecording()
{
    if (this->dirty && this->autoUpdate)
        this->Recreate();

    if (!this->ready)
        return;

    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glutil::PostProcessingPipeLine::Render()
{
    if (this->dirty && this->autoUpdate)
        this->Recreate();

    if (!this->ready)
        return;

    if (this->useUboData)
    {
        if (this->data.width != this->w ||
            this->data.height != this->h)
        {
            this->data.width = this->w;
            this->data.height = this->h;
            this->SetDirty();
        }

        this->Bind();
        this->Upload();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(this->quadVao);

    if (this->requireColors)
        glBindTexture(this->colorTextureTarget, this->colorTexture);

    if (this->requireDepthStencil)
        glBindTexture(this->depthStencilTextureTarget, this->depthStencilTexture);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void glutil::PostProcessingPipeLine::Update()
{
    if (this->dirty)
        this->Recreate();
}

void glutil::PostProcessingPipeLine::SetAutoUpdateEnabled(bool enabled)
{
    this->autoUpdate = enabled;
}

void glutil::PostProcessingPipeLine::SetUseUboData(bool enabled)
{
    this->useUboData = enabled;
}

bool glutil::PostProcessingPipeLine::IsReady() const
{
    return this->ready;
}

glutil::PostProcessingPipeLine &glutil::PostProcessingPipeLine::operator=(PostProcessingPipeLine &&other)
{
    this->TransferFrom(other);

    return *this;
}