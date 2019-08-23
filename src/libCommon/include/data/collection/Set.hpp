#pragma once

#include <functional>

namespace util
{
template <class T, class THash = std::hash<T>, class TEquals = std::equal_to<T>, class TAlloc = std::allocator<T>>
class Set
{
private:
    size_t bucketSize;

    T *data;
    T *last;
    T *end;

    TEquals eqComparer;
    THash hash;

    void resize;

    void CopyFrom(const Set &);
    void TransferFrom(Set &) public : Set();

public:
    class Iterator
    {
    };

    class ConstIterator
    {
    };

    Set();
    Set(const Set &);
    Set(Set &&);

    bool Contains(const T &) const;
    void Add(const T &);
    bool Remove(const T &);
};
} // namespace util
