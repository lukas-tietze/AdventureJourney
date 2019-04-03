#pragma once

#include <iostream>

namespace util
{
template <class T>
class IteratorPrintWrapper
{
};

template <class T>
std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<T> &wrapper)
{
}

template <class T>
IteratorPrintWrapper<T> WrapIterable(T begin, T end)
{
}
} // namespace util
