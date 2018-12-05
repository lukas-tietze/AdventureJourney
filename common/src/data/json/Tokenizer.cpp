#include <cstdlib>
#include <string>
#include <cstring>
#include <stdexcept>

#include "data/String.hpp"
#include "data/Math.hpp"
#include "data/Json.hpp"

json::Tokenizer::Tokenizer() : tokens(),
                               bracketStack(),
                               pos(0),
                               length(0),
                               data(0)
{
}

json::Tokenizer::~Tokenizer()
{
}

bool json::Tokenizer::IsStartOfNumber(char c)
{
    return (c >= '0' && c <= '9') ||
           c == '-' ||
           c == '.';
}

void json::Tokenizer::SkipWhitespace()
{
    while (this->pos < this->length && std::isspace(this->data[this->pos]))
    {
        pos++;
    }
}

void json::Tokenizer::ReadNext()
{
    auto c = this->data[this->pos];

    if (std::isspace(c))
    {
        this->SkipWhitespace();
    }
    else if (c == '"')
    {
        this->ReadString();
    }
    else if (c == '{')
    {
        this->tokens.push_back({TokenType::ObjectStart, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == '[')
    {
        this->tokens.push_back({TokenType::ArrayStart, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == '}')
    {
        this->tokens.push_back({TokenType::ObjectEnd, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == ']')
    {
        this->tokens.push_back({TokenType::ArrayEnd, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == ':')
    {
        this->tokens.push_back({TokenType::ValueAssignment, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == ',')
    {
        this->tokens.push_back({TokenType::ValueSeperator, this->data + this->pos, 1});
        this->pos++;
    }
    else if (this->IsStartOfNumber(c))
    {
        this->ReadNumber();
    }
    else if (this->IsStartOfSpecial(c))
    {
        this->ReadSpecial();
    }
    else
    {
        throw TokenizerException(*this, "Illegal character!");
    }
}

bool json::Tokenizer::CanEscape(char c)
{
    return c == '\"' ||
           c == '\\' ||
           c == '/' ||
           c == 'b' ||
           c == 'f' ||
           c == 'n' ||
           c == 'r' ||
           c == 't' ||
           c == 'u';
}

bool json::Tokenizer::IsStartOfSpecial(char c)
{
    return c == 't' ||
           c == 'f' ||
           c == 'n';
}

void json::Tokenizer::ReadSpecial()
{
    if (this->pos < this->length - 4 && std::strncmp(this->data + this->pos, json::ValueTrue, 4) == 0)
    {
        this->tokens.push_back({TokenType::ValueTrue, this->data + this->pos, 4});
        this->pos += 4;
    }
    else if (this->pos < this->length - 4 && std::strncmp(this->data + this->pos, json::ValueNull, 4) == 0)
    {
        this->tokens.push_back({TokenType::ValueNull, this->data + this->pos, 4});
        this->pos += 4;
    }
    else if (this->pos < this->length - 5 && std::strncmp(this->data + this->pos, json::ValueFalse, 5) == 0)
    {
        this->tokens.push_back({TokenType::ValueFalse, this->data + this->pos, 5});
        this->pos += 5;
    }
    else
    {
        throw TokenizerException(*this, "Unexpected value!");
    }
}

bool json::Tokenizer::IsValidNumberEnd(char c)
{
    return std::isspace(c) || c == '}' || c == ',' || c == ']';
}

void json::Tokenizer::ReadNumber()
{
    constexpr int STATESTART = 0;
    constexpr int STATEMINUS = 1;
    constexpr int STATEFIRSTZERO = 2;
    constexpr int STATEFIRSTDIGITS = 3;
    constexpr int STATESEPERATOR = 4;
    constexpr int STATELASTDIGITS = 5;
    constexpr int STATEEXPONENTSTART = 6;
    constexpr int STATEEXPONENTSIGN = 7;
    constexpr int STATEEXPONENTDIGITS = 8;
    constexpr int STATEEND = 9;

    int state = STATESTART;
    int start = this->pos;

    while (this->pos < this->length && state != STATEEND)
    {
        char c = this->data[this->pos];

        switch (state)
        {
        case STATESTART:
            if (c == '-')
                state = STATEMINUS;
            else if (c == '0')
                state = STATEFIRSTZERO;
            else if (c >= '1' && c <= '9')
                state = STATEFIRSTDIGITS;
            else
                throw TokenizerException(*this, "Illegal number format! Expected - or [0..9].");
            break;
        case STATEMINUS:
            if (c == '0')
                state = STATEFIRSTZERO;
            else if (c >= '1' && c <= '9')
                state = STATEFIRSTDIGITS;
            else
                throw TokenizerException(*this, "Illegal number format! Expected [0..9].");
            break;
        case STATEFIRSTZERO:
            if (c == '.')
                state = STATESEPERATOR;
            else if (c == 'e' || c == 'E')
                state = STATEEXPONENTSTART;
            else if (this->IsValidNumberEnd(c))
                state = STATEEND;
            else
                throw TokenizerException(*this, "Illegal number format! Expected . or e or E or number end.");
            break;
        case STATEFIRSTDIGITS:
            if (c == '.')
                state = STATESEPERATOR;
            else if (c == 'e' || c == 'E')
                state = STATEEXPONENTSTART;
            else if (this->IsValidNumberEnd(c))
                state = STATEEND;
            else if (c < '0' || c > '9')
                throw TokenizerException(*this, "Illegal number format! Expected . or e or E or [0..9] or number end.");
            break;
        case STATESEPERATOR:
            if (c >= '0' && c <= '9')
                state = STATELASTDIGITS;
            else
                throw TokenizerException(*this, "Illegal number format! Expected [0..9].");
            break;
        case STATELASTDIGITS:
            if (c >= '0' && c <= '9')
                state = STATELASTDIGITS;
            else if (c == 'e' || c == 'E')
                state = STATEEXPONENTSTART;
            else if (this->IsValidNumberEnd(c))
                state = STATEEND;
            else
                throw TokenizerException(*this, "Illegal number format! Expected . or e or E or number end.");
            break;
        case STATEEXPONENTSTART:
            if (c == '+' || c == '-')
                state = STATEEXPONENTSIGN;
            else if (c >= '0' && c <= '9')
                state = STATEEXPONENTDIGITS;
            else
                throw TokenizerException(*this, "Illegal number format! Expected + or - or [0..9].");
            break;
        case STATEEXPONENTSIGN:
            if (c >= '0' && c <= '9')
                state = STATEEXPONENTDIGITS;
            else
                throw TokenizerException(*this, "Illegal number format! Expected [0..9].");
            break;
        case STATEEXPONENTDIGITS:
            if (c >= '0' && c <= '9')
                state = STATEEXPONENTDIGITS;
            else if (this->IsValidNumberEnd(c))
                state = STATEEND;
            else
                throw TokenizerException(*this, "Illegal number format! Expected [0..9] or number end.");
            break;
        case STATEEND:
            break;
        default:
            throw util::InvalidCaseException();
        }

        if (state != STATEEND)
        {
            this->pos++;
        }
    }

    Token t;
    t.type = TokenType::Number;
    t.data = this->data + start;
    t.dataLen = this->pos - start;

    this->tokens.push_back(t);
}

void json::Tokenizer::ReadString()
{
    int start = ++this->pos;
    bool escaped = false;

    while (this->pos < this->length)
    {
        char c = this->data[this->pos];

        if (escaped)
        {
            if (!this->CanEscape(c))
            {
                if (!util::IsHexChar(c) ||
                    this->pos + 3 >= this->length ||
                    !util::IsHexChar(this->data[this->pos + 1]) ||
                    !util::IsHexChar(this->data[this->pos + 2]) ||
                    !util::IsHexChar(this->data[this->pos + 3]))
                {
                    throw TokenizerException(*this, "Invalid escape sequence!");
                }
            }

            escaped = false;
        }
        else if (c == '\\')
        {
            escaped = true;
        }
        else if (c == '"')
        {
            break;
        }

        this->pos++;
    }

    Token t;
    t.type = TokenType::String;
    t.data = this->data + start;
    t.dataLen = this->pos - start;

    this->tokens.push_back(t);
    this->pos++;
}

const std::vector<json::Token> &json::Tokenizer::Tokenize(const std::string &data)
{
    return this->Tokenize(data.c_str(), data.length());
}

const std::vector<json::Token> &json::Tokenizer::Tokenize(const char *data, int length)
{
    this->data = data;
    this->length = length;
    this->pos = 0;

    while (this->pos < this->length)
    {
        this->ReadNext();
    }

    return this->tokens;
}

int json::Tokenizer::GetPos() const
{
    return this->pos;
}

const char *json::Tokenizer::GetData() const
{
    return this->data;
}

int json::Tokenizer::GetLength() const
{
    return this->length;
}