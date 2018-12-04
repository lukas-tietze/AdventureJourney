#pragma once

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class ContainerBase : public ControlBase
{
  public:
    ContainerBase();
    virtual ~ContainerBase();

    virtual void handle_child_z_index_changed(ControlBase *);
    virtual void handle_child_tab_index_changed(ControlBase *);
    
    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(KeyInput &);
    virtual void handle_mouse(MouseInput &);
    virtual void handle_add_to_control(ContainerBase *);
    virtual void handle_z_index_changed(int);
    virtual void handle_tab_index_changed(int);

    virtual void render(Canvas &);
};
} // namespace terminal