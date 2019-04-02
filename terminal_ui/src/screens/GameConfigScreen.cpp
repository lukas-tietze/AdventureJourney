#include "Screens.hpp"

tui::GameConfigScreen::GameConfigScreen() : terminal::Screen()
{
    this->galaxySizePicker = new terminal::Picker();
    this->galaxySizePicker->SetName("GalaxySizePicker");
    this->galaxySizePicker->AddOption("Small");
    this->galaxySizePicker->AddOption("Medium");
    this->galaxySizePicker->AddOption("Large");
    this->galaxySizePicker->SetSize(0, 3);
    this->galaxySizePicker->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);

    this->layout = new terminal::LinearContainer();
    this->layout->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->layout->SetPadding(1, 1, 1, 1);
    this->layout->SetName("Layout");
    this->layout->Add(this->galaxySizePicker);

    this->Add(this->layout);
    this->SetName("GameConfigScreen");
}

tui::GameConfigScreen::~GameConfigScreen()
{
}