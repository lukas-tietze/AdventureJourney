#pragma once

#include <vector>

#include "terminal/controls/containers/ContainerBase.hpp"
#include "terminal/controls/ControlBase.hpp"
#include "terminal/View.hpp"

namespace terminal
{
class Window;

class Screen : public ContainerBase
{
    friend Window;

  private:
    Window *parent;

    void AttachToWindow(Window *);
    void DetachFromWindow();

  public:
    Screen();

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