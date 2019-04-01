#pragma once

#include "terminal/Window.hpp"

namespace screens
{
extern terminal::Screen *Start;
extern terminal::Screen *Menu;

terminal::Screen *CreateStartScreen();
terminal::Screen *CreateMenuScreen();
} // namespace screens
