#include "exception.hpp"

#include "terminal/values.hpp"

std::ostream &terminal::operator<<(std::ostream &s, const terminal::input_mode &value)
{
    switch (value)
    {
    case terminal::input_mode::RAW:
        s << "    RAW";
        break;
    case terminal::input_mode::BREAK:
        s << "    BREAK";
        break;
    case terminal::input_mode::LINE:
        s << "    LINE";
        break;
    default:
        throw util::invalid_case_exception();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::resize_mode &value)
{
    switch (value)
    {
    case terminal::resize_mode::North:
        s << "North";
        break;
    case terminal::resize_mode::South:
        s << "South";
        break;
    case terminal::resize_mode::West:
        s << "West";
        break;
    case terminal::resize_mode::East:
        s << "East";
        break;
    case terminal::resize_mode::Horizontal:
        s << "Horizontal";
        break;
    case terminal::resize_mode::Vertical:
        s << "Vertical";
        break;
    case terminal::resize_mode::All:
        s << "All";
        break;
    default:
        throw util::invalid_case_exception();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::output_attribute &value)
{
    switch (value)
    {
    case terminal::output_attribute::None:
        s << "None";
        break;
    case terminal::output_attribute::Standout:
        s << "Standout";
        break;
    case terminal::output_attribute::Underline:
        s << "Underline";
        break;
    case terminal::output_attribute::Reverse:
        s << "Reverse";
        break;
    case terminal::output_attribute::Blink:
        s << "Blink";
        break;
    case terminal::output_attribute::Dimmed:
        s << "Dimmed";
        break;
    case terminal::output_attribute::Bold:
        s << "Bold";
        break;
    case terminal::output_attribute::Protect:
        s << "Protect";
        break;
    case terminal::output_attribute::Invisible:
        s << "Invisible";
        break;
    case terminal::output_attribute::AlternatCharset:
        s << "AlternatCharset";
        break;
    case terminal::output_attribute::All:
        s << "All";
        break;

    default:
        throw util::invalid_case_exception();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::default_colors &value)
{
    switch (value)
    {
    case terminal::default_colors::Black:
        s << "Black";
        break;
    case terminal::default_colors::Red:
        s << "Red";
        break;
    case terminal::default_colors::Green:
        s << "Green";
        break;
    case terminal::default_colors::Yellow:
        s << "Yellow";
        break;
    case terminal::default_colors::Blue:
        s << "Blue";
        break;
    case terminal::default_colors::Magenta:
        s << "Magenta";
        break;
    case terminal::default_colors::Cyan:
        s << "Cyan";
        break;
    case terminal::default_colors::White:
        s << "White";
        break;
    default:
        throw util::invalid_case_exception();
    }

    return s;
}
