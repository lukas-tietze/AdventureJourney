#include "data/key_value_settings.hpp"

util::setting::setting(const std::string &name, setting_type type, const std::string &value) : name(name),
                                                                                               type(type),
                                                                                               value(value)
{
}

util::setting::setting(const std::string &name, double value) : name(name),
                                                                type(setting_type::Number),
                                                                parsed_value(value)
{
}

util::setting::setting(const util::setting &copy) : name(copy.name),
                                                    type(copy.type),
                                                    value(copy.value),
                                                    parsed_value(copy.parsed_value)
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