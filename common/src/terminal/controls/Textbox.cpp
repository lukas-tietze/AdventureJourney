#include "terminal/controls/Textbox.hpp"
#include "data/String.hpp"

terminal::Textbox::Textbox() : ControlBase(),
                               cursorIndex(0)
{
}

terminal::Textbox::Textbox(const std::string &text) : ControlBase(),
                                                      cursorIndex(0)
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
        terminal::Key key = static_cast<terminal::Key>(action.key);

        switch (key)
        {
        case terminal::Key::Backspace:
            if (this->cursorIndex > 0)
            {
                std::string text;
                text.reserve(this->GetText().length());
                text.append(this->GetText(), 0, this->cursorIndex);
                text.append(this->GetText(), this->cursorIndex + 1);

                text.erase();
            }
            break;
        case terminal::Key::Delete:
            if (this->cursorIndex < this->GetText().length())
            {
                std::string text;
                text.reserve(this->GetText().length());
                text.append(this->GetText(), 0, this->cursorIndex);
                text.append(this->GetText(), this->cursorIndex + 1);

                text.erase();
            }
            break;
        case terminal::Key::Left:
            if (this->cursorIndex > 0)
                this->cursorIndex--;
            break;
        case terminal::Key::Right:
            if (this->cursorIndex < this->GetText().length())
                this->cursorIndex++;
            break;
        case terminal::Key::Down:
        case terminal::Key::Up:
        case terminal::Key::Pos1:
        case terminal::Key::F0:
        case terminal::Key::F1:
        case terminal::Key::F2:
        case terminal::Key::F3:
        case terminal::Key::F4:
        case terminal::Key::F5:
        case terminal::Key::F6:
        case terminal::Key::F7:
        case terminal::Key::F8:
        case terminal::Key::F9:
        case terminal::Key::F10:
        case terminal::Key::F11:
        case terminal::Key::F12:
        case terminal::Key::DeleteLine:
        case terminal::Key::InsertLine:
        case terminal::Key::Insert:
        case terminal::Key::Eic:
        case terminal::Key::Clear:
        case terminal::Key::ClearToEndOfScreen:
        case terminal::Key::ClearToEndOfLine:
        case terminal::Key::ScrollForward:
        case terminal::Key::ScrollBackward:
        case terminal::Key::PageUp:
        case terminal::Key::PageDown:
        case terminal::Key::Tab:
        case terminal::Key::ClearTab:
        case terminal::Key::ClearAllTabs:
        case terminal::Key::Enter:
        case terminal::Key::Print:
        case terminal::Key::LowerLeft:
        case terminal::Key::KeypadA1:
        case terminal::Key::KeypadA3:
        case terminal::Key::KeypadB2:
        case terminal::Key::KeypadC1:
        case terminal::Key::KeypadC3:
        case terminal::Key::BackTab:
        case terminal::Key::Begin:
        case terminal::Key::Cancel:
        case terminal::Key::Close:
        case terminal::Key::Command:
        case terminal::Key::Copy:
        case terminal::Key::Create:
        case terminal::Key::End:
        case terminal::Key::Exit:
        case terminal::Key::Find:
        case terminal::Key::Help:
        case terminal::Key::Mark:
        case terminal::Key::Message:
        case terminal::Key::Move:
        case terminal::Key::Next:
        case terminal::Key::Open:
        case terminal::Key::Options:
        case terminal::Key::Previous:
        case terminal::Key::Redo:
        case terminal::Key::Reference:
        case terminal::Key::Refresh:
        case terminal::Key::Replace:
        case terminal::Key::Restart:
        case terminal::Key::Resume:
        case terminal::Key::Save:
        case terminal::Key::Sbeg:
        case terminal::Key::ShiftCommand:
        case terminal::Key::ShiftCancel:
        case terminal::Key::ShiftCopy:
        case terminal::Key::ShiftCreate:
        case terminal::Key::ShiftDeleteChar:
        case terminal::Key::ShiftDeleteLine:
        case terminal::Key::Select:
        case terminal::Key::ShiftEnd:
        case terminal::Key::ShiftClearToEndOfLine:
        case terminal::Key::ShiftExit:
        case terminal::Key::ShiftFind:
        case terminal::Key::ShiftHelp:
        case terminal::Key::ShiftHome:
        case terminal::Key::ShiftInsertChar:
        case terminal::Key::ShiftLeft:
        case terminal::Key::ShiftMessage:
        case terminal::Key::ShiftMove:
        case terminal::Key::ShiftNext:
        case terminal::Key::ShiftOptions:
        case terminal::Key::ShiftPrevious:
        case terminal::Key::ShiftPrint:
        case terminal::Key::ShiftRedo:
        case terminal::Key::ShiftReplace:
        case terminal::Key::ShiftRight:
        case terminal::Key::ShiftResume:
        case terminal::Key::ShiftSave:
        case terminal::Key::ShiftSuspend:
        case terminal::Key::ShiftUndo:
        case terminal::Key::Suspend:
        case terminal::Key::Undo:
        case terminal::Key::Mouse:
        case terminal::Key::Resize:
        case terminal::Key::Event:
            break;
        default:
            throw util::InvalidCaseException();
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

void terminal::Textbox::HandleFocusAquired()
{
    auto view = TerminalView::GetInstance();
    view->SetCursorMode(terminal::CursorMode::Default);
    view->SetCursorPosition(this->GetBounds().GetLocation() + util::Point(this->GetTrueCursorIndex() + 1, 1));
}

void terminal::Textbox::Render(Canvas &c)
{
    c.DrawBox(this->GetBounds(), '-', '|', '+');
    c.DrawString(this->GetBounds().GetMinX() + 1, this->GetBounds().GetMinY() + 1, this->GetText());
    TerminalView::GetInstance()->SetCursorPosition(this->GetBounds().GetLocation() + util::Point(this->GetTrueCursorIndex() + 1, 1));
}

int terminal::Textbox::GetTrueCursorIndex() const
{
    return 0;
}