#include <string>
#include <ncurses.h>

#include "exception.hpp"
#include "terminal.hpp"
#include "data/math.hpp"
#include "data/string.hpp"
#include "data/helper.hpp"

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

    this->set_color(COLOR_BLACK, util::colors::BasicBlack);
    this->set_color(COLOR_BLUE, util::colors::BasicBlue);
    this->set_color(COLOR_CYAN, util::colors::BasicCyan);
    this->set_color(COLOR_GREEN, util::colors::BasicGreen);
    this->set_color(COLOR_MAGENTA, util::colors::BasicMagenta);
    this->set_color(COLOR_RED, util::colors::BasicRed);
    this->set_color(COLOR_WHITE, util::colors::BasicWhite);
    this->set_color(COLOR_YELLOW, util::colors::BasicYellow);

    this->max_color_pairs = COLOR_PAIRS - 1;
    this->used_color_pairs = 1;
    this->color_pairs = new color_pair[this->max_color_pairs];

    this->set_color_pair(1, COLOR_WHITE, COLOR_BLACK);
    // this->set_background_color(COLOR_BLACK);
    this->set_active_color_pair(1);

    this->window = newwin(this->height, this->width, 0, 0);
    keypad(this->window, true);
    this->flush();
}

terminal::terminal_view::~terminal_view()
{
    delete[] this->colors;
    delete[] this->color_pairs;

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

int terminal::terminal_view::get_max_colors() const
{
    return this->max_colors;
}

int terminal::terminal_view::get_used_colors() const
{
    return this->used_colors;
}

int terminal::terminal_view::get_max_color_pairs() const
{
    return this->max_color_pairs;
}

int terminal::terminal_view::get_used_color_pairs() const
{
    return this->used_color_pairs;
}

bool terminal::terminal_view::can_change_colors() const
{
    return can_change_color();
}

const util::color &terminal::terminal_view::get_color(int id) const
{
    if (id < 0 || id >= this->max_colors)
        throw util::index_out_of_range_exception(id, this->max_colors);

    return this->colors[id];
}

int terminal::terminal_view::add_color(const util::color &c)
{
    if (this->used_colors >= this->max_colors)
        throw util::overflow_exception(this->max_colors,
                                       util::format("Can't add new color. %i/%i used", this->used_colors, this->max_colors));

    this->set_color(this->used_colors, c);
    this->used_colors++;
}

void terminal::terminal_view::set_color(int index, const util::color &color)
{
    if (index < 0 || index >= this->max_colors)
        throw util::index_out_of_range_exception(index, this->max_colors);

    this->colors[index] = color;

    init_color(index + 1,
               (int)(color.red_percentage() * 1000),
               (int)(color.green_percentage() * 1000),
               (int)(color.blue_percentage() * 1000));
}

int terminal::terminal_view::find(const util::color &c)
{
    for (int i = 0; i < this->used_colors; i++)
    {
        if (this->colors[i] == c)
            return i;
    }

    return -1;
}

int terminal::terminal_view::add_color_pair(const util::color &fg, const util::color &bg)
{
    if ((this->used_colors + 2) >= this->max_colors)
        throw util::overflow_exception(this->max_colors,
                                       util::format("Failed to add new colors for new color pair. %i/%i used.", this->used_colors, this->max_colors));

    int fgId = this->add_color(fg);
    int bgId = this->add_color(bg);

    return this->add_color_pair(fgId, bgId);
}

int terminal::terminal_view::add_color_pair(int id1, int id2)
{
    if (this->used_color_pairs >= this->max_color_pairs)
        throw util::overflow_exception(this->max_color_pairs,
                                       util::format("Failed to add new color pair. %i/%i pairs used.", this->used_color_pairs, this->max_color_pairs));

    if (id1 < 0 || id1 >= this->used_colors)
        throw util::index_out_of_range_exception(id1,
                                                 this->used_colors,
                                                 util::format("Failed to add new color pair. %i/%i colors used.", this->used_colors, this->max_colors));

    if (id2 < 0 || id2 >= this->used_colors)
        throw util::index_out_of_range_exception(id2,
                                                 this->used_colors,
                                                 util::format("Failed to add new color pair. %i/%i colors used.", this->used_colors, this->max_colors));

    this->color_pairs[this->used_color_pairs] = util::make_tuple(id1, id2);
    this->used_color_pairs++;
    init_pair(this->used_color_pairs, id1, id2);

    return this->used_color_pairs;
}

void terminal::terminal_view::set_color_pair(int index, int id1, int id2)
{
    if (index < 0 || index >= this->max_color_pairs)
        throw util::index_out_of_range_exception(index, this->max_color_pairs);

    init_pair(index + 1, id1, id2);
}

int terminal::terminal_view::find_color_pair(int id1, int id2)
{
    for (int i = 0; i < this->used_color_pairs; i++)
    {
        const auto &pair = this->color_pairs[i];

        if (pair.item_1() == id1 && pair.item_2() == id2)
            return i;
    }

    return -1;
}

bool terminal::terminal_view::can_add_colors() const
{
    return this->used_colors < this->max_colors;
}

bool terminal::terminal_view::can_add_color_pairs() const
{
    return this->used_color_pairs < this->max_color_pairs;
}

void terminal::terminal_view::attribute_on(terminal::output_attribute a)
{
    util::enable_flag(this->active_attributes, a);
    wattron(this->window, static_cast<int>(a));
}

void terminal::terminal_view::attribute_off(terminal::output_attribute a)
{
    util::disable_flag(this->active_attributes, a);
    wattroff(this->window, static_cast<int>(a));
}

void terminal::terminal_view::set_active_attributes(terminal::output_attribute a)
{
    this->active_attributes = a;
    wattrset(this->window, static_cast<int>(a));
}

terminal::output_attribute terminal::terminal_view::get_active_attributes() const
{
    return this->active_attributes;
}

void terminal::terminal_view::set_active_color_pair(int id)
{
    if (id < 1 || id > this->used_color_pairs)
        throw util::index_out_of_range_exception(id, this->used_color_pairs);

    this->active_color_pair = id;
    wcolor_set(this->window, id, nullptr);
}

void terminal::terminal_view::set_background_color_pair(int id)
{
    if (id < 1 || id > this->used_color_pairs)
        throw util::index_out_of_range_exception(id, this->used_color_pairs);

    this->active_background_color_pair = id;
    wbkgd(this->window, id);
}

int terminal::terminal_view::get_active_color_pair() const
{
    return this->active_color_pair;
}

int terminal::terminal_view::get_active_background() const
{
    return this->active_background_color_pair;
}

const terminal::terminal_view::color_pair &terminal::terminal_view::get_content(int id) const
{
    return this->color_pairs[id - 1];
}
