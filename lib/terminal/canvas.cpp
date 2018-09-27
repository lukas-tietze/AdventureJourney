#include "terminal.hpp"
#include "data/helper.hpp"

terminal::canvas::canvas(terminal_view *view) : view(view),
                                                size(view->get_size()),
                                                clipped_area(0, 0, this->size),
                                                origin(0, 0)
{
    this->view->set_live_mode(false);
}

terminal::canvas::canvas(const canvas &copy) : view(copy.view),
                                               size(copy.size),
                                               clipped_area(copy.clipped_area),
                                               origin(copy.origin)
{
}

terminal::canvas &terminal::canvas::draw_vertical_line(const util::point &p, int length, char c)
{
    auto start = this->clipped_area.fit(p);
    auto end = this->clipped_area.fit(p + util::point(0, length));

    for (int y = start.get_y(); y < end.get_y(); y++)
    {
        this->view->print(c, start.get_x(), y);
    }

    return *this;
}

terminal::canvas &terminal::canvas::draw_vertical_line(const util::point &p, int length, char c, int color)
{
    auto activeColor = this->view->get_active_color_pair();
    this->view->set_active_color_pair(color);
    this->draw_vertical_line(p, length, c);
    this->view->set_active_color_pair(activeColor);
}

terminal::canvas &terminal::canvas::draw_horizontal_line(const util::point &p, int length, char c)
{
    auto start = this->clipped_area.fit(p);
    auto end = this->clipped_area.fit(p + util::point(length, 0));

    for (int x = start.get_x(); x < end.get_x(); x++)
    {
        this->view->print(c, x, start.get_y());
    }

    return *this;
}

terminal::canvas &terminal::canvas::draw_horizontal_line(const util::point &p, int length, char c, int color)
{
    auto activeColor = this->view->get_active_color_pair();
    this->view->set_active_color_pair(color);
    this->draw_horizontal_line(p, length, c);
    this->view->set_active_color_pair(activeColor);
}

terminal::canvas &terminal::canvas::draw_box(const util::rectangle &r, char horizontal, char vertical, char cornor)
{
    auto tlc = this->clipped_area.fit(util::point(r.get_min_x(), r.get_min_y()));
    auto brc = this->clipped_area.fit(util::point(r.get_max_x() - 1, r.get_max_y() - 1));

    for (int x = tlc.get_x() + 1; x < brc.get_x(); x++)
    {
        this->view->print(horizontal, x, tlc.get_y());
        this->view->print(horizontal, x, brc.get_y());
    }

    for (int y = tlc.get_y() + 1; y < brc.get_y(); y++)
    {
        this->view->print(vertical, tlc.get_x(), y);
        this->view->print(vertical, brc.get_x(), y);
    }

    this->view->print(cornor, tlc.get_x(), tlc.get_y());
    this->view->print(cornor, brc.get_x(), tlc.get_y());
    this->view->print(cornor, tlc.get_x(), brc.get_y());
    this->view->print(cornor, brc.get_x(), brc.get_y());

    return *this;
}

terminal::canvas &terminal::canvas::draw_box(const util::rectangle &r, char c, int color)
{
    auto activeColor = this->view->get_active_color_pair();
    this->view->set_active_color_pair(color);
    this->draw_box(r, c);
    this->view->set_active_color_pair(activeColor);
}

terminal::canvas &terminal::canvas::draw_box(const util::rectangle &r, char horizontal, char vertical, char cornor, int color)
{
    auto activeColor = this->view->get_active_color_pair();
    this->view->set_active_color_pair(color);
    this->draw_box(r, horizontal, vertical, cornor);
    this->view->set_active_color_pair(activeColor);
}

terminal::canvas &terminal::canvas::draw_box(const util::rectangle &r, char horizontal, int hColor, char vertical, int vColor, char cornor, int cColor)
{
    auto activeColor = this->view->get_active_color_pair();
    auto tlc = this->clipped_area.fit(util::point(r.get_min_x(), r.get_min_y()));
    auto brc = this->clipped_area.fit(util::point(r.get_max_x() - 1, r.get_max_y() - 1));

    this->view->set_active_color_pair(hColor);
    for (int x = tlc.get_x() + 1; x < brc.get_x(); x++)
    {
        this->view->print(horizontal, x, tlc.get_y());
        this->view->print(horizontal, x, brc.get_y());
    }

    this->view->set_active_color_pair(vColor);
    for (int y = tlc.get_y() + 1; y < brc.get_y(); y++)
    {
        this->view->print(vertical, tlc.get_x(), y);
        this->view->print(vertical, brc.get_x(), y);
    }
    this->view->set_active_color_pair(cColor);
    this->view->print(cornor, tlc.get_x(), tlc.get_y());
    this->view->print(cornor, brc.get_x(), tlc.get_y());
    this->view->print(cornor, tlc.get_x(), brc.get_y());
    this->view->print(cornor, brc.get_x(), brc.get_y());

    this->view->set_active_color_pair(activeColor);

    return *this;
}

terminal::canvas &terminal::canvas::draw_box(const util::rectangle &r, char c)
{
    return this->draw_box(r, c, c, c);
}

terminal::canvas &terminal::canvas::fill(const util::rectangle &r, char c)
{
    for (int x = r.get_min_x(); x < r.get_max_x(); x++)
    {
        for (int y = r.get_min_y(); y < r.get_max_y(); y++)
        {
            this->view->print(c, x, y);
        }
    }

    return *this;
}

terminal::canvas &terminal::canvas::clear(char c)
{
    return this->fill(this->clipped_area, c);
}

terminal::canvas &terminal::canvas::clear()
{
    return this->clear(' ');
}

terminal::canvas &terminal::canvas::draw_string(const util::point &p, const std::string &s)
{
    this->view->print(s, p.get_x(), p.get_y());

    return *this;
}

terminal::canvas &terminal::canvas::draw_string(const util::point &p, const std::string &s, int color)
{
    auto activeColor = this->view->get_active_color_pair();
    this->view->set_active_color_pair(color);
    this->draw_string(p, s);
    this->view->set_active_color_pair(activeColor);
}

terminal::canvas &terminal::canvas::draw_string(const util::point &p, const std::string &s, terminal::output_attribute attributes)
{
    auto activeAttributes = this->view->get_active_attributes();
    this->view->set_active_attributes(attributes);
    this->draw_string(p, s);
    this->view->set_active_attributes(activeAttributes);
}

terminal::canvas &terminal::canvas::draw_string(const util::point &p, const std::string &s, int color, terminal::output_attribute attributes)
{

    auto activeAttributes = this->view->get_active_attributes();
    auto activeColor = this->view->get_active_color_pair();
    this->view->set_active_attributes(attributes);
    this->view->set_active_color_pair(color);
    this->draw_string(p, s);
    this->view->set_active_attributes(activeAttributes);
    this->view->set_active_color_pair(activeColor);
}

const util::dimension &terminal::canvas::get_size() const
{
    return this->size;
}

const util::point &terminal::canvas::get_origin() const
{
    return this->origin;
}

const util::rectangle &terminal::canvas::get_clipped_area() const
{
    return this->clipped_area;
}

void terminal::canvas::set_origin(const util::point &p)
{
    this->origin = p;
}

void terminal::canvas::clip_area(const util::dimension &d)
{
    this->clipped_area = util::rectangle(this->origin, d);
}

void terminal::canvas::clip_area(const util::rectangle &p)
{
    this->clipped_area = p;
}

void terminal::canvas::disable_clip()
{
    this->clipped_area = util::rectangle(this->origin, this->size);
}

void terminal::canvas::enable_attribute(terminal::output_attribute a)
{
    this->view->attribute_on(a);
}

void terminal::canvas::disable_attribute(terminal::output_attribute a)
{
    this->view->attribute_off(a);
}

void terminal::canvas::set_foreground_color(const util::color &c)
{
    //     int colorIndex = this->view->find(c);
    //     int pairIndex;

    //     if (colorIndex == -1 && this->view->can_add_colors() && this->view->can_add_color_pairs())
    //     {
    //         colorIndex = this->view->add_color(c);
    //         pairIndex = this->view->add_color_pair(colorIndex, this->view->get_active_color_pair().item_2())
    //     }

    //     if(pairIndex != -1)
    //     this->view->set_active_color_pair(pairIndex);
}

void terminal::canvas::set_background_color(const util::color &c)
{
}

void terminal::canvas::set_foreground_color(int c)
{
}

void terminal::canvas::set_background_color(int c)
{
}

void terminal::canvas::set_active_color_pair(short index)
{
    this->view->set_active_color_pair(index);
}

void terminal::canvas::reset_foreground_color()
{
    this->set_foreground_color(util::colors::BasicWhite);
}

void terminal::canvas::reset_background_color()
{
    this->set_background_color(util::colors::BasicBlack);
}

terminal::terminal_view *terminal::canvas::get_view() const
{
    return this->view;
}

short terminal::canvas::add_color(const util::color &c)
{
    this->view->add_color(c);
}

void terminal::canvas::set_color(short index, const util::color &c)
{
    this->view->set_color(index, c);
}

short terminal::canvas::add_color_pair(const util::color &fg, const util::color &bg)
{
    this->view->add_color_pair(fg, bg);
}

short terminal::canvas::add_color_pair(short fg, short bg)
{
    this->view->add_color_pair(fg, bg);
}

void terminal::canvas::set_color_pair(short index, short fg, short bg)
{
    this->view->set_color_pair(index, fg, bg);
}

short terminal::canvas::find_color_pair(short id1, short id2)
{
    return this->view->find_color_pair(id1, id2);
}

void terminal::canvas::flush()
{
    this->view->flush();
}