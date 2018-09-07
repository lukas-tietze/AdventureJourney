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

template <class T, class TArgs>
struct member_handler
{
    T *obj;
    void (T::*f)(TArgs &);

    void operator()(TArgs &args)
    {
        (obj->*f)(args);
    }
};

template <class T, class TArgs>
member_handler<T, TArgs> make_member_handler(T *obj, void (T::*f)(TArgs &))
{
    return member_handler<T, TArgs>{obj, f};
}

template<class T, class TArgs>
class member_event : public handler_event<member_handler<T, TArgs>, TArgs>
{
};
} // namespace util