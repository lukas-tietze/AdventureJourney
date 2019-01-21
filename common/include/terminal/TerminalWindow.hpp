#pragma once

#include <vector>
#include <thread>

#include "terminal/controls/containers/ContainerBase.hpp"
#include "terminal/controls/ControlBase.hpp"
#include "terminal/TerminalView.hpp"

namespace terminal
{
class TerminalWindow : public ContainerBase
{
  private:
    bool loop;
    int escapeKey;
    bool hasEscapeKey;

    std::thread thread;
    bool hasThread;

    void Render();

  public:
    TerminalWindow();
    ~TerminalWindow();

    void HandleKey(KeyInput &);

    void Start(int);
    void Start();
    void StartAsync(int);
    void StartAsync();
    void Quit();
};
} // namespace terminal