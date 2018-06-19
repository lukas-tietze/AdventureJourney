#include <vector>

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
    std::vector<i_event_listener<T> *> m_listeners;

  public:
    void operator+=(i_event_listener<T> *listener)
    {
        if(m_listeners.find(listener) == std::vector<i_event_listener<T>>::npos)
        {
            m_listeners.push_back(listener);
        }
    }

    void operator-=(i_event_listener<T> listener)
    {
        pos = m_listeners.find(listener)
        if(pos != std::vector<i_event_listener<T>>::npos)
        {
            m_listeners.remove(pos);
        }
    }
};

template <class T>
class function_event
{
  public:
    typedef void (*event_function)(void *, T);

    void operator+=(event_function func)
    {
    }

    void operator-=(event_function func)
    {
    }

  private:
    std::vector<event_func> m_targets;
};
} // namespace util