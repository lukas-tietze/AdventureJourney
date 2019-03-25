#pragma once

#include "terminal/Screen.hpp"
#include "Terminal.hpp"

namespace tui
{
class ScreenCollection;

class StartScreen : public terminal::Screen
{
  private:
    terminal::TextView *titleText;
    terminal::PlacementBox *box;
    ScreenCollection *screens;

    void HandleKey(terminal::KeyEventArgs &args);

  public:
    StartScreen(ScreenCollection *);
    ~StartScreen();
};

class MenuScreen : public terminal::Screen
{
  private:
    ScreenCollection *screens;
    terminal::Selector *selector;
    terminal::TextView *titleBox;
    terminal::PlacementBox *box;
    terminal::LinearContainer *centerLayout;
    terminal::PlacementBox *selectorBox;

    void HandleOptionClicked(terminal::KeyEventArgs &args);

  public:
    MenuScreen(ScreenCollection *);
    ~MenuScreen();
};

class ScreenCollection
{
  private:
    terminal::Window window;
    StartScreen *start;
    MenuScreen *menu;

  public:
    ScreenCollection();
    ~ScreenCollection();

    void Start();

    StartScreen *GetStartScreen();
    MenuScreen *GetMenuScreen();
};
} // namespace tui
