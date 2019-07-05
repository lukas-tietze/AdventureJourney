#include "Calculator.hpp"
#include "data/EnumHelper.hpp"

std::ostream &util::tokenizing::operator<<(std::ostream &s, util::tokenizing::TokenType v)
{
    switch (v)
    {
    case util::tokenizing::TokenType::String:
        s << "String";
        break;
    case util::tokenizing::TokenType::Number:
        s << "Number";
        break;
    case util::tokenizing::TokenType::Identifier:
        s << "Identifier";
        break;
    case util::tokenizing::TokenType::Seperator:
        s << "Seperator";
        break;
    case util::tokenizing::TokenType::OpeningBracket:
        s << "OpeningBracket";
        break;
    case util::tokenizing::TokenType::ClosingBracket:
        s << "ClosingBracket";
        break;
    case util::tokenizing::TokenType::SetStart:
        s << "SetStart";
        break;
    case util::tokenizing::TokenType::SetEnd:
        s << "SetEnd";
        break;
    case util::tokenizing::TokenType::AccessorStart:
        s << "AccessorStart";
        break;
    case util::tokenizing::TokenType::AccessorEnd:
        s << "AccessorEnd";
        break;
    case util::tokenizing::TokenType::FunctionStart:
        s << "FunctionStart";
        break;
    case util::tokenizing::TokenType::FunctionEnd:
        s << "FunctionEnd";
        break;
    case util::tokenizing::TokenType::LazyEvalSeperator:
        s << "LazyEvalSeperator";
        break;
    case util::tokenizing::TokenType::Operator:
        s << "Operator";
        break;
    default:
        throw InvalidCaseException::MakeException(v);
        break;
    }

    return s;
}

template <>
const std::initializer_list<util::tokenizing::TokenType> &util::ListValues<util::tokenizing::TokenType>()
{
    static const std::initializer_list<util::tokenizing::TokenType> list = {
        util::tokenizing::TokenType::String,
        util::tokenizing::TokenType::Number,
        util::tokenizing::TokenType::Identifier,
        util::tokenizing::TokenType::Seperator,
        util::tokenizing::TokenType::OpeningBracket,
        util::tokenizing::TokenType::ClosingBracket,
        util::tokenizing::TokenType::SetStart,
        util::tokenizing::TokenType::SetEnd,
        util::tokenizing::TokenType::AccessorStart,
        util::tokenizing::TokenType::AccessorEnd,
        util::tokenizing::TokenType::FunctionStart,
        util::tokenizing::TokenType::FunctionEnd,
        util::tokenizing::TokenType::LazyEvalSeperator,
        util::tokenizing::TokenType::Operator,
    };

    return list;
}