#include "terminal/controls/Picker.hpp"

terminal::Picker::Picker() : ControlBase(),
                             options(),
                             circleOptions(false),
                             horizontalMode(true),
                             selectedOption(0)
{
}

terminal::Picker::~Picker()
{
}

void terminal::Picker::AddOption(const std::string &value, int marker)
{
    this->options.push_back({value,
                             marker,
                             false,
                             static_cast<colorPairId_t>(-1)});

    this->Invalidate();
}

void terminal::Picker::AddStyledOption(const std::string &value, colorPairId_t style, int marker)
{
    this->options.push_back({value,
                             marker,
                             true,
                             style});

    this->Invalidate();
}

bool terminal::Picker::RemoveOption(const std::string &text)
{
    for (auto pos = this->options.begin(), end = this->options.end(); pos != end; ++pos)
    {
        if (pos->value == text)
        {
            this->options.erase(pos);
            this->Invalidate();

            break;
        }
    }
}

bool terminal::Picker::RemoveOption(int marker)
{
    for (auto pos = this->options.begin(), end = this->options.end(); pos != end; ++pos)
    {
        if (pos->marker == marker)
        {
            this->options.erase(pos);
            this->Invalidate();

            break;
        }
    }
}

bool terminal::Picker::ClearOptions()
{
    this->options.clear();

    this->Invalidate();
}

void terminal::Picker::SetCircleOptions(bool value)
{
    this->circleOptions = value;
}

bool terminal::Picker::IsCircleOptionsSet() const
{
    return this->circleOptions;
}

void terminal::Picker::SetHorizontalMode(bool value)
{
    this->horizontalMode = value;
}

bool terminal::Picker::IsHorizontalModeSet() const
{
    return this->horizontalMode;
}

void terminal::Picker::HandleKey(KeyInput &input)
{
    if (input.handled)
        return;

    if (input.specialKey == Key::Left && this->selectedOption > 0)
        this->selectedOption--;
    else if (input.specialKey == Key::Right && this->selectedOption < this->options.size() - 1)
        this->selectedOption++;
}

void terminal::Picker::Render(Canvas &c)
{
    if (this->options.empty())
        return;

    int x = this->GetContentBounds().GetX();
    int y = this->GetContentBounds().GetY();
    int w = this->GetContentBounds().GetWidth();
    int h = this->GetContentBounds().GetHeight();
    int maxLen;
    const auto &option = this->options[this->selectedOption];

    if (this->horizontalMode)
    {
        if (this->selectedOption > 0 || this->circleOptions)
            c.DrawChar(x, y + h / 2, '<');

        if (this->selectedOption < this->options.size() - 1 || this->circleOptions)
            c.DrawChar(x + w - 1, y + h / 2, '>');

        maxLen = w - 2;
    }
    else
    {
        if (this->selectedOption > 0 || this->circleOptions)
            c.DrawChar(x + w / 2, y, '^');

        if (this->selectedOption < this->options.size() - 1 || this->circleOptions)
            c.DrawChar(x + w / 2, y + h - 1, 'v');

        maxLen = w;
    }

    if (option.hasStyle)
        c.SetActiveColorPair(option.style);

    const std::string &text = option.value.length() > maxLen
                                  ? option.value.substr(0, maxLen)
                                  : option.value;

    if (this->horizontalMode)
        c.DrawString(x + 1 + (w - text.length()) / 2, y + h / 2, text);
    else
        c.DrawString(x + (w - text.length()) / 2, y + 1 + (h - 1) / 2, text);
}
