#pragma once

#include <vector>
#include <algorithm>

#include "defs.hpp"

namespace util
{
template <class THandler, class TArgs>
class handler_event
{
  private:
    std::vector<THandler> handler;

  public:
    void operator+=(THandler &handler)
    {
        if (std::find(this->handler.begin(), this->handler.end(), handler) == this->handler.end())
            this->handler.push_back(handler);
    }

    void operator-=(THandler &handler)
    {
        auto pos = std::find(this->handler.begin(), this->handler.end(), handler);

        if (pos != this->handler.end())
            this->handler.erase(pos);
    }

    void operator()(TArgs &args) const
    {
        for (const auto &item : this->handler)
        {
            item(args);
        }
    }

    uint size() const
    {
        return this->handler.size();
    }
};
} // namespace util