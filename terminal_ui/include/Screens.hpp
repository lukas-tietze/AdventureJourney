#pragma once

#include "terminal/Screen.hpp"
#include "Terminal.hpp"

namespace tui
{
class StartScreen;
class MenuScreen;
class TestScreen;
class GameConfigScreen;

class ScreenCollection
{
  private:
    friend StartScreen;
    friend MenuScreen;
    friend TestScreen;
    friend GameConfigScreen;

    terminal::Window *window;
    StartScreen *start;
    MenuScreen *menu;
    TestScreen *test;
    GameConfigScreen *gameConfig;

    terminal::Border border1;
    terminal::Border border2;
    terminal::Border border3;

  public:
    ScreenCollection();
    ~ScreenCollection();

    void Start();
};

class GameConfigScreen : public terminal::Screen
{
  private:
    ScreenCollection *screens;
    terminal::LinearContainer *layout;
    terminal::LinearContainer *leftLayout;
    terminal::LinearContainer *rightLayout;

    terminal::Picker<> *galaxySizePicker;
    terminal::TextView *galaxySizeLabel;
    terminal::Picker<> *galaxyAgePicker;
    terminal::TextView *galaxyAgeLabel;
    terminal::Picker<> *civilisationCountPicker;
    terminal::TextView *civilisationCountLabel;
    terminal::Picker<> *difficultyPicker;
    terminal::TextView *difficultyLabel;

  public:
    GameConfigScreen(ScreenCollection *);
    ~GameConfigScreen();
};

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

    void HandleOptionClicked(terminal::KeyEventArgs &);

  public:
    MenuScreen(ScreenCollection *);
    ~MenuScreen();
};

class TestScreen : public terminal::Screen
{
  private:
    ScreenCollection *screens;

  public:
    TestScreen();
    ~TestScreen();
};
} // namespace tui