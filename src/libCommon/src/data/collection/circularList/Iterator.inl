#include "libCommon/data/collection/List.hpp"
#include "libCommon/Defs.hpp"

#ifdef DEBUG
template <class T, class TAllocator>
util::collections::List<T, TAllocator>::Iterator::Iterator(T *pos, T *end, uint32_t validationToken) : pos(pos),
                                                                                                       end(end)
{
}
#else
template <class T, class TAllocator>
util::collections::List<T, TAllocator>::Iterator::Iterator(T *pos) : pos(pos)
{
}
#endif

template <class T, class TAllocator>
util::collections::List<T, TAllocator>::Iterator util::collections::List<T, TAllocator>::Iterator::operator++()
{
#ifdef DEBUG

#endif

    var res = *this;

    this->pos++;

    return res;
}

template <class T, class TAllocator>
util::collections::List<T, TAllocator>::Iterator &util::collections::List<T, TAllocator>::Iterator::operator++(int)
{
    this->pos++;

    return *this;
}

template <class T, class TAllocator>
util::collections::List<T, TAllocator>::Iterator util::collections::List<T, TAllocator>::Iterator::operator+(int)
{
    return Iterator(this->pos +)
}

template <class T, class TAllocator>
util::collections::List<T, TAllocator>::Iterator &util::collections::List<T, TAllocator>::Iterator::operator+=(int)
{
}

template <class T, class TAllocator>
util::collections::List<T, TAllocator>::Iterator util::collections::List<T, TAllocator>::Iterator::operator-(int)
{
}

template <class T, class TAllocator>
util::collections::List<T, TAllocator>::Iterator &util::collections::List<T, TAllocator>::Iterator::operator-=(int)
{
}

template <class T, class TAllocator>
bool util::collections::List<T, TAllocator>::Iterator operator==(const Iterator &)
{
}

template <class T, class TAllocator>
bool util::collections::List<T, TAllocator>::Iterator operator!=(const Iterator &)
{
}

template <class T, class TAllocator>
bool util::collections::List<T, TAllocator>::Iterator operator>=(const Iterator &)
{
}

template <class T, class TAllocator>
bool util::collections::List<T, TAllocator>::Iterator operator>(const Iterator &)
{
}

template <class T, class TAllocator>
bool util::collections::List<T, TAllocator>::Iterator operator<=(const Iterator &)
{
}

template <class T, class TAllocator>
bool util::collections::List<T, TAllocator>::Iterator operator<(const Iterator &)
{
}

template <class T, class TAllocator>
T &util::collections::List<T, TAllocator>::Iterator operator*()
{
}

template <class T, class TAllocator>
const T &util::collections::List<T, TAllocator>::Iterator operator*() const
{
}

template <class T, class TAllocator>
T *util::collections::List<T, TAllocator>::Iterator operator->()
{
}

template <class T, class TAllocator>
const T *util::collections::List<T, TAllocator>::Iterator operator->() const
{
}
