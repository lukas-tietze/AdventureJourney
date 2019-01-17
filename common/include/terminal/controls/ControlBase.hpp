#pragma once

#include "terminal/Canvas.hpp"
#include "Geometry.hpp"

namespace terminal
{
struct KeyInput
{
    int key;
    bool handled;
};

struct MouseInput
{
    int cx;
    int cy;
    MouseAction action;
    bool handled;
};

enum class Alignment
{
    Right,
    Left,
    Top,
    Bottom,
    Fill,
    Absolute,
};

class ContainerBase;

class ControlBase
{
  private:
    util::Point location;
    util::Dimension size;
    util::Dimension minimumSize;
    util::Dimension maximumSize;
    ControlBase *parent;
    int zIndex;
    bool hasFocus;
    int tabIndex;
    std::string text;
    bool visible;
    int textStyle;
    bool isValid;

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

    bool ValidateBounds(util::Rectangle &);

    virtual void Update();

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

    ControlBase *GetParent();
    const ControlBase *GetParent() const;
    bool HasParent() const;
    const util::Rectangle &GetBounds() const;
    void SetBounds(const util::Rectangle &);
    void SetBounds(int x, int y, int w, int h);
    void SetZIndex(int);
    int GetZIndex() const;
    const std::string &GetText() const;
    void SetText(const std::string &);
    bool IsVisible() const;
    void SetVisibility(bool visible);
    int GetTabIndex() const;
    void SetTabIndex(int);
    const util::Dimension &GetMinSize() const;
    const util::Dimension &GetMaxSize() const;
    void SetMinSize(const util::Dimension &);
    void SetMaxSize(const util::Dimension &);
    void SetMinSize(int w, int h);
    void SetMaxSize(int w, int h);

    void Invalidate();
    bool IsValid() const;

    virtual void HandleZIndexChanged();
    virtual void HandleTabIndexChanged();
    virtual void HandleBoundsChanged();
    virtual void HandleTextChanged();
    virtual void HandleFocusAquired();
    virtual void HandleFocusLost();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void HandleAddToControl(ContainerBase *);

    virtual void Render(Canvas &) = 0;
};
} // namespace terminal