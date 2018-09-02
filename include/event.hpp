#pragma once

#include <vector>
#include <csignal>

namespace util
{
template <class T>
class i_event_listener
{
  public:
    virtual void handle_event() = 0;
};

template <class T>
class listener_event
{
  private:
    std::vector<i_event_listener<T> *> listeners;

  public:
    listener_event();

    void operator+=(i_event_listener<T> *listener)
    {
        if (this.listeners.find(listener) == std::vector<i_event_listener<T>>::npos)
        {
            this.listeners.push_back(listener);
        }
    }

    void operator-=(i_event_listener<T> listener)
    {
        auto pos = this.listeners.find(listener);

        if (pos != std::vector<i_event_listener<T>>::npos)
        {
            this.listeners.remove(pos);
        }
    }
};

template <class T>
class function_event
{
  public:
    typedef void (*event_function)(T &);

    struct event_handler
    {
        void *target;
        event_function function;
    };

    void operator+=(event_function function)
    {
        *this += {nullptr, function};
    }

    void operator-=(event_function function)
    {
        *this -= {nullptr, function};
    }

    void operator+=(const event_handler &handler);
    void operator-=(const event_handler &data);
    void operator()(T &args) const;

  private:
    std::vector<event_handler> targets;
};

template <class T>
void function_event<T>::operator+=(const event_handler &handler)
{
    this->targets.push_back(handler);
}

template <class T>
void function_event<T>::operator-=(const event_handler &handler)
{
    auto pos = this->targets.find(handler);

    if (pos != this->targets.npos)
        this->targets.erase(pos);
}

template <class T>
void function_event<T>::operator()(T &args) const
{
    // TODO: Fixen!
    // for (const auto &item : this->targets)
    // {
    //     if (item.target != nullptr)
    //         (item.target->*item.function)(args);
    //     else
    //         (*item.function)(args);
    // }
}

enum class signal
{
    SigAbrt,
    SigFpe,
    SigIll,
    SigInt,
    SigSegv,
    SigTerm,
    Unknown,
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