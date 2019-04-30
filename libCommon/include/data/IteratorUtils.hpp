#pragma once

#include <iostream>

namespace util
{
template <class T>
class IteratorPrintWrapper
{
    friend std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<T> &wrapper);

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
};

template <class T>
std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<T> &wrapper)
{
    for (auto pos = wrapper.begin; pos != end; ++pos)
        s << *pos << wrapper.seperator;
}

template <class T>
IteratorPrintWrapper<T> WrapIterable(T begin, T end, std::string seperator = "")
{
    return IteratorPrintWrapper<T>(begin, end, seperator);
}
} // namespace util
