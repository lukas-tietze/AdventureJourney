#include "Objects.hpp"

#include "glad/glad.h"

template <class TData, int bindingTarget>
gui::UboOwnerBase<TData, bindingTarget>::UboOwnerBase() : ubo(0),
                                                          dirty(true),
                                                          data()
{
}

template <class TData, int bindingTarget>
void gui::UboOwnerBase<TData, bindingTarget>::CreateGlObjects()
{
    glGenBuffers(1, &this->ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(TData), &this->data, GL_STATIC_DRAW);
}

template <class TData, int bindingTarget>
void gui::UboOwnerBase<TData, bindingTarget>::DestroyGlObjects()
{
    glDeleteBuffers(1, &this->ubo);
    this->ubo = 0;
}

template <class TData, int bindingTarget>
void gui::UboOwnerBase<TData, bindingTarget>::Bind() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingTarget, this->ubo);
}

template <class TData, int bindingTarget>
void gui::UboOwnerBase<TData, bindingTarget>::Upload() const
{
    if (this->dirty)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(TData), &this->data);

        this->dirty = false;
    }
}

template <class TData, int bindingTarget>
void gui::UboOwnerBase<TData, bindingTarget>::SetDirty()
{
    this->dirty = true;
}
