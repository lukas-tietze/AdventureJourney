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

    typedef std::vector<PatternItem>::Iterator Iterator;
    typedef std::vector<PatternItem>::ConstIterator ConstIterator;

    Pattern &push(const PatternItem &);
    Pattern &push(char c);
    Pattern &push(char c, int count);
    Pattern &push(char c, terminal::OutputAttribute);
    Pattern &push(char c, int count, terminal::OutputAttribute);
    Pattern &push(char c, const util::Color &);
    Pattern &push(char c, int count, const util::Color &);
    Pattern &push(char c, const util::Color &, terminal::OutputAttribute);
    Pattern &push(char c, int count, const util::Color &, terminal::OutputAttribute);
    Pattern &push_ec(char c, int Color);
    Pattern &push_ec(char c, int count, int Color);
    Pattern &push_ec(char c, int, terminal::OutputAttribute);
    Pattern &push_ec(char c, int count, int Color, terminal::OutputAttribute);

    void pop();
    uint getTotalLength();
    uint getItemCount();

    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator begin();
    Iterator end();
};

class canvas
{
  private:
    TerminalView *view;
    util::dimension size;
    util::rectangle clipped_area;
    util::point origin;

  public:
    canvas(TerminalView *);
    canvas(const canvas &);

    terminal::canvas &draw_vertical_line(const util::point &, int length, char c);
    terminal::canvas &draw_vertical_line(const util::point &, int length, char c, int Color);

    terminal::canvas &draw_horizontal_line(const util::point &, int y, char c);
    terminal::canvas &draw_horizontal_line(const util::point &, int y, char c, int Color);

    terminal::canvas &draw_box(const util::rectangle &, char horizontal, char vertical, char cornor);
    terminal::canvas &draw_box(const util::rectangle &, char horizontal, char vertical, char cornor, int Color);
    terminal::canvas &draw_box(const util::rectangle &, char horizontal, int hColor, char vertical, int vColor, char cornor, int cColor);

    terminal::canvas &draw_box(const util::rectangle &, char c);
    terminal::canvas &draw_box(const util::rectangle &, char c, int Color);

    terminal::canvas &draw_string(const util::point &, const std::string &);
    terminal::canvas &draw_string(const util::point &, const std::string &, int Color);
    terminal::canvas &draw_string(const util::point &, const std::string &, terminal::OutputAttribute attributes);
    terminal::canvas &draw_string(const util::point &, const std::string &, int Color, terminal::OutputAttribute attributes);

    terminal::canvas &fill(const util::rectangle &, char c);
    terminal::canvas &clear(char c);
    terminal::canvas &clear();

    const util::dimension &get_size() const;
    const util::point &get_origin() const;
    const util::rectangle &get_clipped_area() const;

    void set_origin(const util::point &);
    void clip_area(const util::dimension &);
    void clip_area(const util::rectangle &);
    void disable_clip();
    void enable_attribute(terminal::OutputAttribute);
    void disable_attribute(terminal::OutputAttribute);
    void set_foreground_color(const util::Color &);
    void set_background_color(const util::Color &);
    void set_foreground_color(int);
    void set_background_color(int);
    void set_active_color_pair(short);
    void reset_foreground_color();
    void reset_background_color();

    void flush();

    TerminalView *get_view() const;

    short add_color(const util::Color &);
    void set_color(short, const util::Color &);
    short add_color_pair(const util::Color &fg, const util::Color &bg);
    short add_color_pair(short, short);
    void set_color_pair(short, short, short);
    short find_color_pair(short, short);
};
} // namespace terminal