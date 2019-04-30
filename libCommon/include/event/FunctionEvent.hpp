#pragma once

#include <vector>
#include <algorithm>

#include "Defs.hpp"

namespace util
{
template <class TArgs>
class FunctionEvent
{
  public:
    typedef void (*EventFunction)(TArgs &);

    void operator+=(EventFunction function);
    void operator-=(EventFunction function);
    void operator()(TArgs &args) const;

    uint Size() const;

  private:
    std::vector<EventFunction> handler;
};

template <class TArgs>
void FunctionEvent<TArgs>::operator+=(util::FunctionEvent<TArgs>::EventFunction handler)
{
    if (std::find(this->handler.begin(), this->handler.end(), handler) == this->handler.end())
        this->handler.push_back(handler);
}

template <class TArgs>
void FunctionEvent<TArgs>::operator-=(util::FunctionEvent<TArgs>::EventFunction handler)
{
    auto pos = std::find(this->handler.begin(), this->handler.end(), handler);

    if (pos != this->handler.end())
        this->handler.erase(pos);
}

template <class TArgs>
void FunctionEvent<TArgs>::operator()(TArgs &args) const
{
    for (const auto &item : this->handler)
    {
        (*item)(args);
    }
}

template <class TArgs>
uint FunctionEvent<TArgs>::Size() const
{
    return this->handler.size();
}
} // namespace util