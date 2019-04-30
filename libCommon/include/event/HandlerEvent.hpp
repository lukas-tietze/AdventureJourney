#pragma once

#include <list>
#include <vector>
#include <algorithm>

#include "Defs.hpp"

namespace util
{
template <class THandler, class TArgs>
class HandlerEvent
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

    uint Size() const
    {
        return this->handler.size();
    }
};

template <class TArgs>
class MemberHandlerBase
{
  public:
    virtual ~MemberHandlerBase()
    {
    }
    
    virtual void operator()(TArgs &args) const = 0;
    virtual bool operator==(const MemberHandlerBase &other) const = 0;
};

template <class TArgs>
class MemberHandlerWrapper
{
  public:
    MemberHandlerBase<TArgs> *wrapped_item;

    void operator()(TArgs &args) const
    {
        (*this->wrapped_item)(args);
    }

    bool operator==(const MemberHandlerWrapper &other)
    {
        return (*this->wrapped_item) == (*other.wrapped_item);
    }
};

template <class T, class TArgs>
class MemberHandler : public MemberHandlerBase<TArgs>
{
  public:
    T *obj;
    void (T::*f)(TArgs &);

    void operator()(TArgs &args) const
    {
        (obj->*f)(args);
    }

    bool operator==(const MemberHandlerBase<TArgs> &other) const
    {
        if (const MemberHandler *m = dynamic_cast<const MemberHandler *>(&other))
            return this->obj == m->obj && this->f == m->f;

        return false;
    }
};

template <class T, class TArgs>
MemberHandlerWrapper<TArgs> MakeMemberHandler(T *obj, void (T::*f)(TArgs &))
{
    auto handler = new MemberHandler<T, TArgs>();
    handler->obj = obj;
    handler->f = f;

    MemberHandlerWrapper<TArgs> wrapper;
    wrapper.wrapped_item = handler;

    return wrapper;
}

template <class TArgs>
class MemberEvent : public HandlerEvent<MemberHandlerWrapper<TArgs>, TArgs>
{
  public:
    void operator-=(MemberHandlerWrapper<TArgs> &handler)
    {
        auto pos = std::find(this->handler.begin(), this->handler.end(), handler);

        if (pos != this->handler.end())
        {
            delete (*pos).wrapped_item;
            this->handler.erase(pos);
        }
    }

    void RemoveAll(void *obj)
    {
        std::vector<MemberHandlerWrapper<TArgs>> toRemove;

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