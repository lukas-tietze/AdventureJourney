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
    terminal::LinearContainer *centerLayout;

    void HandleOptionClicked(terminal::KeyEventArgs &args);

  public:
    MenuScreen(ScreenCollection *);
    ~MenuScreen();
};

class ScreenCollection
{
    friend tui::StartScreen;
    friend tui::MenuScreen;

  private:
    terminal::Window window;
    StartScreen *start;
    MenuScreen *menu;

  public:
    ScreenCollection();
    ~ScreenCollection();

    void Start();
};
} // namespace tui
