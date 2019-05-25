#include "Calculator.hpp"

util::tokenizing::Token::Token() : type(0),
                                   value()
{
}

util::tokenizing::Token::Token(TokenType type) : type(type),
                                                 value()
{
}

util::tokenizing::Token::Token(TokenType type, const std::string &value) : type(type),
                                                                           value(value)
{
}

util::tokenizing::TokenType util::tokenizing::Token::GetType() const
{
    return this->type;
}

const std::string &util::tokenizing::Token::GetValue() const
{
    return this->value;
}
