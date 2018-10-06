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

    size_t lastSpace = 0;
    size_t currentLineLength = 0;
    size_t lastLineBreak = 0;
    size_t maxLineLength = this->get_bounds().get_width() - 2;

    for (size_t i = 0, end = text.length(); i < end; i++)
    {
        currentLineLength++;

        if (std::isspace(text[i]))
        {
            lastSpace = i;
        }

        if (currentLineLength >= maxLineLength)
        {
            this->lines.push_back(util::strip(text.substr(lastLineBreak, i - lastLineBreak)));
            lastLineBreak = lastSpace;
            currentLineLength -= this->lines.back().length();
        }
    }
}

void terminal::text_view::render(terminal::canvas &c)
{
    if (this->get_bounds().get_height() > 2)
    {
        int visibleLines = std::min(this->lines.size(), (size_t)(this->get_bounds().get_height() - 2));

        for (size_t i = 0; i < visibleLines; i++)
        {
            c.draw_string(this->get_bounds().get_location() + util::point(1, i + 1), this->lines[i]);
        }
    }

    c.draw_box(this->get_bounds(), '-', '|', '+');
}