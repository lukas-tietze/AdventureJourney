#pragma once

#include <vector>
#include <algorithm>

#include "defs.hpp"

namespace util
{
template <class T>
class i_event_listener
{
  public:
    virtual void handle_event(T &args) = 0;
};

template <class T>
class listener_event
{
  private:
    std::vector<i_event_listener<T> *> listeners;

  public:
    listener_event() : listeners()
    {
    }

    void operator+=(i_event_listener<T> *listener)
    {
        if (std::find(this->listeners.begin(), this->listeners.end(), listener) == this->listeners.end())
        {
            this->listeners.push_back(listener);
        }
    }

    void operator-=(i_event_listener<T> *listener)
    {
        auto pos = std::find(this->listeners.begin(), this->listeners.end(), listener);

        if (pos != this->listeners.end())
        {
            this->listeners.erase(pos);
        }
    }

    void operator()(T &args)
    {
        for (const auto &listener : this->listeners)
        {
            listener->handle_event(args);
        }
    }

    uint size() const
    {
        return this->listeners.size();
    }
};
} // namespace util