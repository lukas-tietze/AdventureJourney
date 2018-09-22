#include "data/key_value_settings.hpp"

util::setting::setting(const std::string &name, const std::string &value) : name(name),
                                                                            value(value)
{
}

util::setting_type util::setting::get_type() const
{
    return this->type;
}

double util::setting::get_value_as_double() const
{
    return this->parsed_value;
}

const std::string &util::setting::get_value() const
{
    return this->value;
}

const std::string &util::setting::get_reference_target() const
{
    return this->value;
}

const std::string &util::setting::get_name() const
{
    return this->name;
}