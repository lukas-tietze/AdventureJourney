#pragma once

#include <curses.h>

namespace terminal
{
enum class input_mode
{
    RAW,
    BREAK,
    LINE,
};

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
} // namespace terminal