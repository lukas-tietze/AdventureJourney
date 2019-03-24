#include "Screens.hpp"

#include "Terminal.hpp"

namespace
{
void HandleKey(terminal::KeyEventArgs &args)
{
    args.handled = true;
    screens::Menu->Show();
}
} // namespace

terminal::Screen *screens::CreateStartScreen()
{
    auto s = new terminal::Screen();

    auto titleText = new terminal::TextView("Welcome to\nGalaxy At War\n\n[press any key to continue]");
    titleText->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    titleText->SetBorderEnabled(true);
    titleText->SetCenterVertical(true);
    titleText->SetCenterHorizontal(true);

    auto box = new terminal::PlacementBox();
    box->SetHorizontalPartition(0.2f, 0.6f, 0.2f);
    box->SetVerticalPartition(0.05f, 0.8f, 0.15f);
    box->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    box->Add(titleText);

    s->Add(box);
    s->OnKey().Register(&HandleKey);

    return s;
}