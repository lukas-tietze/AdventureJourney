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

    t.close();

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

        t.close();
    }
    catch (...)
    {
        return false;
    }

    return true;
}

void util::write_file(const std::string &file, const std::string &data)
{
    std::ofstream t(file);

    if (!t.good())
    {
        throw file_not_found_exception(file);
    }

    t << data;
    t.close();
}

bool util::try_write_file(const std::string &file, const std::string &data)
{
    try
    {
        std::ofstream t(file);

        if (!t.good())
        {
            return false;
        }

        t << data;
        t.close();
    }
    catch (...)
    {
        return false;
    }

    return true;
}