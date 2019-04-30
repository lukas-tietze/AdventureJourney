#include "terminal/controls/NumberPicker.hpp"

#include <limits>
#include "data/String.hpp"

terminal::NumberPicker::NumberPicker() : ControlBase(),
                                         DataBinderBase(),
                                         min(std::numeric_limits<uint32_t>::min()),
                                         max(std::numeric_limits<uint32_t>::max()),
                                         step(1),
                                         largeStep(50),
                                         largeStepEnabled(true),
                                         value(0),
                                         buf()
{
}

terminal::NumberPicker::~NumberPicker()
{
}

uint32_t &terminal::NumberPicker::GetSelectedValue()
{
    return this->value;
}

void terminal::NumberPicker::SetMin(uint32_t min)
{
    this->min = min;
}

uint32_t terminal::NumberPicker::GetMin() const
{
    return this->min;
}

void terminal::NumberPicker::SetMax(uint32_t max)
{
    this->max = max;
}

uint32_t terminal::NumberPicker::GetMax() const
{
    return this->max;
}

void terminal::NumberPicker::SetStep(uint32_t step)
{
    this->step = step;
}

uint32_t terminal::NumberPicker::GetStep() const
{
    return this->step;
}

void terminal::NumberPicker::SetLargeStep(uint32_t largeStep)
{
    this->largeStep = largeStep;
}

uint32_t terminal::NumberPicker::GetLargeStep() const
{
    return this->largeStep;
}

void terminal::NumberPicker::SetValue(uint32_t value)
{
    if (this->value != value)
    {
        this->value = value;
        this->HandleValueChanged();
    }
}

uint32_t terminal::NumberPicker::GetValue() const
{
    return this->value;
}

void terminal::NumberPicker::SetLargeStepEnabled(bool enabled)
{
    this->largeStepEnabled = enabled;
}

bool terminal::NumberPicker::IsLargeStepEnabled() const
{
    return this->largeStepEnabled;
}

void terminal::NumberPicker::HandleKey(terminal::KeyInput &input)
{
    this->ControlBase::HandleKey(input);

    if (input.handled)
        return;

    bool handled = true;

    if (input.specialKey == Key::Up && this->value < this->max && this->largeStepEnabled)
        this->SetValue(util::Min(this->max, this->value + this->largeStep));
    else if (input.specialKey == Key::Down && this->value > this->min && this->largeStepEnabled)
        this->SetValue(util::Max(this->min, this->value - this->largeStep));
    else if (input.specialKey == Key::Right && this->value < this->max)
        this->SetValue(util::Min(this->max, this->value + this->step));
    else if (input.specialKey == Key::Left && this->value > this->min)
        this->SetValue(util::Max(this->min, this->value - this->step));
    else if (input.key >= '0' && input.key <= '9')
        this->SetValue(util::Crop(this->value * 10 + (input.key - static_cast<int>('0')), this->min, this->max));
    else if (input.specialKey == Key::Backspace)
        this->SetValue(util::Crop(this->value / 10, this->min, this->max));
    else
        handled = false;

    input.handled = handled;
}

void terminal::NumberPicker::HandleValueChanged()
{
    this->buf = util::ToString(this->value);
    this->HandleDataChanged();
}

void terminal::NumberPicker::Render(Canvas &c)
{
    auto x = this->GetContentBounds().GetX();
    auto y = this->GetContentBounds().GetY();

    c.DrawString(x, y, "<> ")
        .DrawString(x + 3, y, this->buf);
}
