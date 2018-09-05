#pragma once

#include <vector>

#include "terminal/controls/control_base.hpp"
#include "terminal/terminal_view.hpp"

namespace terminal
{
class terminal_window : public control_base
{
  private:
    std::vector<terminal::control_base *> controls;
    int focused_control_index;

  public:
    terminal_window();
    ~terminal_window();

    control_base *add_control(control_base *);

    void start();

    control_base *get_focused_control() const;
};
} // namespace terminal