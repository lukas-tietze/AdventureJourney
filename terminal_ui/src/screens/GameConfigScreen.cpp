#include "Screens.hpp"

tui::GameConfigScreen::GameConfigScreen(ScreenCollection *screens) : terminal::Screen(),
                                                                     screens(screens)
{
    this->galaxySizePicker = new terminal::Picker<>();
    this->galaxySizePicker->SetName("GalaxySizePicker");
    this->galaxySizePicker->SetSize(0, 2);
    this->galaxySizePicker->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->galaxySizePicker->AddOption(0, "Very Small");
    this->galaxySizePicker->AddOption(0, "Small");
    this->galaxySizePicker->AddOption(0, "Medium");
    this->galaxySizePicker->AddOption(0, "Large");
    this->galaxySizePicker->AddOption(0, "Very Large");

    this->galaxySizeLabel = new terminal::TextView("Galaxy Size");
    this->galaxySizeLabel->SetSize(0, 2);
    this->galaxySizeLabel->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->galaxySizeLabel->SetName("GalaxySizeLabel");
    this->galaxySizeLabel->SetMultiLineEnabled(false);

    this->galaxyAgePicker = new terminal::Picker<>();
    this->galaxyAgePicker->SetSize(0, 2);
    this->galaxyAgePicker->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->galaxyAgePicker->SetName("GalaxyAgePicker");
    this->galaxyAgePicker->AddOption(0, "Young");
    this->galaxyAgePicker->AddOption(0, "Medium");
    this->galaxyAgePicker->AddOption(0, "Aged");
    this->galaxyAgePicker->AddOption(0, "Old");
    this->galaxyAgePicker->AddOption(0, "Ancient");

    this->galaxyAgeLabel = new terminal::TextView("Galaxy Age");
    this->galaxyAgeLabel->SetSize(0, 2);
    this->galaxyAgeLabel->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->galaxyAgeLabel->SetName("GalaxyAgeLabel");
    this->galaxyAgeLabel->SetMultiLineEnabled(false);

    this->civilisationCountPicker = new terminal::Picker<>();
    this->civilisationCountPicker->SetSize(0, 2);
    this->civilisationCountPicker->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->civilisationCountPicker->SetName("CivilisationCountPicker");
    this->civilisationCountPicker->AddOption(0, "Few (1~3)");
    this->civilisationCountPicker->AddOption(0, "Some (4~6)");
    this->civilisationCountPicker->AddOption(0, "Many (6~10)");
    this->civilisationCountPicker->AddOption(0, "Too Many (11~20)");

    this->civilisationCountLabel = new terminal::TextView("Number of Civilisations");
    this->civilisationCountLabel->SetSize(0, 2);
    this->civilisationCountLabel->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->civilisationCountLabel->SetName("CivilisationCountLabel");
    this->civilisationCountLabel->SetMultiLineEnabled(false);

    this->difficultyPicker = new terminal::Picker<>();
    this->difficultyPicker->SetSize(0, 2);
    this->difficultyPicker->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->difficultyPicker->SetName("DifficultyPicker");
    this->difficultyPicker->AddOption(0, "Beginner");
    this->difficultyPicker->AddOption(0, "Easy");
    this->difficultyPicker->AddOption(0, "Medium");
    this->difficultyPicker->AddOption(0, "Hard");
    this->difficultyPicker->AddOption(0, "Veteran");

    this->difficultyLabel = new terminal::TextView("Difficulty");
    this->difficultyLabel->SetSize(0, 2);
    this->difficultyLabel->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);
    this->difficultyLabel->SetName("DifficultyLabel");
    this->difficultyLabel->SetMultiLineEnabled(false);

    this->leftLayout = new terminal::LinearContainer();
    this->leftLayout->SetAutoSizeMode(terminal::AutoSizeMode::FillVertical);
    this->leftLayout->SetPadding(1, 1, 1, 1);
    this->leftLayout->SetSize(15, 0);
    this->leftLayout->SetName("Layout");
    this->leftLayout->Add(this->galaxySizeLabel);
    this->leftLayout->Add(this->galaxyAgeLabel);
    this->leftLayout->Add(this->civilisationCountLabel);
    this->leftLayout->Add(this->difficultyLabel);

    this->rightLayout = new terminal::LinearContainer();
    this->rightLayout->SetAutoSizeMode(terminal::AutoSizeMode::FillVertical);
    this->rightLayout->SetPadding(1, 1, 1, 1);
    this->rightLayout->SetSize(20, 0);
    this->rightLayout->SetName("Layout");
    this->rightLayout->Add(this->galaxySizePicker);
    this->rightLayout->Add(this->galaxyAgePicker);
    this->rightLayout->Add(this->civilisationCountPicker);
    this->rightLayout->Add(this->difficultyPicker);

    this->layout = new terminal::LinearContainer();
    this->layout->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    this->layout->SetName("Layout");
    this->layout->SetOrientation(terminal::LinearContainer::Orientation::LeftToRight);
    this->layout->Add(this->leftLayout);
    this->layout->Add(this->rightLayout);

    this->Add(this->layout);
    this->SetName("GameConfigScreen");
}

tui::GameConfigScreen::~GameConfigScreen()
{
}