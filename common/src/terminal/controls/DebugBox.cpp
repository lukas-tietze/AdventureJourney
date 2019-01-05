#include "terminal/controls/DebugBox.hpp"
#include "data/String.hpp"
#include "terminal/TerminalWindow.hpp"

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
    int y0 = this->GetBounds().GetMinY();
    int x0 = this->GetBounds().GetMinX();
    c.DrawString(x0 + 1, y0 + 1, this->GetText());
    c.DrawString(x0 + 1, y0 + 2, util::Format("FocusedControlIndex: %i", dynamic_cast<TerminalWindow*>(this->GetParent())->GetFocusedControlIndex()));
    c.DrawString(x0 + 1, y0 + 3, util::Format(""));
}