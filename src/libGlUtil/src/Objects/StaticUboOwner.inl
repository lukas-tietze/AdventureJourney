#include "Objects.hpp"
#include "glad/glad.h"

template <class TData>
glutil::StaticUboOwner<TData>::StaticUboOwner() : UboOwner(),
                                                  data()
{
    this->SetData(&this->data, sizeof(this->data));
}