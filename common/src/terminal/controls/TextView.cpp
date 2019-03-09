#include "terminal/controls/TextView.hpp"
#include "data/String.hpp"
#include "data/Io.hpp"

terminal::TextView::TextView() : ControlBase()
{
}

terminal::TextView::TextView(const std::string &text) : ControlBase()
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

void terminal::TextView::PrepareText()
{
    auto tabCount = 0;
    auto start = this->GetText().c_str();
    auto end = start + this->GetText().length();

    for (auto i = start; i != end; i++)
        if (*i == '\t')
            tabCount++;

    if (tabCount == 0)
        return;

    std::string res;

    res.reserve(this->GetText().length());

    for (auto i = start; i != end; i++)
        if (*i == '\t')
            res.append("    ");
        else
            res.push_back(*i);

    this->SetTextCore(res);
}

void terminal::TextView::PrepareLines()
{
    this->lines.clear();

    const auto &text = this->GetText();
    const size_t maxLineLength = this->GetBounds().GetWidth() - 2;
    size_t pos = 0;

    while (pos < text.length())
    {
        size_t next = 0;
        bool lineBreakFound = false;

        for (auto i = pos; i < text.length() && i < pos + maxLineLength; i++)
        {
            if (text[i] == '\n')
            {
                this->lines.push_back(text.substr(pos, i - pos));
                pos = i + 1;
                lineBreakFound = true;
                break;
            }
        }

        if (lineBreakFound)
            break;

        if (pos + maxLineLength >= text.length())
        {
            this->lines.push_back(text.substr(pos));

            break;
        }
        else
        {
            auto next = pos + maxLineLength;

            // Zum Ende des letzten Wortes gehen
            while (next > pos && !std::isspace(text[next]))
            {
                next--;
            }

            if (next > pos)
            {
                this->lines.push_back(text.substr(pos, next - pos));

                pos = next + 1;
            }
            else
            {
                this->lines.push_back(text.substr(pos, maxLineLength));
                pos += maxLineLength;
            }
        }
    }
}

void terminal::TextView::RestoreLayout()
{
    util::Justify(this->GetText(), this->GetBounds().GetWidth() - 2, this->lines);    

    util::dbg.WriteLine("TextView [%]: justified text: ", this);

    for (size_t i = 0; i < this->lines.size(); i++)
        util::dbg.WriteLine("Line %/%: \"%\"", i, this->lines.size(), this->lines[i]);

    this->ControlBase::RestoreLayout();
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

void terminal::TextView::Render(terminal::Canvas &c)
{
    c.DrawBox(this->GetBounds(), '-', '|', '+');

    const size_t vh = this->GetBounds().GetHeight() - 2;
    const size_t vw = this->GetBounds().GetWidth() - 2;

    if (this->lines.empty() || vh <= 0 || vw <= 0)
        return;

    int x = this->GetBounds().GetMinX() + 1;
    int y = this->GetBounds().GetMinY() + 1;

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

    if (visibleLines > 0)
    {
        if (centerHorizontal)
            for (size_t i = 0; i < visibleLines; i++)
                c.DrawString(x + (vw - this->lines[i].length()) / 2, y + i, this->lines[this->firstLine + i]);
        else
            for (size_t i = 0; i < visibleLines; i++)
                c.DrawString(x, y + i, this->lines[this->firstLine + i]);
    }
}