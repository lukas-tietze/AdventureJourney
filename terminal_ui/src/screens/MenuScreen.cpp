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
    selector->SetSize(40, 6);
    selector->AddOption("Start Game", OPTION_START_GAME);
    selector->AddOption("Run Tests", OPTION_RUN_TESTS);
    selector->AddOption("Exit", OPTION_EXIT);
    selector->OnKey().Register(HandleOptionClicked);

    titleBox = new terminal::TextView("Galaxy At War");
    titleBox->SetSize(40, 2);

    auto centerLayout = new terminal::LinearContainer();
    centerLayout->SetOrientation(terminal::LinearContainer::Orientation::TopToBottom);
    centerLayout->SetSize(42, 10);
    centerLayout->Add(titleBox);
    centerLayout->Add(selector);

    auto box = new terminal::PlacementBox();
    box->SetLeft(1.f);
    box->SetRight(1.f);
    box->SetTop(0.5f);
    box->SetBottom(1);
    box->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    box->Add(centerLayout);

    s->Add(box);

    return s;
}
