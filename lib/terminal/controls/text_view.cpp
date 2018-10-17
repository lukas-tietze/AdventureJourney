#include "terminal/controls/text_view.hpp"
#include "data/string.hpp"

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

void terminal::text_view::handle_text_changed(const std::string &oldText)
{
    if (this->get_text() != oldText)
    {
        this->prepare_lines();
    }
}

void terminal::text_view::prepare_lines()
{
    this->lines.clear();

    const auto &text = this->get_text();

    size_t last = 0;
    size_t pos = 0;
    size_t next = 0;
    size_t maxLineLength = this->get_bounds().get_width() - 2;

    while (pos < text.length())
    {
        next = text.length();

        for (size_t i = pos; i < text.length(); i++)
        {
            if (std::isspace(text[i]))
            {
                next = i;
                break;
            }
            else if (text[i] == '.' ||
                     text[i] == ',' ||
                     text[i] == '-' ||
                     pos + i > maxLineLength)
            {
                next = i + 1;
                break;
            }
        }

        pos = next + 1;
        auto len = next - last;

        if (len > maxLineLength)
        {
            this->lines.push_back(util::strip(text.substr(last, len)));
            last = next;
        }
    }
}

void terminal::text_view::render(terminal::canvas &c)
{
    c.draw_box(this->get_bounds(), '-', '|', '+');

    if (this->get_bounds().get_height() > 2 && !this->lines.empty())
    {
        int visibleLines = std::min(this->lines.size(), (size_t)(this->get_bounds().get_height() - 2));

        for (size_t i = 0; i < visibleLines; i++)
        {
            c.draw_string(this->get_bounds().get_location() + util::point(1, i + 1), this->lines[i]);
        }
    }
}