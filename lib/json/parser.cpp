#include "json.hpp"

#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

json::parser::parser()
{
}

json::parser::~parser()
{
}

void json::parser::parse(const std::string &data, json::node **target)
{
    auto len = data.length();
    auto buf = new char[len];

    std::memcpy(buf, data.data(), len);

    json::parser::tokenizer t;
    const auto &tokens = t.tokenize(buf, len);

    *target = this->parse(tokens);
}

bool json::parser::has_next() const
{
    return this->pos != this->working_set.end();
}

json::parser::token json::parser::next()
{
    return *++this->pos;
}

json::parser::token json::parser::peek() const
{
    auto tmp = this->pos;

    return *++tmp;
}

json::node *json::parser::parse(const std::vector<token> &tokens)
{
    this->working_set = tokens;
    this->pos = this->working_set.begin();
    std::stack<json::node *>().swap(this->nodeStack);

    return this->read_start();
}

json::node *json::parser::read_start()
{
}

json::node *json::parser::read_value()
{
}

json::node *json::parser::read_object()
{
}

json::node *json::parser::read_array()
{
}

std::string json::parser::read_string()
{
}

double json::parser::read_double()
{ 
}

json::parser::token json::parser::read_token(json::parser::token_type type)
{
    if (!this->has_next())
        throw json::parser::parser_exception();

    auto next = this->next();

    if (next.type != type)
        throw json::parser::parser_exception();

    return next;
}

bool json::parser::can_read_token(json::parser::token_type type) const
{
    return this->peek().type == type;
}