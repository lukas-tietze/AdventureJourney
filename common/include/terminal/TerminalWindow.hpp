#pragma once

#include <vector>

#include "terminal/controls/containers/ContainerBase.hpp"
#include "terminal/controls/ControlBase.hpp"
#include "terminal/TerminalView.hpp"

namespace terminal
{
class TerminalWindow;

class Screen : public ContainerBase
{
  private:
    TerminalWindow *parentWindow;

  public:
    void Show();
};

class Window
{
  private:
    bool loop;
    int escapeKey;
    bool hasEscapeKey;

    std::vector<Screen *> screens;
    Screen *activeScreen;
    Screen *emptyScreen;

  public:
    Window();
    ~Window();

    void AddScreen(Screen *);
    void RemoveScreen(Screen *);
    void SetActiveScreen(Screen *);

    void Start(int);
    void Start();
    void Quit();
};
} // namespace terminal