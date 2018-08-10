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

json::parser::token_type json::parser::peek_type() const
{
    auto tmp = this->pos;

    return (++tmp)->type;
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
    auto res = this->read_object();

    if (this->has_next())
    {
        throw parser_exception();
    }

    return res;
}

json::node *json::parser::read_value()
{
    auto name = this->read_string();
    this->read_token(token_type::ObjectSeperator);

    auto res = this->read_item();
    res->set_name(name);

    return res;
}

json::node *json::parser::read_object()
{
    this->read_token(token_type::ObjectStart);

    auto res = new object_node();

    if (this->can_read_token(token_type::ObjectEnd))
    {
        return res;
    }

    auto loop = true;

    while (loop)
    {
        res->add_child(this->read_value());

        if (this->can_read_token(token_type::ObjectEnd))
        {
            loop = false;
        }
        else
        {
            this->read_token(token_type::ObjectSeperator);
        }
    }

    this->read_token(token_type::ObjectEnd);

    return res;
}

json::node *json::parser::read_array()
{
    this->read_token(token_type::ArrayStart);

    auto res = new array_node();

    if (this->can_read_token(token_type::ArrayEnd))
    {
        return res;
    }

    auto loop = true;

    while (loop)
    {
        res->add_child(this->read_item());

        if (this->can_read_token(token_type::ArrayEnd))
        {
            loop = false;
        }
        else
        {
            this->read_token(token_type::ObjectSeperator);
        }
    }

    this->read_token(token_type::ArrayEnd);

    return res;
}

json::node *json::parser::read_item()
{
    node *res;

    switch (this->peek_type())
    {
    case token_type::String:
        res = new primitive_node();
        ((primitive_node *)res)->set_value(this->read_string());
        break;
    case token_type::Number:
        res = new primitive_node();
        ((primitive_node *)res)->set_value(this->read_number());
        break;
    case token_type::ValueTrue:
        res = new primitive_node();
        ((primitive_node *)res)->set_value(true);
        break;
    case token_type::ValueFalse:
        res = new primitive_node();
        ((primitive_node *)res)->set_value(false);
        break;
    case token_type::ValueNull:
        res = new primitive_node();
        ((primitive_node *)res)->set_value_null();
        break;
    case token_type::ArrayStart:
        res = this->read_array();
        break;
    case token_type::ObjectStart:
        res = this->read_object();
        break;
    case token_type::ObjectAssignment:
    case token_type::ObjectSeperator:
    case token_type::ObjectEnd:
    case token_type::ArrayEnd:
    default:
        throw parser_exception();
    }

    return res;
}

std::string json::parser::read_string()
{
    auto token = this->read_token(token_type::String);
    auto res = std::string();
    auto escaped = true;

    res.reserve(token.data_len);

    for (int i = 0; i < token.data_len; i++)
    {
        auto c = token.data[i];

        if (escaped)
        {
            switch (c)
            {
            case '\"':
                res.push_back('\"');
                break;
            case '\\':
                res.push_back('\\');
                break;
            case '/':
                res.push_back('/');
                break;
            case 'b':
                res.push_back('\b');
                break;
            case 'f':
                res.push_back('\f');
                break;
            case 'n':
                res.push_back('\n');
                break;
            case 'r':
                res.push_back('\r');
                break;
            case 't':
                res.push_back('\t');
                break;
            case 'u':
            {
                if (token.data_len - i < 4)
                {
                    throw parser_exception();
                }

                auto digits = std::to_string(util::hex4ToNumber(token.data + i + 1));

                for (const char &digit : digits)
                {
                    res.push_back(digit);
                }

                i += 4;

                break;
            }
            default:
                throw parser_exception("illegal escape sequence!");
            }
        }
        else if (c == '\\')
        {
            escaped = true;
        }
        else
        {
            res.push_back(c);
        }
    }

    return res;
}

double json::parser::read_number()
{
    auto token = this->read_token(token_type::Number);

    return std::strtod(token.data, nullptr);
}

json::parser::token json::parser::read_token(json::parser::token_type type)
{
    if (this->pos != this->working_set.end())
        throw json::parser::parser_exception();

    auto current = *this->pos;

    if (current.type != type)
        throw json::parser::parser_exception();

    this->pos++;

    return current;
}

bool json::parser::can_read_token(json::parser::token_type type) const
{
    return this->peek_type() == type;
}