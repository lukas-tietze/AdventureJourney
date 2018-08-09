#include "json.hpp"

json::value_node::value_node(const std::string &name) : node(name),
                                                        string_value(""),
                                                        numeric_value(0),
                                                        type(json::value_type::Empty)
{
}

json::value_node::~value_node()
{
}

json::value_type json::value_node::get_type() const
{
    return this->type;
}

const std::string &json::value_node::get_value_as_string() const
{
    if (this->type != json::value_type::String)
    {
        throw json::value_exception();
    }

    return this->string_value;
}

double json::value_node::get_value_as_number() const
{
    if (this->type != json::value_type::Number)
    {
        throw json::value_exception();
    }

    return this->numeric_value;
}

const json::node *json::value_node::get_value_as_object() const
{
    throw json::value_exception();
}

const std::vector<json::node *> &json::value_node::get_value_as_array() const
{
    throw json::value_exception();
}

const json::node *json::value_node::find_child(const std::string &name)
{
    throw json::operation_exception();
}

void json::value_node::set_value(bool value)
{
    this->clear_values();
    this->type = value ? json::value_type::BoolTrue : json::value_type::BoolFalse;
}

void json::value_node::set_value_null()
{
    this->clear_values();
    this->type = json::value_type::Empty;
}

void json::value_node::set_value(const std::string &stringValue)
{
    this->clear_values();
    this->type = json::value_type::String;
    this->string_value.assign(stringValue);
}

void json::value_node::set_value(double doubleValue)
{
    this->clear_values();
    this->type = json::value_type::Number;
    this->numeric_value = doubleValue;
}

void json::value_node::set_value(node *nodeValue)
{
    this->clear_values();
    this->type = json::value_type::Object;
    this->object_value = nodeValue;
}

void json::value_node::clear_values()
{
    this->numeric_value = 0;
    this->string_value.clear();
    this->object_value = nullptr;
}
