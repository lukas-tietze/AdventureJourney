#pragma once

#include <vector>

#include "terminal/controls/ControlBase.hpp"
#include "data/String.hpp"
#include "Event.hpp"

namespace terminal
{
template <class TData = int>
class Picker : public ControlBase
{
  private:
    struct Option
    {
        TData value;
        std::string text;
        bool hasText;
        colorPairId_t style;
        bool hasStyle;

        Option(const TData &value, const std::string &text, bool hasText, colorPairId_t style, bool hasStyle) : value(value),
                                                                                                                text(text),
                                                                                                                hasText(hasText),
                                                                                                                style(style),
                                                                                                                hasStyle(hasStyle)
        {
        }
    };

    std::vector<Option> options;
    bool circleOptions;
    bool horizontalMode;
    size_t selectedOption;
    TData *boundData;

  public:
    Picker() : ControlBase(),
               options(),
               circleOptions(false),
               horizontalMode(true),
               selectedOption(0)
    {
    }

    ~Picker()
    {
    }

    void AddOption(const TData &value)
    {
        this->options.push_back(Option(value, "", false, 0, false));

        this->Invalidate();
    }

    void AddOption(const TData &value, const std::string &text)
    {
        this->options.push_back(Option(value, text, true, 0, false));

        this->Invalidate();
    }

    void AddStyledOption(const TData &value, colorPairId_t style, int marker)
    {
        this->options.push_back(Option(value, "", false, style, true));

        this->Invalidate();
    }

    void AddStyledOption(const TData &value, const std::string &text, colorPairId_t style, int marker)
    {
        this->options.push_back(Option(value, text, true, style, true));

        this->Invalidate();
    }

    bool RemoveOption(const std::string &text)
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

    bool RemoveOption(int marker)
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

    bool ClearOptions()
    {
        this->options.clear();

        this->Invalidate();
    }

    void BindValue(TData *target)
    {
        this->boundData = target;
    }

    void UnbindValue()
    {
        this->boundData = nullptr;
    }

    void SetCircleOptions(bool value)
    {
        this->circleOptions = value;
    }

    bool IsCircleOptionsSet() const
    {
        return this->circleOptions;
    }

    void SetHorizontalMode(bool value)
    {
        this->horizontalMode = value;
    }

    bool IsHorizontalModeSet() const
    {
        return this->horizontalMode;
    }

    bool HasOptions() const
    {
        return !this->options.empty();
    }

    size_t GetSelectedOption() const
    {
        return this->selectedOption;
    }

    const std::string &GetSelectedText() const
    {
        return this->options[this->selectedOption].text;
    }

    const TData &GetSelectValue() const
    {
        return this->options[this->selectedOption].value;
    }

    void HandleKey(KeyInput &input)
    {
        if (input.handled)
            return;

        if (input.specialKey == Key::Left && this->selectedOption > 0)
            this->selectedOption--;
        else if (input.specialKey == Key::Right && this->selectedOption < this->options.size() - 1)
            this->selectedOption++;
    }

    void Render(Canvas &c)
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

        std::string text = option.hasText ? option.text : util::ToString(option.value);

        if (text.length() > maxLen)
            text.erase(maxLen);

        if (this->horizontalMode)
            c.DrawString(x + 1 + (w - text.length()) / 2, y + h / 2, text);
        else
            c.DrawString(x + (w - text.length()) / 2, y + 1 + (h - 1) / 2, text);
    }
};
} // namespace terminal