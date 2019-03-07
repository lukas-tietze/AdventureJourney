#pragma once

#include <ostream>

#include "terminal/View.hpp"
#include "terminal/Canvas.hpp"
#include "Geometry.hpp"
#include "Event.hpp"

namespace terminal
{
struct KeyInput
{
    int key;
    Key specialKey;
    bool handled;
};

std::ostream &operator<<(std::ostream &, const KeyInput &);

struct MouseInput
{
    int cx;
    int cy;
    MouseAction action;
    bool handled;
};

std::ostream &operator<<(std::ostream &, const MouseInput &);

enum class Alignment
{
    Right,
    Left,
    Top,
    Bottom,
    Fill,
    Absolute,
};

std::ostream &operator<<(std::ostream &, Alignment);

enum class AutoSizeMode
{
    None,
    Fill,
    FillHorizontal,
    FillVertical,
    Fit,
};

std::ostream &operator<<(std::ostream &, AutoSizeMode);

enum class BorderType
{
    TopEdge = BIT(0),
    RightEdge = BIT(1),
    BottomEdge = BIT(2),
    LeftEdge = BIT(3),
    TopLeftCorner = BIT(4),
    TopRightCorner = BIT(5),
    BottomRightCorner = BIT(6),
    BottomLeftCorner = BIT(7),

    TopLine = TopLeftCorner | TopEdge | TopRightCorner,
    BottomLine = BottomLeftCorner | BottomEdge | BottomRightCorner,
    LeftLine = TopLeftCorner | LeftEdge | BottomLeftCorner,
    RightLine = TopRightCorner | RightEdge | BottomRightCorner,

    AllEdges = TopEdge | RightEdge | BottomEdge | LeftEdge,
    AllCorners = TopLeftCorner | TopRightCorner | BottomRightCorner | BottomLeftCorner,
    All = AllEdges | AllCorners
};

class Border
{
  private:
    colorPairId_t styles[8];
    int values[8];
    bool enabled[8];

  public:
    Border();

    void SetStyle(colorPairId_t);
    void SetStyle(BorderType, colorPairId_t);
    colorPairId_t GetStyle(BorderType) const;

    void SetChar(BorderType, int);
    int GetChar(BorderType) const;

    void SetEnabled(bool);
    void SetEnabled(BorderType, bool);
    bool IsEnabled(BorderType) const;

    void Render(const util::Rectangle &bounds, Canvas &);
};

class ContainerBase;
class ControlBase;

struct MouseEventArgs
{
    int absoluteX;
    int absoluteY;
    int relativeX;
    int relativeY;
    MouseAction action;
    bool handled;
    terminal::ControlBase *sender;
};

struct KeyEventArgs
{
    int key;
    Key specialKey;
    bool handled;
    terminal::ControlBase *sender;
};

class ControlBase
{
  private:
    util::Rectangle bounds;
    util::Dimension minimumSize;
    util::Dimension maximumSize;
    ContainerBase *parent;
    int zIndex;
    bool hasFocus;
    int tabIndex;
    std::string text;
    bool visible;
    int textStyle;
    bool isValid;
    AutoSizeMode autoSizeMode;
    Border border;
    bool borderEnabled;

    std::string name;

    util::Event<MouseEventArgs> onMouse;
    util::Event<KeyEventArgs> onKey;

  protected:
    void SetBoundsCore(const util::Rectangle &);
    void SetSizeCore(const util::Dimension &);
    void SetLocationCore(const util::Point &);
    void SetZIndexCore(int);
    void SetTextCore(const std::string &);
    void SetVisibilityCore(bool visible);
    void SetTabIndexCore(int);
    void SetMinSizeCore(const util::Dimension &);
    void SetMaxSizeCore(const util::Dimension &);

    bool ValidateSize(const util::Dimension &) const;

    virtual void Update();
    colorPairId_t Style(ControlStyleColor);

  public:
    ControlBase();
    virtual ~ControlBase();

    struct ZIndexSorter
    {
        int operator()(const ControlBase &, const ControlBase &);
    };

    struct TabIndexSorter
    {
        int operator()(const ControlBase &, const ControlBase &);
    };

    ContainerBase *GetParent();
    const ContainerBase *GetParent() const;
    bool HasParent() const;
    void SetZIndex(int);
    int GetZIndex() const;
    const std::string &GetText() const;
    void SetText(const std::string &);
    bool IsVisible() const;
    void SetVisibility(bool visible);
    int GetTabIndex() const;
    void SetTabIndex(int);
    const std::string &GetName() const;
    const util::Dimension &GetMinSize() const;
    const util::Dimension &GetMaxSize() const;
    const util::Dimension &GetSize() const;
    const util::Point &GetLocation() const;
    const util::Rectangle &GetBounds() const;
    const Border &GetBorder() const;
    Border &GetBorder();
    bool IsBorderEnabled() const;
    AutoSizeMode GetAutoSizeMode() const;
    void SetName(const std::string &);
    void SetSize(const util::Dimension &);
    void SetSize(int w, int h);
    void SetMinSize(const util::Dimension &);
    void SetMaxSize(const util::Dimension &);
    void SetMinSize(int w, int h);
    void SetMaxSize(int w, int h);
    void SetLocation(const util::Point &);
    void SetLocation(int x, int y);
    void SetBounds(int x, int y, int w, int h);
    void SetBounds(const util::Rectangle &);
    void SetAutoSizeMode(AutoSizeMode mode);
    void SetBorder(const Border &);
    void SetBorderEnabled(bool);
    bool Contains(int x, int y) const;
    bool IsValid() const;
    virtual void Invalidate();
    virtual void RestoreLayout();

    virtual void ApplyAutoSize(const util::Dimension &availableSpace);

    virtual void HandleZIndexChanged();
    virtual void HandleTabIndexChanged();
    virtual void HandleBoundsChanged();
    virtual void HandleTextChanged();
    virtual void HandleFocusAquired();
    virtual void HandleFocusLost();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void HandleAddToControl(ContainerBase *);

    util::Event<MouseEventArgs> &OnMouse();
    util::Event<KeyEventArgs> &OnKey();

    virtual void Render(Canvas &);
};
} // namespace terminal