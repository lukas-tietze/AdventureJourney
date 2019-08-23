#pragma once

#include "controls/containers/ContainerBase.hpp"
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

    util::Event<ScreenEventArgs> &OnShown();
    util::Event<ScreenEventArgs> &OnHidden();
    util::Event<ScreenEventArgs> &OnDetached();
    util::Event<ScreenEventArgs> &OnAttached();

    void Show();
};
} // namespace terminal
