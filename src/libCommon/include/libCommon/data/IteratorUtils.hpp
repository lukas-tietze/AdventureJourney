#pragma once

#include <iostream>

namespace util
{
template <typename T>
struct DefaultConverter
{
    const auto &operator()(const T &t) const
    {
        return *t;
    }
};

template <typename T>
struct PointerToRefConverter
{
    const auto &operator()(const T &t) const
    {
        return **t;
    }
};

template <typename TIterator, typename TSeperator, typename TConverter>
class IteratorPrintWrapper
{
private:
    TIterator begin;
    TIterator end;
    TSeperator seperator;
    TConverter converter;

public:
    IteratorPrintWrapper(const TIterator &begin, const TIterator &end, const TSeperator &sep, const TConverter &conv) : begin(begin),
                                                                                                                        end(end),
                                                                                                                        seperator(sep),
                                                                                                                        converter(conv)

    {
    }

    TIterator begin()
    {
        return this->begin;
    }

    TIterator end()
    {
        return this->end;
    }

    template <typename TNewSeperator>
    IteratorPrintWrapper<TIterator, TNewSeperator, TConverter> WithSeperator(const TNewSeperator &)
    {
    }

    template <typename TNewConverter>
    IteratorPrintWrapper<TIterator, TSeperator, TNewConverter> ConvertTo(const TNewConverter &)
    {
    }
};

template <typename TIterator>
std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<TIterator, void, void> &wrapper)
{
    for (const auto &item : wrapper)
    {
        s << item;
    }

    return s;
}

template <typename TIterator, typename TSeperator>
std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<TIterator, TSeperator, void> &wrapper)
{
    auto pos = wrapper.begin();

    if (pos != wrapper.end())
    {
        s << *pos;
    }

    while (++pos != wrapper.end())
    {
        s << wrapper.GetSeperator() << *pos;
    }

    return s;
}

template <typename TIterator, typename T>
std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<TIterator, void, void> &wrapper)
{
    for (const auto &item : wrapper)
    {
        s << wrapper.GetConverter()(item);
    }

    return s;
}

template <typename TIterator, typename TSeperator, typename TConverter>
std::ostream &operator<<(std::ostream &s, const IteratorPrintWrapper<TIterator, void, void> &wrapper)
{
    auto pos = wrapper.begin();

    if (pos != wrapper.end())
    {
        s << wrapper.GetConverter()(*pos);
    }

    while (++pos != wrapper.end())
    {
        s << wrapper.GetSeperator() << wrapper.GetConverter()(*pos);
    }

    return s;
}

template <typename TIterator>
IteratorPrintWrapper<TIterator, void, void> WrapIterable(TIterator begin, TIterator end)
{
    return IteratorPrintWrapper<TIterator, TSeperator, TConverter>(begin, end);
}
} // namespace util
