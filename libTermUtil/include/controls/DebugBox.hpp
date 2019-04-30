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
    colorId_t color;

    void HandleCommand();

  public:
    DebugBox();
    virtual ~DebugBox();

    void SetColor(colorId_t color);

    virtual void HandleFocusAquired();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void Render(Canvas &);
};
} // namespace terminal
