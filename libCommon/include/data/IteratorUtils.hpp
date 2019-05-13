#pragma once

#include <iostream>

namespace util
{
namespace
{
template <class T>
struct DefaultConverter
{
    const auto &operator()(const T &t) const
    {
        return *t;
    }
};

template <class T>
struct PointerToRefConverter
{
    const auto &operator()(const T &t) const
    {
        return **t;
    }
};
} // namespace

template <class TIterator, class TConverter>
class IteratorPrintWrapper
{
private:
    TIterator begin;
    TIterator end;
    std::string seperator;
    TConverter converter;

public:
    IteratorPrintWrapper(const TIterator &begin, const TIterator &end, const std::string &sep) : begin(begin),
                                                                                                 end(end),
                                                                                                 converter(),
                                                                                                 seperator(sep)
    {
    }

    IteratorPrintWrapper(const TIterator &begin, const TIterator &end, const TConverter &conv, const std::string &sep) : begin(begin),
                                                                                                                         end(end),
                                                                                                                         converter(conv),
                                                                                                                         seperator(sep)
    {
    }

    const TIterator &GetBegin() const
    {
        return this->begin;
    }

    const TIterator &GetEnd() const
    {
        return this->end;
    }

    const TConverter &GetConverter() const
    {
        return this->converter;
    }

    const std::string &GetSeperator() const
    {
        return this->seperator;
    }
};

template <class TIterator, class TConverter>
std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<TIterator, TConverter> &wrapper)
{
    auto pos = wrapper.GetBegin();
    auto end = wrapper.GetEnd();

    if (pos != end)
        s << wrapper.GetConverter()(pos);
    else
        return s;

    ++pos;

    for (; pos != end; ++pos)
        s << wrapper.GetSeperator() << wrapper.GetConverter()(pos);

    return s;
}

template <class TIterator, class TConverter>
IteratorPrintWrapper<TIterator, TConverter> WrapConvertIterable(TIterator begin, TIterator end, const TConverter &converter, const std::string &seperator = "")
{
    return IteratorPrintWrapper<TIterator, TConverter>(begin, end, converter, seperator);
}

template <class TIterator>
IteratorPrintWrapper<TIterator, PointerToRefConverter<TIterator>> WrapPointerIterable(TIterator begin, TIterator end, const std::string &seperator = "")
{
    return IteratorPrintWrapper<TIterator, PointerToRefConverter<TIterator>>(begin, end, seperator);
}

template <class TIterator>
IteratorPrintWrapper<TIterator, DefaultConverter<TIterator>> WrapIterable(TIterator begin, TIterator end, const std::string &seperator = "")
{
    return IteratorPrintWrapper<TIterator, DefaultConverter<TIterator>>(begin, end, seperator);
}
} // namespace util
