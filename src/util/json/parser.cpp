#include "util/json/json.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

json::parser::parser()
{
}

json::parser::~parser()
{}

json::node json::parser::parse(const std::string &data)
{
    auto len = data.length;
    auto buf = new char[len];

    std::memcpy(buf, data.data(), len);

    parser::tokenizer tokenizer();
    auto tokens = tokenizer.tokenize(buf, len);

    return this->parse(tokens);
}