#include "terminal/controls/Selector.hpp"

terminal::Selector::Selector() : ControlBase(),
                                 items(),
                                 selectedItem(0),
                                 onOptionSelected()
{
}

void terminal::Selector::AddOption(const std::string &name, int marker)
{
    this->items.push_back({name, marker});
}

bool terminal::Selector::RemoveOption(const std::string &name)
{
    for (auto pos = this->items.begin(), end = this->items.end(); pos != end; ++pos)
    {
        if (pos->name == name)
        {
            this->items.erase(pos);
            break;
        }
    }
}

void terminal::Selector::HandleKey(KeyInput &k)
{
    if (k.specialKey == Key::Up && this->selectedItem > 0)
        this->selectedItem--;
    else if (k.specialKey == Key::Down && this->selectedItem < this->items.size() - 1)
        this->selectedItem++;
}

void terminal::Selector::HandleMouse(MouseInput &m)
{
}

void terminal::Selector::Render(Canvas &c)
{
    this->ControlBase::Render(c);

    int x0 = this->GetBounds().GetX();
    int y0 = this->GetBounds().GetY();

    c.SetActiveColorPair(this->Style(ControlStyleColor::UnselectedOption));

    for (size_t i = 0; i < this->items.size() && i < this->GetBounds().GetHeight(); i++)
    {
        if (i == this->selectedItem)
        {
            c.SetActiveColorPair(this->Style(ControlStyleColor::SelectedOption));
            c.DrawString(x0, y0 + i, "> ");
            c.DrawString(x0 + 2, y0 + i, this->items[i].text);
            c.SetActiveColorPair(this->Style(ControlStyleColor::UnselectedOption));
        }
        else
        {
            c.DrawString(x0, y0 + i, "  ");
            c.DrawString(x0 + 2, y0 + i, this->items[i].text);
        }
    }
}

util::Event<terminal::OptionSelectedEventArgs> const &terminal::Selector::OnOptionSelected()
{
    return this->onOptionSelected;
}

const std::string &terminal::Selector::GetSelectedText() const
{
    if (!this->items.empty())
        return this->items[this->selectedItem].text;
}

size_t terminal::Selector::GetSelectedIndex() const
{
    if (!this->items.empty())
        return this->selectedItem;
}

int terminal::Selector::GetSelectedMarker() const
{
    if (!this->items.empty())
        return this->items[this->selectedItem].marker;
}
