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
    this->selector->OnKey().Register(this, &MenuScreen::HandleOptionClicked);
    this->selector->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->selector->SetName("Menu::Selector");

    this->selectorBox = new terminal::PlacementBox();
    this->selectorBox->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->selectorBox->SetVerticalPartition(0, 1, 0);
    this->selectorBox->SetHorizontalPartition(1, 1, 1);
    this->selectorBox->Add(selector);
    this->selectorBox->SetName("Menu::SelectorBox");

    this->titleBox = new terminal::TextView("Galaxy At War");
    this->titleBox->SetSize(40, 5);
    this->titleBox->SetCenterHorizontal(true);
    this->titleBox->SetCenterVertical(true);
    this->titleBox->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->titleBox->SetName("Menu::TitleBox");

    this->centerLayout = new terminal::LinearContainer();
    this->centerLayout->SetOrientation(terminal::LinearContainer::Orientation::TopToBottom);
    this->centerLayout->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->centerLayout->Add(titleBox);
    this->centerLayout->Add(selectorBox);
    this->centerLayout->SetName("Menu::CenterLayout");

    this->box = new terminal::PlacementBox();
    this->box->SetHorizontalPartition(0.3f, 0.4f, 0.3f);
    this->box->SetVerticalPartition(0.05f, 0.75f, 0.2f);
    this->box->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->box->Add(centerLayout);
    this->box->SetName("Menu::MainPlacementBox");

    this->Add(box);
    this->SetName("MenuScreen");
}

tui::MenuScreen::~MenuScreen()
{
    // delete this->selector;
    // delete this->titleBox;
    // delete this->box;
    // delete this->centerLayout;
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