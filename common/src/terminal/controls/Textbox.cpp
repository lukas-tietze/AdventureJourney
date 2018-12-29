#include "terminal/controls/Textbox.hpp"
#include "data/String.hpp"

terminal::Textbox::Textbox() : TextView()
{
}

terminal::Textbox::Textbox(const std::string &text) : TextView()
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
    if (action.handled)
        return;

    if (terminal::IsSpecialKey(action.key))
    {
        this->SetText(util::ToString(static_cast<terminal::Key>(action.key)));
    }
    else
    {
        std::string copy = this->GetText();
        copy.append(util::UtfCodePointToNarrowString(action.key));

        this->SetText(copy);
    }

    action.handled = true;
}

// void terminal::Textbox::Render(terminal::Canvas &c)
// {
//     c.DrawString(this->GetBounds().GetLocation() + util::Point(1, 1), this->GetText());
//     c.DrawBox(this->GetBounds(), '-', '|', '+');
// }

void terminal::Textbox::HandleFocusAquired()
{
    TerminalView::GetInstance()->SetCursorMode(terminal::CursorMode::Default);
}