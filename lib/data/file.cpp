#include <string>
#include <fstream>
#include <streambuf>

#include "data.hpp"

std::string util::read_file(const std::string &file)
{
    std::ifstream t(file);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    return std::string();
}