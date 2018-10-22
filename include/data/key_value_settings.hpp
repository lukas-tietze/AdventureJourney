#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

namespace util
{
enum class setting_type
{
    Number,
    String,
    Reference,
};

class setting
{
  private:
    setting_type type;
    std::string name;
    std::string value;
    double parsed_value;

  public:
    setting(const std::string &name, const std::string &value);

    setting_type get_type() const;
    double get_value_as_double() const;
    const std::string &get_value() const;
    const std::string &get_reference_target() const;
    const std::string &get_name() const;
};

int read_settings(std::istream &in, std::unordered_map<std::string, std::string> &);
int parse_settings(const std::unordered_map<std::string, std::string> &, std::unordered_map<std::string, setting> &);
} // namespace util