#pragma once

#include <string>

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class DebugBox : public terminal::ControlBase
{
  private:
    int cursorIndex;
    std::string command;

  public:
    DebugBox();
    virtual ~DebugBox();

    virtual void HandleFocusAquired();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void Render(Canvas &);
};
} // namespace terminal
