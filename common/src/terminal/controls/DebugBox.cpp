#include "terminal/controls/DebugBox.hpp"
#include "data/String.hpp"
#include "terminal/TerminalWindow.hpp"
#include "data/Io.hpp"

terminal::DebugBox::DebugBox() : ControlBase()
{
    this->SetMinSize(util::Dimension(10, 5));
}

terminal::DebugBox::~DebugBox()
{
}

void terminal::DebugBox::HandleMouse(terminal::MouseInput &action)
{
    if (action.handled)
        return;

    this->SetText(util::Format("{%} [%/%]", action.action, action.cx, action.cy));

    action.handled = true;
}

void terminal::DebugBox::HandleKey(terminal::KeyInput &action)
{
    if (action.handled)
        return;

    auto view = TerminalView::GetInstance();

    if (terminal::IsSpecialKey(action.key))
    {
        auto key = static_cast<terminal::Key>(action.key);

        view->SetCursorMode(CursorMode::Default);

        if (key == Key::Up)
            view->SetCursorPosition(view->GetCursorPosition() + util::Point(0, 1));
        else if (key == Key::Down)
            view->SetCursorPosition(view->GetCursorPosition() + util::Point(0, -1));
        else if (key == Key::Right)
            view->SetCursorPosition(view->GetCursorPosition() + util::Point(1, 0));
        else if (key == Key::Left)
            view->SetCursorPosition(view->GetCursorPosition() + util::Point(-1, 0));
        else if (key == Key::Insert)
            if (view->GetCursorMode() == CursorMode::Highlighted)
                view->SetCursorMode(CursorMode::Default);
            else
                view->SetCursorMode(CursorMode::Highlighted);

        this->SetText(util::Format("<%> [%]", key, action.key));
    }
    else if (terminal::IsAsciiKey(action.key))
    {
        auto key = static_cast<char>(action.key);

        if (key == '\n')
        {
            this->HandleCommand();
        }
        else if (this->command.length() < 10 && ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')))
        {
            this->command.push_back(key);
        }

        this->SetText(util::Format("'%' [%]", util::Unescape(key), action.key));
    }
    else
    {
        this->SetText(util::Format("\"%\" [%]", util::UtfCodePointToNarrowString(action.key), action.key));
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
    int y0 = this->GetBounds().GetMinY();
    int x0 = this->GetBounds().GetMinX();
    c.DrawString(x0 + 1, y0 + 1, this->GetText());
    c.DrawString(x0 + 1, y0 + 2, util::Format(""));
    c.DrawString(x0 + 1, y0 + 3, this->command);
}

void terminal::DebugBox::HandleCommand()
{
    if (this->command == "colDump")
    {
        TerminalView::GetInstance()->SaveCurrentColorPallette("colors.json");

        util::err.WriteLine("Dumped colors");
    }
    else
    {
        util::err.WriteLine("Unknown command \"%\"", this->command);
    }

    this->command.clear();
}