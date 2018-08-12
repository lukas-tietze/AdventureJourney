#include "json.hpp"

json::formatted_printer::formatted_printer() : formatted_printer(2)
{
}

json::formatted_printer::formatted_printer(int indentLength) : formatted_printer(std::string(indentLength, ' '))
{
}

json::formatted_printer::formatted_printer(int indentLength, bool useTabs) : formatted_printer(useTabs ? std::string(indentLength, ' ') : std::string(indentLength, '\t'))
{
}

json::formatted_printer::formatted_printer(const std::string &indentTemplate) : indent_level(0),
                                                                                indent(""),
                                                                                indent_template(indentTemplate),
                                                                                value_written(false),
                                                                                buf(std::ios_base::openmode::_S_out)
{
}

json::formatted_printer &json::formatted_printer::begin_indent()
{
    this->indent_level++;
    this->indent.append(this->indent_template);
    return *this;
}

json::formatted_printer &json::formatted_printer::end_indent()
{
    if (this->indent_level > 0)
    {
        this->indent_level--;
        this->indent.erase(this->indent_level * 2, this->indent_template.length());
    }

    return *this;
}

json::formatted_printer &json::formatted_printer::begin_array()
{
    this->next_property();
    this->begin_indent();
    this->buf << '[' << std::endl << this->indent;
    this->value_written = false;

    return *this;
}

json::formatted_printer &json::formatted_printer::end_array()
{
    this->end_indent();
    this->buf << std::endl
              << this->indent << ']';
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::begin_object()
{
    this->next_property();

    this->buf << '{' << std::endl;

    this->begin_indent();
    this->value_written = false;

    return *this;
}

json::formatted_printer &json::formatted_printer::end_object()
{
    this->end_indent();
    this->buf << std::endl
              << this->indent << '}';
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print_property(const std::string &name)
{
    this->next_property();
    this->buf << this->indent << '"' << name << "\": ";
    this->value_written = false;

    return *this;
}

json::formatted_printer &json::formatted_printer::next_property()
{
    if (this->value_written)
    {
        this->buf << ',' << std::endl;
    }

    return *this;
}

json::formatted_printer &json::formatted_printer::indent_property()
{
    if (this->value_written)
    {
        this->buf << this->indent;
    }

    return *this;
}

json::formatted_printer &json::formatted_printer::print(const std::string &s)
{
    this->next_property();
    this->indent_property();
    this->buf << '"' << s << '"';
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print(double d)
{
    this->next_property();
    this->indent_property();
    this->buf << d;
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print_false()
{
    this->next_property();
    this->indent_property();
    this->buf << json::ValueFalse;
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print_true()
{
    this->next_property();
    this->indent_property();
    this->buf << json::ValueTrue;
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print_null()
{
    this->next_property();
    this->indent_property();
    this->buf << json::ValueNull;
    this->value_written = true;

    return *this;
}

std::string json::formatted_printer::to_string() const
{
    return this->buf.str();
}

std::ostream &json::formatted_printer::operator<<(std::ostream &s) const
{
    s << this->buf.str();

    return s;
}