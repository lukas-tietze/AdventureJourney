#include <string>
#include <ncurses.h>

#include "Exception.hpp"
#include "Terminal.hpp"
#include "data/Math.hpp"
#include "data/String.hpp"
#include "data/Helper.hpp"

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

    std::fprintf(stderr, "CursorMode Supported: %i", this->cursorMode);

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
        switch (mode)
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
            throw util::Exception();
        }

        this->inputMode = mode;
        this->OnTerminalPropertyChanged();
    }
}

void terminal::TerminalView::SetEcho(bool enableEcho)
{
    if (enableEcho != this->echoOn)
    {
        if (enableEcho)
        {
            echo();
        }
        else
        {
            noecho();
        }

        this->echoOn = enableEcho;
        this->OnTerminalPropertyChanged();
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

bool terminal::TerminalView::BufferColor(colorId_t index, const util::Color &Color)
{
    this->colors[index] = Color;

    return init_color(index,
                      static_cast<int>(Color.RedPercentage() * 1000),
                      static_cast<int>(Color.GreenPercentage() * 1000),
                      static_cast<int>(Color.BluePercentage() * 1000)) == OK;
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
    int x, y;

    getyx(this->window, y, x);

    return util::Point(x, y);
}

void terminal::TerminalView::SetCursorPosition(const util::Point &point)
{
    wmove(this->window, point.GetY(), point.GetX());
    wrefresh(this->window);
}

terminal::CursorMode terminal::TerminalView::GetCursorMode() const
{
    if (!this->cursorModeSupported)
        return CursorMode::Default;

    return this->cursorMode;
}

void terminal::TerminalView::SetCursorMode(terminal::CursorMode mode)
{
    if (this->cursorModeSupported && curs_set(static_cast<int>(mode)) != ERR)
    {
        this->cursorMode = mode;
        wrefresh(this->window);
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

void terminal::TerminalView::ApplyColorPallette(const ColorPallette &)
{
}

terminal::ColorPallette terminal::TerminalView::ExportCurrentColorPallette() const
{
}

void terminal::TerminalView::LoadColorPalletteFromJson(const std::string &path)
{
}

void terminal::TerminalView::SaveCurrentColorPallette(const std::string &path) const
{
}

void terminal::TerminalView::RestoreDefaultColors()
{
}
