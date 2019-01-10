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
    this->Maximise();
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

    this->window = newwin(this->height, this->width, 0, 0);
    keypad(this->window, true);

    this->colorsSupported = has_colors();
    this->cursorModeSupported = curs_set(static_cast<int>(terminal::CursorMode::Invisible)) != ERR;
    this->cursorMode = terminal::CursorMode::Invisible;

    this->Flush();
}

terminal::TerminalView::~TerminalView()
{
    wrefresh(this->window);
    delwin(this->window);
    refresh();
}

terminal::TerminalView *terminal::TerminalView::GetInstance()
{
    if (TerminalView::instance == nullptr)
    {
        initscr();
        start_color();
        mousemask(ALL_MOUSE_EVENTS, nullptr);
        TerminalView::instance = new TerminalView();
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
            throw util::Exception();
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
    return wgetch(this->window);
}

std::string terminal::TerminalView::ReadLine()
{
    wgetstr(this->window, this->inputBuf);
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
    wprintw(this->window, text.c_str());

    if (this->liveMode)
        wrefresh(this->window);
}

void terminal::TerminalView::Print(const std::string &text, int x, int y)
{
    mvwprintw(this->window, y, x, text.c_str());

    if (this->liveMode)
        wrefresh(this->window);
}

void terminal::TerminalView::Print(char c)
{
    waddch(this->window, c);

    if (this->liveMode)
        wrefresh(this->window);
}

void terminal::TerminalView::Print(char c, int x, int y)
{
    mvwaddch(this->window, y, x, c);

    if (this->liveMode)
        wrefresh(this->window);
}

void terminal::TerminalView::OnTerminalPropertyChanged()
{
    wrefresh(this->window);
}

util::Dimension terminal::TerminalView::GetSize() const
{
    int x, y;

    getmaxyx(this->window, y, x);

    return util::Dimension(x, y);
}

bool terminal::TerminalView::SetSize(const util::Dimension &dim)
{
    return resizeterm(dim.GetHeight(), dim.GetWidth()) == OK;
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
    if (wmove(this->window, this->cursorPos.GetY(), this->cursorPos.GetX()) == ERR)
        util::err.WriteLine("Failed to set cursor position to %", this->cursorPos);

    if (curs_set(static_cast<int>(this->cursorMode)) == ERR)
        util::err.WriteLine("Failed to set cursor mode to %", this->cursorMode);

    wrefresh(this->window);
    refresh();
}

void terminal::TerminalView::Maximise()
{
    int x, y;
    getmaxyx(this->window, y, x);
    resize_term(y, x);
    wresize(this->window, y, x);
    this->Flush();
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

const util::Color &terminal::TerminalView::GetColor(colorId_t id) const
{
    return this->colors[id];
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
    wattron(this->window, static_cast<int>(a));
}

void terminal::TerminalView::AttributeOff(terminal::OutputAttribute a)
{
    util::DisableFlag(this->activeAttributes, a);
    wattroff(this->window, static_cast<int>(a));
}

void terminal::TerminalView::SetActiveAttributes(terminal::OutputAttribute a)
{
    this->activeAttributes = a;
    wattrset(this->window, static_cast<int>(a));
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
    wcolor_set(this->window, id, nullptr);
}

void terminal::TerminalView::SetBackgroundColorPair(colorPairId_t id)
{
    if (id < 0 || id >= this->colorPairs.Length())
        throw util::IndexOutOfRangeException(id, this->colorPairs.Length());

    this->activeBackgroundColorPair = id;
    wbkgd(this->window, id);
}

terminal::colorPairId_t terminal::TerminalView::GetActiveColorPair() const
{
    return this->activeColorPair;
}

terminal::colorPairId_t terminal::TerminalView::GetActiveBackground() const
{
    return this->activeBackgroundColorPair;
}

const terminal::ColorPair &terminal::TerminalView::GetContent(colorPairId_t id) const
{
    return this->colorPairs[id - 1];
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

terminal::ColorPallette terminal::TerminalView::ExportCurrentColorPallette() const
{
    return ColorPallette(this->colors, this->colorPairs);
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

void terminal::TerminalView::SaveCurrentColorPallette(const std::string &path) const
{
    std::ofstream out;

    out.open(path);
    json::FormattedPrinter p;

    p.Print(this->ExportCurrentColorPallette().Serialize());

    util::WriteFile(path, p.ToString());
}

void terminal::TerminalView::RestoreDefaultColors()
{
}
