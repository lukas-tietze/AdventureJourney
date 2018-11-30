#pragma once

#include <vector>

#include "terminal/controls/ContainerBase.hpp"
#include "terminal/controls/ControlBase.hpp"
#include "terminal/TerminalView.hpp"

namespace terminal
{
class TerminalWindow : public ContainerBase
{
  private:
    std::vector<terminal::control_base *> controls;
    std::vector<terminal::control_base *> controlsByTabIndex;
    int focusedControlIndex;
    bool loop;
    int escapeKey;
    bool hasEscapeKey;

    void render();
    void switchFocus(int);

  public:
    TerminalWindow();
    ~TerminalWindow();

    control_base *addControl(control_base *);

    void start(int);
    void start();
    void quit();

    control_base *getFocusedControl() const;
};
} // namespace terminal