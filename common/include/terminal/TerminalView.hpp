#pragma once

#include <curses.h>
#include <string>
#include <tuple>

#include "Util.hpp"
#include "Values.hpp"
#include "Geometry.hpp"
#include "graphics/Color.hpp"

namespace terminal
{
class TerminalView
{
  public:
    typedef std::tuple<int, int> ColorPair;

    ~TerminalView();

    static TerminalView *GetInstance();
    static TerminalView *DeleteInstance();

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
    void Clear(const util::rectangle &area);
    void Flush();

    void Maximise();
    void SetLiveMode(bool);

    void SetAttribute(terminal::OutputAttribute, bool);
    void ResetAttribtues();
    void AttributeOn(terminal::OutputAttribute);
    void AttributeOff(terminal::OutputAttribute);
    void SetActiveAttributes(terminal::OutputAttribute);
    OutputAttribute GetActiveAttributes() const;

    void SetActiveColorPair(int);
    void SetBackgroundColorPair(int);
    int GetActiveColorPair() const;
    int GetActiveBackground() const;
    const ColorPair &GetContent(int id) const;
    const util::Color &GetColor(int id) const;

    int GetMaxColors() const;
    int GetUsedColors() const;
    int GetMaxColorPairs() const;
    int GetUsedColorPairs() const;
    bool CanChangeColors() const;

    int AddColor(const util::Color &);
    void SetColor(int, const util::Color &);
    int Find(const util::Color &);
    int AddColorPair(const util::Color &fg, const util::Color &bg);
    int AddColorPair(int, int);
    void SetColorPair(int, int, int);
    int FindColorPair(int, int);

    bool CanAddColors() const;
    bool CanAddColorPairs() const;
    
    int CreateStyle(terminal::OutputAttribute attributes, int colorPair);

  protected:
    void OnTerminalPropertyChanged();

  private:
    static TerminalView *instance;

    WINDOW *window;
    int width;
    int height;
    char inputBuf[4096];

    InputMode inputMode;
    bool echoOn;
    bool liveMode;

    util::Color *colors;
    int maxColors;
    int usedColors;
    ColorPair *colorPairs;
    int activeColorPair;
    int activeBackgroundColorPair;
    int maxColorPairs;
    int usedColorPairs;

    OutputAttribute activeAttributes;

    TerminalView();
    TerminalView(int width, int height);
};
} // namespace terminal