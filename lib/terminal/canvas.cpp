#include "terminal.hpp"

terminal::canvas::canvas(terminal_view *view) : view(view)
{
}

terminal::canvas &terminal::canvas::draw_vertical_line(const util::point &p, int length, char c)
{
}

terminal::canvas &terminal::canvas::draw_horizontal_line(const util::point &p, int y, char c)
{
}

terminal::canvas &terminal::canvas::draw_box(const util::rectangle &r, char c)
{
}
