#include "Objects.hpp"
#include "glad/glad.h"

template <class TData>
glutil::DynamicUboOwner<TData>::DynamicUboOwner() : UboOwner(),
                                                    data()
{
    this->SetData(this->data.data(), sizeof(TData) * this->data.size());
}

template <class TData>
void glutil::DynamicUboOwner<TData>::Resize()
{
    this->SetData(this->data.data(), sizeof(TData) * this->data.size());
    this->Update();
}