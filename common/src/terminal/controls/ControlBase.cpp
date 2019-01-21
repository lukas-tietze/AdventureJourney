#include "Terminal.hpp"

int terminal::ControlBase::ZIndexSorter::operator()(const ControlBase &a, const ControlBase &b)
{
    return a.zIndex - b.zIndex;
}

int terminal::ControlBase::TabIndexSorter::operator()(const ControlBase &a, const ControlBase &b)
{
    return a.tabIndex - b.tabIndex;
}

terminal::ControlBase::ControlBase() : size(0, 0),
                                       location(0, 0),
                                       parent(nullptr),
                                       zIndex(0),
                                       hasFocus(false),
                                       visible(true),
                                       minimumSize(0, 0),
                                       maximumSize(std::numeric_limits<int>::max(), std::numeric_limits<int>::max())
{
}

terminal::ControlBase::~ControlBase()
{
}

terminal::ControlBase *terminal::ControlBase::GetParent()
{
    return this->parent;
}

const terminal::ControlBase *terminal::ControlBase::GetParent() const
{
    return this->parent;
}

bool terminal::ControlBase::HasParent() const
{
    return this->parent != nullptr;
}

void terminal::ControlBase::SetLocation(const util::Point &location)
{
    if (location != this->location)
    {
        this->SetLocationCore(location);
    }
}

void terminal::ControlBase::SetLocation(int x, int y)
{
    if (this->location.GetX() != x || this->location.GetY() != y)
    {
        this->SetLocationCore(util::Point(x, y));
    }
}

void terminal::ControlBase::SetSize(const util::Dimension &size)
{
    if (this->size != size)
    {
        this->SetSizeCore(size);
    }
}

void terminal::ControlBase::SetSize(int w, int h)
{
    if (this->size.GetWidth() != w || this->size.GetHeight() != h)
    {
        this->SetSizeCore(util::Dimension(w, h));
    }
}

const util::Dimension &terminal::ControlBase::GetSize() const
{
    return this->size;
}

const util::Point &terminal::ControlBase::GetLocation() const
{
    return this->location;
}

bool terminal::ControlBase::Contains(int x, int y) const
{
    return x >= this->location.GetX() &&
           x <= this->location.GetX() + this->size.GetWidth() &&
           y >= this->location.GetY() &&
           y <= this->location.GetY() + this->size.GetHeight();
}

bool terminal::ControlBase::ValidateSize(const util::Dimension &size) const
{
    return (size.GetWidth() < this->minimumSize.GetWidth() ||
            size.GetHeight() < this->minimumSize.GetHeight() ||
            size.GetWidth() > this->maximumSize.GetWidth() ||
            size.GetHeight() > this->maximumSize.GetHeight());
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
}

bool terminal::ControlBase::IsVisible() const
{
    return this->visible;
}

void terminal::ControlBase::SetVisibility(bool visible)
{
    this->visible = visible;
}

int terminal::ControlBase::GetTabIndex() const
{
    return this->tabIndex;
}

void terminal::ControlBase::SetTabIndex(int tabIndex)
{
    this->tabIndex = tabIndex;
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

    if (this->size.GetHeight() < this->minimumSize.GetHeight() ||
        this->size.GetWidth() < this->minimumSize.GetWidth())
    {
        this->SetSizeCore(this->size.Crop(this->minimumSize, this->maximumSize));
    }
}

void terminal::ControlBase::SetMaxSize(int w, int h)
{
    this->SetMaxSize(util::Dimension(w, h));
}

void terminal::ControlBase::SetMaxSize(const util::Dimension &size)
{
    this->maximumSize = size;
}

void terminal::ControlBase::HandleFocusAquired()
{
}

void terminal::ControlBase::HandleFocusLost()
{
}

void terminal::ControlBase::HandleKey(KeyInput &)
{
}

void terminal::ControlBase::HandleMouse(MouseInput &)
{
}

void terminal::ControlBase::HandleAddToControl(ContainerBase *newParent)
{
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

void terminal::ControlBase::Update()
{
    this->isValid = true;
}

bool terminal::ControlBase::IsValid() const
{
    return this->isValid;
}

void terminal::ControlBase::Invalidate()
{
    this->isValid = false;

    if (this->parent != nullptr)
        this->parent->Invalidate();
}
