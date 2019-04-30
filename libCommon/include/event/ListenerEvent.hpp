#pragma once

#include <vector>
#include <algorithm>

#include "Defs.hpp"

namespace util
{
template <class T>
class IEventListener
{
  public:
    virtual void HandleEvent(T &args) = 0;
};

template <class T>
class ListenerEvent
{
  private:
    std::vector<IEventListener<T> *> listeners;

  public:
    ListenerEvent() : listeners()
    {
    }

    void operator+=(IEventListener<T> *listener)
    {
        if (std::find(this->listeners.begin(), this->listeners.end(), listener) == this->listeners.end())
        {
            this->listeners.push_back(listener);
        }
    }

    void operator-=(IEventListener<T> *listener)
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
            listener->HandleEvent(args);
        }
    }

    uint Size() const
    {
        return this->listeners.size();
    }
};
} // namespace util