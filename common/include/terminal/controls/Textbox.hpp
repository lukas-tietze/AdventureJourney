#pragma once

#include <string>

#include "terminal/controls/ControlBase.hpp"
#include "terminal/controls/TextView.hpp"

namespace terminal
{
class Textbox : public terminal::TextView
{
  private:
    int cursorIndex;

  public:
    Textbox();
    Textbox(const std::string &);
    virtual ~Textbox();

    virtual void HandleFocusAquired();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);

    // virtual void Render(Canvas &);
};
} // namespace terminal
