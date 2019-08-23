#include "Objects.hpp"
#include "glad/glad.h"

glutil::UboOwner::UboOwner() : ubo(0),
                               bindingTarget(0),
                               contentDirty(true),
                               bufferDirty(true),
                               data(nullptr),
                               dataSize(0),
                               autoUpdate(false)
{
}

glutil::UboOwner::~UboOwner()
{
    this->DestroyGlObjects();
}

void glutil::UboOwner::CreateGlObjects()
{
    this->DestroyGlObjects();
    glGenBuffers(1, &this->ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
    glBufferData(GL_UNIFORM_BUFFER, this->dataSize, this->data, GL_STATIC_DRAW);
    this->bufferDirty = false;
    this->contentDirty = false;
}

void glutil::UboOwner::DestroyGlObjects()
{
    if (this->ubo)
    {
        glDeleteBuffers(1, &this->ubo);
        this->ubo = 0;
    }
}

void glutil::UboOwner::Bind() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, this->bindingTarget, this->ubo);
}

void glutil::UboOwner::SetBindingTarget(int target)
{
    this->bindingTarget = target;
}

void glutil::UboOwner::Upload(bool force)
{
    if (this->bufferDirty && this->autoUpdate)
        this->CreateGlObjects();

    if (this->contentDirty || force)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, this->dataSize, this->data);

        this->contentDirty = false;
    }
}

void glutil::UboOwner::SetDirty()
{
    this->contentDirty = true;
}

void glutil::UboOwner::SetData(void *data, size_t size)
{
    if (this->data != data || this->dataSize != size)
    {
        this->data = data;
        this->dataSize = size;
        this->bufferDirty = true;
    }
}

void glutil::UboOwner::Update(bool force)
{
    if (this->bufferDirty || force)
    {
        this->CreateGlObjects();
    }
}

void glutil::UboOwner::SetAutoUpdate(bool enable)
{
    this->autoUpdate = enable;
}
