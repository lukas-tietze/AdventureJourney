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
    if (action.handled)
        return;

    this->SetText(util::Format2("{%} [%/%]", action.action, action.cx, action.cy));

    action.handled = true;
}

void terminal::DebugBox::HandleKey(terminal::KeyInput &action)
{
    if (action.handled)
        return;

    if (terminal::IsSpecialKey(action.key))
    {
        this->SetText(util::Format2("<%> [%]", static_cast<terminal::Key>(action.key), action.key));
    }
    else if (terminal::IsAsciiKey(action.key))
    {
        this->SetText(util::Format2("'%' [%]", static_cast<char>(action.key), action.key));
    }
    else
    {
        this->SetText(util::Format2("\"%\" [%]", util::UtfCodePointToNarrowString(action.key), action.key));
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