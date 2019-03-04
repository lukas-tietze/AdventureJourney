#include "terminal/controls/containers/PlacementBox.hpp"

namespace
{
constexpr int TOP = 0;
constexpr int RIGHT = 1;
constexpr int BOTTOM = 2;
constexpr int LEFT = 3;
} // namespace

terminal::PlacementBox::PlacementBox() : ContainerBase()
{
    this->weights[TOP] = 0;
    this->weights[RIGHT] = 0;
    this->weights[BOTTOM] = 0;
    this->weights[LEFT] = 0;
}

terminal::PlacementBox::~PlacementBox()
{
}

void terminal::PlacementBox::Add(ControlBase *item)
{
    if (this->item != nullptr)
        this->Remove(this->item);

    this->item = item;

    this->ContainerBase::Add(item);
}

bool terminal::PlacementBox::Remove(ControlBase *item)
{
    return this->item == item ? this->ContainerBase::Remove(item) : false;
}

void terminal::PlacementBox::RestoreLayout()
{
    if (this->IsValid() || this->item == nullptr)
        return;

    this->item->ApplyAutoSize(this->GetSize());

    auto wWeight = this->weights[LEFT] / (this->weights[LEFT] + this->weights[RIGHT]);
    auto hWeight = this->weights[TOP] / (this->weights[TOP] + this->weights[BOTTOM]);
    auto w = this->GetSize().GetWidth() - this->item->GetSize().GetWidth();
    auto h = this->GetSize().GetHeight() - this->item->GetSize().GetHeight();

    this->item->SetLocation(this->GetLocation() + util::Point(w * wWeight, h * hWeight));

    this->ContainerBase::RestoreLayout();
}

void terminal::PlacementBox::SetTop(float f)
{
    this->weights[TOP] = f;
}

void terminal::PlacementBox::SetBottom(float f)
{
    this->weights[BOTTOM] = f;
}

void terminal::PlacementBox::SetLeft(float f)
{
    this->weights[LEFT] = f;
}

void terminal::PlacementBox::SetRight(float f)
{
    this->weights[RIGHT] = f;
}
