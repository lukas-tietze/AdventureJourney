#pragma once

#include <memory>
#include <cstring>
#include <algorithm>

#include "Exception.hpp"

namespace util
{
template <class T, class TAlloc = std::allocator<T>>
class List
{
  private:
    T *data;
    T *pos;
    T *cap;
    TAlloc allocator;

    void ReleaseResources()
    {
        if (this->data != nullptr)
        {
            this->allocator.deallocate(this->data, this->Capacity());
            this->data = nullptr;
            this->pos = nullptr;
            this->cap = nullptr;
        }
    }

    void Resize(size_t size)
    {
        if (this->data != nullptr)
        {
            auto cap = this->Capacity();
            auto len = this->Length();

            T *buf;
            this->allocator.allocate(buf, size);

            std::memcpy(this->data, buf, sizeof(T) * len);

            this->allocator.deallocate(this->data, cap);

            this->data = buf;
            this->pos = this->data + len;
            this->cap = this->data + size;
        }
    }

    void InitFromInitializerList(const std::initializer_list<T> &list)
    {
        this->EnsureCapacity(list.size());
        T *i;

        for (auto pos = list.begin(), end = list.end(); pos != end; pos++, i++)
        {
            *i = *pos;
        }
    }

  public:
    static constexpr size_t NPos = static_cast<size_t>(-1l);

    class Iterator
    {
      private:
        T *pos;
        T *end;

      public:
        Iterator(T *pos, T *end) : pos(pos),
                                   end(end)
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
            return this->cap == other.end &&
                   this->pos < other.pos;
        }

        bool operator<=(const Iterator &other) const
        {
            return this->cap == other.end &&
                   this->pos <= other.pos;
        }

        bool operator>(const Iterator &other) const
        {
            return this->cap == other.end &&
                   this->pos > other.pos;
        }

        bool operator>=(const Iterator &other) const
        {
            return this->cap == other.end &&
                   this->pos >= other.pos;
        }

        bool operator==(const Iterator &other) const
        {
            return this->cap == other.end &&
                   this->pos == other.pos;
        }

        bool operator!=(const Iterator &other) const
        {
            return this->cap != other.end ||
                   this->pos != other.pos;
        }

        T &operator*()
        {
            return *(this->pos);
        }

        const T &operator*() const
        {
            return *(this->pos);
        }

        T *operator->()
        {
            return this->pos;
        }

        const T *operator->() const
        {
            return this->pos;
        }
    };

    List(size_t length)
    {
        this->data = this->allocator.allocate(length);
        this->pos = this->data;
        this->cap = this->data + length;
    }

    List() : List(std::min((size_t)(4096 / sizeof(T)), (size_t)16))
    {
    }

    List(const List<T> &copy)
    {
        this->CopyFrom(copy);
    }

    List(List &&initializer)
    {
        this->Swap(initializer);
    }

    List(const std::initializer_list<T> &list)
    {
        this->InitFromInitializerList(list);
    }

    ~List()
    {
        this->ReleaseResources();
    }

    T &First()
    {
        return *this->data;
    }

    const T &First() const
    {
        return *this->data;
    }

    T &Last()
    {
        return *this->pos;
    }

    const T &Last() const
    {
        return *this->pos;
    }

    size_t Length() const
    {
        return this->pos - this->data;
    }

    const T &operator[](int index) const
    {
        T *res = this->data + index;

        if (index < 0 || res >= this->pos)
            throw util::IndexOutOfRangeException();

        return *res;
    }

    T &operator[](int index)
    {
        T *res = this->data + index;

        if (index < 0 || res >= this->pos)
            throw util::IndexOutOfRangeException();

        return *res;
    }

    Iterator begin()
    {
        return Iterator(this->data, this->pos);
    }

    Iterator end()
    {
        return Iterator(this->pos, this->pos);
    }

    void Swap(List<T> &other)
    {
        std::swap(this->data, other.data);
        std::swap(this->pos, other.pos);
    }

    void CopyFrom(const List<T> &other)
    {
        this->ReleaseResources();
        this->data = this->allocator.allocate(this->data, other.Capacity());

        std::memcpy(other.data, this->data, other.Length() * sizeof(T));
        this->cap = this->data + other.Capacity();
        this->pos = this->data + other.Length();
    }

    void Reserve(size_t count)
    {
        this->EnsureCapacity(this->Length() + count);
    }

    void EnsureCapacity(size_t count)
    {
        if (this->Capacity() < count)
        {
            this->Resize(count);
        }
    }

    size_t Capacity() const
    {
        return this->cap - this->data;
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
        this->InitFromInitializerList(list);
    }

    size_t IndexOf(const T &item)
    {
        for (T *i = 0; i < end; i++)
        {
            if (*i == item)
                return i;
        }

        return List<T>::NPos;
    }

    bool Empty() const
    {
        return this->pos == this->data;
    }

    bool Full() const
    {
        return this->pos == this->cap;
    }

    void Add(const T &item)
    {
        if (this->Full())
            this->Resize(this->Capacity() * 2);

        *this->pos = item;
        this->pos++;
    }

    void Remove()
    {
    }
}; /*List*/
} // namespace util