#ifndef TERMINAL_TERMINAL_WINDOW_HPP
#define TERMINAL_TERMINAL_WINDOW_HPP

#include <vector>

#include "control_base.hpp"
#include "terminal_view.hpp"

namespace terminal
{
class terminal_window
{
  private:
    std::vector<terminal::control_base *> controls;
    int focused_control_index;
    terminal_view view;

  public:
    terminal_window();
    ~terminal_window();

    control_base *add_control(control_base *);

    void start();

    control_base *get_focused_control() const;
};
} // namespace terminal

#endif /*TERMINAL_TERMINAL_WINDOW_HPP*/