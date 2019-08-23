#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "data/Json.hpp"
#include "data/Math.hpp"
#include "data/String.hpp"

json::Parser::Parser()
{
}

json::Parser::~Parser()
{
}

void json::Parser::parse(const std::string &data, json::Node *&target)
{
    std::allocator<char> allocator;
    auto len = data.length();
    auto buf = allocator.allocate(len);

    std::memcpy(buf, data.c_str(), len * sizeof(char));

    json::Tokenizer t;
    const auto &tokens = t.Tokenize(buf, len);

    target = this->Parse(tokens);

    allocator.deallocate(buf, len);
}

json::Node *json::Parser::Parse(const std::vector<Token> &tokens)
{
    this->workingSet = tokens;
    this->pos = this->workingSet.begin();

    return this->ReadStart();
}

json::Node *json::Parser::ReadStart()
{
    auto res = this->ReadObject();

    if (this->HasNext())
    {
        throw ParserException();
    }

    return res;
}

json::Node *json::Parser::ReadObject()
{
    this->ReadToken(TokenType::ObjectStart);

    auto res = new ObjectNode();

    if (this->PeekType() == TokenType::ObjectEnd)
    {
        return res;
    }

    auto loop = true;

    while (loop)
    {
        auto name = this->ReadString();
        this->ReadToken(TokenType::ValueAssignment);

        res->Put(name, this->ReadItem());

        if (this->PeekType() == TokenType::ObjectEnd)
        {
            loop = false;
        }
        else
        {
            this->ReadToken(TokenType::ValueSeperator);
        }
    }

    this->ReadToken(TokenType::ObjectEnd);

    return res;
}

json::Node *json::Parser::ReadArray()
{
    this->ReadToken(TokenType::ArrayStart);

    auto res = new ArrayNode();

    if (this->PeekType() == TokenType::ArrayEnd)
    {
        return res;
    }

    auto loop = true;

    while (loop)
    {
        res->Put(this->ReadItem());

        if (this->PeekType() == TokenType::ArrayEnd)
        {
            loop = false;
        }
        else
        {
            this->ReadToken(TokenType::ValueSeperator);
        }
    }

    this->ReadToken(TokenType::ArrayEnd);

    return res;
}

json::Node *json::Parser::ReadItem()
{
    Node *res;

    switch (this->PeekType())
    {
    case TokenType::String:
        res = new PrimitiveNode();
        ((PrimitiveNode *)res)->SetValue(this->ReadString());
        break;
    case TokenType::Number:
        res = new PrimitiveNode();
        ((PrimitiveNode *)res)->SetValue(this->ReadNumber());
        break;
    case TokenType::ValueTrue:
        this->ReadToken(TokenType::ValueTrue);
        res = new PrimitiveNode();
        ((PrimitiveNode *)res)->SetValue(true);
        break;
    case TokenType::ValueFalse:
        this->ReadToken(TokenType::ValueFalse);
        res = new PrimitiveNode();
        ((PrimitiveNode *)res)->SetValue(false);
        break;
    case TokenType::ValueNull:
        this->ReadToken(TokenType::ValueNull);
        res = new PrimitiveNode();
        ((PrimitiveNode *)res)->SetValueNull();
        break;
    case TokenType::ArrayStart:
        res = this->ReadArray();
        break;
    case TokenType::ObjectStart:
        res = this->ReadObject();
        break;
    case TokenType::ValueAssignment:
    case TokenType::ValueSeperator:
    case TokenType::ObjectEnd:
    case TokenType::ArrayEnd:
    default:
        throw ParserException();
    }

    return res;
}

std::string json::Parser::ReadString()
{
    auto token = this->ReadToken(TokenType::String);
    auto escaped = false;
    std::string res;

    res.reserve(token.dataLen);

    for (int i = 0; i < token.dataLen; i++)
    {
        auto c = token.data[i];

        if (escaped)
        {
            escaped = false;

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
                if (token.dataLen - i < 4)
                {
                    throw ParserException();
                }

                res.append(util::UtfCodePointToNarrowString(util::Hex4ToNumber(token.data + i + 1)));

                i += 4;

                break;
            }
            default:
                throw ParserException("illegal escape sequence '" + std::to_string(c) + "'!");
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

double json::Parser::ReadNumber()
{
    auto Token = this->ReadToken(TokenType::Number);

    return std::strtod(Token.data, nullptr);
}

json::Token json::Parser::ReadToken(json::TokenType type)
{
    if (this->pos == this->workingSet.end())
        throw json::ParserException();

    auto current = *this->pos;

    if (current.type != type)
        throw json::ParserException();

    this->pos++;

    return current;
}

bool json::Parser::HasNext() const
{
    return this->pos != this->workingSet.end();
}

json::TokenType json::Parser::PeekType() const
{
    return this->pos->type;
}