#pragma once

#include <string>

#include "control_base.hpp"

namespace terminal
{
class textbox : public control_base
{
  public:
    textbox();
    textbox(const std::string &);
    virtual ~textbox();

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(container_base *);
    virtual void handle_z_index_changed(int);
    virtual void handle_tab_index_changed(int);

    virtual void render(canvas &);
};
} // namespace terminal
