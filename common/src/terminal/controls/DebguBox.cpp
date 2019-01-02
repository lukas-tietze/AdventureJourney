#include "terminal/controls/DebugBox.hpp"
#include "data/String.hpp"

terminal::DebugBox::DebugBox() : ControlBase()
{
}

terminal::DebugBox::~DebugBox()
{
}

void terminal::DebugBox::HandleMouse(terminal::MouseInput &action)
{
}

void terminal::DebugBox::HandleKey(terminal::KeyInput &action)
{
    if (action.handled)
        return;

    std::string format = "% [%]";

    if (terminal::IsSpecialKey(action.key))
    {
        this->SetText(util::Format2(format, static_cast<terminal::Key>(action.key), action.key));
    }
    else if (terminal::IsAsciiKey(action.key))
    {
        this->SetText(util::Format2(format, static_cast<char>(action.key), action.key));
    }
    else
    {
        this->SetText(util::Format2(format, util::UtfCodePointToNarrowString(action.key), action.key));
    }

    return;

    if (terminal::IsSpecialKey(action.key))
    {
        auto key = static_cast<terminal::Key>(action.key);

        if (key == Key::Backspace && this->cursorIndex > 0)
        {
            std::string text;
            text.reserve(this->GetText().length());
            text.append(this->GetText(), 0, this->cursorIndex);
            text.append(this->GetText(), this->cursorIndex + 1);

            text.erase();
        }
        else if (key == Key::Delete && this->cursorIndex < this->GetText().length())
        {
            std::string text;
            text.reserve(this->GetText().length());
            text.append(this->GetText(), 0, this->cursorIndex);
            text.append(this->GetText(), this->cursorIndex + 1);

            text.erase();
        }
        else if (key == Key::Left && this->cursorIndex > 0)
        {
            this->cursorIndex--;
        }
        else if (key == Key::Right && this->cursorIndex < this->GetText().length())
        {
            this->cursorIndex++;
        }
    }
    else if (terminal::IsAsciiKey(action.key))
    {
        char c = static_cast<char>(action.key);
        std::string copy = this->GetText();

        if (c == '\n')
            return;

        if (c == '\t')
        {
            copy.append(4, ' ');
        }
        else
        {
            copy.push_back(c);
        }

        this->SetText(copy);
    }
    else
    {
        std::string copy = this->GetText();
        copy.append(util::UtfCodePointToNarrowString(action.key));

        this->SetText(copy);
    }

    action.handled = true;
}

void terminal::DebugBox::HandleFocusAquired()
{
    auto view = TerminalView::GetInstance();
    view->SetCursorMode(terminal::CursorMode::Default);
}

void terminal::DebugBox::Render(Canvas &c)
{
    c.DrawBox(this->GetBounds(), '-', '|', '+');
    c.DrawString(this->GetBounds().GetMinX() + 1, this->GetBounds().GetMinY() + 1, this->GetText());
}