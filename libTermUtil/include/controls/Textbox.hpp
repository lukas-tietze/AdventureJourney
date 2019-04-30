#pragma once

#include <string>

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class Textbox : public terminal::ControlBase
{
  private:
    int cursorIndex;

    int GetTrueCursorIndex() const;

  public:
    Textbox();
    Textbox(const std::string &);
    virtual ~Textbox();

    virtual void HandleFocusAquired();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void Render(Canvas &);
};
} // namespace terminal
