#include "controls/Button.hpp"

terminal::Button::Button() : ControlBase()
{
}

terminal::Button::Button(const std::string &text) : ControlBase()
{
    this->SetText(text);
}

terminal::Button::~Button()
{
}

void terminal::Button::HandleMouse(terminal::MouseInput &action)
{
    this->SetText("Yo pressed me!");
}

void terminal::Button::HandleKey(terminal::KeyInput &action)
{
}

void terminal::Button::Render(Canvas &c)
{
    c.DrawString(this->GetBounds().GetLocation() + util::Point(1, 1), this->GetText());
    c.DrawBox(this->GetBounds(), '-', '|', '+');
}