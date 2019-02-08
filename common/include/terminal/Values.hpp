#pragma once

#include <curses.h>
#include <iostream>

namespace terminal
{
enum class InputMode
{
    Raw,
    Break,
    Line,
};

std::ostream &operator<<(std::ostream &, const InputMode);

enum class ResizeMode
{
    North = 1,
    South = 2,
    West = 4,
    East = 8,
    Horizontal = West | East,
    Vertical = North | South,
    All = North | South | West | East,
};

std::ostream &operator<<(std::ostream &, const ResizeMode);

enum class OutputAttribute
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

std::ostream &operator<<(std::ostream &, const OutputAttribute);

enum class DefaultColors
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

std::ostream &operator<<(std::ostream &, const DefaultColors);

enum class MouseAction
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

std::ostream &operator<<(std::ostream &, const MouseAction);

enum class CursorMode
{
    Invisible = 0,
    Default = 1,
    Highlighted = 2
};

std::ostream &operator<<(std::ostream &, const CursorMode);

bool IsSpecialKey(int key);
bool IsAsciiKey(int key);
bool IsMouse(int key);

enum class Key
{
    Down = KEY_DOWN,
    Up = KEY_UP,
    Left = KEY_LEFT,
    Right = KEY_RIGHT,
    Pos1 = KEY_HOME,
    Backspace = KEY_BACKSPACE,
    F0 = KEY_F0,
    F1 = KEY_F(1),
    F2 = KEY_F(2),
    F3 = KEY_F(3),
    F4 = KEY_F(4),
    F5 = KEY_F(5),
    F6 = KEY_F(6),
    F7 = KEY_F(7),
    F8 = KEY_F(8),
    F9 = KEY_F(9),
    F10 = KEY_F(10),
    F11 = KEY_F(11),
    F12 = KEY_F(12),
    DeleteLine = KEY_DL,
    InsertLine = KEY_IL,
    Delete = KEY_DC,
    Insert = KEY_IC,
    Eic = KEY_EIC,
    Clear = KEY_CLEAR,
    ClearToEndOfScreen = KEY_EOS,
    ClearToEndOfLine = KEY_EOL,
    ScrollForward = KEY_SF,
    ScrollBackward = KEY_SR,
    PageDown = KEY_NPAGE,
    PageUp = KEY_PPAGE,
    Tab = KEY_STAB,
    ClearTab = KEY_CTAB,
    ClearAllTabs = KEY_CATAB,
    Enter = KEY_ENTER,
    Print = KEY_PRINT,
    LowerLeft = KEY_LL, //?
    KeypadA1 = KEY_A1,
    KeypadA3 = KEY_A3,
    KeypadB2 = KEY_B2,
    KeypadC1 = KEY_C1,
    KeypadC3 = KEY_C3,
    BackTab = KEY_BTAB,
    Begin = KEY_BEG,
    Cancel = KEY_CANCEL,
    Close = KEY_CLOSE,
    Command = KEY_COMMAND,
    Copy = KEY_COPY,
    Create = KEY_CREATE,
    End = KEY_END,
    Exit = KEY_EXIT,
    Find = KEY_FIND,
    Help = KEY_HELP,
    Mark = KEY_MARK,
    Message = KEY_MESSAGE,
    Move = KEY_MOVE,
    Next = KEY_NEXT,
    Open = KEY_OPEN,
    Options = KEY_OPTIONS,
    Previous = KEY_PREVIOUS,
    Redo = KEY_REDO,
    Reference = KEY_REFERENCE,
    Refresh = KEY_REFRESH,
    Replace = KEY_REPLACE,
    Restart = KEY_RESTART,
    Resume = KEY_RESUME,
    Save = KEY_SAVE,
    Sbeg = KEY_SBEG,
    ShiftCommand = KEY_SCOMMAND,
    ShiftCancel = KEY_SCANCEL,
    ShiftCopy = KEY_SCOPY,
    ShiftCreate = KEY_SCREATE,
    ShiftDeleteChar = KEY_SDC,
    ShiftDeleteLine = KEY_SDL,
    Select = KEY_SELECT,
    ShiftEnd = KEY_SEND,
    ShiftClearToEndOfLine = KEY_SEOL,
    ShiftExit = KEY_SEXIT,
    ShiftFind = KEY_SFIND,
    ShiftHelp = KEY_SHELP,
    ShiftHome = KEY_SHOME,
    ShiftInsertChar = KEY_SIC,
    ShiftLeft = KEY_SLEFT,
    ShiftMessage = KEY_SMESSAGE,
    ShiftMove = KEY_SMOVE,
    ShiftNext = KEY_SNEXT,
    ShiftOptions = KEY_SOPTIONS,
    ShiftPrevious = KEY_SPREVIOUS,
    ShiftPrint = KEY_SPRINT,
    ShiftRedo = KEY_SREDO,
    ShiftReplace = KEY_SREPLACE,
    ShiftRight = KEY_SRIGHT,
    ShiftResume = KEY_SRSUME,
    ShiftSave = KEY_SSAVE,
    ShiftSuspend = KEY_SSUSPEND,
    ShiftUndo = KEY_SUNDO,
    Suspend = KEY_SUSPEND,
    Undo = KEY_UNDO,
    Mouse = KEY_MOUSE,
    Resize = KEY_RESIZE,
    Event = KEY_EVENT,
};

std::ostream &operator<<(std::ostream &, const Key);
} // namespace terminal