#include "Screens.hpp"

using terminal::colorPairId_t;

tui::ScreenCollection::ScreenCollection() : window(nullptr),
                                            start(nullptr),
                                            menu(nullptr)
{
    auto view = terminal::View::GetInstance();

    colorPairId_t colorBase = view->SystemColorCount();
    colorPairId_t color1 = colorBase + 1;
    colorPairId_t color2 = colorBase + 2;
    colorPairId_t color3 = colorBase + 3;

    colorPairId_t pair1 = view->SystemColorPairCount();
    colorPairId_t pair2 = pair1 + 1;
    colorPairId_t pair3 = pair1 + 2;

    view->BufferColor(colorBase, util::colors::Black);
    view->BufferColor(color1, util::colors::Red);
    view->BufferColor(color2, util::colors::Blue);
    view->BufferColor(color3, util::colors::Yellow);

    view->BufferColorPair(pair1, colorBase, color1);
    view->BufferColorPair(pair2, colorBase, color2);
    view->BufferColorPair(pair3, colorBase, color3);

    this->border1.SetStyle(pair1);
    this->border2.SetStyle(pair2);
    this->border3.SetStyle(pair3);
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
