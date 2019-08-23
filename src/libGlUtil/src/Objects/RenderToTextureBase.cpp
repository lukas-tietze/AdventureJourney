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
    util::dbg.WriteLine("Created Framebuffer %", this->fbo);
}

void glutil::RenderToTextureBase::ValidateFrameBuffer()
{
    switch (glCheckFramebufferStatus(GL_FRAMEBUFFER))
    {
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        util::dbg.WriteLine("Error: Not all framebuffer attachment points are framebuffer attachment complete. This means that at least one attachment point with a renderbuffer or texture attached has its attached object no longer in existence or has an attached image with a width or height of zero, or the color attachment point has a non-color-renderable image attached, or the depth attachment point has a non-depth-renderable image attached, or the stencil attachment point has a non-stencil-renderable image attached.");
        break;
        util::dbg.WriteLine("Error: Not all attached images have the same width and height.");
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        util::dbg.WriteLine("Error: No images are attached to the framebuffer.");
        break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
        util::dbg.WriteLine("Error: The combination of internal formats of the attached images violates an implementation-dependent set of restrictions.");
        break;
    case GL_FRAMEBUFFER_COMPLETE:
        this->ready = true;
        break;
    }

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
    util::dbg.WriteLine("Creating RenderToTextureBase...");
    this->CreateFrameBuffer();

    util::dbg.WriteLine("\tFilling Framebuffer!");
    this->FillFrameBuffer();

    this->ValidateFrameBuffer();

    if (this->ready)
        util::dbg.WriteLine("Done!\n");
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

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glutil::RenderToTextureBase::Render()
{
    if (!this->CheckBeforUsage())
        return;

    if (this->useUboData)
    {
        this->Bind();
        this->Upload(true);
    }

    this->BeginRender();

    // glBlitFramebuffer(0, 0, this->data.width, this->data.height,
    //                   0, 0, this->data.width, this->data.height,
    //                   GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
    //                   GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
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