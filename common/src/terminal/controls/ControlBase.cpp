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
                                       paddings({0, 0, 0, 0}),
                                       paddingModes({true, true, true, true}),
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
    this->UpdateColors();
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

namespace
{
constexpr int RELATIVE_WIDTH = 0;
constexpr int RELATIVE_HEIGHT = 1;
} // namespace

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
    {
        this->border.Render(this->bounds, c);
        // this->contentBorder.Render(this->contentBounds, c);
    }
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

namespace
{
constexpr size_t TOP = 0;
constexpr size_t RIGHT = 1;
constexpr size_t BOTTOM = 2;
constexpr size_t LEFT = 3;
} // namespace

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

void terminal::ControlBase::UpdateColors()
{
    this->backgroundColor = this->Style(ControlStyleColor::ClearColor);
    this->textColor = this->Style(ControlStyleColor::ControlText);
    this->border.SetStyle(this->Style(ControlStyleColor::ControlBorder));
}

terminal::AutoSizeMode terminal::ControlBase::GetAutoSizeMode() const
{
    return this->autoSizeMode;
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

terminal::colorPairId_t terminal::ControlBase::Style(ControlStyleColor color)
{
    return terminal::View::GetInstance()->GetControlStyle(color);
}