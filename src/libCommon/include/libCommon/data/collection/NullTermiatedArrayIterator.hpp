#pragma once

#include <type_traits>

namespace util
{
template <typename T, bool TIsConst>
class NullTerminatedArrayIterator
{
public:
    using iterator_category = random_access_iterator_tag;
    using pointer = std::conditional_t<TIsConst, const T *, T *>;
    using reference = std::conditional_t<TIsConst, const T &, T &>;
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    NullTerminatedArrayIterator(pointer *pos) : pos(pos)
    {
    }

    NullTerminatedArrayIterator(const NullTerminatedArrayIterator &) = default;

    template <bool TOtherIssConst, typename = std::enable_if_t<TIsConst || !TOtherIsConst>>
    NullTerminatedArrayIterator(const NullTerminatedArrayIterator<T, TOtherIsConst> &other) : pos(other.pos)
    {
    }

    template <bool TOtherIsConst>
    bool operator>(const NullTerminatedArrayIterator<T, TOtherIsConst> &other) const
    {
        return this->pos > other.pos;
    }

    template <bool TOtherIsConst>
    bool operator<(const NullTerminatedArrayIterator<T, TOtherIsConst> &other) const
    {
        return this->pos < other.pos;
    }

    template <bool TOtherIsConst>
    bool operator>=(const NullTerminatedArrayIterator<T, TOtherIsConst> &other) const
    {
        return this->pos >= other.pos;
    }
    template <bool TOtherIsConst>
    bool operator<=(const NullTerminatedArrayIterator<T, TOtherIsConst> &other) const
    {
        return this->pos <= other.pos;
    }

    template <bool TOtherIsConst>
    bool operator==(const NullTerminatedArrayIterator<T, TOtherIsConst> &other) const
    {
        return this->pos == other.pos;
    }

    template <bool TOtherIsConst>
    bool operator!=(const NullTerminatedArrayIterator<T, TOtherIsConst> &other) const
    {
        return this->pos != other.pos;
    }

    NullTerminatedArrayIterator &operator+=(size_t n)
    {
        this->pos += n;

        return *this;
    }

    NullTerminatedArrayIterator &operator-=(size_t n)
    {
        this->pos -= n;

        return *this;
    }

    NullTerminatedArrayIterator operator+(size_t n) const
    {
        return NullTerminatedArrayIterator(this->pos + n);
    }

    NullTerminatedArrayIterator operator-(size_t n) const
    {
        return NullTerminatedArrayIterator(this->pos - n);
    }

    template <bool TOtherIsConst>
    difference_type operator-(const NullTerminatedArrayIterator<T, TOtherIsConst> &other)
    {
        return this->pos - other.pos;
    }

    NullTerminatedArrayIterator &operator++()
    {
        this->pos++;

        return *this;
    }

    NullTerminatedArrayIterator operator++(int)
    {
        auto res = *this;

        this->pos++;

        return res;
    }

    NullTerminatedArrayIterator &operator--()
    {
        this->pos--;

        return *this;
    }

    NullTerminatedArrayIterator operator++(int)
    {
        auto res = *this;

        this->pos--;

        return res;
    }

    reference operator*()
    {
        return *this->pos;
    }

    pointer operator->()
    {
        return this->pos;
    }

private:
    pointer *pos;
};

template <typename T>
NullTerminatedArrayIterator<T, false> BeginNullTerminatedArray(T *t)
{
    return NullTerminatedArrayIterator<T, false>(t);
}

template <typename T>
NullTerminatedArrayIterator<T, false> EndNullTerminatedArray()
{
    return NullTerminatedArrayIterator<T, false>(nullptr);
}

template <typename T>
NullTerminatedArrayIterator<T, false> EndNullTerminatedArray(T *t)
{
    return NullTerminatedArrayIterator<T, false>(nullptr);
}

template <typename T>
NullTerminatedArrayIterator<T, true> CBeginNullTerminatedArray(T *t)
{
    return NullTerminatedArrayIterator<T, true>(t);
}

template <typename T>
NullTerminatedArrayIterator<T, true> CEndNullTerminatedArray()
{
    return NullTerminatedArrayIterator<T, true>(nullptr);
}

template <typename T>
NullTerminatedArrayIterator<T, true> CEndNullTerminatedArray(T *t)
{
    return NullTerminatedArrayIterator<T, true>(nullptr);
}

namespace nta
{
template <typename T>
NullTerminatedArrayIterator<T, false> begin(T *t)
{
    return NullTerminatedArrayIterator<T, false>(t);
}

template <typename T>
NullTerminatedArrayIterator<T, false> end()
{
    return NullTerminatedArrayIterator<T, false>(nullptr);
}

template <typename T>
NullTerminatedArrayIterator<T, false> end(T *t)
{
    return NullTerminatedArrayIterator<T, false>(nullptr);
}

template <typename T>
NullTerminatedArrayIterator<T, true> cbegin(T *t)
{
    return NullTerminatedArrayIterator<T, true>(t);
}

template <typename T>
NullTerminatedArrayIterator<T, true> cend()
{
    return NullTerminatedArrayIterator<T, true>(nullptr);
}

template <typename T>
NullTerminatedArrayIterator<T, true> cend(T *t)
{
    return NullTerminatedArrayIterator<T, true>(nullptr);
}
} // namespace nta

template <class T>
class NullTerminatedArray
{
public:
    NullTerminatedArray(T *data) : data(data)
    {
    }

    NullTerminatedArrayIterator<T, false> begin()
    {
        return NullTerminatedArrayIterator<T, false>(this->data);
    }

    NullTerminatedArrayIterator<T, false> end()
    {
        return NullTerminatedArrayIterator<T, false>(nullptr);
    }

    NullTerminatedArrayIterator<T, true> cbegin()
    {
        return NullTerminatedArrayIterator<T, true>(this->data);
    }

    NullTerminatedArrayIterator<T, true> cend()
    {
        return NullTerminatedArrayIterator<T, true>(nullptr);
    }

private:
    T *data;
};
} // namespace util
