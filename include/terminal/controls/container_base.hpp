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
};
} // namespace terminal