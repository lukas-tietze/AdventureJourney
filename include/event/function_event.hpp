#pragma once

#include <vector>
#include <algorithm>

#include "defs.hpp"

namespace util
{
template <class T>
class function_event
{
  public:
    typedef void (*event_function)(T &);

    void operator+=(event_function function);
    void operator-=(event_function function);
    void operator()(T &args) const;

    uint size() const;

  private:
    std::vector<event_function> handler;
};

template <class T>
void function_event<T>::operator+=(util::function_event<T>::event_function handler)
{
    if (std::find(this->handler.begin(), this->handler.end(), handler) == this->handler.end())
        this->handler.push_back(handler);
}

template <class T>
void function_event<T>::operator-=(util::function_event<T>::event_function handler)
{
    auto pos = std::find(this->handler.begin(), this->handler.end(), handler);

    if (pos != this->handler.end())
        this->handler.erase(pos);
}

template <class T>
void function_event<T>::operator()(T &args) const
{
    for (const auto &item : this->handler)
    {
        (*item)(args);
    }
}

template <class T>
uint function_event<T>::size() const
{
    return this->handler.size();
}
} // namespace util