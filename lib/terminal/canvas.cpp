#include "terminal.hpp"

terminal::canvas::canvas(terminal_view *view) : view(view)
{
}

terminal::canvas &terminal::canvas::draw_vertical_line(int x, int y, int length, char c)
{
    auto dim = this->view->get_size();

    if (x >= 0 && x < dim.get_width())
    {
        for(int i = 0; i < dim.get_height())
        {
            this->view.
        }
    }
}

terminal::canvas &terminal::canvas::draw_horizontal_line(int y, char c)
{
}

terminal::canvas &terminal::canvas::draw_box(int x, int y, char c)
{
}
