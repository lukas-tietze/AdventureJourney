#pragma once

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class Button : public ControlBase
{
  public:
    Button();
    Button(const std::string &);
    virtual ~Button();

    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);

    virtual void Render(Canvas &);
};
} // namespace terminal