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
                                       contentBounds(0, 0, 0, 0),
                                       topWeigth(0),
                                       bottomWeigth(0),
                                       leftWeigth(0),
                                       rightWeigth(0),
                                       widthWeigth(1),
                                       heightWeigth(1),
                                       parent(nullptr),
                                       zIndex(0),
                                       hasFocus(false),
                                       visible(true),
                                       minimumSize(0, 0),
                                       maximumSize(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()),
                                       autoSizeMode(AutoSizeMode::None),
                                       borderEnabled(false)
{
    // this->name = util::Format("% [%]", typeid(*this).name(), this);
    this->name = util::Format("%", this);
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

util::Event<terminal::MouseEventArgs> &terminal::ControlBase::OnMouse()
{
    return this->onMouse;
}

util::Event<terminal::KeyEventArgs> &terminal::ControlBase::OnKey()
{
    return this->onKey;
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

void terminal::ControlBase::SetHorizontalAlignment(float l, float c, float r)
{
    this->leftWeigth = l;
    this->widthWeigth = c;
    this->rightWeigth = r;
}

void terminal::ControlBase::SetVerticalAlignment(float t, float c, float b)
{
    this->topWeigth = t;
    this->heightWeigth = c;
    this->bottomWeigth = b;
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

void terminal::ControlBase::RestoreDefaultColors()
{
    this->backgroundColor = this->Style(ControlStyleColor::ClearColor);
    this->textColor = this->Style(ControlStyleColor::ControlText);
    this->border.SetStyle(this->Style(ControlStyleColor::ControlBorder));
}

terminal::AutoSizeMode terminal::ControlBase::GetAutoSizeMode() const
{
    return this->autoSizeMode;
}

void terminal::ControlBase::RestoreLayout()
{
    auto wTotal = this->leftWeigth + this->rightWeigth + this->widthWeigth;
    auto hTotal = this->topWeigth + this->bottomWeigth + this->heightWeigth;

    if (wTotal == 0.f)
        wTotal = 1.f;

    if (hTotal == 0.f)
        hTotal = 1.f;

    auto w = this->bounds.GetWidth() * this->widthWeigth / wTotal;
    auto h = this->bounds.GetHeight() * this->heightWeigth / hTotal;

    this->contentBounds = util::Rectangle((this->bounds.GetWidth() - w) * this->leftWeigth / wTotal,
                                          (this->bounds.GetHeight() - h) * this->topWeigth / hTotal,
                                          w,
                                          h);

    util::dbg.WriteLine("ControlBase [%]: Restored Layout, bounds: %, contentBounds: %",
                        this->GetName(),
                        this->bounds,
                        this->contentBounds);

    this->isValid = true;
}

void terminal::ControlBase::ApplyAutoSize(const util::Rectangle &availableSpace)
{
    switch (this->autoSizeMode)
    {
    case AutoSizeMode::None:
        return;
    case AutoSizeMode::FillHorizontal:
        this->SetSize(availableSpace.GetWidth(), this->GetSize().GetHeight());
        this->SetLocation(availableSpace.GetMinX(), this->GetLocation().GetY());
        break;
    case AutoSizeMode::FillVertical:
        this->SetSize(this->GetSize().GetWidth(), availableSpace.GetHeight());
        this->SetLocation(this->GetLocation().GetX(), availableSpace.GetMinY());
        break;
    case AutoSizeMode::Fill:
        this->SetSize(availableSpace.GetSize());
        this->SetLocation(availableSpace.GetLocation());
        break;
    default:
        throw util::InvalidCaseException::MakeException(this->autoSizeMode);
    }

    util::dbg.WriteLine("Applied Autosize to [%]. Mode is %. Proposed size: %. New size is %.", this->GetName(), this->autoSizeMode, availableSpace, this->GetSize());
}

terminal::colorPairId_t terminal::ControlBase::Style(ControlStyleColor color)
{
    return terminal::View::GetInstance()->GetControlStyle(color);
}