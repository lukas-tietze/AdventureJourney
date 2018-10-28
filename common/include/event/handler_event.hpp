#pragma once

#include <list>
#include <vector>
#include <algorithm>

#include "defs.hpp"

namespace util
{
template <class THandler, class TArgs>
class handler_event
{
  protected:
    std::list<THandler> handler;

  public:
    virtual void operator+=(THandler &handler)
    {
        if (std::find(this->handler.begin(), this->handler.end(), handler) == this->handler.end())
            this->handler.push_back(handler);
    }

    virtual void operator-=(THandler &handler)
    {
        auto pos = std::find(this->handler.begin(), this->handler.end(), handler);

        if (pos != this->handler.end())
            this->handler.erase(pos);
    }

    virtual void operator()(TArgs &args) const
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

template <class TArgs>
class member_handler_base
{
  public:
    virtual ~member_handler_base()
    {
    }
    
    virtual void operator()(TArgs &args) const = 0;
    virtual bool operator==(const member_handler_base &other) const = 0;
};

template <class TArgs>
class member_handler_wrapper
{
  public:
    member_handler_base<TArgs> *wrapped_item;

    void operator()(TArgs &args) const
    {
        (*this->wrapped_item)(args);
    }

    bool operator==(const member_handler_wrapper &other)
    {
        return (*this->wrapped_item) == (*other.wrapped_item);
    }
};

template <class T, class TArgs>
class member_handler : public member_handler_base<TArgs>
{
  public:
    T *obj;
    void (T::*f)(TArgs &);

    void operator()(TArgs &args) const
    {
        (obj->*f)(args);
    }

    bool operator==(const member_handler_base<TArgs> &other) const
    {
        if (const member_handler *m = dynamic_cast<const member_handler *>(&other))
            return this->obj == m->obj && this->f == m->f;

        return false;
    }
};

template <class T, class TArgs>
member_handler_wrapper<TArgs> make_member_handler(T *obj, void (T::*f)(TArgs &))
{
    auto handler = new member_handler<T, TArgs>();
    handler->obj = obj;
    handler->f = f;

    member_handler_wrapper<TArgs> wrapper;
    wrapper.wrapped_item = handler;

    return wrapper;
}

template <class TArgs>
class member_event : public handler_event<member_handler_wrapper<TArgs>, TArgs>
{
  public:
    void operator-=(member_handler_wrapper<TArgs> &handler)
    {
        auto pos = std::find(this->handler.begin(), this->handler.end(), handler);

        if (pos != this->handler.end())
        {
            delete (*pos).wrapped_item;
            this->handler.erase(pos);
        }
    }

    void remove_all(void *obj)
    {
        std::vector<member_handler_wrapper<TArgs>> toRemove;

        for (const auto &item : this->handler())
        {
            if (item.obj == obj)
                toRemove.push_back(item);
        }

        for (auto i = toRemove.rbegin(), end = toRemove.rend(); i != end; i++)
        {
            (*this) -= *i;
        }
    }
};
} // namespace util