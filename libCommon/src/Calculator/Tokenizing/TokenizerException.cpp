#include "Calculator.hpp"

util::tokenizing::TokenizerException::TokenizerException(TokenizerError what, Tokenizer *t)
{
    switch (what)
    {
    case util::tokenizing::TokenizerError::MissingBracket:
        break;
    case util::tokenizing::TokenizerError::ExtraClosingBracket:
        break;
    case util::tokenizing::TokenizerError::MismatchingBracket:
        break;
    case util::tokenizing::TokenizerError::InvalidChar:
        break;
    case util::tokenizing::TokenizerError::UnexpectedEndOfLazyExpression:
        break;
    case util::tokenizing::TokenizerError::UnexpectedEndOfStringExpression:
        break;
    default:
        break;
    }
}