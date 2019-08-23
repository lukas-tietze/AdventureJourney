#pragma once

#include <map>

namespace util
{
template <class TItem, class TIndex>
class IndexMapper
{
  private:
    TIndex last;
    TIndex startIndex;
    std::map<TItem, TIndex> map;

  public:
    IndexMapper() : last(),
                    startIndex(last),
                    map()
    {
    }

    IndexMapper(TIndex start) : last(start),
                                startIndex(start),
                                map()
    {
    }

    TIndex operator[](const TItem &item)
    {
        auto pos = this->map.find(item);

        if (pos == this->map.end())
        {
            auto next = this->last;
            this->last++;

            this->map.insert(std::make_pair(item, next));

            return next;
        }
        else
        {
            return pos->second;
        }
    }

    void Clear()
    {
        this->map.clear();
        this->last = startIndex;
    }
};
} // namespace util
