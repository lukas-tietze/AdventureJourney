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
    this->selector->SetPadding(0.05f, 0.2f, 0.f, 0.2f);
    this->selector->OnKey().Register(this, &MenuScreen::HandleOptionClicked);
    this->selector->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->selector->SetName("Menu::Selector");
    this->selector->SetBorderEnabled(true);
    this->selector->SetBorder(this->screens->border1);
    this->selector->SetCenterText(true);

    this->titleBox = new terminal::TextView("Galaxy At War");
    this->titleBox->SetSize(40, 5);
    this->titleBox->SetCenterHorizontal(true);
    this->titleBox->SetCenterVertical(true);
    this->titleBox->SetPadding(0.3f, 0.3f, 0.3f, 0.3f);
    this->titleBox->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->titleBox->SetName("Menu::TitleBox");
    this->titleBox->SetBorderEnabled(true);
    this->titleBox->SetBorder(this->screens->border2);

    this->centerLayout = new terminal::LinearContainer();
    this->centerLayout->SetOrientation(terminal::LinearContainer::Orientation::TopToBottom);
    this->centerLayout->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->centerLayout->SetPadding(0.2, 0.35f, 0.f, 0.35f);
    this->centerLayout->Add(titleBox);
    this->centerLayout->Add(selector);
    this->centerLayout->SetName("Menu::CenterLayout");
    this->centerLayout->SetBorderEnabled(true);
    this->centerLayout->SetBorder(this->screens->border3);

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
        this->screens->test->Show();
        break;
    case OPTION_EXIT:
        this->screens->window->Quit();
        break;
    default:
        break;
    }
}