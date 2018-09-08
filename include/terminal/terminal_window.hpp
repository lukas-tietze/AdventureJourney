#pragma once

#include <vector>

#include "terminal/controls/container_base.hpp"
#include "terminal/controls/control_base.hpp"
#include "terminal/terminal_view.hpp"

namespace terminal
{
class terminal_window : public container_base
{
  private:
    std::vector<terminal::control_base *> controls;
    std::vector<terminal::control_base *> controls_by_tab_index;
    int focused_control_index;
    bool loop;

    void render();
    void switch_focus(int);

  public:
    terminal_window();
    ~terminal_window();

    control_base *add_control(control_base *);

    void start();
    void quit();

    control_base *get_focused_control() const;
};
} // namespace terminal