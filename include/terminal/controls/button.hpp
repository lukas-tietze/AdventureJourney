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

    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);

    virtual void render(canvas &);
};
} // namespace terminal