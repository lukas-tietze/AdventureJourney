#pragma once

#include <iostream>

namespace util
{
template <class T>
class IteratorPrintWrapper
{
private:
    T begin;
    T end;
    std::string seperator;

public:
    IteratorPrintWrapper(const T &begin, const T &end, const std::string &sep) : begin(begin),
                                                                                 end(end),
                                                                                 seperator(sep)
    {
    }

    const T &GetBegin() const
    {
        return this->begin;
    }

    const T &GetEnd() const
    {
        return this->end;
    }

    const std::string &GetSeperator() const
    {
        return this->seperator;
    }
};

template <class T>
std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<T> &wrapper)
{
    auto pos = wrapper.GetBegin();
    auto end = wrapper.GetEnd();

    if (pos != end)
        s << *pos;

    ++pos;

    for (; pos != end; ++pos)
        s << wrapper.GetSeperator() << *pos;

    return s;
}

template <class T>
IteratorPrintWrapper<T> WrapIterable(T begin, T end, const std ::string &seperator = ", ")
{
    return IteratorPrintWrapper<T>(begin, end, seperator);
}

template <class T>
class MultiIterator
{
};
} // namespace util
