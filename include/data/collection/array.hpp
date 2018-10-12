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
    size_t size;
    TAlloc allocator;

    void release_resources()
    {
        if (this->data != nullptr)
        {
            this->allocator.deallocate(this->data, this->size);
            this->data = nullptr;
            this->size = 0;
        }
    }

  public:
    class iterator
    {
      private:
        T *data;
        size_t pos;
        size_t count;

      public:
        iterator(T *data, size_t pos, size_t count) : data(data),
                                                      pos(pos),
                                                      count(count)
        {
        }

        iterator operator++()
        {
            auto res = iterator(*this);

            this->pos++;

            return res;
        }

        iterator &operator++(int)
        {
            this->pos++;

            return *this;
        }

        bool operator==(const iterator &other) const
        {
            return this->data == other.data &&
                   this->pos == other.pos &&
                   this->count == other.count;
        }

        bool operator!=(const iterator &other) const
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

    array(size_t size)
    {
        this->size = size;
        this->data = this->allocator.allocate(this->size);
    }

    array(const array<T> &copy)
    {
        this->copy_from(copy);
    }

    array(array &&initializer)
    {
        this->swap(initializer);
    }

    ~array()
    {
        this->release_resources();
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

    iterator begin()
    {
        return iterator(this->data, 0, this->size);
    }

    iterator end()
    {
        return iterator(this->data, this->size, this->size);
    }

    void swap(array<T> &other)
    {
        std::swap(this->data, other.data);
        std::swap(this->size, other.size);
    }

    void copy_from(const array<T> &other)
    {
        this->release_resources();
        this->size = other.size();
        this->data = this->allocator.allocate(this->size);

        for (size_t i = 0; i < this->size; i++)
        {
            this->allocator.construct(this->data + i, other.data[i]);
        }
    }

    array &operator=(const array<T> &copy)
    {
        this->copy_from(copy);
    }

    array &operator=(array<T> &&initializer)
    {
        this->release_resources();
        this->swap(initializer);
    }
}; /*array*/
} // namespace util