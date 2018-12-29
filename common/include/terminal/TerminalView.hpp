#pragma once

#include <curses.h>
#include <string>
#include <tuple>

#include "Util.hpp"
#include "Values.hpp"
#include "Geometry.hpp"
#include "graphics/Color.hpp"
#include "data/collection/Array.hpp"

namespace terminal
{
typedef uint16_t colorId_t;
typedef uint16_t colorPairId_t;
typedef std::tuple<colorId_t, colorId_t> ColorPair;

class TerminalView
{
  public:
    ~TerminalView();

    static TerminalView *GetInstance();
    static void DeleteInstance();

    void SetInputMode(terminal::InputMode mode);
    void SetEcho(bool echo);

    util::Dimension GetSize() const;
    bool SetSize(const util::Dimension &);

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

    void Maximise();
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
    const ColorPair &GetContent(colorPairId_t id) const;
    const util::Color &GetColor(colorId_t id) const;

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

  protected:
    void OnTerminalPropertyChanged();

  private:
    static TerminalView *instance;
    
    TerminalView();
    TerminalView(int width, int height);

    WINDOW *window;
    int width;
    int height;
    char inputBuf[4096];

    InputMode inputMode;
    bool echoOn;
    bool liveMode;
    bool colorsSupported;
    bool cursorModeSupported;
    CursorMode cursorMode;

    util::Array<util::Color> colors;
    util::Array<ColorPair> colorPairs;
    int activeColorPair;
    int activeBackgroundColorPair;

    OutputAttribute activeAttributes;
};
} // namespace terminal