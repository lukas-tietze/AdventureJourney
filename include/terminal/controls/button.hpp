#pragma once

#include "terminal/controls/control_base.hpp"

namespace terminal
{
class button : public control_base
{
  public:
    button();
    button(const std::string &);
    virtual ~button();

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(control_base *);
    virtual void handle_z_index_changed(int);
    virtual void handle_tab_index_changed(int);
};
} // namespace terminal