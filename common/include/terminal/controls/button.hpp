#pragma once

#include "terminal/controls/control_base.hpp"

namespace terminal
{
class Button : public ControlBase
{
  public:
    Button();
    Button(const std::string &);
    virtual ~Button();

    virtual void handle_key(KeyInput &);
    virtual void handle_mouse(MouseInput &);

    virtual void render(Canvas &);
};
} // namespace terminal