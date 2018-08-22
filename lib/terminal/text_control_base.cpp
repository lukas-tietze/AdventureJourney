#ifndef TEXT_CONTROL_BASE
#define TEXT_CONTROL_BASE

#include "terminal.hpp"

terminal::text_control_base::text_control_base() : text("")
{
}

terminal::text_control_base::text_control_base(const std::string &text) : text(text)
{
}

terminal::text_control_base::~text_control_base()
{
}

std::string &terminal::text_control_base::get_text()
{
    return this->text;
}

const std::string &terminal::text_control_base::get_text() const
{
    return this->text;
}

void terminal::text_control_base::set_text(const std::string &text)
{
    this->text = text;
}

#endif /*TEXT_CONTROL_BASE*/