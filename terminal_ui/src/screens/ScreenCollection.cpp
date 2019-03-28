#include "Screens.hpp"

tui::ScreenCollection::ScreenCollection() : window(nullptr),
                                            start(nullptr),
                                            menu(nullptr)
{
    auto view = terminal::View::GetInstance();

    terminal::colorPairId_t colorBase = 9;
    terminal::colorPairId_t color1 = colorBase + 1;
    terminal::colorPairId_t color2 = colorBase + 2;
    terminal::colorPairId_t color3 = colorBase + 3;

    view->BufferColor(colorBase, util::colors::Black);
    view->BufferColor(color1, util::colors::Red);
    view->BufferColor(color2, util::colors::Blue);
    view->BufferColor(color3, util::colors::Yellow);

    this->border1.SetStyle(0);
    this->border2.SetStyle(0);
    this->border3.SetStyle(0);
    this->border1.SetEnabled(true);
    this->border2.SetEnabled(true);
    this->border3.SetEnabled(true);
}

tui::ScreenCollection::~ScreenCollection()
{
    // delete this->start;
    // delete this->menu;
}

void tui::ScreenCollection::Start()
{
    if (this->window != nullptr)
        delete this->window;

    this->window = new terminal::Window();

    this->start = new tui::StartScreen(this);
    this->menu = new tui::MenuScreen(this);

    this->window->AddScreen(this->start);
    this->window->AddScreen(this->menu);

    this->start->Show();
    this->window->Start('q');
}
