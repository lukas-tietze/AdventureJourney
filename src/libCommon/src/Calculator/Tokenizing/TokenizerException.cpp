#include "Internal.hpp"

calculator::tokenizing::TokenizerException::TokenizerException(TokenizerError what, Tokenizer *t)
{
    switch (what)
    {
    case calculator::tokenizing::TokenizerError::MissingBracket:
        break;
    case calculator::tokenizing::TokenizerError::ExtraClosingBracket:
        break;
    case calculator::tokenizing::TokenizerError::MismatchingBracket:
        break;
    case calculator::tokenizing::TokenizerError::InvalidChar:
        break;
    case calculator::tokenizing::TokenizerError::UnexpectedEndOfLazyExpression:
        break;
    case calculator::tokenizing::TokenizerError::UnexpectedEndOfStringExpression:
        break;
    default:
        break;
    }
}