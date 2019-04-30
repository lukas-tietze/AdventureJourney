#include "terminal/controls/TextView.hpp"
#include "data/String.hpp"
#include "data/Io.hpp"

terminal::TextView::TextView() : ControlBase(),
                                 lines(),
                                 firstLine(0),
                                 centerVertical(false),
                                 centerHorizontal(false),
                                 scrollAllowed(false),
                                 trimLines(false)
{
}

terminal::TextView::TextView(const std::string &text) : TextView()
{
    this->SetText(text);
}

terminal::TextView::~TextView()
{
}

void terminal::TextView::HandleMouse(terminal::MouseInput &action)
{
}

void terminal::TextView::HandleKey(terminal::KeyInput &action)
{
    if (action.handled || !terminal::IsSpecialKey(action.key) || !this->scrollAllowed)
        return;

    auto key = action.specialKey;
    bool handled = true;

    if (key == Key::Up && this->firstLine > 0)
    {
        this->firstLine--;
    }
    else if (key == Key::Down && this->firstLine < this->lines.size())
    {
        this->firstLine++;
    }
    else if (key == Key::PageUp && this->firstLine > 0)
    {
        this->firstLine = std::max(static_cast<size_t>(0), this->firstLine - (this->GetBounds().GetHeight() - 2));
    }
    else if (key == Key::PageDown && this->firstLine < this->lines.size())
    {
        this->firstLine = std::min(this->lines.size() - 1, this->firstLine + (this->GetBounds().GetHeight() - 2));
    }
    else
    {
        handled = false;
    }

    action.handled = handled;
}

void terminal::TextView::HandleBoundsChanged()
{
    this->Invalidate();
}

void terminal::TextView::HandleTextChanged()
{
    this->Invalidate();
}

void terminal::TextView::RestoreLayout()
{
    this->ControlBase::RestoreLayout();

    this->lines.clear();

    if (this->multiLine)
    {
        util::Justify(this->GetText(), this->GetContentBounds().GetWidth(), this->lines);

        for (auto &line : this->lines)
            util::StripInplace(line);
    }
    else
    {
        auto lineBreak = this->GetText().find('\n');
        auto len = lineBreak == std::string::npos ? this->GetText().length() : lineBreak;

        this->lines.push_back(this->GetText().substr(0, util::Min(static_cast<size_t>(this->GetContentBounds().GetWidth()), len)));
    }
}

void terminal::TextView::SetCenterHorizontal(bool value)
{
    this->centerHorizontal = value;
}

void terminal::TextView::SetCenterVertical(bool value)
{
    this->centerVertical = value;
}

bool terminal::TextView::IsCenterdHorizontal() const
{
    return this->centerHorizontal;
}

bool terminal::TextView::IsCenterdVertical() const
{
    return this->centerVertical;
}

void terminal::TextView::SetScrollingEnabeld(bool value)
{
    this->scrollAllowed = value;
}

bool terminal::TextView::IsScrollingEnabled() const
{
    return this->scrollAllowed;
}

void terminal::TextView::SetTrimLinesEnabeld(bool value)
{
    this->trimLines = value;
}

bool terminal::TextView::IsTrimLinesEnabled() const
{
    return this->trimLines;
}

void terminal::TextView::SetMultiLineEnabled(bool value)
{
    this->multiLine = value;

    this->Invalidate();
}

bool terminal::TextView::IsMultiLineEnabled() const
{
    return this->multiLine;
}

void terminal::TextView::Render(terminal::Canvas &c)
{
    this->ControlBase::Render(c);

    const size_t vh = this->GetContentBounds().GetHeight() - 2;
    const size_t vw = this->GetContentBounds().GetWidth() - 2;

    if (this->lines.empty() || vh <= 0 || vw <= 0)
        return;

    int x = this->GetContentBounds().GetMinX() + 1;
    int y = this->GetContentBounds().GetMinY() + 1;

    size_t visibleLines;

    if (vh > this->lines.size() && this->centerVertical)
    {
        y += (vh - this->lines.size()) / 2;
        visibleLines = this->lines.size();
    }
    else
    {
        visibleLines = std::min(this->lines.size() - this->firstLine, vh);
    }

    c.SetActiveColorPair(0);

    if (visibleLines > 0)
    {
        if (this->centerHorizontal)
            for (size_t i = this->firstLine; i < this->firstLine + visibleLines; i++)
                c.DrawString(x + ((vw - this->lines[i].length()) / 2), y + i, this->lines[i]);

        else
            for (size_t i = this->firstLine; i < this->firstLine + visibleLines; i++)
                c.DrawString(x, y + i, this->lines[i]);
    }
}