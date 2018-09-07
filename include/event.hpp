#pragma once

#include <vector>
#include <csignal>
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
    // TODO: Fixen!
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

enum class signal
{
    Abort = SIGABRT,
    FloatingPointException = SIGFPE,
    IllegalInstruction = SIGILL,
    Interrupt = SIGINT,
    SegmentationViolation = SIGSEGV,
    Terminate = SIGTERM,
    Unknown = 0,
};

struct signal_event_args
{
    util::signal signal;
    int code;
};

class signal_event : public function_event<signal_event_args>
{
  public:
    signal_event();
    ~signal_event();
};
} // namespace util