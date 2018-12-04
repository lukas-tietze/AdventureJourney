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
    std::vector<terminal::ControlBase *> controls;
    std::vector<terminal::ControlBase *> controlsByTabIndex;
    int focusedControlIndex;
    bool loop;
    int escapeKey;
    bool hasEscapeKey;

    void Render();
    void SwitchFocus(int);

  public:
    TerminalWindow();
    ~TerminalWindow();

    ControlBase *AddControl(ControlBase *);

    void Start(int);
    void Start();
    void Quit();

    ControlBase *GetFocusedControl() const;
};
} // namespace terminal