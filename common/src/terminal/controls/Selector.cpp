#include "terminal/controls/Selector.hpp"
#include "data/Io.hpp"

terminal::Selector::Selector() : ControlBase(),
                                 items(),
                                 selectedItem(0),
                                 onOptionSelected(),
                                 marker('>')
{
}

void terminal::Selector::SetCenterText(bool value)
{
    this->centerText = value;
}

bool terminal::Selector::IsTextCentered() const
{
    return this->centerText;
}

void terminal::Selector::SetMarker(char marker)
{
    this->marker = marker;
}

void terminal::Selector::ResetMarker()
{
    this->marker = '>';
}

void terminal::Selector::DisableMarker()
{
    this->marker = ' ';
}

char terminal::Selector::GetMarker() const
{
    return this->marker;
}

void terminal::Selector::AddOption(const std::string &name, int marker)
{
    this->items.push_back(this->selectableItems.size());
    this->selectableItems.push_back({name, marker >= 0 ? marker : 0});
}

void terminal::Selector::AddSeperator(char placeholder)
{
    this->items.push_back(-1);
}

bool terminal::Selector::RemoveOption(const std::string &name)
{
    for (auto pos = this->selectableItems.begin(), end = this->selectableItems.end(); pos != end; ++pos)
    {
        if (pos->text == name)
        {
            this->selectableItems.erase(pos);
            break;
        }
    }

    this->Invalidate();
}

bool terminal::Selector::RemoveOption(int marker)
{
    for (auto pos = this->selectableItems.begin(), end = this->selectableItems.end(); pos != end; ++pos)
    {
        if (pos->marker == marker)
        {
            this->selectableItems.erase(pos);
            break;
        }
    }

    this->Invalidate();
}

bool terminal::Selector::ClearOptions()
{
    this->items.clear();
    this->selectableItems.clear();
    this->Invalidate();
}

void terminal::Selector::UpdateColors()
{
    this->ControlBase::UpdateColors();

    this->markerStyle = this->Style(ControlStyleColor::SelectedOption);
    this->selectedOptionForeground = this->Style(ControlStyleColor::ControlText);
    this->selectedOptionBackground = this->Style(ControlStyleColor::ControlText);
}

void terminal::Selector::HandleKey(KeyInput &k)
{
    if (k.specialKey == Key::Up && this->selectedItem > 0)
    {
        this->selectedItem--;
        k.handled = true;
        util::dbg.WriteLine("Selector [%]: Selected next option index=% text=%, marker=%",
                            this->GetName(),
                            this->selectedItem,
                            this->selectableItems[this->selectedItem].text,
                            this->selectableItems[this->selectedItem].marker);
    }
    else if (k.specialKey == Key::Down && this->selectedItem < this->selectableItems.size() - 1)
    {
        this->selectedItem++;
        k.handled = true;
        util::dbg.WriteLine("Selector [%]: Selected next option index=% text=%, marker=%",
                            this->GetName(),
                            this->selectedItem,
                            this->selectableItems[this->selectedItem].text,
                            this->selectableItems[this->selectedItem].marker);
    }
}

void terminal::Selector::HandleMouse(MouseInput &m)
{
}

void terminal::Selector::Render(Canvas &c)
{
    this->ControlBase::Render(c);

    int x0 = this->GetContentBounds().GetX();
    int y0 = this->GetContentBounds().GetY();
    std::string placeholder(this->GetContentBounds().GetWidth() - 2, '-');

    c.SetActiveColorPair(this->Style(ControlStyleColor::UnselectedOption));

    for (size_t i = 0; i < this->items.size() && i < this->GetContentBounds().GetHeight(); i++)
    {
        auto pos = this->items[i];

        if (pos == -1)
        {
            c.DrawString(x0 + 1, y0 + i, placeholder);
        }
        else
        {
            auto &item = this->selectableItems[pos];

            if (pos == this->selectedItem)
            {
                c.SetActiveColorPair(this->markerStyle);
                c.DrawChar(x0, y0 + i, this->marker);
                c.SetActiveColorPair(this->selectedOptionForeground);

                if (this->centerText)
                    c.DrawString(x0 + (this->GetContentBounds().GetWidth() - item.text.length()) / 2, y0 + i, item.text);
                else
                    c.DrawString(x0 + 2, y0 + i, item.text);

                c.SetActiveColorPair(this->GetTextColor());
            }
            else
            {
                if (this->centerText)
                    c.DrawString(x0 + (this->GetContentBounds().GetWidth() - item.text.length()) / 2, y0 + i, item.text);
                else
                    c.DrawString(x0 + 2, y0 + i, item.text);
            }
        }
    }
}

util::Event<terminal::OptionSelectedEventArgs> const &terminal::Selector::OnOptionSelected()
{
    return this->onOptionSelected;
}

const std::string &terminal::Selector::GetSelectedText() const
{
    return this->selectableItems.empty() ? "" : this->selectableItems[this->selectedItem].text;
}

size_t terminal::Selector::GetSelectedIndex() const
{
    return this->selectableItems.empty() ? static_cast<size_t>(-1) : this->selectedItem;
}

int terminal::Selector::GetSelectedMarker() const
{
    return this->selectableItems.empty() ? 0 : this->selectableItems[this->selectedItem].marker;
}

char terminal::Selector::GetSeperatorChar() const
{
    return this->seperatorChar;
}

void terminal::Selector::SetSeperatorChar(char value)
{
    this->seperatorChar = value;
}

terminal::colorPairId_t terminal::Selector::GetMarkerStyle() const
{
    return this->markerStyle;
}

void terminal::Selector::SetMarkerStyle(colorPairId_t value)
{
    this->markerStyle = value;
}

terminal::colorPairId_t terminal::Selector::GetSeperatorStyle() const
{
    return this->seperatorStyle;
}

void terminal::Selector::SetSeperatorStyle(colorPairId_t value)
{
    this->seperatorStyle = value;
}

terminal::colorPairId_t terminal::Selector::GetSelectedOptionForeground() const
{
    return this->selectedOptionForeground;
}

void terminal::Selector::SetSelectedOptionForeground(colorPairId_t value)
{
    this->selectedOptionForeground = value;
}

terminal::colorPairId_t terminal::Selector::GetSelectedOptionBackground() const
{
    return this->selectedOptionBackground;
}

void terminal::Selector::SetSelectedOptionBackground(colorPairId_t value)
{
    this->selectedOptionBackground = value;
}
