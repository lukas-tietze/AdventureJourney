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

enum class AutoSizeMode
{
    None,
    FillHorizontal,
    FillVertical,
    Fill,
    FitContent,
};

class Border
{
  private:
    uint8_t sizes[4];
    int styles[4];

  public:
    Border();

    void SetSize(uint8_t size);
    void SetStyle(int style);

    void SetTopSize(uint8_t size);
    void SetTopStyle(int style);

    void SetRightSize(uint8_t size);
    void SetRightStyle(int style);

    void SetBottomSize(uint8_t size);
    void SetBottomStyle(int style);

    void SetLeftSize(uint8_t size);
    void SetLeftStyle(int style);

    uint8_t GetTopSize();
    int GetTopStyle();

    uint8_t GetRightSize();
    int GetRightStyle();

    uint8_t GetBottomSize();
    int GetBottomStyle();

    uint8_t GetLeftSize();
    int GetLeftStyle();

    void Render(const util::Rectangle &bounds, Canvas &);
};

class ContainerBase;

class ControlBase
{
  private:
    util::Rectangle bounds;
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
    AutoSizeMode autoSizeMode;
    Border border;
    bool borderEnabled;

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
    const util::Dimension &GetSize() const;
    const util::Point &GetLocation() const;
    const util::Rectangle &GetBounds() const;
    const Border &GetBorder() const;
    Border &GetBorder();
    bool IsBorderEnabled() const;
    AutoSizeMode GetAutoSizeMode() const;
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

    virtual void Render(Canvas &);
};
} // namespace terminal