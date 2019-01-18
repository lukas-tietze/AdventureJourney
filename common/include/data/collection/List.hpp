#pragma once

#include <memory>

#include "Exception.hpp"

namespace util
{
template <class T, class TAlloc = std::allocator<T>>
class List
{
  private:
    T *data;
    size_t length;
    TAlloc allocator;

    void ReleaseResources()
    {
        if (this->data != nullptr)
        {
            this->allocator.deallocate(this->data, this->length);
            this->data = nullptr;
            this->length = 0;
        }
    }

    void Resize()
    {
        if (this->data != nullptr)
        {
            T *buf;
            this->allocator.allocate(buf, this->length * 2);
        }
    }

  public:
    static constexpr size_t NPos = static_cast<size_t>(-1l);

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

        bool operator<(const Iterator &other) const
        {
            return this->data == other.data &&
                   this->count == other.count &&
                   this->pos < other.pos;
        }

        bool operator<=(const Iterator &other) const
        {
            return this->data == other.data &&
                   this->count == other.count &&
                   this->pos <= other.pos;
        }

        bool operator>(const Iterator &other) const
        {
            return this->data == other.data &&
                   this->count == other.count &&
                   this->pos > other.pos;
        }

        bool operator>=(const Iterator &other) const
        {
            return this->data == other.data &&
                   this->count == other.count &&
                   this->pos >= other.pos;
        }

        bool operator==(const Iterator &other) const
        {
            return this->data == other.data &&
                   this->pos == other.pos &&
                   this->count == other.count;
        }

        bool operator!=(const Iterator &other) const
        {
            return this->data != other.data ||
                   this->pos != other.pos ||
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

        size_t Index() const
        {
            return this->pos;
        }
    };

    List(size_t length)
    {
        this->length = length;
        this->data = this->allocator.allocate(this->length);
    }

    List(const List<T> &copy)
    {
        this->CopyFrom(copy);
    }

    List(List &&initializer)
    {
        this->Swap(initializer);
    }

    ~List()
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
        return this->data[this->length - 1];
    }

    const T &Last() const
    {
        return this->data[this->length - 1];
    }

    size_t Length() const
    {
        return this->length;
    }

    const T &operator[](int index) const
    {
        if (index < 0 || (size_t)index >= this->length)
            throw util::IndexOutOfRangeException();

        return this->data[index];
    }

    T &operator[](int index)
    {
        if (index < 0 || (size_t)index >= this->length)
            throw util::IndexOutOfRangeException();

        return this->data[index];
    }

    Iterator begin()
    {
        return Iterator(this->data, 0, this->length);
    }

    Iterator end()
    {
        return Iterator(this->data, this->length, this->length);
    }

    void Swap(List<T> &other)
    {
        std::swap(this->data, other.data);
        std::swap(this->length, other.length);
        std::swap(this->allocator, other.allocator);
    }

    void CopyFrom(const List<T> &other)
    {
        this->ReleaseResources();
        this->length = other.length;
        this->data = this->allocator.allocate(this->length);

        for (size_t i = 0; i < this->length; i++)
        {
            this->allocator.construct(this->data + i, other.data[i]);
        }
    }

    List &operator=(const List<T> &copy)
    {
        this->CopyFrom(copy);
    }

    List &operator=(List<T> &&initializer)
    {
        this->ReleaseResources();
        this->Swap(initializer);
    }

    List &operator=(const std::initializer_list<T> &list)
    {
        size_t i = 0;

        for (auto pos = list.begin(), end = list.end(); pos != end && i < this->length; pos++, i++)
        {
            this->data[i] = *pos;
        }
    }

    size_t IndexOf(const T &item)
    {
        for (size_t i = 0; i < this->length; i++)
        {
            if (this->data[i] == item)
                return i;
        }

        return List<T>::NPos;
    }
}; /*List*/
} // namespace util