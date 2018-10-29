#pragma once

#include "terminal/controls/control_base.hpp"

namespace terminal
{
class container_base : public control_base
{
  public:
    container_base();
    virtual ~container_base();

    virtual void handle_child_z_index_changed(control_base *);
    virtual void handle_child_tab_index_changed(control_base *);
    
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