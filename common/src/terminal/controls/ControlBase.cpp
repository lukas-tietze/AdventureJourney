#include "Terminal.hpp"

int terminal::ControlBase::ZIndexSorter::operator()(const ControlBase &a, const ControlBase &b)
{
    return a.zIndex - b.zIndex;
}

int terminal::ControlBase::TabIndexSorter::operator()(const ControlBase &a, const ControlBase &b)
{
    return a.tabIndex - b.tabIndex;
}

terminal::ControlBase::ControlBase() : bounds(0, 0, 0, 0),
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

const util::Rectangle &terminal::ControlBase::GetBounds() const
{
    return this->bounds;
}

void terminal::ControlBase::SetBounds(int x, int y, int w, int h)
{
    this->SetBounds(util::Rectangle(x, y, w, h));
}

void terminal::ControlBase::SetBounds(const util::Rectangle &bounds)
{
    if (this->bounds != bounds)
    {
        this->SetBoundsCore(bounds);
        this->HandleBoundsChanged();
    }
}

void terminal::ControlBase::SetBoundsCore(const util::Rectangle &bounds)
{
    if (this->ValidateBounds(this->bounds))
        this->bounds = bounds;
    else
        this->bounds = util::Rectangle(bounds.GetLocation(), bounds.GetSize().Crop(this->minimumSize, this->maximumSize));
}

bool terminal::ControlBase::ValidateBounds(util::Rectangle &alternative)
{
    return (bounds.GetSize().GetWidth() < this->minimumSize.GetWidth() ||
            bounds.GetSize().GetHeight() < this->minimumSize.GetHeight() ||
            bounds.GetSize().GetWidth() > this->maximumSize.GetWidth() ||
            bounds.GetSize().GetHeight() > this->maximumSize.GetHeight());
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

    if (this->bounds.GetSize().GetHeight() < this->minimumSize.GetHeight() ||
        this->bounds.GetSize().GetWidth() < this->minimumSize.GetWidth())
    {
        this->SetBoundsCore(util::Rectangle(
            this->bounds.GetLocation(),
            this->bounds.GetSize().Crop(this->minimumSize, this->maximumSize)));
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