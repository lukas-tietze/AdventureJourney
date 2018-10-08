#pragma once

#include <memory>

#include "exception.hpp"

namespace util
{
template <class T, class TAlloc = std::allocator<T>>
class array
{
  private:
    T *data;
    int size;
    TAlloc allocator;

  public:
    array(int size)
    {
        this->size = size;
        this->data = this->allocator.allocate(this->size);
    }

    ~array()
    {
        this->allocator.deallocate(this->data, this->size);
    }

    T &first()
    {
        return this->data[0];
    }

    const T &first() const
    {
        return this->data[0];
    }

    T &last()
    {
        return this->data[this->size - 1];
    }

    const T &last() const
    {
        return this->data[this->size - 1];
    }

    size_t length() const
    {
        return this->size;
    }

    const T &operator[](int index) const
    {
        if (index < 0 || index >= this->size)
            throw util::index_out_of_range_exception();

        return this->data[index];
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= this->size)
            throw util::index_out_of_range_exception();

        return this->data[index];
    }
}; /*array*/
} // namespace util