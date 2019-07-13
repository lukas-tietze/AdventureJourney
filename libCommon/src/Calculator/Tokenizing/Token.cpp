#include "Internal.hpp"

calculator::tokenizing::Token::Token() : type(),
                                         start(0),
                                         len(0)
{
}

calculator::tokenizing::Token::Token(TokenType type) : type(type),
                                                       start(0),
                                                       len(0)
{
}

calculator::tokenizing::Token::Token(TokenType type, int start, int len) : type(type),
                                                                           start(start),
                                                                           len(len)
{
}
