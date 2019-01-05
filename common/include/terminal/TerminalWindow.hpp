#pragma once

#include <vector>
#include <thread>

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

    std::thread thread;
    bool hasThread;

    void Render();
    void SwitchFocus(int);

  public:
    TerminalWindow();
    ~TerminalWindow();

    ControlBase *AddControl(ControlBase *);

    void HandleKey(KeyInput);

    void Start(int);
    void Start();

    void StartAsync(int);
    void StartAsync();

    void Quit();

    ControlBase *GetFocusedControl();
    const ControlBase *GetFocusedControl() const;
    size_t GetFocusedControlIndex() const;
};
} // namespace terminal