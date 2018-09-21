#include "data/json.hpp"
#include "exception.hpp"
#include "data/string.hpp"

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

bool json::primitive_node::try_get_value_as_string(std::string &s) const
{
    if (this->get_type() == json::value_type::String)
    {
        s.assign(this->string_value);
        return true;
    }
    else
    {
        return false;
    }
}

bool json::primitive_node::try_get_value_as_number(double &d) const
{
    if (this->get_type() == json::value_type::Number)
    {
        d = this->numeric_value;
        return true;
    }
    else
    {
        return false;
    }
}

bool json::primitive_node::try_get_value_as_bool(bool &b) const
{
    if (this->get_type() == json::value_type::True)
    {
        b = true;
        return true;
    }
    else if (this->get_type() == json::value_type::False)
    {
        b = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool json::primitive_node::try_get_value_as_string_or_default(std::string &target, const std::string &defaultValue) const
{
    auto res = this->try_get_value_as_string(target);

    if (!res)
        target = defaultValue;

    return res;
}

bool json::primitive_node::try_get_value_as_number_or_default(double &target, double defaultValue) const
{
    auto res = this->try_get_value_as_number(target);

    if (!res)
        target = defaultValue;

    return res;
}

bool json::primitive_node::try_get_value_as_bool_or_default(bool &target, bool defaultValue) const
{
    auto res = this->try_get_value_as_bool(target);

    if (!res)
        target = defaultValue;

    return res;
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

bool json::primitive_node::operator==(const json::node &other) const
{
    if (auto primitiveNode = dynamic_cast<const json::primitive_node *>(&other))
    {
        if (this->type == primitiveNode->type)
        {
            switch (this->type)
            {
            case json::value_type::String:
                return this->string_value == primitiveNode->string_value;
            case json::value_type::Number:
                return this->numeric_value == primitiveNode->numeric_value;
            case json::value_type::True:
            case json::value_type::False:
            case json::value_type::Null:
                return true;
            case json::value_type::Object:
            case json::value_type::Array:
                throw util::invalid_case_exception(util::to_string(this->type), "Illegal state");
            default:
                throw util::invalid_case_exception(util::to_string(this->type), "Unknown case");
            }
        }

        return false;
    }

    return false;
}

bool json::primitive_node::operator!=(const json::node &other) const
{
    return !((*this) == other);
}