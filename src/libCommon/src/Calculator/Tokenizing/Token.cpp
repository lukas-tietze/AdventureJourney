#include "Internal.hpp"

calculator::tokenizing::Token::Token() : type(),
                                         start(nullptr),
                                         len(0)
{
}

calculator::tokenizing::Token::Token(TokenType type) : type(type),
                                                       start(nullptr),
                                                       len(0)
{
}

calculator::tokenizing::Token::Token(TokenType type, const char *start, int len) : type(type),
                                                                                   start(start),
                                                                                   len(len)
{
}

std::ostream &calculator::tokenizing::operator<<(std::ostream &s, const calculator::tokenizing::Token &t)
{
    s << '(' << t.type << ':' << std::string(t.start, t.len) << ')';

    return s;
}