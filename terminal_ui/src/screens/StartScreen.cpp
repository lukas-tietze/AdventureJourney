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

    auto titleText = new terminal::TextView("Welcome to \n Galaxy At War \n\n [press any key to continue]");
    titleText->SetSize(20, 6);

    auto box = new terminal::PlacementBox();
    box->SetLeft(1.f);
    box->SetRight(1.f);
    box->SetTop(0.5f);
    box->SetBottom(1);
    box->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    box->Add(titleText);

    s->Add(box);
    s->OnKey().Register(&HandleKey);

    return s;
}