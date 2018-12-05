#include "terminal/controls/TextView.hpp"
#include "data/String.hpp"

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
}

void terminal::TextView::HandleBoundsChanged(const util::Rectangle &oldBounds)
{
    if (oldBounds.GetSize() != this->GetBounds().GetSize())
    {
        this->PrepareLines();
    }
}

void terminal::TextView::HandleTextChanged(const std::string &oldText)
{
    if (this->GetText() != oldText)
    {
        this->PrepareText();
        this->PrepareLines();
    }
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

    size_t last = 0;
    size_t pos = 0;
    size_t next = 0;
    size_t maxLineLength = this->GetBounds().GetWidth() - 2;

    while (pos < text.length())
    {
        next = text.length();

        for (size_t i = pos; i < text.length(); i++)
        {
            if (std::isspace(text[i]) ||
                pos + i > maxLineLength)
            {
                next = i;
                break;
            }
        }

        if (next - last > maxLineLength || text[next] == '\n')
        {
            this->lines.push_back(util::Strip(text.substr(last, pos - last)));
            last = pos;
        }

        pos = next + 1;
    }
}

void terminal::TextView::Render(terminal::Canvas &c)
{
    c.DrawBox(this->GetBounds(), '-', '|', '+');

    if (this->GetBounds().GetHeight() > 2 && !this->lines.empty())
    {
        int visibleLines = std::min(this->lines.size(), (size_t)(this->GetBounds().GetHeight() - 2));

        for (size_t i = 0; i < visibleLines; i++)
        {
            c.DrawString(this->GetBounds().GetLocation() + util::Point(1, i + 1), this->lines[i]);
        }
    }
}