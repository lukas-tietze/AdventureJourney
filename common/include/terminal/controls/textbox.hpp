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

    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);

    virtual void render(canvas &);
};
} // namespace terminal
