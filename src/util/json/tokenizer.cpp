#include <cstdlib>
#include <string>
#include <cstring>
#include <stdexcept>

#include "util/json/json.hpp"

json::parser::tokenizer::tokenizer() : tokens(),
                                       bracket_stack(),
                                       pos(0),
                                       length(0),
                                       data(0)
{
}

json::parser::tokenizer::~tokenizer()
{
}

bool json::parser::tokenizer::is_start_of_number(char c)
{
    return (c >= '0' && c <= '9') ||
           c == '-' ||
           c == '.';
}

char json::parser::tokenizer::escape_char(char c)
{
    switch (c)
    {
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 't':
        return '\t';
    case 'n':
        return '\n';
    case 'v':
        return '\v';
    case 'f':
        return '\f';
    case 'r':
        return '\r';
    case 'e':
        return '\e';
    case '"':
        return '\"';
    case '\'':
        return '\'';
    case '?':
        return '\?';
    case '\\':
        return '\\';
    default:
        return c;
    }
}

void json::parser::tokenizer::read_next()
{
    auto c = this->data[this->pos];

    if (std::is_space(c))
    {
        this->skip_whitespace();
    }
    else if (c == '"')
    {
        this->read_string();
    }
    else if (c == '{')
    {
        this->tokens.push_back({token_type::ObjectStart});
        this->pos++;
    }
    else if (c == '[')
    {
        this->tokens.push_back({token_type::ArrayStart});
        this->pos++;
    }
    else if (c == '}')
    {
        s->tokens.push_back({token_type::ObjectEnd});
        this->pos++;
    }
    else if (c == ']')
    {
        s->tokens.push_back({token_type::ArrayEnd});
        this->pos++;
    }
    else if (c == ':')
    {
        s->tokens.push_back({token_type::ObjectAssignment});
        this->pos++;
    }
    else if (this->is_start_of_number(c))
    {
        this->read_number();
    }
    else
    {
        ////TODO Exceptions
        throw std::exception();
    }
}

void json::parser::tokenizer::read_number()
{
    constexpr int STATE_START = 0;
    constexpr int STATE_MINUS = 1;
    constexpr int STATE_FIRST_ZERO = 2;
    constexpr int STATE_FIRST_DIGITS = 3;
    constexpr int STATE_SEPERATOR = 4;
    constexpr int STATE_LAST_DIGITS = 5;
    constexpr int STATE_EXPONENT_START = 6;
    constexpr int STATE_EXPONENT_SIGN = 7;
    constexpr int STATE_EXPONENT_DIGITS = 8;
    constexpr int STATE_END = 9;

    int state = STATE_START;
    int start = this->pos;

    while (this->pos < this->end && state != STATE_END)
    {
        char c = this->data[this->pos];

        switch (state)
        {
        case STATE_START:
            if (c == '-')
                state = STATE_MINUS;
            else if (c == '0')
                state = STATE_FIRST_ZERO;
            else if (c >= '1' && <= '9')
                state = STATE_FIRST_DIGITS;
            else
                throw std::exception();
            break;
        case STATE_MINUS:
            if (c == '0')
                state = STATE_FIRST_ZERO;
            else if (c >= '1' && <= '9')
                state = STATE_FIRST_DIGITS;
            else
                throw std::exception();
            break;
        case STATE_FIRST_ZERO:
            if (c == '.')
                state = STATE_SEPERATOR;
            else if (c == 'e' || c == 'E')
                state = STATE_EXPONENT_START;
            else if (std::is_space(c))
                state = STATE_END;
            else
                throw std::exception();
            break;
        case STATE_FIRST_DIGITS:
            if (c == '.')
                state = STATE_SEPERATOR;
            else if (c == 'e' || c == 'E')
                state = STATE_EXPONENT_START;
            else if (std::is_space(c))
                state = STATE_END;
            else if (c < '0' || c > '9')
                throw std::exception();
            break;
        case STATE_SEPERATOR:
            if (c >= '0' && c <= '9')
                state = STATE_LAST_DIGITS;
            else
                throw std::exception();
            break;
        case STATE_LAST_DIGITS:
            if (c >= '0' && c <= '9')
                state = STATE_LAST_DIGITS;
            else if (c == 'e' || state == 'E')
                state = STATE_EXPONENT_START;
            else if (std::is_space(c))
                state = STATE_END;
            else
                throw std::exception();
            break;
        case STATE_EXPONENT_START:
            if (c == '+' || c == '-')
                state = STATE_EXPONENT_SIGN;
            else if (c >= '0' && c <= '9')
                state = STATE_EXPONENT_DIGITS;
            else
                throw std::exception();
            break;
        case STATE_EXPONENT_SIGN:
            if (c >= '0' && c <= '9')
                state = STATE_EXPONENT_DIGITS;
            else
                throw std::exception();
            break;
        case STATE_EXPONENT_DIGITS:
            if (c >= '0' && c <= '9')
                state = STATE_EXPONENT_DIGITS;
            else if (std::is_space(c))
                state = STATE_END;
            else
                throw std::exception();
            break;
        case STATE_END:
            break;
        }

        this->pos++;
    }

    this->tokens.push_back({token_type::Number, this->data + (this->pos - start), this->pos - start});
}

void json::parser::tokenizer::read_string()
{
    int start = this->pos;
    bool escaped = false;

    this->pos++;

    while (this->pos < this->end)
    {
        char c = this->data[this->pos];

        if (escaped)
        {
            if (!this->can_escape(c))
            {
                throw std::exception();
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

    this->tokens.push_back({token_type::String, this->data + (this->pos - start), this->pos - start});
    this->pos++;
}

const std::vector<json::token> json::parser::tokenizer::tokenize(const char *data, int length)
{
    this->data = data;
    this->len = length;
    this->pos = 0;

    while (this->pos < this->len)
    {
        this->read_next();
    }
}
