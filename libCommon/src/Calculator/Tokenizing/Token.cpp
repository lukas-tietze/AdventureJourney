#include "Calculator.hpp"

calculator::tokenizing::Token::Token() : type(),
                                   value()
{
}

calculator::tokenizing::Token::Token(TokenType type) : type(type),
                                                 value()
{
}

calculator::tokenizing::Token::Token(TokenType type, const std::string &value) : type(type),
                                                                           value(value)
{
}

calculator::tokenizing::TokenType calculator::tokenizing::Token::GetType() const
{
    return this->type;
}

const std::string &calculator::tokenizing::Token::GetValue() const
{
    return this->value;
}
