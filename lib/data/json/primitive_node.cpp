#include "data/json.hpp"

json::primitive_node::primitive_node(const std::string &value) : node(),
                                                                 string_value(value),
                                                                 numeric_value(0),
                                                                 type(json::value_type::String)
{
}

json::primitive_node::primitive_node(const char *value) : node(),
                                                          string_value(value),
                                                          numeric_value(0),
                                                          type(json::value_type::String)
{
}

json::primitive_node::primitive_node(double value) : node(),
                                                     string_value(""),
                                                     numeric_value(value),
                                                     type(json::value_type::Number)
{
}

json::primitive_node::primitive_node(int value) : node(),
                                                  string_value(""),
                                                  numeric_value(value),
                                                  type(json::value_type::Number)
{
}

json::primitive_node::primitive_node(bool value) : node(),
                                                   string_value(""),
                                                   numeric_value(0),
                                                   type(value ? json::value_type::True : json::value_type::False)
{
}

json::primitive_node::primitive_node() : node(),
                                         string_value(""),
                                         numeric_value(0),
                                         type(json::value_type::Null)
{
}

json::primitive_node::~primitive_node()
{
}

json::value_type json::primitive_node::get_type() const
{
    return this->type;
}

const std::string &json::primitive_node::get_value_as_string() const
{
    if (this->type != json::value_type::String)
    {
        throw json::value_exception();
    }

    return this->string_value;
}

double json::primitive_node::get_value_as_number() const
{
    if (this->type != json::value_type::Number)
    {
        throw json::value_exception();
    }

    return this->numeric_value;
}

bool json::primitive_node::is_value_null() const
{
    return this->type == json::value_type::Null;
}

bool json::primitive_node::get_value_as_bool() const
{
    if (this->type == json::value_type::True)
        return true;
    else if (this->type == json::value_type::False)
        return false;
    else
        throw json::value_exception();
}

void json::primitive_node::set_value(bool value)
{
    this->clear_values();
    this->type = value ? json::value_type::True : json::value_type::False;
}

void json::primitive_node::set_value_null()
{
    this->clear_values();
    this->type = json::value_type::Null;
}

void json::primitive_node::set_value(const std::string &stringValue)
{
    this->clear_values();
    this->type = json::value_type::String;
    this->string_value.assign(stringValue);
}

void json::primitive_node::set_value(double doubleValue)
{
    this->clear_values();
    this->type = json::value_type::Number;
    this->numeric_value = doubleValue;
}

void json::primitive_node::clear_values()
{
    this->numeric_value = 0;
    this->string_value.clear();
}

std::ostream &json::primitive_node::operator<<(std::ostream &stream) const
{
    switch (this->get_type())
    {
    case json::value_type::String:
        stream << this->string_value;
        break;
    case json::value_type::Number:
        stream << this->numeric_value;
        break;
    case json::value_type::True:
        stream << json::ValueTrue;
        break;
    case json::value_type::False:
        stream << json::ValueFalse;
        break;
    case json::value_type::Null:
        stream << json::ValueNull;
        break;
    case json::value_type::Object:
    case json::value_type::Array:
    default:
        throw std::runtime_error("Invalid case!");
        break;
    }

    return stream;
}

json::formatted_printer &json::primitive_node::print_formatted(json::formatted_printer &p) const
{
    switch (this->get_type())
    {
    case json::value_type::String:
        p.print(this->string_value);
        break;
    case json::value_type::Number:
        p.print(this->numeric_value);
        break;
    case json::value_type::True:
        p.print_true();
        break;
    case json::value_type::False:
        p.print_false();
        break;
    case json::value_type::Null:
        p.print_null();
        break;
    case json::value_type::Object:
    case json::value_type::Array:
    default:
        throw std::runtime_error("Invalid case!");
        break;
    }

    return p;
}