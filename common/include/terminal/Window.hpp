#pragma once

#include <vector>

#include "terminal/Screen.hpp"

namespace terminal
{
class Window
{
  private:
    bool loop;
    int escapeKey;
    bool hasEscapeKey;

    std::vector<Screen *> screens;
    Screen *emptyScreen;
    Screen *activeScreen;

  public:
    Window();
    ~Window();

    void AddScreen(Screen *);
    void RemoveScreen(Screen *);
    void SetActiveScreen(Screen *);
    void Blank();

    void Start(int);
    void Start();
    void Quit();
};
} // namespace terminal
