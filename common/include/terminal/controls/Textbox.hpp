#pragma once

#include <string>

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class Textbox : public ControlBase
{
  public:
    Textbox();
    Textbox(const std::string &);
    virtual ~Textbox();

    virtual void handle_key(KeyInput &);
    virtual void handle_mouse(MouseInput &);

    virtual void render(Canvas &);
};
} // namespace terminal
