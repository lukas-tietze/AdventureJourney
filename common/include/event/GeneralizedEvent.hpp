#pragma once

#include <vector>

namespace util
{
template <class TArgs>
class Event
{
  private:
    enum class EventHandlerType
    {
        StaticFunction,
        MemberFunction,
        Struct,
    };

    class EventHandler
    {
      private:
        EventHandlerType type;

      public:
        EventHandler(EventHandlerType type) : type(type)
        {
        }

        virtual ~EventHandler()
        {
        }

        EventHandlerType GetType() const
        {
            return this->type;
        }

        virtual void Execute(TArgs &) = 0;
    };

    template <class T>
    struct AlwaysEqual
    {
        bool operator()(const T &a, const T &b)
        {
            return true;
        }
    };

    template <class THandler, class TEqual = AlwaysEqual<THandler>>
    class StructEventHandler : public EventHandler
    {
      private:
        THandler f;
        TEqual equal;

      public:
        StructEventHandler() : EventHandler(EventHandlerType::Struct),
                               f(),
                               equal()
        {
        }

        StructEventHandler(THandler f) : EventHandler(EventHandlerType::Struct),
                                         f(f),
                                         equal()
        {
        }

        void Execute(TArgs &args)
        {
            f(args);
        }

        bool Equals(const THandler &f)
        {
            return this->equal(this->f, f);
        }
    };

    class FunctionEventHandler : public EventHandler
    {
      private:
        typedef void (*EventFunction)(TArgs &);

        EventFunction f;

      public:
        FunctionEventHandler(EventFunction f) : EventHandler(EventHandlerType::StaticFunction),
                                                f(f)
        {
        }

        void Execute(TArgs &args)
        {
            f(args);
        }

        bool Equals(EventFunction f)
        {
            return this->f == f;
        }
    };

    template <class T>
    class MemberEventHandler : public EventHandler
    {
      private:
        typedef void (T::*MemberFunction)(TArgs &);

        T *target;
        MemberFunction f;

      public:
        MemberEventHandler(T *target, MemberFunction f) : EventHandler(EventHandlerType::MemberFunction),
                                                          target(target),
                                                          f(f)
        {
        }

        void Execute(TArgs &args)
        {
            ((*this->target).*(this->f))(args);
        }

        bool Equals(T *t, MemberFunction f)
        {
            return this->target == t && this->f == f;
        }
    };

    std::vector<EventHandler *> handlers;

    typename std::vector<EventHandler *>::iterator Find(void (*f)(TArgs &))
    {
        for (auto pos = this->handlers.begin(), end = this->handlers.end(); pos != end; ++pos)
            if ((*pos)->GetType() == EventHandlerType::StaticFunction &&
                dynamic_cast<FunctionEventHandler *>(*pos)->Equals(f))
                return pos;

        return this->handlers.end();
    }

    template <class T>
    typename std::vector<EventHandler *>::iterator Find(const T &t)
    {
        for (auto pos = this->handlers.begin(), end = this->handlers.end(); pos != end; ++pos)
            if ((*pos)->GetType() == EventHandlerType::Struct &&
                dynamic_cast<StructEventHandler<T> *>(*pos)->Equals(t))
                return pos;

        return this->handlers.end();
    }

    template <class T>
    typename std::vector<EventHandler *>::iterator Find(T *t, void (T::*f)(TArgs &args))
    {
        for (auto pos = this->handlers.begin(), end = this->handlers.end(); pos != end; ++pos)
            if ((*pos)->GetType() == EventHandlerType::MemberFunction &&
                dynamic_cast<MemberEventHandler<T> *>(*pos)->Equals(t, f))
                return pos;

        return this->handlers.end();
    }

  public:
    Event() : handlers()
    {
    }

    Event(const Event &copyFrom) : handlers(copyFrom.handlers)
    {
    }

    Event(Event &&transferFrom) : handlers(transferFrom.handlers)
    {
    }

    ~Event()
    {
        this->Clear();
    }

    Event &operator=(const Event &copyFrom)
    {
        return *this;
    }

    Event &operator=(Event &&transferFrom)
    {
        return *this;
    }

    void operator()(TArgs &args)
    {
        for (auto &handler : this->handlers)
            handler->Execute(args);
    }

    void Register(void (*f)(TArgs &))
    {
        if (this->Find(f) == this->handlers.end())
            this->handlers.push_back(new FunctionEventHandler(f));
    }

    template <class T>
    void Register(T t)
    {
        if (this->Find(t) == this->handlers.end())
            this->handlers.push_back(new StructEventHandler<T>(t));
    }

    template <class T>
    void Register(T *t, void (T::*f)(TArgs &args))
    {
        if (this->Find(t, f) == this->handlers.end())
            this->handlers.push_back(new MemberEventHandler<T>(t, f));
    }

    void Remove(void (*f)(TArgs &))
    {
        auto pos = this->Find(f);

        if (pos != this->handlers.end())
            this->handlers.erase(pos);
    }

    template <class T>
    void Remove(T t)
    {
        auto pos = this->Find(t);

        if (pos != this->handlers.end())
            this->handlers.erase(pos);
    }

    template <class T>
    void Remove(T *t, void (T::*f)(TArgs &args))
    {
        auto pos = this->Find(t, f);

        if (pos != this->handlers.end())
            this->handlers.erase(pos);
    }

    void Clear()
    {
        for (const auto &handler : this->handlers)
            delete handler;

        this->handlers.clear();
    }

    size_t Size() const
    {
        return this->handlers.size();
    }
};
} // namespace util
