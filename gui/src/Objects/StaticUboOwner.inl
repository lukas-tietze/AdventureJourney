#include "Objects.hpp"
#include "glad/glad.h"

template <class TData>
glutil::StaticUboOwner<TData>::StaticUboOwner() : ubo(static_cast<GLuint>(0)),
                                                  bindingTarget(static_cast<GLuint>(0)),
                                                  dirty(true),
                                                  data()
{
}

template <class TData>
void glutil::StaticUboOwner<TData>::CreateGlObjects()
{
    glGenBuffers(1, &this->ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(TData), &this->data, GL_STATIC_DRAW);
}

template <class TData>
void glutil::StaticUboOwner<TData>::DestroyGlObjects()
{
    glDeleteBuffers(1, &this->ubo);
    this->ubo = 0;
}

template <class TData>
void glutil::StaticUboOwner<TData>::Bind() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, this->bindingTarget, this->ubo);
}

template <class TData>
void glutil::StaticUboOwner<TData>::SetBindingTarget(int target)
{
    this->bindingTarget = target;
}

template <class TData>
void glutil::StaticUboOwner<TData>::Upload(bool force)
{
    if (this->dirty || force)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(TData), &this->data);

        this->dirty = false;
    }
}

template <class TData>
void glutil::StaticUboOwner<TData>::SetDirty()
{
    this->dirty = true;
}
