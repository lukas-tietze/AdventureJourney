#include <string>
#include <ncurses.h>
#include <fstream>

#include "Exception.hpp"
#include "Terminal.hpp"
#include "data/Math.hpp"
#include "data/String.hpp"
#include "data/Helper.hpp"
#include "data/Io.hpp"

terminal::TerminalView *terminal::TerminalView::instance = nullptr;

terminal::TerminalView::TerminalView() : TerminalView(COLS, LINES)
{
    this->Recreate();
    this->Flush();
}

terminal::TerminalView::TerminalView(int width, int height) : width(width),
                                                              height(height),
                                                              colors(COLORS),
                                                              colorPairs(COLOR_PAIRS)
{
    // this->BufferColor(COLOR_BLACK, util::colors::BasicBlack);
    // this->BufferColor(COLOR_BLUE, util::colors::BasicBlue);
    // this->BufferColor(COLOR_CYAN, util::colors::BasicCyan);
    // this->BufferColor(COLOR_GREEN, util::colors::BasicGreen);
    // this->BufferColor(COLOR_MAGENTA, util::colors::BasicMagenta);
    // this->BufferColor(COLOR_RED, util::colors::BasicRed);
    // this->BufferColor(COLOR_WHITE, util::colors::BasicWhite);
    // this->BufferColor(COLOR_YELLOW, util::colors::BasicYellow);

    this->BufferColorPair(0, COLOR_WHITE, COLOR_BLACK);
    this->SetActiveColorPair(0);
    this->SetBackgroundColorPair(0);
    this->RestoreDefaultColors();

    this->colorsSupported = has_colors();
    this->cursorModeSupported = curs_set(static_cast<int>(terminal::CursorMode::Invisible)) != ERR;
    this->cursorMode = terminal::CursorMode::Invisible;

    this->Flush();
}

void terminal::TerminalView::Recreate()
{
    endwin();

    initscr();
    start_color();

    switch (this->inputMode)
    {
    case InputMode::Break:
        raw();
        break;
    case InputMode::Raw:
        cbreak();
        break;
    case InputMode::Line:
        nocbreak();
        break;
    default:
        throw util::InvalidCaseException();
    }

    if (this->echoOn)
        echo();
    else
        noecho();

    mousemask(ALL_MOUSE_EVENTS, nullptr);
    keypad(stdscr, true);

    refresh();
}

terminal::TerminalView::~TerminalView()
{
    refresh();
}

terminal::TerminalView *terminal::TerminalView::GetInstance()
{
    if (TerminalView::instance == nullptr)
    {
        initscr();
        start_color();
        TerminalView::instance = new TerminalView();
        TerminalView::instance->Recreate();
    }

    return TerminalView::instance;
}

void terminal::TerminalView::DeleteInstance()
{
    if (TerminalView::instance != nullptr)
    {
        delete TerminalView::instance;
        TerminalView::instance = nullptr;

        endwin();
    }
}

void terminal::TerminalView::SetInputMode(terminal::InputMode mode)
{
    if (mode != this->inputMode)
    {
        int res;

        switch (mode)
        {
        case InputMode::Break:
            res = raw();
            break;
        case InputMode::Raw:
            res = cbreak();
            break;
        case InputMode::Line:
            res = nocbreak();
            break;
        default:
            throw util::InvalidCaseException();
        }

        if (res == ERR)
        {
            util::err.WriteLine("Failed to set input mode to %", mode);
        }
        else
        {
            this->inputMode = mode;
            this->OnTerminalPropertyChanged();
        }
    }
}

void terminal::TerminalView::SetEcho(bool enableEcho)
{
    if (enableEcho != this->echoOn)
    {
        int res = enableEcho ? echo() : noecho();

        if (res == ERR)
        {
            util::err.WriteLine("Failed to set echo mode to %", enableEcho);
        }
        else
        {
            this->echoOn = enableEcho;
            this->OnTerminalPropertyChanged();
        }
    }
}

int terminal::TerminalView::ReadKey()
{
    return wgetch(stdscr);
}

std::string terminal::TerminalView::ReadLine()
{
    wgetstr(stdscr, this->inputBuf);
    return std::string(this->inputBuf);
}

bool terminal::TerminalView::ReadKey(long timeOut, int &result)
{
    return false;
}

bool terminal::TerminalView::ReadLine(long timeOut, std::string &result)
{
    return false;
}

void terminal::TerminalView::Print(const std::string &text)
{
    printw(text.c_str());

    if (this->liveMode)
        refresh();
}

void terminal::TerminalView::Print(const std::string &text, int x, int y)
{
    mvprintw(y, x, text.c_str());

    if (this->liveMode)
        refresh();
}

void terminal::TerminalView::Print(char c)
{
    addch(c);

    if (this->liveMode)
        refresh();
}

void terminal::TerminalView::Print(char c, int x, int y)
{
    mvaddch(y, x, c);

    if (this->liveMode)
        refresh();
}

void terminal::TerminalView::OnTerminalPropertyChanged()
{
    refresh();
}

util::Dimension terminal::TerminalView::GetSize() const
{
    int w, h;

    getmaxyx(stdscr, h, w);

    return util::Dimension(w, h);
}

bool terminal::TerminalView::NeedsResize() const
{
    int w, h;

    getmaxyx(stdscr, h, w);

    return w != this->width || h != this->height;
}

void terminal::TerminalView::Resize()
{
    this->Recreate();

    int w, h;

    getmaxyx(stdscr, h, w);

    this->width = w;
    this->height = h;
}

void terminal::TerminalView::SetLiveMode(bool live)
{
    this->liveMode = live;
}

void terminal::TerminalView::Clear(const util::Rectangle &area)
{
    std::string buf(area.GetWidth(), ' ');
    auto liveRestore = this->liveMode;
    this->liveMode = false;

    for (int y = area.GetMinY(); y < area.GetMaxY(); y++)
    {
        this->Print(buf, area.GetMinX(), y);
    }

    this->Flush();
    this->liveMode = liveRestore;
}

void terminal::TerminalView::Flush()
{
    if (move(this->cursorPos.GetY(), this->cursorPos.GetX()) == ERR)
        util::err.WriteLine("Failed to set cursor position to %", this->cursorPos);

    if (curs_set(static_cast<int>(this->cursorMode)) == ERR)
        util::err.WriteLine("Failed to set cursor mode to %", this->cursorMode);

    refresh();
}

size_t terminal::TerminalView::GetMaxColors() const
{
    return this->colors.Length();
}

size_t terminal::TerminalView::GetMaxColorPairs() const
{
    return this->colorPairs.Length();
}

bool terminal::TerminalView::CanChangeColors() const
{
    return can_change_color();
}

util::Color terminal::TerminalView::GetColor(colorId_t id) const
{
    return this->colors[id];
}

terminal::ColorPair terminal::TerminalView::GetContent(colorPairId_t id) const
{
    return this->colorPairs[id - 1];
}

terminal::colorPairId_t terminal::TerminalView::GetControlStyle(ControlStyleColor id) const
{
    return this->controlStyles[static_cast<size_t>(id)];
}

bool terminal::TerminalView::BufferColor(colorId_t index, const util::Color &color)
{
    this->colors[index] = color;

    return init_color(index,
                      static_cast<int>(color.RedPercentage() * 1000),
                      static_cast<int>(color.GreenPercentage() * 1000),
                      static_cast<int>(color.BluePercentage() * 1000)) != ERR;
}

bool terminal::TerminalView::BufferColorPair(colorPairId_t index, colorId_t id1, colorId_t id2)
{
    if (index >= this->colors.Length())
        return false;

    this->colorPairs[index] = std::make_tuple(id1, id2);
    init_pair(index + 1, id1, id2);

    return true;
}

void terminal::TerminalView::AttributeOn(terminal::OutputAttribute a)
{
    util::EnableFlag(this->activeAttributes, a);
    attron(static_cast<int>(a));
}

void terminal::TerminalView::AttributeOff(terminal::OutputAttribute a)
{
    util::DisableFlag(this->activeAttributes, a);
    attroff(static_cast<int>(a));
}

void terminal::TerminalView::SetActiveAttributes(terminal::OutputAttribute a)
{
    this->activeAttributes = a;
    attrset(static_cast<int>(a));
}

terminal::OutputAttribute terminal::TerminalView::GetActiveAttributes() const
{
    return this->activeAttributes;
}

void terminal::TerminalView::SetActiveColorPair(colorPairId_t id)
{
    if (id < 0 || id >= this->colorPairs.Length())
        throw util::IndexOutOfRangeException(id, this->colorPairs.Length());

    this->activeColorPair = id;
    color_set(id, nullptr);
}

void terminal::TerminalView::SetBackgroundColorPair(colorPairId_t id)
{
    if (id < 0 || id >= this->colorPairs.Length())
        throw util::IndexOutOfRangeException(id, this->colorPairs.Length());

    this->activeBackgroundColorPair = id;
    bkgd(id);
}

terminal::colorPairId_t terminal::TerminalView::GetActiveColorPair() const
{
    return this->activeColorPair;
}

terminal::colorPairId_t terminal::TerminalView::GetActiveBackground() const
{
    return this->activeBackgroundColorPair;
}

int terminal::TerminalView::CreateStyle(terminal::OutputAttribute attribs, int ColorPair)
{
    return static_cast<int>(attribs) | COLOR_PAIR(ColorPair);
}

util::Point terminal::TerminalView::GetCursorPosition() const
{
    return this->cursorPos;
}

void terminal::TerminalView::SetCursorPosition(const util::Point &point)
{
    this->cursorPos = point;

    if (this->liveMode)
        this->Flush();
}

terminal::CursorMode terminal::TerminalView::GetCursorMode() const
{
    if (!this->cursorModeSupported)
        return CursorMode::Default;

    return this->cursorMode;
}

void terminal::TerminalView::SetCursorMode(terminal::CursorMode mode)
{
    if (this->cursorModeSupported)
    {
        this->cursorMode = mode;
    }
}

bool terminal::TerminalView::CursorVisibilitySupported() const
{
    return this->cursorModeSupported;
}

bool terminal::TerminalView::ColorsSupported() const
{
    return this->colorsSupported;
}

void terminal::TerminalView::ApplyColorPallette(const ColorPallette &p)
{
    const auto &newColors = p.GetColors();

    for (size_t i = 0; i < this->colors.Length() && i < newColors.Length(); i++)
    {
        this->BufferColor(i, newColors[i]);
    }

    const auto &newColorPairs = p.GetColorPairs();

    for (size_t i = 0; i < this->colorPairs.Length() && i < newColorPairs.Length(); i++)
    {
        this->BufferColorPair(i, std::get<0>(newColorPairs[i]), std::get<1>(newColorPairs[i]));
    }

    if (this->liveMode)
        this->Flush();
}

void terminal::TerminalView::ApplyControlColorPallette(const ControlStyleColorPallette &p)
{
    this->ApplyColorPallette(p);

    this->controlStyles = p.GetControlColors();

    if (this->liveMode)
        this->Flush();
}

terminal::ColorPallette terminal::TerminalView::ExportCurrentColorPallette() const
{
    return ColorPallette(this->colors, this->colorPairs);
}

terminal::ControlStyleColorPallette terminal::TerminalView::ExportCurrentControlColorPallette() const
{
    return ControlStyleColorPallette(this->colors, this->colorPairs, this->controlStyles);
}

void terminal::TerminalView::LoadColorPalletteFromJson(const std::string &path)
{
    json::Node *res;
    json::Parser p;
    ColorPallette c;

    p.parse(util::ReadFile(path), res);
    c.Deserialize(res);

    this->ApplyColorPallette(c);
}

void terminal::TerminalView::LoadControlColorPalletteFromJson(const std::string &path)
{
    json::Node *res;
    json::Parser p;
    ControlStyleColorPallette c;

    p.parse(util::ReadFile(path), res);
    c.Deserialize(res);

    this->ApplyControlColorPallette(c);
}

void terminal::TerminalView::SaveCurrentColorPallette(const std::string &path) const
{
    std::ofstream out;

    out.open(path);
    json::FormattedPrinter p;

    p.Print(this->ExportCurrentColorPallette().Serialize());

    util::WriteFile(path, p.ToString());
}

void terminal::TerminalView::SaveCurrentControlColorPallette(const std::string &path) const
{
    std::ofstream out;

    out.open(path);
    json::FormattedPrinter p;

    p.Print(this->ExportCurrentControlColorPallette().Serialize());

    util::WriteFile(path, p.ToString());
}

void terminal::TerminalView::RestoreDefaultColors()
{
    auto colors = this->colors.Length();
    auto colorPairs = this->colorPairs.Length();
    auto &c = this->colors;
    auto &p = this->colorPairs;
    auto &s = this->controlStyles;

    if (colors >= 8 && colorPairs >= 8)
    {
        c[0] = util::colors::Black;
        c[1] = util::colors::White;
        c[2] = util::colors::Red1;
        c[3] = util::colors::Red4;
        c[4] = util::colors::Green1;
        c[5] = util::colors::Green4;
        c[6] = util::colors::Blue1;
        c[7] = util::colors::Blue4;

        p[0] = std::make_pair(0, 1);
        p[1] = std::make_pair(0, 2);
        p[2] = std::make_pair(0, 3);
        p[3] = std::make_pair(0, 4);
        p[4] = std::make_pair(0, 5);
        p[5] = std::make_pair(0, 6);
        p[6] = std::make_pair(0, 7);
        p[7] = std::make_pair(1, 0);

        s[static_cast<size_t>(ControlStyleColor::ControlText)] = 0;
        s[static_cast<size_t>(ControlStyleColor::DisabledControlText)] = 0;
        s[static_cast<size_t>(ControlStyleColor::ControlBorder)] = 0;
        s[static_cast<size_t>(ControlStyleColor::InactiveControlBorder)] = 0;
        s[static_cast<size_t>(ControlStyleColor::DisabledControlBorder)] = 0;
        s[static_cast<size_t>(ControlStyleColor::ClearColor)] = 0;
    }

    for (size_t i = 0; i < colors; i++)
    {
        init_color(i,
                   static_cast<int>(c[i].RedPercentage() * 1000),
                   static_cast<int>(c[i].GreenPercentage() * 1000),
                   static_cast<int>(c[i].BluePercentage() * 1000));
    }

    for (size_t i = 0; i < colorPairs; i++)
    {
        init_pair(i + 1, std::get<0>(p[i]), std::get<1>(p[i]));
    }
}
