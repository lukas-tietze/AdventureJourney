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
    IteratorPrintWrapper(const T &begin, const T &end, const std::string &) : begin(begin),
                                                                              end(end),
                                                                              seperator(seperator)
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
    for (auto pos = wrapper.GetBegin(); pos != wrapper.GetEnd(); ++pos)
        s << *pos << wrapper.GetSeperator();
}

template <class T>
IteratorPrintWrapper<T> WrapIterable(T begin, T end, std::string seperator = "")
{
    return IteratorPrintWrapper<T>(begin, end, seperator);
}

template <class T>
class MultiIterator
{
};
} // namespace util
