#include "Objects.hpp"
#include "glad/glad.h"

template <class TData>
gui::DynamicUboOwner<TData>::DynamicUboOwner() : ubo(0),
                                                 dirty(true),
                                                 data(),
                                                 bufferSize(0)
{
}

template <class TData>
void gui::DynamicUboOwner<TData>::CreateGlObjects()
{
    glGenBuffers(1, &this->ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(TData) * this->data.size(), this->data.data(), GL_STATIC_DRAW);
}

template <class TData>
void gui::DynamicUboOwner<TData>::DestroyGlObjects()
{
    glDeleteBuffers(1, &this->ubo);
    this->ubo = 0;
}

template <class TData>
void gui::DynamicUboOwner<TData>::Bind() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, this->bindingTarget, this->ubo);
}

template <class TData>
void gui::DynamicUboOwner<TData>::SetBindingTarget(int target)
{
    this->bindingTarget = target;
}

template <class TData>
void gui::DynamicUboOwner<TData>::Upload() const
{
    if (this->dirty)
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
void gui::DynamicUboOwner<TData>::SetDirty()
{
    this->dirty = true;
}
