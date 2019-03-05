#include "terminal/controls/containers/PlacementBox.hpp"

namespace
{
constexpr int TOP = 0;
constexpr int RIGHT = 1;
constexpr int BOTTOM = 2;
constexpr int LEFT = 3;
} // namespace

terminal::PlacementBox::PlacementBox() : ContainerBase(),
                                         top(0.f),
                                         bottom(0.f),
                                         left(0.f),
                                         right(0.f),
                                         width(1.f),
                                         height(1.f)
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
    if (this->item == item && this->ContainerBase::Remove(item))
    {
        this->item = nullptr;
        return true;
    }

    return false;
}

void terminal::PlacementBox::RestoreLayout()
{
    if (this->IsValid() || this->item == nullptr)
        return;

    auto wTotal = this->left + this->right + this->width;
    auto hTotal = this->top + this->bottom + this->height;

    if (wTotal == 0.f)
        wTotal = 1.f;

    if (hTotal == 0.f)
        hTotal = 1.f;

    auto w = this->GetSize().GetWidth();
    auto h = this->GetSize().GetHeight();

    this->item->ApplyAutoSize(util::Dimension(w * this->width / wTotal, h * this->height / hTotal));

    auto rw = w - this->item->GetSize().GetWidth();
    auto rh = h - this->item->GetSize().GetHeight();

    this->item->SetLocation(this->GetLocation() + util::Point(w * (this->left + this->right) / wTotal, h * (this->top + this->bottom) / hTotal));

    this->ContainerBase::RestoreLayout();
}

void terminal::PlacementBox::SetTop(float f)
{
    this->top = f;
}

void terminal::PlacementBox::SetBottom(float f)
{
    this->bottom = f;
}

void terminal::PlacementBox::SetLeft(float f)
{
    this->left = f;
}

void terminal::PlacementBox::SetRight(float f)
{
    this->right = f;
}

void terminal::PlacementBox::SetItemWidth(float f)
{
    this->width = f;
}

void terminal::PlacementBox::SetItemHeight(float f)
{
    this->height = f;
}

void terminal::PlacementBox::SetHorizontalPartition(float l, float c, float r)
{
    this->left = l;
    this->width = c;
    this->right = r;
}

void terminal::PlacementBox::SetVerticalPartition(float t, float c, float b)
{
    this->top = t;
    this->height = c;
    this->bottom = b;
}
