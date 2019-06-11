#include "Objects.hpp"
#include "glad/glad.h"

template <class TData>
glutil::VectoredUboOwner<TData>::VectoredUboOwner() : UboOwner(),
                                                      data()
{
    this->SetData(this->data.data(), sizeof(TData) * this->data.size());
}

template <class TData>
void glutil::VectoredUboOwner<TData>::Resize()
{
    this->SetData(this->data.data(), sizeof(TData) * this->data.size());
    this->Update();
}

template <class TData>
TData &glutil::VectoredUboOwner<TData>::Add()
{
    this->data.push_back(TData());

    return this->data.back();
}

template <class TData>
TData &glutil::VectoredUboOwner<TData>::Add(const TData &)
{
    this->data.push_back(TData());

    return this->data.back();
}

template <class TData>
void glutil::VectoredUboOwner<TData>::Clear()
{
    this->data.clear();
}

template <class TData>
size_t glutil::VectoredUboOwner<TData>::Size() const
{
    return this->data.size();
}

template <class TData>
bool glutil::VectoredUboOwner<TData>::Remove(const TData &item)
{
    auto pos = std::find(this->data.begin(), this->data.end(), item);

    if (pos != this->data.end())
    {
        this->data.erase(pos);
        return true;
    }

    return false;
}

template <class TData>
bool glutil::VectoredUboOwner<TData>::RemoveAt(int index)
{
    this->data.Erase(this->data.begin() + index);

    return true;
}

template <class TData>
TData &glutil::VectoredUboOwner<TData>::operator[](size_t i)
{
    return this->data[i];
}

template <class TData>
const TData &glutil::VectoredUboOwner<TData>::operator[](size_t i) const
{
    return this->data[i];
}
