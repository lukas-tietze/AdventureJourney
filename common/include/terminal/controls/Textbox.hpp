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

    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);

    virtual void Render(Canvas &);
};
} // namespace terminal
