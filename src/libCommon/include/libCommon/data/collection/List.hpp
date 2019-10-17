#pragma once

#include <initializer_list>
#include <iterator>

namespace util
{
namespace collections
{
template <typename T, bool IsConst>
class _ListIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
    T *pos;

public:
    using reference = typename std::conditional_t<IsConst, const T &, T &>;
    using pointer = typename std::conditional_t<IsConst, const T *, T *>;

    Iterator(T *pos);

    Iterator operator++();
    Iterator &operator++(int);
    Iterator operator+(int);
    Iterator &operator+=(int);
    Iterator operator-(int);
    Iterator &operator-=(int);
    bool operator==(const Iterator &);
    bool operator!=(const Iterator &);
    bool operator>=(const Iterator &);
    bool operator>(const Iterator &);
    bool operator<=(const Iterator &);
    bool operator<(const Iterator &);
    reference operator*();
    pointer operator->();
};

template <typename T, typename TAllocator>
class List
{
private:
    static TAllocator allocator;
    T *memStart;
    T *memEnd;
    T *end;

public:
    using Iterator = _ListIterator<T, false>;
    using ConstIterator = _ListIterator<T, true>;
    using ReverseIterator = std::reverse_iterator<_ListIterator<T, false>>;
    using ConstReverseIterator = std::reverse_iterator<_ListIterator<T, true>>;

    List(const List &copy);
    List(List &&other);
    List(const std::initializer_list<T> &values);
    List();
    List(int size);

    List &assign(const List &copy);
    List &assign(List &&other);
    List &assign(const std::initializer_list<T> &values);

    void AddBack(const T &);
    void AddFront(const T &);
    template <typename T...>
    void EmplaceBack(const T... &args);
    template <typename T...>
    void EmplaceFront(const T... &args);
    size_t Count();
    size_t Capacity();
    void Resize(size_t);
    void Reserve(size_t);
    const T &Head() const;
    T &Head();
    const T &Tail() const;
    T &Tail();

    void Clear();
    void PopHead();
    void PopTail();
    void RealignHead();
    void Trim();

    Iterator begin();
    ConstIterator begin() const;
    Iterator begin();
    ConstIterator begin() const;
    Iterator begin();
    ConstIterator begin() const;
    Iterator begin();
    ConstIterator begin() const;

    List &
    operator=(const List &copy);
    List &operator=(List &&other);
    List &operator=(const std::initializer_list<T> &values);
};
} // namespace collections
} // namespace util