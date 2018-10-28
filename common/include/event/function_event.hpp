#pragma once

#include <vector>
#include <algorithm>

#include "defs.hpp"

namespace util
{
template <class TArgs>
class function_event
{
  public:
    typedef void (*event_function)(TArgs &);

    void operator+=(event_function function);
    void operator-=(event_function function);
    void operator()(TArgs &args) const;

    uint size() const;

  private:
    std::vector<event_function> handler;
};

template <class TArgs>
void function_event<TArgs>::operator+=(util::function_event<TArgs>::event_function handler)
{
    if (std::find(this->handler.begin(), this->handler.end(), handler) == this->handler.end())
        this->handler.push_back(handler);
}

template <class TArgs>
void function_event<TArgs>::operator-=(util::function_event<TArgs>::event_function handler)
{
    auto pos = std::find(this->handler.begin(), this->handler.end(), handler);

    if (pos != this->handler.end())
        this->handler.erase(pos);
}

template <class TArgs>
void function_event<TArgs>::operator()(TArgs &args) const
{
    for (const auto &item : this->handler)
    {
        (*item)(args);
    }
}

template <class TArgs>
uint function_event<TArgs>::size() const
{
    return this->handler.size();
}
} // namespace util