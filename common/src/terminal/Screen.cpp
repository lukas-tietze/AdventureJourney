#include "terminal/Window.hpp"

terminal::Screen::Screen() : ContainerBase()
{
}

void terminal::Screen::AttachToWindow(Window *newParent)
{
    if (this->parent != nullptr)
        this->parent->RemoveScreen(this);

    this->parent = newParent;

    auto args = this->MakeArgs();

    this->onAttached(args);
}

void terminal::Screen::DetachFromWindow()
{
    this->parent = nullptr;

    auto args = this->MakeArgs();

    this->onDetached(args);
}

void terminal::Screen::Show()
{
    if (this->parent != nullptr)
        this->parent->SetActiveScreen(this);
}

void terminal::Screen::HandleShow()
{
    this->visible = true;

    auto args = this->MakeArgs();

    this->onShown(args);
}

void terminal::Screen::HandleHide()
{
    this->visible = false;

    auto args = this->MakeArgs();

    this->onHidden(args);
}

terminal::ScreenEventArgs terminal::Screen::MakeArgs()
{
    ScreenEventArgs args;
    args.sender = this;
    args.parent = this->parent;
    args.visible = this->visible;

    return args;
}

util::Event<terminal::ScreenEventArgs> const &terminal::Screen::OnShown()
{
    return this->onShown;
}

util::Event<terminal::ScreenEventArgs> const &terminal::Screen::OnHidden()
{
    return this->onHidden;
}

util::Event<terminal::ScreenEventArgs> const &terminal::Screen::OnDetached()
{
    return this->onDetached;
}

util::Event<terminal::ScreenEventArgs> const &terminal::Screen::OnAttached()
{
    return this->onAttached;
}
