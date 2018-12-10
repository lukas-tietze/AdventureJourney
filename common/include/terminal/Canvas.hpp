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
    util::Rectangle clippedArea;
    util::Point origin;

  public:
    Canvas(TerminalView *);
    Canvas(const Canvas &);

    terminal::Canvas &DrawVerticalLine(int x, int y, int length, char c);
    terminal::Canvas &DrawHorizontalLine(int x, int y, int length, char c);
    terminal::Canvas &DrawBox(int x, int y, int width, int height, char horizontal, char vertical, char cornor);

    terminal::Canvas &DrawBox(int x, int y, int width, int height, char c);

    terminal::Canvas &DrawString(int x, int y, const std::string &);
    terminal::Canvas &DrawString(int x, int y, const std::string &, terminal::OutputAttribute attributes);

    terminal::Canvas &Fill(int x, int y, int width, int height, char c);
    terminal::Canvas &Clear(char c);
    terminal::Canvas &Clear();

    const util::Dimension &GetSize() const;
    const util::Point &GetOrigin() const;
    const util::Rectangle &GetClippedArea() const;

    terminal::Canvas &SetOrigin(int x, int y);
    terminal::Canvas &ClipArea(int x, int y, int width, int height);
    terminal::Canvas &DisableClip();
    terminal::Canvas &EnableAttribute(terminal::OutputAttribute);
    terminal::Canvas &DisableAttribute(terminal::OutputAttribute);
    terminal::Canvas &SetBackgroundColorPair(colorPairId_t);
    terminal::Canvas &SetActiveColorPair(colorPairId_t);

    void Flush();

    TerminalView *GetView() const;
};
} // namespace terminal