#pragma once

#include <vector>

#include "terminal/controls/containers/ContainerBase.hpp"
#include "terminal/controls/ControlBase.hpp"
#include "terminal/View.hpp"
#include "Event.hpp"

namespace terminal
{
class Window;
class Screen;

struct ScreenEventArgs
{
    Screen *sender;
    Window *parent;
    bool visible;
    bool handled;
};

class Screen : public ContainerBase
{
    friend Window;

  private:
    Window *parent;
    bool visible;

    ScreenEventArgs MakeArgs();

    void AttachToWindow(Window *);
    void DetachFromWindow();
    void HandleShow();
    void HandleHide();

    util::Event<ScreenEventArgs> onShown;
    util::Event<ScreenEventArgs> onHidden;
    util::Event<ScreenEventArgs> onDetached;
    util::Event<ScreenEventArgs> onAttached;

  public:
    Screen();

    util::Event<ScreenEventArgs> const &OnShown();
    util::Event<ScreenEventArgs> const &OnHidden();
    util::Event<ScreenEventArgs> const &OnDetached();
    util::Event<ScreenEventArgs> const &OnAttached();

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