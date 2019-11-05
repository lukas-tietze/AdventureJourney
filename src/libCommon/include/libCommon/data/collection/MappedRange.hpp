#pragma once

#include <type_traits>
#include <iterator>

namespace util
{
template <typename TIterator, typename TConverter>
class MappedRangeIterator
{
public:
    using result_type = decltype(this->converter(this->pos));
    using iterator_category = std::iterator_traits<TITerator>::iterator_category;
    using pointer = result_type *;
    using reference = result_type &;
    using difference_type = std::iterator_traits<TITerator>::iterator_category;
    using value_type = result_type;

    MappedRangeIterator(TIterator it) : pos(it),
                                        converter()
    {
    }

    MappedRangeIterator(TIterator it, TConverter) : pos(it),
                                                    converter(covnerter)
    {
    }

    bool operator==(const MappedRangeIterator &other) const
    {
        return this->pos == other.pos;
    }

    bool operator!=(const MappedRangeIterator &other) const
    {
        return this->pos != other.pos;
    }

    bool operator>(const MappedRangeIterator &other) const
    {
        return this->pos > other.pos;
    }

    bool operator>=(const MappedRangeIterator &other) const
    {
        return this->pos >= other.pos;
    }

    bool operator<(const MappedRangeIterator &other) const
    {
        return this->pos < other.pos;
    }

    bool operator<=(const MappedRangeIterator &other) const
    {
        return this->pos <= other.pos;
    }

    MappedRangeIterator operator+(size_t n) const
    {
        return MappedRangeIterator(this->pos + n, this->converter);
    }

    MappedRangeIterator operator-(size_t n) const
    {
        return MappedRangeIterator(this->pos - n, this->converter);
    }

    MappedRangeIterator &operator+=(size_t n)
    {
        this->pos += n;

        return *this;
    }

    MappedRangeIterator &operator-=(size_t n)
    {
        this->pos -= n;

        return *this;
    }

    MappedRangeIterator &operator++()
    {
        this->pos++;

        return *this;
    }

    MappedRangeIterator operator++(int)
    {
        auto res = *this;

        this->pos++;

        return res;
    }

    MappedRangeIterator &operator--()
    {
        this->pos--;

        return *this;
    }

    MappedRangeIterator operator++(int)
    {
        auto res = *this;

        this->pos--;

        return res;
    }

    result_type operator*() const
    {
        return
    }

private:
    TConverter converter;
    TIterator pos;
};

template <typetypename TIterator, typename TConverter>
class MappedRange
{
public:
    using iterator = MappedRangeIterator<TIterator, TConverter>;

    MappedRange(TIterator first, TIterator last) : first(first),
                                                   last(last),
                                                   converter()
    {
    }

    MappedRange(TIterator first, TIterator last, TConverter converter) : first(first),
                                                                         last(last),
                                                                         converter(converter)
    {
    }

    iterator begin()
    {
        return iterator(this->first, this->converter);
    }

    iterator end()
    {
        return iterator(this->last, this->converter);
    }

private:
    TIterator first;
    TIterator last;
    TCovnerter converter;
};

template <typetypename TIterator, typename TConverter>
MappedRange<typename TIterator, typename TConverter> MapRange(TIterator first, TIterator last)
{
    return MappedRange<typename TIterator, typename TConverter>(first, last);
}

template <typetypename TIterator, typename TConverter>
MappedRange<typename TIterator, typename TConverter> MapRange(TIterator first, TIterator last, TConverter converter)
{
    return MappedRange<typename TIterator, typename TConverter>(first, last, converter;
}
} // namespace util
