#pragma once

#include <curses.h>
#include <string>
#include <tuple>

#include "Util.hpp"
#include "Values.hpp"
#include "Geometry.hpp"
#include "graphics/Color.hpp"
#include "data/collection/Array.hpp"
#include "data/Json.hpp"

namespace terminal
{
typedef int32_t colorId_t;
typedef int32_t colorPairId_t;
typedef std::tuple<colorId_t, colorId_t> ColorPair;

class ColorPallette : public json::IJsonSerializable
{
  private:
    util::Array<util::Color> colors;
    util::Array<ColorPair> colorPairs;

  public:
    ColorPallette();
    ColorPallette(size_t colors, size_t colorPairs);
    ColorPallette(const util::Array<util::Color> &, const util::Array<ColorPair> &);

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);

    const util::Array<util::Color> &GetColors() const;
    const util::Array<ColorPair> &GetColorPairs() const;

    util::Array<util::Color> &GetColors();
    util::Array<ColorPair> &GetColorPairs();

    size_t GetColorCount() const;
    size_t GetColorPairCount() const;

    bool IsCompatible(size_t colors, size_t colorPairs) const;
    bool Matches(size_t colors, size_t colorPairs) const;

    bool operator==(const ColorPallette &) const;
    bool operator!=(const ColorPallette &) const;
};

enum class ControlStyleColor
{
    ControlText = 0,
    DisabledControlText,
    ControlBorder,
    InactiveControlBorder,
    DisabledControlBorder,
    UnselectedOption,
    SelectedOption,
    ClearColor,
};

std::ostream &operator<<(std::ostream &, ControlStyleColor);

class ControlStyleColorPallette : public ColorPallette
{
  private:
    std::array<colorId_t, static_cast<size_t>(ControlStyleColor::ClearColor) + 1> styles;

  public:
    ControlStyleColorPallette();
    ControlStyleColorPallette(const util::Array<util::Color> &, const util::Array<ColorPair> &);
    ControlStyleColorPallette(const util::Array<util::Color> &, const util::Array<ColorPair> &, const std::array<colorId_t, static_cast<size_t>(ControlStyleColor::ClearColor) + 1> &);

    colorId_t operator[](ControlStyleColor) const;
    colorId_t &operator[](ControlStyleColor);

    colorId_t GetStyle(ControlStyleColor) const;
    void SetStyle(ControlStyleColor, colorId_t);

    std::array<colorId_t, static_cast<size_t>(ControlStyleColor::ClearColor) + 1> &GetControlColors();
    const std::array<colorId_t, static_cast<size_t>(ControlStyleColor::ClearColor) + 1> &GetControlColors() const;

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

class View
{
  public:
    ~View();

    static View *GetInstance();
    static void DeleteInstance();

    void SetInputMode(terminal::InputMode mode);
    void SetEcho(bool echo);

    util::Dimension GetSize() const;
    void Resize();
    bool NeedsResize() const;

    int ReadKey();
    std::string ReadLine();

    bool ReadKey(long timeOut, int &result);
    bool ReadLine(long timeOut, std::string &result);

    void Print(const std::string &text);
    void Print(const std::string &text, int x, int y);
    void Print(char c);
    void Print(char c, int x, int y);
    void Clear(const util::Rectangle &area);
    void Flush();

    void SetLiveMode(bool);

    void SetAttribute(terminal::OutputAttribute, bool);
    void ResetAttribtues();
    void AttributeOn(terminal::OutputAttribute);
    void AttributeOff(terminal::OutputAttribute);
    void SetActiveAttributes(terminal::OutputAttribute);
    OutputAttribute GetActiveAttributes() const;

    void SetActiveColorPair(colorPairId_t);
    void SetBackgroundColorPair(colorPairId_t);
    colorPairId_t GetActiveColorPair() const;
    colorPairId_t GetActiveBackground() const;
    ColorPair GetContent(colorPairId_t id) const;
    util::Color GetColor(colorId_t id) const;
    colorPairId_t GetControlStyle(ControlStyleColor) const;

    size_t GetMaxColors() const;
    size_t GetMaxColorPairs() const;
    bool CanChangeColors() const;

    bool BufferColor(colorId_t, const util::Color &);
    bool BufferColorPair(colorPairId_t, colorId_t, colorId_t);

    int CreateStyle(terminal::OutputAttribute attributes, int colorPair);

    util::Point GetCursorPosition() const;
    void SetCursorPosition(const util::Point &point);
    terminal::CursorMode GetCursorMode() const;
    void SetCursorMode(terminal::CursorMode);

    bool CursorVisibilitySupported() const;
    bool ColorsSupported() const;

    void ApplyColorPallette(const ColorPallette &);
    void ApplyControlColorPallette(const ControlStyleColorPallette &);
    ColorPallette ExportCurrentColorPallette() const;
    ControlStyleColorPallette ExportCurrentControlColorPallette() const;
    void LoadColorPalletteFromJson(const std::string &path);
    void LoadControlColorPalletteFromJson(const std::string &path);
    void SaveCurrentColorPallette(const std::string &path) const;
    void SaveCurrentControlColorPallette(const std::string &path) const;
    void RestoreDefaultColors();

  protected:
    void OnTerminalPropertyChanged();

  private:
    static View *instance;

    View();
    View(int width, int height);

    void Recreate();

    // WINDOW *window;
    int width;
    int height;
    char inputBuf[4096];

    InputMode inputMode;
    bool echoOn;
    bool liveMode;
    bool colorsSupported;
    bool cursorModeSupported;
    CursorMode cursorMode;
    util::Point cursorPos;

    util::Array<util::Color> colors;
    util::Array<ColorPair> colorPairs;
    std::array<colorId_t, static_cast<int>(ControlStyleColor::ClearColor) + 1> controlStyles;
    int activeColorPair;
    int activeBackgroundColorPair;

    OutputAttribute activeAttributes;
};
} // namespace terminal