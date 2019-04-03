#include "Terminal.hpp"
#include "data/Io.hpp"

terminal::ContainerBase *terminal::ControlBase::GetParent()
{
    return this->parent;
}

const terminal::ContainerBase *terminal::ControlBase::GetParent() const
{
    return this->parent;
}

bool terminal::ControlBase::HasParent() const
{
    return this->parent != nullptr;
}

void terminal::ControlBase::SetName(const std::string &name)
{
    this->name = name;
    this->Invalidate();
}

const std::string &terminal::ControlBase::GetName() const
{
    return this->name;
}

void terminal::ControlBase::SetSizeCore(const util::Dimension &size)
{
    this->bounds.SetWidth(util::Crop(size.GetWidth(), this->minimumSize.GetWidth(), this->maximumSize.GetWidth()));
    this->bounds.SetHeight(util::Crop(size.GetHeight(), this->minimumSize.GetHeight(), this->maximumSize.GetHeight()));
}

void terminal::ControlBase::SetLocationCore(const util::Point &location)
{
    util::dbg.WriteLine("Setting location of [%]. (%)->(%)", this->GetName(), this->bounds.GetLocation(), location);

    this->bounds.SetLocation(location);

    this->Invalidate();
}

void terminal::ControlBase::SetBoundsCore(const util::Rectangle &bounds)
{
    this->SetLocationCore(bounds.GetLocation());
    this->SetSizeCore(bounds.GetSize());

    this->Invalidate();
}

void terminal::ControlBase::SetBounds(int x, int y, int w, int h)
{
    if (this->bounds.GetX() != x ||
        this->bounds.GetY() != y ||
        this->bounds.GetWidth() != w ||
        this->bounds.GetHeight() != h)
    {
        this->SetBoundsCore(util::Rectangle(x, y, w, h));
        this->HandleBoundsChanged();
    }
}

void terminal::ControlBase::SetBounds(const util::Rectangle &bounds)
{
    if (this->bounds != bounds)
    {
        this->SetBoundsCore(bounds);
        this->HandleBoundsChanged();
    }
}

void terminal::ControlBase::SetLocation(const util::Point &location)
{
    if (location != this->bounds.GetLocation())
    {
        this->SetLocationCore(location);
    }
}

void terminal::ControlBase::SetLocation(int x, int y)
{
    if (this->bounds.GetLocation().GetX() != x || this->bounds.GetLocation().GetY() != y)
    {
        this->SetLocationCore(util::Point(x, y));
    }
}

void terminal::ControlBase::SetSize(const util::Dimension &size)
{
    if (this->bounds.GetSize() != size)
    {
        this->SetSizeCore(size);
    }
}

void terminal::ControlBase::SetSize(int w, int h)
{
    if (this->bounds.GetSize().GetWidth() != w || this->bounds.GetSize().GetHeight() != h)
    {
        this->SetSizeCore(util::Dimension(w, h));
    }
}

void terminal::ControlBase::SetRelativeWidth(float w)
{
    this->relativeSizes[RELATIVE_WIDTH] = w;
    this->useRelativeSizes[RELATIVE_WIDTH] = true;
}

void terminal::ControlBase::SetRelativeHeight(float h)
{
    this->relativeSizes[RELATIVE_HEIGHT] = h;
    this->useRelativeSizes[RELATIVE_HEIGHT] = true;
}

void terminal::ControlBase::SetRelativeSize(float w, float h)
{
    this->relativeSizes[RELATIVE_WIDTH] = w;
    this->useRelativeSizes[RELATIVE_WIDTH] = true;

    this->relativeSizes[RELATIVE_HEIGHT] = h;
    this->useRelativeSizes[RELATIVE_HEIGHT] = true;
}

void terminal::ControlBase::UnsetRelativeWidth()
{
    this->useRelativeSizes[RELATIVE_WIDTH] = false;
}

void terminal::ControlBase::UnsetRelativeHeight()
{
    this->useRelativeSizes[RELATIVE_HEIGHT] = false;
}

void terminal::ControlBase::UnsetRelativeSiez()
{
    this->useRelativeSizes[RELATIVE_WIDTH] = false;
    this->useRelativeSizes[RELATIVE_HEIGHT] = false;
}

bool terminal::ControlBase::IsRelativeWidthSet() const
{
    return this->useRelativeSizes[RELATIVE_WIDTH];
}

bool terminal::ControlBase::IsRelativeHeightSet() const
{
    return this->useRelativeSizes[RELATIVE_HEIGHT];
}

const util::Rectangle &terminal::ControlBase::GetBounds() const
{
    return this->bounds;
}

const util::Rectangle &terminal::ControlBase::GetContentBounds() const
{
    return this->contentBounds;
}

const util::Dimension &terminal::ControlBase::GetSize() const
{
    return this->bounds.GetSize();
}

const util::Dimension &terminal::ControlBase::GetContentSize() const
{
    return this->contentBounds.GetSize();
}

const util::Point &terminal::ControlBase::GetLocation() const
{
    return this->bounds.GetLocation();
}

const util::Point &terminal::ControlBase::GetContentLocation() const
{
    return this->contentBounds.GetLocation();
}

void terminal::ControlBase::SetZIndex(int zIndex)
{
    if (this->zIndex != zIndex)
    {
        this->SetZIndexCore(zIndex);
        this->HandleZIndexChanged();
    }
}

void terminal::ControlBase::SetZIndexCore(int zIndex)
{
    this->zIndex = zIndex;

    if (this->parent != nullptr)
    {
        // this->parent->invalidate();
    }
}

int terminal::ControlBase::GetZIndex() const
{
    return this->zIndex;
}

const std::string &terminal::ControlBase::GetText() const
{
    return this->text;
}

void terminal::ControlBase::SetText(const std::string &text)
{
    if (this->text != text)
    {
        this->SetTextCore(text);
        this->HandleTextChanged();
    }
}

void terminal::ControlBase::SetTextCore(const std::string &text)
{
    this->text = text;

    this->Invalidate();
}

bool terminal::ControlBase::IsVisible() const
{
    return this->visible;
}

void terminal::ControlBase::SetVisibility(bool visible)
{
    this->visible = visible;

    this->Invalidate();
}

int terminal::ControlBase::GetTabIndex() const
{
    return this->tabIndex;
}

void terminal::ControlBase::SetTabIndex(int tabIndex)
{
    this->tabIndex = tabIndex;

    this->Invalidate();
}

const util::Dimension &terminal::ControlBase::GetMinSize() const
{
    return this->minimumSize;
}

const util::Dimension &terminal::ControlBase::GetMaxSize() const
{
    return this->maximumSize;
}

void terminal::ControlBase::SetMinSize(int w, int h)
{
    this->SetMinSize(util::Dimension(w, h));
}

void terminal::ControlBase::SetMinSize(const util::Dimension &size)
{
    this->minimumSize = size;

    if (this->bounds.GetSize().GetHeight() < this->minimumSize.GetHeight() ||
        this->bounds.GetSize().GetWidth() < this->minimumSize.GetWidth())
    {
        this->SetSizeCore(this->bounds.GetSize().Crop(this->minimumSize, this->maximumSize));
    }

    this->Invalidate();
}

void terminal::ControlBase::SetMaxSize(int w, int h)
{
    this->SetMaxSize(util::Dimension(w, h));
}

void terminal::ControlBase::SetMaxSize(const util::Dimension &size)
{
    this->maximumSize = size;

    this->Invalidate();
}

util::Event<terminal::MouseEventArgs> &terminal::ControlBase::OnMouse()
{
    return this->onMouse;
}

util::Event<terminal::KeyEventArgs> &terminal::ControlBase::OnKey()
{
    return this->onKey;
}

bool terminal::ControlBase::IsValid() const
{
    return this->isValid;
}

const terminal::Border &terminal::ControlBase::GetBorder() const
{
    return this->border;
}

terminal::Border &terminal::ControlBase::GetBorder()
{
    return this->border;
}

bool terminal::ControlBase::IsBorderEnabled() const
{
    return this->borderEnabled;
}

void terminal::ControlBase::SetPadding(float top, float right, float bottom, float left)
{
    this->paddings[TOP] = top;
    this->paddings[RIGHT] = right;
    this->paddings[BOTTOM] = bottom;
    this->paddings[LEFT] = left;

    this->paddingModes[TOP] = top < 1.f;
    this->paddingModes[RIGHT] = right < 1.f;
    this->paddingModes[BOTTOM] = bottom < 1.f;
    this->paddingModes[LEFT] = left < 1.f;
}

void terminal::ControlBase::SetRelativeLeftPadding(float value)
{
    this->paddings[LEFT] = value;
    this->paddingModes[LEFT] = true;
}

void terminal::ControlBase::SetAbsoluteLeftPadding(int value)
{
    this->paddings[LEFT] = value;
    this->paddingModes[LEFT] = false;
}

void terminal::ControlBase::SetRelativeRightPadding(float value)
{
    this->paddings[RIGHT] = value;
    this->paddingModes[RIGHT] = true;
}

void terminal::ControlBase::SetAbsoluteRightPadding(int value)
{
    this->paddings[RIGHT] = value;
    this->paddingModes[RIGHT] = false;
}

void terminal::ControlBase::SetRelativeTopPadding(float value)
{
    this->paddings[TOP] = value;
    this->paddingModes[TOP] = true;
}

void terminal::ControlBase::SetAbsoluteTopPadding(int value)
{
    this->paddings[TOP] = value;
    this->paddingModes[TOP] = false;
}

void terminal::ControlBase::SetRelativeBottomPadding(float value)
{
    this->paddings[BOTTOM] = value;
    this->paddingModes[BOTTOM] = true;
}

void terminal::ControlBase::SetAbsoluteBottomPadding(int value)
{
    this->paddings[BOTTOM] = value;
    this->paddingModes[BOTTOM] = false;
}

void terminal::ControlBase::SetAutoSizeMode(AutoSizeMode mode)
{
    this->autoSizeMode = mode;

    this->Invalidate();
}

void terminal::ControlBase::SetBorder(const Border &b)
{
    this->border = b;

    this->Invalidate();
}

void terminal::ControlBase::SetBorderEnabled(bool enabled)
{
    this->borderEnabled = enabled;

    this->Invalidate();
}

void terminal::ControlBase::SetTextColor(colorPairId_t value)
{
    this->textColor = value;
}

void terminal::ControlBase::SetBackgroundColor(colorPairId_t value)
{
    this->backgroundColor = value;
}

terminal::colorPairId_t terminal::ControlBase::GetTextColor() const
{
    return this->textColor;
}

terminal::colorPairId_t terminal::ControlBase::GetBackgroundColor() const
{
    return this->backgroundColor;
}

bool terminal::ControlBase::IsFillPaddingSet() const {
    return this->fillPadding;
}

void terminal::ControlBase::SetFillPadding(bool value) {
    this->fillPadding = value;
}

bool terminal::ControlBase::IsUseBackgroundSet() const {
    return this->useBackground;
}

void terminal::ControlBase::SetUseBackground(bool value) {
    this->useBackground = value;
}

terminal::AutoSizeMode terminal::ControlBase::GetAutoSizeMode() const
{
    return this->autoSizeMode;
}

terminal::colorPairId_t terminal::ControlBase::Style(ControlStyleColor color)
{
    return terminal::View::GetInstance()->GetControlStyle(color);
}