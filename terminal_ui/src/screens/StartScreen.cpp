#include "Screens.hpp"

tui::StartScreen::StartScreen(ScreenCollection *screens)
{
    this->screens = screens;

    this->titleText = new terminal::TextView("Welcome to\nGalaxy At War\n\n[press any key to continue]");
    this->titleText->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->titleText->SetBorderEnabled(true);
    this->titleText->SetCenterVertical(true);
    this->titleText->SetCenterHorizontal(true);
    this->titleText->SetName("Start::TitleText");

    this->box = new terminal::PlacementBox();
    this->box->SetHorizontalPartition(0.2f, 0.6f, 0.2f);
    this->box->SetVerticalPartition(0.05f, 0.8f, 0.15f);
    this->box->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->box->Add(titleText);
    this->box->SetName("Start::MainPlacementBox");

    this->Add(box);
    this->OnKey().Register(this, &StartScreen::HandleKey);
    this->SetName("StartScreen");
}

tui::StartScreen::~StartScreen()
{
    // delete this->titleText;
    // delete this->box;
}

void tui::StartScreen::HandleKey(terminal::KeyEventArgs &args)
{
    args.handled = true;
    this->screens->GetMenuScreen()->Show();
}