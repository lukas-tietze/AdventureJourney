#include "json.hpp"

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

void json::parser::parse(const std::string &data, json::node **target)
{
    auto len = data.length();
    auto buf = new char[len];

    std::memcpy(buf, data.data(), len);

    json::parser::tokenizer t;
    auto tokens = t.tokenize(buf, len);

    // (&target) = this->parse(tokens);
}