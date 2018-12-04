#pragma once

#include <string>
#include <vector>

#include "TerminalView.hpp"
#include "graphics/Color.hpp"

namespace terminal
{
struct PatternItem final
{
    int length;
    char symbol;
    bool useCustomColor;
    util::Color customColor;
    bool useCustomAttributes;
    terminal::OutputAttribute customAttributes;
};

class Pattern final
{
  private:
    std::vector<PatternItem> items;
    uint totalLength;

  public:
    Pattern();
    Pattern(const Pattern &);

    typedef std::vector<PatternItem>::iterator Iterator;
    typedef std::vector<PatternItem>::const_iterator ConstIterator;

    Pattern &Push(const PatternItem &);
    Pattern &Push(char c);
    Pattern &Push(char c, int count);
    Pattern &Push(char c, terminal::OutputAttribute);
    Pattern &Push(char c, int count, terminal::OutputAttribute);
    Pattern &Push(char c, const util::Color &);
    Pattern &Push(char c, int count, const util::Color &);
    Pattern &Push(char c, const util::Color &, terminal::OutputAttribute);
    Pattern &Push(char c, int count, const util::Color &, terminal::OutputAttribute);
    Pattern &PushEc(char c, int Color);
    Pattern &PushEc(char c, int count, int Color);
    Pattern &PushEc(char c, int, terminal::OutputAttribute);
    Pattern &PushEc(char c, int count, int Color, terminal::OutputAttribute);

    void Pop();
    uint GetTotalLength();
    uint GetItemCount();

    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator begin();
    Iterator end();
};

class Canvas
{
  private:
    TerminalView *view;
    util::Dimension size;
    util::Rectangle clipped_area;
    util::Point origin;

  public:
    Canvas(TerminalView *);
    Canvas(const Canvas &);

    terminal::Canvas &DrawVerticalLine(const util::Point &, int length, char c);
    terminal::Canvas &DrawVerticalLine(const util::Point &, int length, char c, int Color);

    terminal::Canvas &DrawHorizontalLine(const util::Point &, int y, char c);
    terminal::Canvas &DrawHorizontalLine(const util::Point &, int y, char c, int Color);

    terminal::Canvas &DrawBox(const util::Rectangle &, char horizontal, char vertical, char cornor);
    terminal::Canvas &DrawBox(const util::Rectangle &, char horizontal, char vertical, char cornor, int Color);
    terminal::Canvas &DrawBox(const util::Rectangle &, char horizontal, int hColor, char vertical, int vColor, char cornor, int cColor);

    terminal::Canvas &DrawBox(const util::Rectangle &, char c);
    terminal::Canvas &DrawBox(const util::Rectangle &, char c, int Color);

    terminal::Canvas &DrawString(const util::Point &, const std::string &);
    terminal::Canvas &DrawString(const util::Point &, const std::string &, int Color);
    terminal::Canvas &DrawString(const util::Point &, const std::string &, terminal::OutputAttribute attributes);
    terminal::Canvas &DrawString(const util::Point &, const std::string &, int Color, terminal::OutputAttribute attributes);

    terminal::Canvas &Fill(const util::Rectangle &, char c);
    terminal::Canvas &Clear(char c);
    terminal::Canvas &Clear();

    const util::Dimension &GetSize() const;
    const util::Point &GetOrigin() const;
    const util::Rectangle &GetClippedArea() const;

    void SetOrigin(const util::Point &);
    void ClipArea(const util::Dimension &);
    void ClipArea(const util::Rectangle &);
    void DisableClip();
    void EnableAttribute(terminal::OutputAttribute);
    void DisableAttribute(terminal::OutputAttribute);
    void SetForegroundColor(const util::Color &);
    void SetBackgroundColor(const util::Color &);
    void SetForegroundColor(int);
    void SetBackgroundColor(int);
    void SetActiveColorPair(short);
    void ResetForegroundColor();
    void ResetBackgroundColor();

    void Flush();

    TerminalView *GetView() const;

    short AddColor(const util::Color &);
    void SetColor(short, const util::Color &);
    short AddColorPair(const util::Color &fg, const util::Color &bg);
    short AddColorPair(short, short);
    void SetColorPair(short, short, short);
    short FindColorPair(short, short);
};
} // namespace terminal