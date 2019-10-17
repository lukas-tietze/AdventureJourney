#pragma once

#include <type_traits>

namespace util
{
template <typename TCounter>
class _RangeIterator
{
private:
    TCounter value;
    TCounter step;

public:
    Iterator(TCounter value, TCounter step) : value(value),
                                              step(step)
    {
    }

    bool operator==(const Iterator &other) const
    {
        return this->value == other.value &&
               this->step == other.step;
    }

    bool operator!=(const Iterator &other) const
    {
        return this->value != other.value ||
               this->step != other.step;
    }

    bool operator>(const Iterator &other) const
    {
        return this->value > other.value &&
               this->step == other.step;
    }

    bool operator>=(const Iterator &other) const
    {
        return this->value >= other.value &&
               this->step == other.step;
    }

    bool operator<(const Iterator &other) const
    {
        return this->value < other.value &&
               this->step == other.step;
    }

    bool operator<=(const Iterator &other) const
    {
        return this->value <= other.value &&
               this->step == other.step;
    }

    Iterator<typename TCounter> operator++()
    {
        auto res = *this;

        this->value += this->step;

        return res;
    }

    Iterator<typename TCounter> &operator++(int)
    {
        this->value += this->step;

        return &this;
    }

    Iterator<typename TCounter> operator+(int i)
    {
        return Iterator(this->value + i * this->step);
    }

    Iterator<typename TCounter> operator-(int i)
    {
        return Iterator(this->value - i * this->step);
    }

    Iterator<typename TCounter> &operator+=(int i)
    {
        this->value += i * this->step;

        return *this;
    }

    Iterator<typename TCounter> &operator-=(int i)
    {
        this->value -= i * this->step;

        return *this;
    }

    TCOunter operator*()
    {
        return this->value;
    }
};

template <typename TCounter = int>
class Range
{
private:
    TCounter start;
    TCounter end;
    TCounter step;

public:
    using _RangeIterator<TCounter> = iterator;

    Range(TCounter start, TCounter end, TCounter step) : start(start),
                                                         end(end),
                                                         step(step)
    {
    }

    iterator begin() const
    {
        return iterator(this->start, this->step);
    }

    iterator end() const
    {
        return iterator(this->end, this->step);
    }
};
} // namespace  util
