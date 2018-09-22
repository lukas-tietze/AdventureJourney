#include "data/key_value_settings.hpp"

int read_settings(std::istream &in, std::unordered_map<std::string, util::setting> &target)
{
    if (!in.good())
    {
    }

    std::string name;
    std::string value;
    bool readingValue = true;

    while (!in.eof())
    {
        char c;
        in.read(&c, 1);

        if(c == '=')
        {

        }
        else if(c == ';')
        {
            
        }
    }
}