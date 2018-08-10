#include <cstdlib>
#include <string>
#include <cstring>
#include <stdexcept>

#include "json.hpp"

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

void json::parser::tokenizer::skip_whitespace()
{
    while (this->pos < this->length && std::isspace(this->data[this->pos]))
    {
        pos++;
    }
}

void json::parser::tokenizer::read_next()
{
    auto c = this->data[this->pos];

    if (std::isspace(c))
    {
        this->skip_whitespace();
    }
    else if (c == '"')
    {
        this->read_string();
    }
    else if (c == '{')
    {
        this->tokens.push_back({token_type::ObjectStart, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == '[')
    {
        this->tokens.push_back({token_type::ArrayStart, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == '}')
    {
        this->tokens.push_back({token_type::ObjectEnd, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == ']')
    {
        this->tokens.push_back({token_type::ArrayEnd, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == ':')
    {
        this->tokens.push_back({token_type::ObjectAssignment, this->data + this->pos, 1});
        this->pos++;
    }
    else if (c == ',')
    {
        this->tokens.push_back({token_type::ObjectSeperator, this->data + this->pos, 1});
    }
    else if (this->is_start_of_number(c))
    {
        this->read_number();
    }
    else if (this->is_start_of_special(c))
    {
        this->read_special();
    }
    else
    {
        ////TODO Exceptions
        throw std::exception();
    }
}

bool json::parser::tokenizer::can_escape(char c)
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

bool json::parser::tokenizer::is_start_of_special(char c)
{
    return c == 't' ||
           c == 'f' ||
           c == 'n';
}

void json::parser::tokenizer::read_special()
{
    if (this->pos < this->length - 4 && std::strncmp(this->data + this->pos, "true", 4) == 0)
    {
        this->tokens.push_back({token_type::ValueTrue, this->data + this->pos, 4});
        this->pos += 4;
    }
    else if (this->pos < this->length - 4 && std::strncmp(this->data + this->pos, "null", 4) == 0)
    {
        this->tokens.push_back({token_type::ValueNull, this->data + this->pos, 4});
        this->pos += 4;
    }
    else if (this->pos < this->length - 5 && std::strncmp(this->data + this->pos, "false", 5) == 0)
    {
        this->tokens.push_back({token_type::ValueFalse, this->data + this->pos, 5});
        this->pos += 5;
    }
    else
    {
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

    while (this->pos < this->length && state != STATE_END)
    {
        char c = this->data[this->pos];

        switch (state)
        {
        case STATE_START:
            if (c == '-')
                state = STATE_MINUS;
            else if (c == '0')
                state = STATE_FIRST_ZERO;
            else if (c >= '1' && c <= '9')
                state = STATE_FIRST_DIGITS;
            else
                throw std::exception();
            break;
        case STATE_MINUS:
            if (c == '0')
                state = STATE_FIRST_ZERO;
            else if (c >= '1' && c <= '9')
                state = STATE_FIRST_DIGITS;
            else
                throw std::exception();
            break;
        case STATE_FIRST_ZERO:
            if (c == '.')
                state = STATE_SEPERATOR;
            else if (c == 'e' || c == 'E')
                state = STATE_EXPONENT_START;
            else if (std::isspace(c))
                state = STATE_END;
            else
                throw std::exception();
            break;
        case STATE_FIRST_DIGITS:
            if (c == '.')
                state = STATE_SEPERATOR;
            else if (c == 'e' || c == 'E')
                state = STATE_EXPONENT_START;
            else if (std::isspace(c))
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
            else if (std::isspace(c))
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
            else if (std::isspace(c))
                state = STATE_END;
            else
                throw std::exception();
            break;
        case STATE_END:
            break;
        default:
            throw std::runtime_error("Illegal case!");
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

    while (this->pos < this->length)
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

    json::parser::token t = {token_type::String, this->data + (this->pos - start), this->pos - start};
    this->tokens.push_back(t);
    this->pos++;
}

const std::vector<json::parser::token> &json::parser::tokenizer::tokenize(const char *data, int length)
{
    this->data = data;
    this->length = length;
    this->pos = 0;

    while (this->pos < this->length)
    {
        this->read_next();
    }
    
    return this->tokens;
}
