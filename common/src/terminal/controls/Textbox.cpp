#include "terminal/controls/Textbox.hpp"

terminal::Textbox::Textbox() : ControlBase()
{
}

terminal::Textbox::Textbox(const std::string &text) : ControlBase()
{
    this->SetText(text);
}

terminal::Textbox::~Textbox()
{
}

void terminal::Textbox::HandleMouse(terminal::MouseInput &action)
{
}

void terminal::Textbox::HandleKey(terminal::KeyInput &action)
{
}

void terminal::Textbox::Render(terminal::Canvas &c)
{
    c.DrawString(this->GetBounds().GetLocation() + util::Point(1, 1), this->GetText());
    c.DrawBox(this->GetBounds(), '-', '|', '+');
}