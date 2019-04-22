#include "Objects.hpp"
#include "glad/glad.h"

template <class TData>
glutil::DynamicUboOwner<TData>::DynamicUboOwner() : ubo(0),
                                                 dirty(true),
                                                 data(),
                                                 bufferSize(0)
{
}

template <class TData>
void glutil::DynamicUboOwner<TData>::CreateGlObjects()
{
    glGenBuffers(1, &this->ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(TData) * this->data.size(), this->data.data(), GL_STATIC_DRAW);
}

template <class TData>
void glutil::DynamicUboOwner<TData>::DestroyGlObjects()
{
    glDeleteBuffers(1, &this->ubo);
    this->ubo = 0;
}

template <class TData>
void glutil::DynamicUboOwner<TData>::Bind() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, this->bindingTarget, this->ubo);
}

template <class TData>
void glutil::DynamicUboOwner<TData>::SetBindingTarget(int target)
{
    this->bindingTarget = target;
}

template <class TData>
void glutil::DynamicUboOwner<TData>::Upload(bool force)
{
    if (this->dirty || force)
    {
        if (this->bufferSize != this->data.size())
        {
            this->DestroyGlObjects();
            this->CreateGlObjects();
        }
        else
        {
            glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(TData) * this->data.size(), this->data.data());
        }
        
        this->dirty = false;
    }
}

template <class TData>
void glutil::DynamicUboOwner<TData>::SetDirty()
{
    this->dirty = true;
}
