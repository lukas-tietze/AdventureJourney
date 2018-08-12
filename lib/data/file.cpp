#include <string>
#include <fstream>
#include <streambuf>

#include "data.hpp"

std::string util::read_file(const std::string &file)
{
    std::ifstream t(file);
    std::string str;

    if (!t.good())
    {
        throw file_not_found_exception(file);
    }

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    return str;
}

bool util::try_read_file(const std::string &file, std::string &buf)
{
    try
    {
        std::ifstream t(file);

        if (!t.good())
        {
            return false;
        }
        t.seekg(0, std::ios::end);
        buf.clear();
        buf.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        buf.assign((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());
    }
    catch (...)
    {
        return false;
    }

    return true;
}