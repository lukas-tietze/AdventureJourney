#include <string>
#include <ncurses.h>
#include <fstream>

#include "Exception.hpp"
#include "Terminal.hpp"
#include "data/Math.hpp"
#include "data/String.hpp"
#include "data/Helper.hpp"
#include "data/Io.hpp"

terminal::View *terminal::View::instance = nullptr;

terminal::View::View() : View(COLS, LINES)
{
    this->Recreate();
    this->Flush();
}

terminal::View::View(int width, int height) : width(width),
                                              height(height),
                                              colors(COLORS),
                                              colorPairs(COLOR_PAIRS)
{
    this->colorsSupported = has_colors();
    this->cursorModeSupported = curs_set(static_cast<int>(terminal::CursorMode::Invisible)) != ERR;
    this->cursorMode = terminal::CursorMode::Invisible;

    this->RestoreDefaultColors();
    this->SetActiveColorPair(0);
    this->SetBackgroundColorPair(0);
    this->Flush();
}

void terminal::View::Recreate()
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

terminal::View::~View()
{
    refresh();
}

terminal::View *terminal::View::GetInstance()
{
    if (View::instance == nullptr)
    {
        initscr();
        start_color();
        View::instance = new View();
        View::instance->Recreate();
    }

    return View::instance;
}

void terminal::View::DeleteInstance()
{
    if (View::instance != nullptr)
    {
        delete View::instance;
        View::instance = nullptr;

        refresh();
        endwin();
    }
}

void terminal::View::SetInputMode(terminal::InputMode mode)
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

void terminal::View::SetEcho(bool enableEcho)
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

int terminal::View::ReadKey()
{
    return wgetch(stdscr);
}

std::string terminal::View::ReadLine()
{
    wgetstr(stdscr, this->inputBuf);
    return std::string(this->inputBuf);
}

bool terminal::View::ReadKey(long timeOut, int &result)
{
    return false;
}

bool terminal::View::ReadLine(long timeOut, std::string &result)
{
    return false;
}

void terminal::View::Print(const std::string &text)
{
    printw(text.c_str());

    if (this->liveMode)
        refresh();
}

void terminal::View::Print(const std::string &text, int x, int y)
{
    mvprintw(y, x, text.c_str());

    if (this->liveMode)
        refresh();
}

void terminal::View::Print(char c)
{
    addch(c);

    if (this->liveMode)
        refresh();
}

void terminal::View::Print(char c, int x, int y)
{
    mvaddch(y, x, c);

    if (this->liveMode)
        refresh();
}

void terminal::View::OnTerminalPropertyChanged()
{
    refresh();
}

util::Dimension terminal::View::GetSize() const
{
    int w, h;

    getmaxyx(stdscr, h, w);

    return util::Dimension(w, h);
}

bool terminal::View::NeedsResize() const
{
    int w, h;

    getmaxyx(stdscr, h, w);

    return w != this->width || h != this->height;
}

void terminal::View::Resize()
{
    this->Recreate();

    int w, h;

    getmaxyx(stdscr, h, w);

    this->width = w;
    this->height = h;
}

void terminal::View::SetLiveMode(bool live)
{
    this->liveMode = live;
}

void terminal::View::Clear(const util::Rectangle &area)
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

void terminal::View::Flush()
{
    if (move(this->cursorPos.GetY(), this->cursorPos.GetX()) == ERR)
        util::err.WriteLine("Failed to set cursor position to %", this->cursorPos);

    if (curs_set(static_cast<int>(this->cursorMode)) == ERR)
        util::err.WriteLine("Failed to set cursor mode to %", this->cursorMode);

    refresh();
}

size_t terminal::View::ColorCount() const
{
    return this->colors.Length();
}

size_t terminal::View::ColorPairCount() const
{
    return this->colorPairs.Length();
}

size_t terminal::View::CustomColorCount() const
{
    return this->colors.Length() - this->systemColorCount;
}

size_t terminal::View::CustomColorPairCount() const
{
    return this->colorPairs.Length() - this->systemColorPairCount;
}

size_t terminal::View::SystemColorCount() const
{
    return this->systemColorCount;
}

size_t terminal::View::SystemColorPairCount() const
{
    return this->systemColorPairCount;
}

bool terminal::View::CanChangeColors() const
{
    return can_change_color();
}

util::Color terminal::View::GetColor(colorId_t id) const
{
    return this->colors[id];
}

terminal::ColorPair terminal::View::GetContent(colorPairId_t id) const
{
    return this->colorPairs[id - 1];
}

terminal::colorPairId_t terminal::View::GetControlStyle(ControlStyleColor id) const
{
    return this->controlStyles[static_cast<size_t>(id)];
}

bool terminal::View::BufferColor(colorId_t index, const util::Color &color)
{
    this->colors[index] = color;

    return init_color(index,
                      static_cast<int>(color.RedPercentage() * 1000),
                      static_cast<int>(color.GreenPercentage() * 1000),
                      static_cast<int>(color.BluePercentage() * 1000)) != ERR;
}

bool terminal::View::BufferColorPair(colorPairId_t index, colorId_t id1, colorId_t id2)
{
    if (index >= this->colors.Length())
        return false;

    this->colorPairs[index] = std::make_tuple(id1, id2);
    init_pair(index + 1, id1, id2);

    return true;
}

void terminal::View::AttributeOn(terminal::OutputAttribute a)
{
    util::EnableFlag(this->activeAttributes, a);
    attron(static_cast<int>(a));
}

void terminal::View::AttributeOff(terminal::OutputAttribute a)
{
    util::DisableFlag(this->activeAttributes, a);
    attroff(static_cast<int>(a));
}

void terminal::View::SetActiveAttributes(terminal::OutputAttribute a)
{
    this->activeAttributes = a;
    attrset(static_cast<int>(a));
}

terminal::OutputAttribute terminal::View::GetActiveAttributes() const
{
    return this->activeAttributes;
}

void terminal::View::SetActiveColorPair(colorPairId_t id)
{
    if (id < 0 || id >= this->colorPairs.Length())
        throw util::IndexOutOfRangeException(id, this->colorPairs.Length());

    this->activeColorPair = id;
    color_set(id, nullptr);
}

void terminal::View::SetBackgroundColorPair(colorPairId_t id)
{
    if (id < 0 || id >= this->colorPairs.Length())
        throw util::IndexOutOfRangeException(id, this->colorPairs.Length());

    this->activeBackgroundColorPair = id;
    bkgd(id);
}

terminal::colorPairId_t terminal::View::GetActiveColorPair() const
{
    return this->activeColorPair;
}

terminal::colorPairId_t terminal::View::GetActiveBackground() const
{
    return this->activeBackgroundColorPair;
}

int terminal::View::CreateStyle(terminal::OutputAttribute attribs, int ColorPair)
{
    return static_cast<int>(attribs) | COLOR_PAIR(ColorPair);
}

util::Point terminal::View::GetCursorPosition() const
{
    return this->cursorPos;
}

void terminal::View::SetCursorPosition(const util::Point &point)
{
    this->cursorPos = point;

    if (this->liveMode)
        this->Flush();
}

terminal::CursorMode terminal::View::GetCursorMode() const
{
    if (!this->cursorModeSupported)
        return CursorMode::Default;

    return this->cursorMode;
}

void terminal::View::SetCursorMode(terminal::CursorMode mode)
{
    if (this->cursorModeSupported)
    {
        this->cursorMode = mode;
    }
}

bool terminal::View::CursorVisibilitySupported() const
{
    return this->cursorModeSupported;
}

bool terminal::View::ColorsSupported() const
{
    return this->colorsSupported;
}

void terminal::View::ApplyColorPallette(const ColorPallette &p)
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

void terminal::View::ApplyControlColorPallette(const ControlStyleColorPallette &p)
{
    this->ApplyColorPallette(p);

    this->controlStyles = p.GetControlColors();

    if (this->liveMode)
        this->Flush();
}

terminal::ColorPallette terminal::View::ExportCurrentColorPallette() const
{
    return ColorPallette(this->colors, this->colorPairs);
}

terminal::ControlStyleColorPallette terminal::View::ExportCurrentControlColorPallette() const
{
    return ControlStyleColorPallette(this->colors, this->colorPairs, this->controlStyles);
}

void terminal::View::LoadColorPalletteFromJson(const std::string &path)
{
    json::Node *res;
    json::Parser p;
    ColorPallette c;

    p.parse(util::ReadFile(path), res);
    c.Deserialize(res);

    this->ApplyColorPallette(c);
}

void terminal::View::LoadControlColorPalletteFromJson(const std::string &path)
{
    json::Node *res;
    json::Parser p;
    ControlStyleColorPallette c;

    p.parse(util::ReadFile(path), res);
    c.Deserialize(res);

    this->ApplyControlColorPallette(c);
}

void terminal::View::SaveCurrentColorPallette(const std::string &path) const
{
    std::ofstream out;

    out.open(path);
    json::FormattedPrinter p;

    p.Print(this->ExportCurrentColorPallette().Serialize());

    util::WriteFile(path, p.ToString());
}

void terminal::View::SaveCurrentControlColorPallette(const std::string &path) const
{
    std::ofstream out;

    out.open(path);
    json::FormattedPrinter p;

    p.Print(this->ExportCurrentControlColorPallette().Serialize());

    util::WriteFile(path, p.ToString());
}

void terminal::View::RestoreDefaultColors()
{
    auto colors = this->colors.Length();
    auto colorPairs = this->colorPairs.Length();
    auto &c = this->colors;
    auto &p = this->colorPairs;
    auto &s = this->controlStyles;

    if (colors >= 8 && colorPairs >= 8)
    {
        this->systemColorCount = 8;
        this->systemColorPairCount = 8;

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
        init_pair(i, std::get<0>(p[i]), std::get<1>(p[i]));
    }
}
