#include "json.hpp"

json::primitive_node::primitive_node(const std::string &name) : node(name),
                                                                string_value(""),
                                                                numeric_value(0),
                                                                type(json::value_type::Empty)
{
}

json::primitive_node::primitive_node() : node(),
                                         string_value(""),
                                         numeric_value(0),
                                         type(json::value_type::Empty)
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

const json::node *json::primitive_node::get_value_as_object() const
{
    throw json::value_exception();
}

const std::vector<json::node *> &json::primitive_node::get_value_as_array() const
{
    throw json::value_exception();
}

const json::node *json::primitive_node::find_child(const std::string &name)
{
    throw json::operation_exception();
}

void json::primitive_node::set_value(bool value)
{
    this->clear_values();
    this->type = value ? json::value_type::BoolTrue : json::value_type::BoolFalse;
}

void json::primitive_node::set_value_null()
{
    this->clear_values();
    this->type = json::value_type::Empty;
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
    case json::value_type::BoolTrue:
        stream << "true";
        break;
    case json::value_type::BoolFalse:
        stream << "false";
        break;
    case json::value_type::Empty:
        stream << "null";
        break;
    case json::value_type::Object:
    case json::value_type::Array:
    default:
        throw std::runtime_error("Invalid case!");
    }

    return stream;
}