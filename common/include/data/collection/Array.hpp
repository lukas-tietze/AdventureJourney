#pragma once

#include <memory>

#include "Exception.hpp"

namespace util
{
template <class T, class TAlloc = std::allocator<T>>
class Array
{
  private:
    T *data;
    size_t size;
    TAlloc allocator;

    void ReleaseResources()
    {
        if (this->data != nullptr)
        {
            this->allocator.deallocate(this->data, this->size);
            this->data = nullptr;
            this->size = 0;
        }
    }

  public:
    class Iterator
    {
      private:
        T *data;
        size_t pos;
        size_t count;

      public:
        Iterator(T *data, size_t pos, size_t count) : data(data),
                                                      pos(pos),
                                                      count(count)
        {
        }

        Iterator operator++()
        {
            auto res = Iterator(*this);

            this->pos++;

            return res;
        }

        Iterator &operator++(int)
        {
            this->pos++;

            return *this;
        }

        bool operator==(const Iterator &other) const
        {
            return this->data == other.data &&
                   this->pos == other.pos &&
                   this->count == other.count;
        }

        bool operator!=(const Iterator &other) const
        {
            return this->data != other.data &&
                   this->pos != other.pos &&
                   this->count != other.count;
        }

        T &operator*()
        {
            return this->data[this->pos];
        }

        const T &operator*() const
        {
            return this->data[this->pos];
        }

        T *operator->()
        {
            return this->data + this->pos;
        }

        const T *operator->() const
        {
            return this->data + this->pos;
        }
    };

    Array(size_t size)
    {
        this->size = size;
        this->data = this->allocator.allocate(this->size);
    }

    Array(const Array<T> &copy)
    {
        this->copy_from(copy);
    }

    Array(Array &&initializer)
    {
        this->swap(initializer);
    }

    ~Array()
    {
        this->ReleaseResources();
    }

    T &First()
    {
        return this->data[0];
    }

    const T &First() const
    {
        return this->data[0];
    }

    T &Last()
    {
        return this->data[this->size - 1];
    }

    const T &Last() const
    {
        return this->data[this->size - 1];
    }

    size_t Length() const
    {
        return this->size;
    }

    const T &operator[](int index) const
    {
        if (index < 0 || (size_t)index >= this->size)
            throw util::IndexOutOfRangeException();

        return this->data[index];
    }

    T &operator[](int index)
    {
        if (index < 0 || (size_t)index >= this->size)
            throw util::IndexOutOfRangeException();

        return this->data[index];
    }

    Iterator begin()
    {
        return Iterator(this->data, 0, this->size);
    }

    Iterator end()
    {
        return Iterator(this->data, this->size, this->size);
    }

    void Swap(Array<T> &other)
    {
        std::swap(this->data, other.data);
        std::swap(this->size, other.size);
    }

    void CopyFrom(const Array<T> &other)
    {
        this->ReleaseResources();
        this->size = other.size();
        this->data = this->allocator.allocate(this->size);

        for (size_t i = 0; i < this->size; i++)
        {
            this->allocator.construct(this->data + i, other.data[i]);
        }
    }

    Array &operator=(const Array<T> &copy)
    {
        this->CopyFrom(copy);
    }

    Array &operator=(Array<T> &&initializer)
    {
        this->ReleaseResources();
        this->Swap(initializer);
    }
}; /*Array*/
} // namespace util