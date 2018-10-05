#include "terminal/controls/text_view.hpp"

terminal::text_view::text_view() : control_base()
{
}

terminal::text_view::text_view(const std::string &text) : control_base()
{
    this->set_text(text);
}

terminal::text_view::~text_view()
{
}

void terminal::text_view::handle_mouse(terminal::mouse_input &action)
{
}

void terminal::text_view::handle_key(terminal::key_input &action)
{
}

void terminal::text_view::handle_bounds_changed(const util::rectangle &oldBounds)
{
    if (oldBounds.get_size() != this->get_bounds().get_size())
    {
        this->prepare_lines();
    }
}

void terminal::text_view::prepare_lines()
{
    this->lines.clear();

    const auto &text = this->get_text();

    size_t lastSpace = 0;
    size_t currentLineLength = 0;
    size_t maxLineLength = this->get_bounds().get_width() - 2;

    for (size_t i = 0, end = text.length(); i < end; i++)
    {
        ////TODO :P
    }
}

void terminal::text_view::render(terminal::canvas &c)
{
    c.draw_string(this->get_bounds().get_location() + util::point(1, 1), this->get_text());
    c.draw_box(this->get_bounds(), '-', '|', '+');
}