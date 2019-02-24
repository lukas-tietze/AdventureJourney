#include "Terminal.hpp"
#include "data/Io.hpp"

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
                                       maximumSize(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()),
                                       autoSizeMode(AutoSizeMode::None)
{
}

terminal::ControlBase::~ControlBase()
{
}

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

void terminal::ControlBase::SetSizeCore(const util::Dimension &size)
{
    this->bounds.SetWidth(util::Crop(size.GetWidth(), this->minimumSize.GetWidth(), this->maximumSize.GetWidth()));
    this->bounds.SetHeight(util::Crop(size.GetHeight(), this->minimumSize.GetHeight(), this->maximumSize.GetHeight()));
}

void terminal::ControlBase::SetLocationCore(const util::Point &location)
{
    util::dbg.WriteLine("Setting location of [%]. (%)->(%)", this, this->bounds.GetLocation(), location);

    this->bounds.SetLocation(location);
}

void terminal::ControlBase::SetBoundsCore(const util::Rectangle &bounds)
{
    this->SetLocationCore(bounds.GetLocation());
    this->SetSizeCore(bounds.GetSize());
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

const util::Rectangle &terminal::ControlBase::GetBounds() const
{
    return this->bounds;
}

const util::Dimension &terminal::ControlBase::GetSize() const
{
    return this->bounds.GetSize();
}

const util::Point &terminal::ControlBase::GetLocation() const
{
    return this->bounds.GetLocation();
}

bool terminal::ControlBase::Contains(int x, int y) const
{
    return x >= this->bounds.GetLocation().GetX() &&
           x <= this->bounds.GetLocation().GetX() + this->bounds.GetSize().GetWidth() &&
           y >= this->bounds.GetLocation().GetY() &&
           y <= this->bounds.GetLocation().GetY() + this->bounds.GetSize().GetHeight();
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

    if (this->bounds.GetSize().GetHeight() < this->minimumSize.GetHeight() ||
        this->bounds.GetSize().GetWidth() < this->minimumSize.GetWidth())
    {
        this->SetSizeCore(this->bounds.GetSize().Crop(this->minimumSize, this->maximumSize));
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

void terminal::ControlBase::Render(Canvas &c)
{
    if (this->borderEnabled)
        this->border.Render(this->bounds, c);
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

void terminal::ControlBase::ApplyAutoSize(const util::Dimension &availableSpace)
{
    switch (this->autoSizeMode)
    {
    case AutoSizeMode::None:
        return;
    case AutoSizeMode::Fill:
        this->SetSize(availableSpace);
        break;
    case AutoSizeMode::Fit:
        this->RestoreLayout();
        break;
    default:
        throw util::InvalidCaseException::MakeException(this->autoSizeMode);
    }

    util::dbg.WriteLine("Applied Autosize to [%]. Mode is %. Proposed size: %. New size is %.", static_cast<void *>(this), this->autoSizeMode, availableSpace, this->GetSize());
}

void terminal::ControlBase::SetAutoSizeMode(AutoSizeMode mode)
{
    this->autoSizeMode = mode;
}

void terminal::ControlBase::SetBorder(const Border &b)
{
    this->border = b;
}

void terminal::ControlBase::SetBorderEnabled(bool enabled)
{
    this->borderEnabled = enabled;
}

terminal::AutoSizeMode terminal::ControlBase::GetAutoSizeMode() const
{
    return this->autoSizeMode;
}

void terminal::ControlBase::RestoreLayout()
{
}

terminal::colorPairId_t terminal::ControlBase::Style(ControlStyleColor color)
{
    return TerminalView::GetInstance()->GetControlStyle(color);
}