#pragma once

#include <curses.h>
#include <iostream>

namespace terminal
{
enum class input_mode
{
    RAW,
    BREAK,
    LINE,
};

std::ostream &operator<<(std::ostream &, const input_mode &);

enum class resize_mode
{
    North = 1,
    South = 2,
    West = 4,
    East = 8,
    Horizontal = West | East,
    Vertical = North | South,
    All = North | South | West | East,
};

std::ostream &operator<<(std::ostream &, const resize_mode &);

enum class output_attribute
{
    None = A_NORMAL,
    Standout = A_STANDOUT,
    Underline = A_UNDERLINE,
    Reverse = A_REVERSE,
    Blink = A_BLINK,
    Dimmed = A_DIM,
    Bold = A_BOLD,
    Protect = A_PROTECT,
    Invisible = A_INVIS,
    AlternatCharset = A_ALTCHARSET,
    All = None | Standout | Underline | Reverse | Blink | Dimmed | Bold | Protect | Invisible | AlternatCharset,
};

std::ostream &operator<<(std::ostream &, const output_attribute &);

enum class default_colors
{
    Black = COLOR_BLACK,
    Red = COLOR_RED,
    Green = COLOR_GREEN,
    Yellow = COLOR_YELLOW,
    Blue = COLOR_BLUE,
    Magenta = COLOR_MAGENTA,
    Cyan = COLOR_CYAN,
    White = COLOR_WHITE,
};

std::ostream &operator<<(std::ostream &, const default_colors &);

enum class mouse_action
{
    Button1Pressed = BUTTON1_PRESSED,
    Button1Released = BUTTON1_RELEASED,
    Button1Clicked = BUTTON1_CLICKED,
    Button1DoubleClicked = BUTTON1_DOUBLE_CLICKED,
    Button1TripleClicked = BUTTON1_TRIPLE_CLICKED,
    Button2Pressed = BUTTON2_PRESSED,
    Button2Released = BUTTON2_RELEASED,
    Button2Clicked = BUTTON2_CLICKED,
    Button2DoubleClicked = BUTTON2_DOUBLE_CLICKED,
    Button2TripleClicked = BUTTON2_TRIPLE_CLICKED,
    Button3Pressed = BUTTON3_PRESSED,
    Button3Released = BUTTON3_RELEASED,
    Button3Clicked = BUTTON3_CLICKED,
    Button3DoubleClicked = BUTTON3_DOUBLE_CLICKED,
    Button3TripleClicked = BUTTON3_TRIPLE_CLICKED,
    Button4Pressed = BUTTON4_PRESSED,
    Button4Released = BUTTON4_RELEASED,
    Button4Clicked = BUTTON4_CLICKED,
    Button4DoubleClicked = BUTTON4_DOUBLE_CLICKED,
    Button4TripleClicked = BUTTON4_TRIPLE_CLICKED,
    ButtonShift = BUTTON_SHIFT,
    ButtonCtrl = BUTTON_CTRL,
    ButtonAlt = BUTTON_ALT,
};
} // namespace terminal