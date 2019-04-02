#include "Screens.hpp"

namespace
{
constexpr int OPTION_NEW_GAME = 0;
constexpr int OPTION_LOAD_GAME = 1;
constexpr int OPTION_OPTIONS = 2;
constexpr int OPTION_MANAGE_CONTENT = 3;
constexpr int OPTION_MANAGE_PROFILE = 4;
constexpr int OPTION_RUN_TESTS = 5;
constexpr int OPTION_EXIT = 6;
} // namespace

tui::MenuScreen::MenuScreen(ScreenCollection *screens)
{
    this->screens = screens;

    this->selector = new terminal::Selector();
    this->selector->AddOption("New Game", OPTION_NEW_GAME);
    this->selector->AddOption("Load Game", OPTION_LOAD_GAME);
    this->selector->AddSeperator();
    this->selector->AddOption("Options", OPTION_OPTIONS);
    this->selector->AddOption("Manage Content", OPTION_MANAGE_CONTENT);
    this->selector->AddOption("Manage Profile", OPTION_MANAGE_PROFILE);
    this->selector->AddSeperator();
    this->selector->AddOption("Run Tests", OPTION_RUN_TESTS);
    this->selector->AddOption("Exit", OPTION_EXIT);
    this->selector->SetPadding(0.05f, 0.2f, 0.f, 0.2f);
    this->selector->OnKey().Register(this, &MenuScreen::HandleOptionClicked);
    this->selector->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->selector->SetName("Menu::Selector");
    this->selector->SetBorderEnabled(true);
    this->selector->SetBorder(this->screens->border1);
    this->selector->SetCenterText(true);

    this->titleBox = new terminal::TextView("Galaxy At War");
    this->titleBox->SetSize(40, 5);
    this->titleBox->SetCenterHorizontal(true);
    this->titleBox->SetCenterVertical(true);
    this->titleBox->SetPadding(0.f, 0.f, 0.f, 0.f);
    this->titleBox->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->titleBox->SetName("Menu::TitleBox");
    this->titleBox->SetBorderEnabled(true);
    this->titleBox->SetBorder(this->screens->border2);

    this->centerLayout = new terminal::LinearContainer();
    this->centerLayout->SetOrientation(terminal::LinearContainer::Orientation::TopToBottom);
    this->centerLayout->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->centerLayout->SetPadding(0.2f, 0.35f, 0.1f, 0.35f);
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
    if (args.key == '\n')
        switch (this->selector->GetSelectedMarker())
        {
        case OPTION_NEW_GAME:
            this->screens->gameConfig->Show();
            break;
        case OPTION_LOAD_GAME:
            break;
        case OPTION_OPTIONS:
            break;
        case OPTION_MANAGE_CONTENT:
            break;
        case OPTION_MANAGE_PROFILE:
            break;
        case OPTION_RUN_TESTS:
            break;
        case OPTION_EXIT:
            break;
        default:
            break;
        }
}