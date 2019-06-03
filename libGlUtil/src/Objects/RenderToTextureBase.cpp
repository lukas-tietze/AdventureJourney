#include "Objects.hpp"

#include "data/Io.hpp"
#include "RenderUtils.hpp"

glutil::RenderToTextureBase::RenderToTextureBase() : dirty(true),
                                                     useUboData(true),
                                                     ready(false),
                                                     autoUpdate(true),
                                                     fbo(0)
{
}

glutil::RenderToTextureBase::RenderToTextureBase(RenderToTextureBase &&other)
{
    this->TransferFrom(other);
}

glutil::RenderToTextureBase::~RenderToTextureBase()
{
    this->DestroyFrameBuffer();
}

int glutil::RenderToTextureBase::GetWidth() const
{
    return this->data.width;
}

int glutil::RenderToTextureBase::GetHeight() const
{
    return this->data.height;
}

void glutil::RenderToTextureBase::Update()
{
    if (this->dirty)
        this->Recreate();
}

void glutil::RenderToTextureBase::DestroyFrameBuffer()
{
    if (this->fbo)
    {
        glDeleteFramebuffers(1, &this->fbo);
        this->fbo = 0;
        util::dbg.WriteLine("Destroyed Framebuffer %", this->fbo);
    }
}

void glutil::RenderToTextureBase::CreateFrameBuffer()
{
    this->DestroyFrameBuffer();

    glGenFramebuffers(1, &this->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
    util::dbg.WriteLine("Generated Framebuffer %", this->fbo);
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
    this->data = other.data;
    this->dirty = other.dirty;

    other.fbo = 0;
    other.dirty = true;
}

void glutil::RenderToTextureBase::SetSize(int w, int h)
{
    if (this->data.width != w || this->data.height != h)
    {
        this->data.width = w;
        this->data.height = h;
        this->dirty = true;
        this->SetDirty();
    }
}

void glutil::RenderToTextureBase::SetFrameBufferDirty()
{
    this->dirty = true;
}

void glutil::RenderToTextureBase::Recreate()
{
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

    if (this->useUboData || true)
    {
        this->Bind();
        this->Upload(true);
    }

    this->BeginRender();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glutil::renderUtil::RenderNdcRect();

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