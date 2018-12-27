#pragma once

#include <string>
#include <vector>

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class TextView : public ControlBase
{
  private:
    std::vector<std::string> lines;
    void PrepareLines();
    void PrepareText();

  public:
    TextView();
    TextView(const std::string &);
    virtual ~TextView();

    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void HandleBoundsChanged();
    virtual void HandleTextChanged();

    virtual void Render(Canvas &);
};
} // namespace terminal
