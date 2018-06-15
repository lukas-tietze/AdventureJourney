#include <vector>

namespace util
{
template <class T>
class event_handler
{
  public:
    typedef void(*event_function)(void*, T);
    void operator+=(event_function func);
    void operator-=(event_function func);

  private:
    std::vector<event_func> m_targets;
};
} // namespace util