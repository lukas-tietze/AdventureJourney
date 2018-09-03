#include <string>
#include <ncurses.h>

#include "exception.hpp"
#include "terminal.hpp"
#include "data/math.hpp"

terminal::terminal_view *terminal::terminal_view::instance = nullptr;

terminal::terminal_view::terminal_view() : terminal_view(COLS, LINES)
{
    this->maximise();
    this->flush();
}

terminal::terminal_view::terminal_view(int width, int height) : width(width),
                                                                height(height)
{
    this->max_colors = COLORS - 1;
    this->used_colors = 8;
    this->colors = new util::color[this->max_colors];

    this->set_color(COLOR_BLACK, util::color_black);
    this->set_color(COLOR_BLUE, util::color_blue);
    this->set_color(COLOR_CYAN, util::color_cyan);
    this->set_color(COLOR_GREEN, util::color_green);
    this->set_color(COLOR_MAGENTA, util::color_magenta);
    this->set_color(COLOR_RED, util::color_red);
    this->set_color(COLOR_WHITE, util::color_white);
    this->set_color(COLOR_YELLOW, util::color_yellow);

    this->max_color_pairs = COLOR_PAIRS - 1;
    this->used_color_pairs = 1;
    this->color_pairs = new color_pair[this->max_color_pairs];

    this->set_color_pair(0, COLOR_WHITE, COLOR_BLACK);
    this->set_background_color(COLOR_BLACK);
    this->set_active_color_pair(0);

    this->window = newwin(this->height, this->width, 0, 0);
    keypad(this->window, true);
    this->flush();
}

terminal::terminal_view::~terminal_view()
{
    wrefresh(this->window);
    delwin(this->window);
    refresh();
}

terminal::terminal_view *terminal::terminal_view::get_instance()
{
    if (terminal_view::instance == nullptr)
        terminal_view::instance = new terminal_view();

    return terminal_view::instance;
}

terminal::terminal_view *terminal::terminal_view::delete_instance()
{
    delete terminal_view::instance;
    terminal_view::instance = nullptr;
}

void terminal::terminal_view::set_input_mode(terminal::input_mode mode)
{
    if (mode != this->input_mode)
    {
        switch (mode)
        {
        case input_mode::BREAK:
            raw();
            break;
        case input_mode::RAW:
            cbreak();
            break;
        case input_mode::LINE:
            nocbreak();
            break;
        default:
            throw std::exception();
        }

        this->input_mode = mode;
        this->on_terminal_property_changed();
    }
}

void terminal::terminal_view::set_echo(bool enableEcho)
{
    if (enableEcho != this->echo_on)
    {
        if (enableEcho)
        {
            echo();
        }
        else
        {
            noecho();
        }

        this->echo_on = enableEcho;
        this->on_terminal_property_changed();
    }
}

int terminal::terminal_view::read_key()
{
    return wgetch(this->window);
}

std::string terminal::terminal_view::read_line()
{
    wgetstr(this->window, this->input_buf);
    return std::string(this->input_buf);
}

bool terminal::terminal_view::read_key(long timeOut, int &result)
{
}

bool terminal::terminal_view::read_line(long timeOut, std::string &result)
{
}

void terminal::terminal_view::print(const std::string &text)
{
    wprintw(this->window, text.c_str());

    if (this->live_mode)
        wrefresh(this->window);
}

void terminal::terminal_view::print(const std::string &text, int x, int y)
{
    mvwprintw(this->window, y, x, text.c_str());

    if (this->live_mode)
        wrefresh(this->window);
}

void terminal::terminal_view::print(char c)
{
    waddch(this->window, c);

    if (this->live_mode)
        wrefresh(this->window);
}

void terminal::terminal_view::print(char c, int x, int y)
{
    mvwaddch(this->window, y, x, c);

    if (this->live_mode)
        wrefresh(this->window);
}

void terminal::terminal_view::on_terminal_property_changed()
{
    wrefresh(this->window);
}

util::dimension terminal::terminal_view::get_size() const
{
    int x, y;

    getmaxyx(this->window, y, x);

    return util::dimension(x, y);
}

bool terminal::terminal_view::set_size(const util::dimension &dim)
{
    resizeterm(dim.get_height(), dim.get_width());
}

void terminal::terminal_view::set_live_mode(bool live)
{
    this->live_mode = live;
}

void terminal::terminal_view::clear(const util::rectangle &area)
{
    std::string buf(area.get_width(), ' ');
    auto liveRestore = this->live_mode;
    this->live_mode = false;

    for (int y = area.get_min_y(); y < area.get_max_y(); y++)
    {
        this->print(buf, area.get_min_x(), y);
    }

    this->flush();
    this->live_mode = liveRestore;
}

void terminal::terminal_view::flush()
{
    wrefresh(this->window);
    refresh();
}

void terminal::terminal_view::maximise()
{
    int x, y;
    getmaxyx(this->window, y, x);
    resize_term(y, x);
    wresize(this->window, y, x);
    this->flush();
}

void terminal::terminal_view::set_active_color_pair(short id)
{
    wcolor_set(this->window, id + 1, nullptr);
}

void terminal::terminal_view::set_background_color(short id)
{
    wbkgdset(this->window, id + 1);
}

short terminal::terminal_view::get_max_colors() const
{
    return this->max_colors;
}

short terminal::terminal_view::get_used_colors() const
{
    return this->used_colors;
}

short terminal::terminal_view::get_max_color_pairs() const
{
    return this->max_color_pairs;
}

short terminal::terminal_view::get_used_color_pairs() const
{
    return this->used_color_pairs;
}

bool terminal::terminal_view::can_change_colors() const
{
    return can_change_color();
}

const util::color &terminal::terminal_view::get_color(short id) const
{
    if (id < 0 || id >= this->max_colors)
        throw util::index_out_of_range_exception(id, this->max_colors);

    return this->colors[id];
}

short terminal::terminal_view::add_color(const util::color &c)
{
    if (this->used_colors >= this->max_colors)
        throw util::index_out_of_range_exception();

    this->set_color(this->used_colors, c);
    this->used_colors++;
}

void terminal::terminal_view::set_color(short index, const util::color &color)
{
    if (index < 0 || index >= this->max_colors)
        throw util::index_out_of_range_exception(index, this->max_colors);

    this->colors[index] = color;

    init_color(index + 1,
               (short)(color.red_percentage() * 1000),
               (short)(color.green_percentage() * 1000),
               (short)(color.blue_percentage() * 1000));
}

short terminal::terminal_view::find_closest_match(const util::color &c)
{
    for (int i = 0; i < this->used_colors; i++)
    {
        if (this->colors[i] == c)
            return i;
    }

    return -1;
}

short terminal::terminal_view::add_color_pair(const util::color &fg, const util::color &bg)
{
    if (this->used_colors + 2 > this->max_colors)
        throw util::index_out_of_range_exception();

    int fgId = this->add_color(fg);
    int bgId = this->add_color(bg);

    return this->add_color_pair(fg, bg);
}

short terminal::terminal_view::add_color_pair(short id1, short id2)
{
    if (this->used_color_pairs >= this->max_color_pairs)
        throw util::index_out_of_range_exception();

    this->used_color_pairs++;
    init_pair(this->used_color_pairs, id1 + 1, id2 + 1);
    return this->used_color_pairs;
}

void terminal::terminal_view::set_color_pair(short index, short id1, short id2)
{
    if (index < 0 || index >= this->max_color_pairs)
        throw util::index_out_of_range_exception();

    init_pair(index + 1, id1 + 1, id2 + 1);
}
