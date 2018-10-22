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

int util::parse_settings(const std::unordered_map<std::string, std::string> &, std::unordered_map<std::string, setting> &)
{
    return 0;
}