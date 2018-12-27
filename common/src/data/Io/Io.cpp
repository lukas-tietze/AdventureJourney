#include <string>
#include <fstream>
#include <streambuf>

#include "data/Io.hpp"
#include "Exception.hpp"

std::string util::ReadFile(const std::string &file)
{
    std::ifstream t(file);
    std::string str;

    if (!t.good())
    {
        throw util::FileNotFoundException(file);
    }

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    t.close();

    return str;
}

bool util::TryReadFile(const std::string &file, std::string &buf)
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

void util::WriteFile(const std::string &file, const std::string &data)
{
    std::ofstream t(file);

    if (!t.good())
    {
        throw FileNotFoundException(file);
    }

    t << data;
    t.close();
}

bool util::TryWriteFile(const std::string &file, const std::string &data)
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