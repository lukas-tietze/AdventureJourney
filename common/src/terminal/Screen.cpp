#include "terminal/Window.hpp"

terminal::Screen::Screen() : ContainerBase()
{
}

void terminal::Screen::AttachToWindow(TerminalWindow *newParent)
{
    if (this->parent != nullptr)
        this->parent->RemoveScreen(this);

    this->parent = newParent();
}

void terminal::Screen::DetachFromWindow()
{
    this->parent = nullptr;
}

void terminal::Screen::Show()
{
    if (this->parent != nullptr)
        this->parent->SetActiveScreen(this);
}
