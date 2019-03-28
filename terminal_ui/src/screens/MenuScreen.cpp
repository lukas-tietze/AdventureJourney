#include "Screens.hpp"

namespace
{
const int OPTION_START_GAME = 1;
const int OPTION_RUN_TESTS = 0;
const int OPTION_EXIT = 2;
} // namespace

tui::MenuScreen::MenuScreen(ScreenCollection *screens)
{
    this->screens = screens;

    this->selector = new terminal::Selector();
    this->selector->AddOption("Start Game", OPTION_START_GAME);
    this->selector->AddOption("Run Tests", OPTION_RUN_TESTS);
    this->selector->AddOption("Exit", OPTION_EXIT);
    this->selector->SetVerticalAlignment(0, 1, 0);
    this->selector->SetHorizontalAlignment(1, 1, 1);
    this->selector->OnKey().Register(this, &MenuScreen::HandleOptionClicked);
    this->selector->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->selector->SetName("Menu::Selector");

    this->titleBox = new terminal::TextView("Galaxy At War");
    this->titleBox->SetSize(40, 5);
    this->titleBox->SetCenterHorizontal(true);
    this->titleBox->SetCenterVertical(true);
    this->titleBox->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->titleBox->SetName("Menu::TitleBox");

    this->centerLayout = new terminal::LinearContainer();
    this->centerLayout->SetOrientation(terminal::LinearContainer::Orientation::TopToBottom);
    this->centerLayout->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->centerLayout->SetHorizontalAlignment(0.3f, 0.4f, 0.3f);
    this->centerLayout->SetVerticalAlignment(0.05f, 0.75f, 0.2f);
    this->centerLayout->Add(titleBox);
    this->centerLayout->Add(selector);
    this->centerLayout->SetName("Menu::CenterLayout");

    this->Add(centerLayout);
    this->SetName("MenuScreen");
}

tui::MenuScreen::~MenuScreen()
{
}

void tui::MenuScreen::HandleOptionClicked(terminal::KeyEventArgs &args)
{
    switch (this->selector->GetSelectedMarker())
    {
    case OPTION_START_GAME:
        break;
    case OPTION_RUN_TESTS:
        break;
    case OPTION_EXIT:
        break;
    default:
        break;
    }
}