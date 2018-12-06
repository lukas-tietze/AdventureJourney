#pragma once

#include "vector"

namespace util
{
template <class TIterator, class TItem>
size_t IndexOf(const TIterator &start, const TIterator &end, const TItem &item)
{
    size_t i = 0;
    TIterator pos = start;

    while (pos != end && *pos != item)
    {
        i++;
        pos++;
    }

    return i;
}
} // namespace util