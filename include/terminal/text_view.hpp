#pragma once

#include <string>

#include "control_base.hpp"

namespace terminal
{
class text_view : public text_control_base
{
  public:
    text_view();
    text_view(const std::string &);
    virtual ~text_view();

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(control_base *);

    virtual void render(const util::rectangle &, canvas &);
};
} // namespace terminal
