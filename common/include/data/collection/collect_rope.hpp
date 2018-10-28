#pragma once

#include <memory>
#include <tuple>
#include <iterator>

namespace util
{
template <class T, int PartCapacity = 16>
class collect_rope
{
  private:
    struct rope_element
    {
        rope_element *next;
        size_t count;
        T *data;
    };

    rope_element *start;
    rope_element *last;
    size_t total_count;
    size_t part_count;

    std::allocator<T> item_allocator;
    std::allocator<rope_element> element_allocator;

    void append_rope();
    void release_resources();

  public:
    class iterator
    {
      private:
        rope_element *element;
        size_t pos;

        void advance()
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
        iterator(const iterator &copy) : element(copy.element),
                                         pos(copy.pos)
        {
        }

        iterator(rope_element *element) : element(element),
                                          pos(0)
        {
        }

        iterator(rope_element *element, size_t pos) : element(element),
                                                      pos(pos)
        {
        }

        iterator operator++() const
        {
            auto copy = iterator(*this);

            return copy++;
        }

        ////x++;
        iterator operator++()
        {
            auto res = iterator(*this);

            this->advance();

            return res;
        }

        ////++x;
        iterator &operator++(int)
        {
            this->advance();

            return *this;
        }

        bool operator==(const iterator &other) const
        {
            return this->element == other.element &&
                   this->pos == other.pos;
        }

        bool operator!=(const iterator &other) const
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

    collect_rope() : start(nullptr),
                     last(nullptr),
                     total_count(0),
                     part_count(0),
                     item_allocator(),
                     element_allocator()
    {
    }

    collect_rope(const collect_rope<T, PartCapacity> &copy);
    collect_rope(collect_rope<T, PartCapacity> &&a);

    ~collect_rope()
    {
        this->release_resources();
    }

    void swap(collect_rope<T, PartCapacity> &&other)
    {
        std::swap(this->start, other.start);
        std::swap(this->last, other.last);
        std::swap(this->total_count, other.total_count);
        std::swap(this->part_count, other.part_count);
    }

    void copy_from(const collect_rope<T, PartCapacity> &other)
    {
        auto current = other.start;

        while (current != nullptr)
        {
            this->append_rope();

            for (size_t i = 0; i < current.count; i++)
            {
                this->item_allocator.construct(this->last->data + i, current.data[i]);
            }

            current = current.next;
        }

        this->total_count = other.total_count;
    }

    iterator begin()
    {
        return iterator(this->start);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    void push_back(const T &item)
    {
        this->total_count++;

        if (this->last == nullptr || this->last->count == PartCapacity)
        {
            this->append_rope();
        }

        this->item_allocator.construct(this->last->data + this->last->count, item);
        this->last->count++;
    }

    size_t size() const
    {
        return this->total_count;
    }

    size_t parts() const
    {
        return this->part_count;
    }

    size_t part_size() const
    {
        return PartCapacity;
    }

    // Copy assignment -> Do deep copy
    collect_rope &operator=(const collect_rope<T, PartCapacity> &a)
    {
        if (&a == this)
            return *this;

        this->release_resources();
        this->copy_from(a);

        return *this;
    }

    //// Move assignment -> Transfer ownership
    collect_rope &operator=(collect_rope<T, PartCapacity> &&a)
    {
        if (&a == this)
            return *this;

        this->release_resources();
        this->swap(a);

        return *this;
    }
};

template <class T, int PartCapacity>
collect_rope<T, PartCapacity>::collect_rope(const collect_rope<T, PartCapacity> &copy) : collect_rope()
{
    this->copy_from(copy);
}

template <class T, int PartCapacity>
collect_rope<T, PartCapacity>::collect_rope(collect_rope<T, PartCapacity> &&a) : collect_rope()
{
    this->swap(a);
}

template <class T, int PartCapacity>
void collect_rope<T, PartCapacity>::append_rope()
{
    auto newItems = this->item_allocator.allocate(PartCapacity);
    auto nextElement = this->element_allocator.allocate(1);

    rope_element element;
    element.next = nullptr;
    element.count = 0;
    element.data = newItems;

    this->element_allocator.construct(nextElement, element);

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

    this->part_count++;
}

template <class T, int PartCapacity>
void collect_rope<T, PartCapacity>::release_resources()
{
    auto current = this->start;
    auto next = current;

    while (current != nullptr)
    {
        next = current.next;

        for (size_t i = 0; i < current->count; i++)
        {
            this->item_allocator.destroy(next->data + i);
        }

        this->item_allocator.deallocate(current->data, PartCapacity);
        this->element_allocator.deallocate(current, 1);

        current = next;
    }

    this->start = nullptr;
    this->last = nullptr;
    this->total_count = 0;
    this->part_count = 0;
}

} // namespace util