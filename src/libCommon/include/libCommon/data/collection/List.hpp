#pragma once

#include <initializer_list>
#include <iterator>

namespace util
{
namespace collections
{
template <typename T>
class _ListIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
        T *pos;

public:
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
        T &operator*();
        const T &operator*() const;
        T *operator->();
        const T *operator->() const;
};

template <typename T>
class _ListConstIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
        const T *pos;

public:
        Iterator(T *pos);
#endif

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
        const T &operator*() const;
        const T *operator->() const;
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
        using Iterator = _ListIterator<T>;
        using ConstIterator = Iterator<T>;
        using ReverseIterator = std::reverse_iterator<_ListIterator<T>>;
        using ConstReverseIterator = std::reverse_iterator<_ListConstIterator<T>>;

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

#include "libCommon/src/data/collection/circularList/Iterator.inl"
#include "libCommon/src/data/collection/circularList/Iterator.inl"
#include "libCommon/src/data/collection/circularList/Iterator.inl"
#include "libCommon/src/data/collection/circularList/Iterator.inl"
#include "libCommon/src/data/collection/circularList/List.inl"
