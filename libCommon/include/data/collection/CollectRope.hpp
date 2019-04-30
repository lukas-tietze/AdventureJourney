#pragma once

#include <memory>
#include <tuple>
#include <iterator>

namespace util
{
template <class T, int PartCapacity = 16>
class CollectRope
{
  private:
    struct RopeElement
    {
        RopeElement *next;
        size_t count;
        T *data;
    };

    RopeElement *start;
    RopeElement *last;
    size_t totalCount;
    size_t partCount;

    std::allocator<T> itemAllocator;
    std::allocator<RopeElement> elementAllocator;

    void AppendRope();
    void ReleaseResources();

  public:
    class Iterator
    {
      private:
        RopeElement *element;
        size_t pos;

        void Advance()
        {
            if (this->element == nullptr)
            {

                return;
            }
            this->pos++;

            if (this->pos == this->element->count)
            {
                this->element = this->element->next;
                this->pos = 0;
            }
        }

      public:
        Iterator(const Iterator &copy) : element(copy.element),
                                         pos(copy.pos)
        {
        }

        Iterator(RopeElement *element) : element(element),
                                          pos(0)
        {
        }

        Iterator(RopeElement *element, size_t pos) : element(element),
                                                      pos(pos)
        {
        }

        Iterator operator++() const
        {
            auto copy = Iterator(*this);

            return copy++;
        }

        ////x++;
        Iterator operator++()
        {
            auto res = Iterator(*this);

            this->Advance();

            return res;
        }

        ////++x;
        Iterator &operator++(int)
        {
            this->Advance();

            return *this;
        }

        bool operator==(const Iterator &other) const
        {
            return this->element == other.element &&
                   this->pos == other.pos;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }

        T &operator*()
        {
            return this->element->data[this->pos];
        }

        const T &operator*() const
        {
            return this->element->data[this->pos];
        }
    };

    CollectRope() : start(nullptr),
                     last(nullptr),
                     totalCount(0),
                     partCount(0),
                     itemAllocator(),
                     elementAllocator()
    {
    }

    CollectRope(const CollectRope<T, PartCapacity> &copy);
    CollectRope(CollectRope<T, PartCapacity> &&a);

    ~CollectRope()
    {
        this->ReleaseResources();
    }

    void Swap(CollectRope<T, PartCapacity> &&other)
    {
        std::swap(this->start, other.start);
        std::swap(this->last, other.last);
        std::swap(this->totalCount, other.totalCount);
        std::swap(this->partCount, other.partCount);
    }

    void CopyFrom(const CollectRope<T, PartCapacity> &other)
    {
        auto current = other.start;

        while (current != nullptr)
        {
            this->AppendRope();

            for (size_t i = 0; i < current.count; i++)
            {
                this->itemAllocator.construct(this->last->data + i, current.data[i]);
            }

            current = current.next;
        }

        this->totalCount = other.totalCount;
    }

    Iterator begin()
    {
        return Iterator(this->start);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    void Push(const T &item)
    {
        this->totalCount++;

        if (this->last == nullptr || this->last->count == PartCapacity)
        {
            this->AppendRope();
        }

        this->itemAllocator.construct(this->last->data + this->last->count, item);
        this->last->count++;
    }

    size_t Size() const
    {
        return this->totalCount;
    }

    size_t Parts() const
    {
        return this->partCount;
    }

    size_t PartSize() const
    {
        return PartCapacity;
    }

    // Copy assignment -> Do deep copy
    CollectRope &operator=(const CollectRope<T, PartCapacity> &a)
    {
        if (&a == this)
            return *this;

        this->ReleaseResources();
        this->CopyFrom(a);

        return *this;
    }

    //// Move assignment -> Transfer ownership
    CollectRope &operator=(CollectRope<T, PartCapacity> &&a)
    {
        if (&a == this)
            return *this;

        this->ReleaseResources();
        this->swap(a);

        return *this;
    }
};

template <class T, int PartCapacity>
CollectRope<T, PartCapacity>::CollectRope(const CollectRope<T, PartCapacity> &copy) : CollectRope()
{
    this->CopyFrom(copy);
}

template <class T, int PartCapacity>
CollectRope<T, PartCapacity>::CollectRope(CollectRope<T, PartCapacity> &&a) : CollectRope()
{
    this->Swap(a);
}

template <class T, int PartCapacity>
void CollectRope<T, PartCapacity>::AppendRope()
{
    auto newItems = this->itemAllocator.allocate(PartCapacity);
    auto nextElement = this->elementAllocator.allocate(1);

    RopeElement element;
    element.next = nullptr;
    element.count = 0;
    element.data = newItems;

    this->elementAllocator.construct(nextElement, element);

    if (this->last == nullptr)
    {
        this->last = nextElement;
        this->start = this->last;
    }
    else
    {
        this->last->next = nextElement;
        this->last = nextElement;
    }

    this->partCount++;
}

template <class T, int PartCapacity>
void CollectRope<T, PartCapacity>::ReleaseResources()
{
    auto current = this->start;
    auto next = current;

    while (current != nullptr)
    {
        next = current.next;

        for (size_t i = 0; i < current->count; i++)
        {
            this->itemAllocator.destroy(next->data + i);
        }

        this->itemAllocator.deallocate(current->data, PartCapacity);
        this->elementAllocator.deallocate(current, 1);

        current = next;
    }

    this->start = nullptr;
    this->last = nullptr;
    this->totalCount = 0;
    this->partCount = 0;
}

} // namespace util