#include "Terminal.hpp"
#include "data/Io.hpp"

bool terminal::ControlBase::Contains(int x, int y) const
{
    return x >= this->contentBounds.GetLocation().GetX() &&
           x <= this->contentBounds.GetLocation().GetX() + this->contentBounds.GetSize().GetWidth() &&
           y >= this->contentBounds.GetLocation().GetY() &&
           y <= this->contentBounds.GetLocation().GetY() + this->contentBounds.GetSize().GetHeight();
}

bool terminal::ControlBase::ValidateSize(const util::Dimension &size) const
{
    return (size.GetWidth() < this->minimumSize.GetWidth() ||
            size.GetHeight() < this->minimumSize.GetHeight() ||
            size.GetWidth() > this->maximumSize.GetWidth() ||
            size.GetHeight() > this->maximumSize.GetHeight());
}

bool terminal::ControlBase::RequestFocus()
{
    return this->parent->RequestFocus(this);
}

void terminal::ControlBase::HandleFocusAquired()
{
}

void terminal::ControlBase::HandleFocusLost()
{
}

void terminal::ControlBase::HandleKey(KeyInput &k)
{
    if (k.handled)
        return;

    KeyEventArgs args;
    args.handled = false;
    args.key = k.key;
    args.specialKey = k.specialKey;
    args.sender = this;

    this->onKey(args);

    k.handled = args.handled;
}

void terminal::ControlBase::HandleMouse(MouseInput &m)
{
    if (m.handled)
        return;

    MouseEventArgs args;
    args.handled = false;
    args.action = m.action;
    args.absoluteX = m.screenX;
    args.absoluteY = m.screenY;
    args.relativeX = m.x;
    args.relativeY = m.y;
    args.sender = this;

    this->onMouse(args);

    m.handled = args.handled;
}

void terminal::ControlBase::HandleAddToControl(ContainerBase *newParent)
{
    if (this->parent != nullptr)
        this->parent->Remove(this);

    this->parent = newParent;
}

void terminal::ControlBase::HandleTabIndexChanged()
{
}

void terminal::ControlBase::HandleZIndexChanged()
{
}

void terminal::ControlBase::HandleBoundsChanged()
{
}

void terminal::ControlBase::HandleTextChanged()
{
}

void terminal::ControlBase::Invalidate()
{
    this->isValid = false;

    if (this->parent != nullptr)
        this->parent->Invalidate();
}

void terminal::ControlBase::Render(Canvas &c)
{
    if (this->borderEnabled)
    {
        this->border.Render(this->bounds, c);
        // this->contentBorder.Render(this->contentBounds, c);
    }
}

void terminal::ControlBase::UpdateColors()
{
    this->backgroundColor = this->Style(ControlStyleColor::ClearColor);
    this->textColor = this->Style(ControlStyleColor::ControlText);
    this->border.SetStyle(this->Style(ControlStyleColor::ControlBorder));
}

namespace
{
void Partition(float w0, float w1, bool m0, bool m1, int size, int &outOffset, int &outSize)
{
    outOffset = static_cast<int>(m0 ? w0 * size + 0.5f : w0);
    outSize = size - outOffset - static_cast<int>(m1 ? w1 * size + 0.5f : w1);
}
} // namespace

void terminal::ControlBase::RestoreLayout()
{
    int x, y, w, h;

    Partition(this->paddings[TOP], this->paddings[BOTTOM],
              this->paddingModes[TOP], this->paddingModes[BOTTOM],
              this->GetBounds().GetHeight(), y, h);

    Partition(this->paddings[LEFT], this->paddings[RIGHT],
              this->paddingModes[LEFT], this->paddingModes[RIGHT],
              this->GetBounds().GetWidth(), x, w);

    this->contentBounds = util::Rectangle(this->GetLocation() + util::Point(x, y), w, h);

    util::dbg.WriteLine("ControlBase [%]: Restored Layout, bounds: %, contentBounds: %",
                        this->GetName(),
                        this->bounds,
                        this->contentBounds);

    this->isValid = true;
}

void terminal::ControlBase::ApplyAutoSize(const util::Rectangle &availableSpace)
{
    auto proposedWidth = this->useRelativeSizes[RELATIVE_WIDTH]
                             ? availableSpace.GetWidth() * this->relativeSizes[RELATIVE_WIDTH]
                             : this->bounds.GetWidth();

    auto proposedHeight = this->useRelativeSizes[RELATIVE_HEIGHT]
                              ? availableSpace.GetHeight() * this->relativeSizes[RELATIVE_HEIGHT]
                              : this->bounds.GetHeight();

    switch (this->autoSizeMode)
    {
    case AutoSizeMode::None:
        this->SetSize(proposedWidth, proposedHeight);
        return;
    case AutoSizeMode::FillHorizontal:
        this->SetSize(availableSpace.GetWidth(), proposedHeight);
        this->SetLocation(availableSpace.GetMinX(), this->GetLocation().GetY());
        break;
    case AutoSizeMode::FillVertical:
        this->SetSize(proposedWidth, availableSpace.GetHeight());
        this->SetLocation(this->GetLocation().GetX(), availableSpace.GetMinY());
        break;
    case AutoSizeMode::Fill:
        this->SetSize(availableSpace.GetSize());
        this->SetLocation(availableSpace.GetLocation());
        break;
    default:
        throw util::InvalidCaseException::MakeException(this->autoSizeMode);
    }

    this->contentBounds = this->bounds;

    util::dbg.WriteLine("Applied Autosize to [%]. Mode is %. Proposed size: %. New size is %.", this->GetName(), this->autoSizeMode, availableSpace, this->GetSize());
}