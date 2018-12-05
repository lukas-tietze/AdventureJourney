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
                                                              height(height)
{
    this->maxColors = COLORS;
    this->usedColors = 8;
    this->colors = new util::Color[this->maxColors];

    this->SetColor(COLOR_BLACK, util::colors::BasicBlack);
    this->SetColor(COLOR_BLUE, util::colors::BasicBlue);
    this->SetColor(COLOR_CYAN, util::colors::BasicCyan);
    this->SetColor(COLOR_GREEN, util::colors::BasicGreen);
    this->SetColor(COLOR_MAGENTA, util::colors::BasicMagenta);
    this->SetColor(COLOR_RED, util::colors::BasicRed);
    this->SetColor(COLOR_WHITE, util::colors::BasicWhite);
    this->SetColor(COLOR_YELLOW, util::colors::BasicYellow);

    this->maxColorPairs = COLOR_PAIRS - 1;
    this->usedColorPairs = 0;
    this->colorPairs = new ColorPair[this->maxColorPairs];

    auto defaultColors = this->AddColorPair(COLOR_WHITE, COLOR_BLACK);
    this->SetActiveColorPair(defaultColors);
    this->SetBackgroundColorPair(defaultColors);

    this->window = newwin(this->height, this->width, 0, 0);
    keypad(this->window, true);
    this->Flush();
}

terminal::TerminalView::~TerminalView()
{
    delete[] this->colors;
    delete[] this->colorPairs;

    wrefresh(this->window);
    delwin(this->window);
    refresh();
}

terminal::TerminalView *terminal::TerminalView::GetInstance()
{
    if (TerminalView::instance == nullptr)
        TerminalView::instance = new TerminalView();

    return TerminalView::instance;
}

terminal::TerminalView *terminal::TerminalView::DeleteInstance()
{
    delete TerminalView::instance;
    TerminalView::instance = nullptr;
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
}

bool terminal::TerminalView::ReadLine(long timeOut, std::string &result)
{
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
    resizeterm(dim.GetHeight(), dim.GetWidth());
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

int terminal::TerminalView::GetMaxColors() const
{
    return this->maxColors;
}

int terminal::TerminalView::GetUsedColors() const
{
    return this->usedColors;
}

int terminal::TerminalView::GetMaxColorPairs() const
{
    return this->maxColorPairs;
}

int terminal::TerminalView::GetUsedColorPairs() const
{
    return this->usedColorPairs;
}

bool terminal::TerminalView::CanChangeColors() const
{
    return can_change_color();
}

const util::Color &terminal::TerminalView::GetColor(int id) const
{
    if (id < 0 || id >= this->maxColors)
        throw util::IndexOutOfRangeException(id, this->maxColors);

    return this->colors[id];
}

int terminal::TerminalView::AddColor(const util::Color &c)
{
    if (this->usedColors >= this->maxColors)
        throw util::OverflowException(this->maxColors,
                                       util::Format("Can't add new color. %i/%i used", this->usedColors, this->maxColors));

    int id = this->usedColors++;

    this->SetColor(id, c);

    return id;
}

void terminal::TerminalView::SetColor(int index, const util::Color &Color)
{
    if (index < 0 || index >= this->maxColors)
        throw util::IndexOutOfRangeException(index, this->maxColors);

    this->colors[index] = Color;

    init_color(index,
               (int)(Color.RedPercentage() * 1000),
               (int)(Color.GreenPercentage() * 1000),
               (int)(Color.BluePercentage() * 1000));
}

int terminal::TerminalView::Find(const util::Color &c)
{
    for (int i = 0; i < this->usedColors; i++)
    {
        if (this->colors[i] == c)
            return i;
    }

    return -1;
}

int terminal::TerminalView::AddColorPair(const util::Color &fg, const util::Color &bg)
{
    if ((this->usedColors + 2) >= this->maxColors)
        throw util::OverflowException(this->maxColors,
                                       util::Format("Failed to add new colors for new Color pair. %i/%i used.", this->usedColors, this->maxColors));

    return this->AddColorPair(this->AddColor(fg), this->AddColor(bg));
}

int terminal::TerminalView::AddColorPair(int id1, int id2)
{
    if (this->usedColorPairs >= this->maxColorPairs)
        throw util::OverflowException(this->maxColorPairs,
                                       util::Format("Failed to add new Color pair. %i/%i pairs used.", this->usedColorPairs, this->maxColorPairs));

    if (id1 < 0 || id1 >= this->usedColors)
        throw util::IndexOutOfRangeException(id1,
                                                 this->usedColors,
                                                 util::Format("Failed to add new Color pair. %i/%i colors used.", this->usedColors, this->maxColors));

    if (id2 < 0 || id2 >= this->usedColors)
        throw util::IndexOutOfRangeException(id2,
                                                 this->usedColors,
                                                 util::Format("Failed to add new Color pair. %i/%i colors used.", this->usedColors, this->maxColors));

    this->colorPairs[this->usedColorPairs] = std::make_tuple(id1, id2);
    this->usedColorPairs++;
    init_pair(this->usedColorPairs, id1, id2);

    return this->usedColorPairs;
}

void terminal::TerminalView::SetColorPair(int index, int id1, int id2)
{
    if (index < 0 || index >= this->maxColorPairs)
        throw util::IndexOutOfRangeException(index, this->maxColorPairs);

    init_pair(index + 1, id1, id2);
}

int terminal::TerminalView::FindColorPair(int id1, int id2)
{
    for (int i = 0; i < this->usedColorPairs; i++)
    {
        const auto &pair = this->colorPairs[i];

        if (std::get<0>(pair) == id1 && std::get<1>(pair) == id2)
            return i;
    }

    return -1;
}

bool terminal::TerminalView::CanAddColors() const
{
    return this->usedColors < this->maxColors;
}

bool terminal::TerminalView::CanAddColorPairs() const
{
    return this->usedColorPairs < this->maxColorPairs;
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

void terminal::TerminalView::SetActiveColorPair(int id)
{
    if (id < 1 || id > this->usedColorPairs)
        throw util::IndexOutOfRangeException(id, this->usedColorPairs);

    this->activeColorPair = id;
    wcolor_set(this->window, id, nullptr);
}

void terminal::TerminalView::SetBackgroundColorPair(int id)
{
    if (id < 1 || id > this->usedColorPairs)
        throw util::IndexOutOfRangeException(id, this->usedColorPairs);

    this->activeBackgroundColorPair = id;
    wbkgd(this->window, id);
}

int terminal::TerminalView::GetActiveColorPair() const
{
    return this->activeColorPair;
}

int terminal::TerminalView::GetActiveBackground() const
{
    return this->activeBackgroundColorPair;
}

const terminal::TerminalView::ColorPair &terminal::TerminalView::GetContent(int id) const
{
    return this->colorPairs[id - 1];
}

int terminal::TerminalView::CreateStyle(terminal::OutputAttribute attribs, int ColorPair)
{
    return static_cast<int>(attribs) | COLOR_PAIR(ColorPair);
}
