#include "Objects.hpp"

#include "data/Io.hpp"

glutil::RenderToTextureBase::RenderToTextureBase() : dirty(true),
                                                     useUboData(true),
                                                     ready(false),
                                                     autoUpdate(true),
                                                     quadVao(0),
                                                     quadVbo(0),
                                                     fbo(0),
                                                     w(0),
                                                     h(0)
{
}

glutil::RenderToTextureBase::RenderToTextureBase(RenderToTextureBase &&other)
{
    this->TransferFrom(other);
}

glutil::RenderToTextureBase::~RenderToTextureBase()
{
    this->DestroyFrameBuffer();
    this->DestroyQuad();
}

int glutil::RenderToTextureBase::GetWidth() const
{
    return this->w;
}

int glutil::RenderToTextureBase::GetHeight() const
{
    return this->h;
}

void glutil::RenderToTextureBase::Update()
{
    if (this->dirty)
        this->Recreate();
}

void glutil::RenderToTextureBase::CreateQuad()
{
    this->DestroyQuad();

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
}

void glutil::RenderToTextureBase::DestroyQuad()
{
    if (this->quadVao)
    {
        glDeleteVertexArrays(1, &this->quadVao);
        this->quadVao = 0;
    }

    if (this->quadVbo)
    {
        glDeleteBuffers(1, &this->quadVbo);
        this->quadVbo = 0;
    }
}

void glutil::RenderToTextureBase::DestroyFrameBuffer()
{
    if (this->fbo)
    {
        glDeleteFramebuffers(1, &this->fbo);
        this->fbo = 0;
    }
}

void glutil::RenderToTextureBase::CreateFrameBuffer()
{
    this->DestroyFrameBuffer();

    glGenFramebuffers(1, &this->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
}

void glutil::RenderToTextureBase::ValidateFrameBuffer()
{
    this->ready = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

    if (this->ready)
        util::dbg.WriteLine("Created Framebuffer!");
    else
        util::dbg.WriteLine("Failed to create Framebuffer!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    this->dirty = false;
}

void glutil::RenderToTextureBase::TransferFrom(RenderToTextureBase &other)
{
    // this->StaticUboOwner::TransferFrom(other);

    this->autoUpdate = other.autoUpdate;
    this->w = other.w;
    this->h = other.h;
    this->quadVao = other.quadVao;
    this->quadVbo = other.quadVbo;
    this->dirty = other.dirty;

    other.quadVao = 0;
    other.quadVbo = 0;
    other.fbo = 0;
    other.dirty = true;
}

void glutil::RenderToTextureBase::SetSize(int w, int h)
{
    if (this->w != w || this->h != h)
    {
        this->w = w;
        this->h = h;
        this->dirty = true;
    }
}

void glutil::RenderToTextureBase::SetFrameBufferDirty()
{
    this->dirty = true;
}

void glutil::RenderToTextureBase::Recreate()
{
    if (!this->quadVao || !this->quadVbo)
    {
        this->DestroyQuad();
        this->CreateQuad();
    }

    this->DestroyFrameBuffer();
    this->CreateFrameBuffer();
    this->FillFrameBuffer();
    this->ValidateFrameBuffer();
}

bool glutil::RenderToTextureBase::CheckBeforUsage()
{
    if (this->dirty && this->autoUpdate)
        this->Recreate();

    return this->ready;
}

void glutil::RenderToTextureBase::StartRecording()
{
    if (!this->CheckBeforUsage())
        return;

    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
}

void glutil::RenderToTextureBase::Render()
{
    if (!this->CheckBeforUsage())
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

    this->BeginRender();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(this->quadVao);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    this->EndRender();
}

void glutil::RenderToTextureBase::BeginRender()
{
}

void glutil::RenderToTextureBase::EndRender()
{
}

void glutil::RenderToTextureBase::SetAutoUpdateEnabled(bool enabled)
{
    this->autoUpdate = enabled;
}

void glutil::RenderToTextureBase::SetUseUboData(bool enabled)
{
    this->useUboData = enabled;
}

bool glutil::RenderToTextureBase::IsReady() const
{
    return this->ready;
}

glutil::RenderToTextureBase &glutil::RenderToTextureBase::operator=(RenderToTextureBase &&other)
{
    this->TransferFrom(other);

    return *this;
}