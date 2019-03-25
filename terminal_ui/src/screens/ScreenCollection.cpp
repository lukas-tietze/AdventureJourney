#include "Screens.hpp"

tui::ScreenCollection::ScreenCollection()
{
    this->start = new tui::StartScreen(this);
    this->menu = new tui::MenuScreen(this);

    this->window.AddScreen(this->start);
    this->window.AddScreen(this->menu);
}

tui::ScreenCollection::~ScreenCollection()
{
    // delete this->start;
    // delete this->menu;
}

void tui::ScreenCollection::Start()
{
    this->start->Show();
    this->window.Start('q');
}

tui::StartScreen *tui::ScreenCollection::GetStartScreen()
{
    return this->start;
}

tui::MenuScreen *tui::ScreenCollection::GetMenuScreen()
{
    return this->menu;
}
