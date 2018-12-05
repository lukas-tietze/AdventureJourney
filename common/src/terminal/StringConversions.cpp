#include "Exception.hpp"

#include "terminal/Values.hpp"

std::ostream &terminal::operator<<(std::ostream &s, const terminal::InputMode &value)
{
    switch (value)
    {
    case terminal::InputMode::Raw:
        s << "    RAW";
        break;
    case terminal::InputMode::Break:
        s << "    BREAK";
        break;
    case terminal::InputMode::Line:
        s << "    LINE";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::ResizeMode &value)
{
    switch (value)
    {
    case terminal::ResizeMode::North:
        s << "North";
        break;
    case terminal::ResizeMode::South:
        s << "South";
        break;
    case terminal::ResizeMode::West:
        s << "West";
        break;
    case terminal::ResizeMode::East:
        s << "East";
        break;
    case terminal::ResizeMode::Horizontal:
        s << "Horizontal";
        break;
    case terminal::ResizeMode::Vertical:
        s << "Vertical";
        break;
    case terminal::ResizeMode::All:
        s << "All";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::OutputAttribute &value)
{
    switch (value)
    {
    case terminal::OutputAttribute::None:
        s << "None";
        break;
    case terminal::OutputAttribute::Standout:
        s << "Standout";
        break;
    case terminal::OutputAttribute::Underline:
        s << "Underline";
        break;
    case terminal::OutputAttribute::Reverse:
        s << "Reverse";
        break;
    case terminal::OutputAttribute::Blink:
        s << "Blink";
        break;
    case terminal::OutputAttribute::Dimmed:
        s << "Dimmed";
        break;
    case terminal::OutputAttribute::Bold:
        s << "Bold";
        break;
    case terminal::OutputAttribute::Protect:
        s << "Protect";
        break;
    case terminal::OutputAttribute::Invisible:
        s << "Invisible";
        break;
    case terminal::OutputAttribute::AlternatCharset:
        s << "AlternatCharset";
        break;
    case terminal::OutputAttribute::All:
        s << "All";
        break;

    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::DefaultColors &value)
{
    switch (value)
    {
    case terminal::DefaultColors::Black:
        s << "Black";
        break;
    case terminal::DefaultColors::Red:
        s << "Red";
        break;
    case terminal::DefaultColors::Green:
        s << "Green";
        break;
    case terminal::DefaultColors::Yellow:
        s << "Yellow";
        break;
    case terminal::DefaultColors::Blue:
        s << "Blue";
        break;
    case terminal::DefaultColors::Magenta:
        s << "Magenta";
        break;
    case terminal::DefaultColors::Cyan:
        s << "Cyan";
        break;
    case terminal::DefaultColors::White:
        s << "White";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}
