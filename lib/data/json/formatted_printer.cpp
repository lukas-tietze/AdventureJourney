#include <iostream>
#include <sstream>

#include "data/json.hpp"

json::formatted_printer::formatted_printer() : formatted_printer(nullptr)
{
}

json::formatted_printer::formatted_printer(bool useTabs) : formatted_printer(nullptr, useTabs)
{
}

json::formatted_printer::formatted_printer(int indentLength) : formatted_printer(nullptr, indentLength)
{
}

json::formatted_printer::formatted_printer(int indentLength, bool useTabs) : formatted_printer(nullptr, indentLength, useTabs)
{
}

json::formatted_printer::formatted_printer(const std::string &indentTemplate) : formatted_printer(nullptr, indentTemplate)
{
}

json::formatted_printer::formatted_printer(std::iostream *stream) : formatted_printer(stream, 4)
{
}

json::formatted_printer::formatted_printer(std::iostream *stream, bool useTabs) : formatted_printer(stream, useTabs ? 1 : 4, useTabs)
{
}

json::formatted_printer::formatted_printer(std::iostream *stream, int indentLength) : formatted_printer(stream, std::string(indentLength, ' '))
{
}

json::formatted_printer::formatted_printer(std::iostream *stream, int indentLength, bool useTabs) : formatted_printer(stream, useTabs ? std::string(indentLength, ' ') : std::string(indentLength, '\t'))
{
}

json::formatted_printer::formatted_printer(std::iostream *stream, const std::string &indentTemplate) : indent(""),
                                                                                                       indent_template(indentTemplate),
                                                                                                       indent_level(0),
                                                                                                       out(stream),
                                                                                                       out_is_managed(stream == nullptr),
                                                                                                       value_written(false)
{
    if (this->out == nullptr)
    {
        this->out = new std::stringstream(std::iostream::openmode::_S_out);
    }
    else
    {
        this->out = stream;
    }
}

json::formatted_printer::~formatted_printer()
{
    if (this->out_is_managed)
    {
        delete this->out;
    }
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
    (*this->out) << '[' << std::endl
                 << this->indent;
    this->value_written = false;

    return *this;
}

json::formatted_printer &json::formatted_printer::end_array()
{
    this->end_indent();
    (*this->out) << std::endl
                 << this->indent << ']';
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::begin_object()
{
    this->next_property();

    (*this->out) << '{' << std::endl;

    this->begin_indent();
    this->value_written = false;

    return *this;
}

json::formatted_printer &json::formatted_printer::end_object()
{
    this->end_indent();
    (*this->out) << std::endl
                 << this->indent << '}';
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print_property(const std::string &name)
{
    this->next_property();
    (*this->out) << this->indent << '"' << name << "\": ";
    this->value_written = false;

    return *this;
}

json::formatted_printer &json::formatted_printer::next_property()
{
    if (this->value_written)
    {
        (*this->out) << ',' << std::endl;
    }

    return *this;
}

json::formatted_printer &json::formatted_printer::indent_property()
{
    if (this->value_written)
    {
        (*this->out) << this->indent;
    }

    return *this;
}

json::formatted_printer &json::formatted_printer::print(const std::string &s)
{
    this->next_property();
    this->indent_property();
    (*this->out) << '"' << s << '"';
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print(double d)
{
    this->next_property();
    this->indent_property();
    (*this->out) << d;
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print_false()
{
    this->next_property();
    this->indent_property();
    (*this->out) << json::ValueFalse;
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print_true()
{
    this->next_property();
    this->indent_property();
    (*this->out) << json::ValueTrue;
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print_null()
{
    this->next_property();
    this->indent_property();
    (*this->out) << json::ValueNull;
    this->value_written = true;

    return *this;
}

json::formatted_printer &json::formatted_printer::print(json::node *n)
{
    n->print_formatted(*this);

    return *this;
}

std::string json::formatted_printer::to_string() const
{
    if (this->out_is_managed)
    {
        return (static_cast<std::stringstream *>(this->out))->str();
    }

    return std::string();
}

std::ostream &json::formatted_printer::operator<<(std::ostream &s) const
{
    if (this->out_is_managed)
    {
        s << (static_cast<std::stringstream *>(this->out))->str();
    }

    return s;
}

const std::string &json::formatted_printer::get_indent_template() const
{
    return this->indent_template;
}

uint json::formatted_printer::get_indent_length() const
{
    return this->indent_template.length();
}

const std::iostream *json::formatted_printer::get_output() const
{
    return this->out;
}

bool json::formatted_printer::is_independent() const
{
    return this->out_is_managed;
}
