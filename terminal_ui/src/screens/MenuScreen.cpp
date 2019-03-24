#include "Terminal.hpp"
#include "Screens.hpp"

namespace
{
const int OPTION_START_GAME = 1;
const int OPTION_RUN_TESTS = 0;
const int OPTION_EXIT = 2;

terminal::Selector *selector;
terminal::TextView *titleBox;

void HandleOptionClicked(terminal::KeyEventArgs &args)
{
    switch (selector->GetSelectedMarker())
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
} // namespace

terminal::Screen *screens::CreateMenuScreen()
{
    auto s = new terminal::Screen();

    selector = new terminal::Selector();
    selector->AddOption("Start Game", OPTION_START_GAME);
    selector->AddOption("Run Tests", OPTION_RUN_TESTS);
    selector->AddOption("Exit", OPTION_EXIT);
    selector->OnKey().Register(HandleOptionClicked);
    selector->SetSize(40, 10);
    selector->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);

    titleBox = new terminal::TextView("Galaxy At War");
    titleBox->SetSize(40, 5);
    titleBox->SetCenterHorizontal(true);
    titleBox->SetCenterVertical(true);
    titleBox->SetAutoSizeMode(terminal::AutoSizeMode::FillHorizontal);

    auto centerLayout = new terminal::LinearContainer();
    centerLayout->SetOrientation(terminal::LinearContainer::Orientation::TopToBottom);
    centerLayout->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    centerLayout->Add(titleBox);
    // centerLayout->Add(selector);

    auto box = new terminal::PlacementBox();
    box->SetHorizontalPartition(0.3f, 0.4f, 0.3f);
    box->SetVerticalPartition(0.05f, 0.75f, 0.2f);
    box->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    box->Add(centerLayout);
    // box->Add(selector);

    s->Add(box);

    return s;
}
