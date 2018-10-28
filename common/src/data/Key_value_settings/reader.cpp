#include "data/key_value_settings.hpp"

int util::read_settings(std::istream &in, std::unordered_map<std::string, std::string> &target)
{
    if (!in.good())
    {
        return -1;
    }

    std::string name;
    std::string value;
    bool nameRead = false;

    while (!in.eof())
    {
        char c;
        in.read(&c, 1);

        if (c == '=')
        {
            nameRead = true;
        }
        else if (c == ';')
        {
            target.insert(std::make_pair(name, value));
            name.clear();
            value.clear();
        }
        else if (nameRead)
        {
            value.push_back(c);
        }
        else
        {
            name.push_back(c);
        }
    }
}

int util::parse_settings(const std::unordered_map<std::string, std::string> &raw, std::unordered_map<std::string, setting> &target)
{
    for (const auto &kvp : raw)
    {
        char *end;
        double res = std::strtod(kvp.second.c_str(), &end);

        if (end - kvp.second.c_str() == kvp.second.length())
        {
            target.insert(std::make_pair(kvp.first, setting(kvp.first, res)));
        }
        else if (kvp.second.front() == '@' && raw.find(kvp.second.substr(1)) != raw.end())
        {
            target.insert(std::make_pair(kvp.first, setting(kvp.first, setting_type::Reference, kvp.second.substr(1))));
        }
        else
        {
            target.insert(std::make_pair(kvp.first, setting(kvp.first, setting_type::String, kvp.second)));
        }
    }

    return 0;
}