#include "Internal.hpp"
#include "libCommon/data/EnumHelper.hpp"

std::ostream &calculator::tokenizing::operator<<(std::ostream &s, calculator::tokenizing::TokenType v)
{
    switch (v)
    {
    case calculator::tokenizing::TokenType::String:
        s << "String";
        break;
    case calculator::tokenizing::TokenType::Number:
        s << "Number";
        break;
    case calculator::tokenizing::TokenType::Identifier:
        s << "Identifier";
        break;
    case calculator::tokenizing::TokenType::Seperator:
        s << "Seperator";
        break;
    case calculator::tokenizing::TokenType::OpeningBracket:
        s << "OpeningBracket";
        break;
    case calculator::tokenizing::TokenType::ClosingBracket:
        s << "ClosingBracket";
        break;
    case calculator::tokenizing::TokenType::SetStart:
        s << "SetStart";
        break;
    case calculator::tokenizing::TokenType::SetEnd:
        s << "SetEnd";
        break;
    case calculator::tokenizing::TokenType::AccessorStart:
        s << "AccessorStart";
        break;
    case calculator::tokenizing::TokenType::AccessorEnd:
        s << "AccessorEnd";
        break;
    case calculator::tokenizing::TokenType::FunctionStart:
        s << "FunctionStart";
        break;
    case calculator::tokenizing::TokenType::FunctionEnd:
        s << "FunctionEnd";
        break;
    case calculator::tokenizing::TokenType::LazyEvalSeperator:
        s << "LazyEvalSeperator";
        break;
    case calculator::tokenizing::TokenType::Operator:
        s << "Operator";
        break;
    case calculator::tokenizing::TokenType::OperatorAdd:
        s << "op +";
        break;
    case calculator::tokenizing::TokenType::OperatorAddEq:
        s << "op +=";
        break;
    case calculator::tokenizing::TokenType::OperatorSub:
        s << "op -";
        break;
    case calculator::tokenizing::TokenType::OperatorSubEq:
        s << "op -=";
        break;
    case calculator::tokenizing::TokenType::OperatorMul:
        s << "op *";
        break;
    case calculator::tokenizing::TokenType::OperatorMulEq:
        s << "op *=";
        break;
    case calculator::tokenizing::TokenType::OperatorDiv:
        s << "op /";
        break;
    case calculator::tokenizing::TokenType::OperatorDivEq:
        s << "op /=";
        break;
    case calculator::tokenizing::TokenType::OperatorEq:
        s << "op =";
        break;
    case calculator::tokenizing::TokenType::OperatorNot:
        s << "op !";
        break;
    case calculator::tokenizing::TokenType::OperatorEqEq:
        s << "op ==";
        break;
    case calculator::tokenizing::TokenType::OperatorNotEq:
        s << "op !=";
        break;
    case calculator::tokenizing::TokenType::OperatorNotNot:
        s << "op !!";
        break;
    case calculator::tokenizing::TokenType::OperatorEqEqEq:
        s << "op ===";
        break;
    case calculator::tokenizing::TokenType::OperatorNotEqEq:
        s << "op !==";
        break;
    case calculator::tokenizing::TokenType::OperatorGt:
        s << "op >";
        break;
    case calculator::tokenizing::TokenType::OperatorGtEq:
        s << "op >=";
        break;
    case calculator::tokenizing::TokenType::OperatorGtGt:
        s << "op >>";
        break;
    case calculator::tokenizing::TokenType::OperatorGtGtEq:
        s << "op >>=";
        break;
    case calculator::tokenizing::TokenType::OperatorLs:
        s << "op <";
        break;
    case calculator::tokenizing::TokenType::OperatorLsEq:
        s << "op <=";
        break;
    case calculator::tokenizing::TokenType::OperatorLsLs:
        s << "op <<";
        break;
    case calculator::tokenizing::TokenType::OperatorLsLsEq:
        s << "op <<=";
        break;
    case calculator::tokenizing::TokenType::OperatorNeq:
        s << "op <>";
        break;
    case calculator::tokenizing::TokenType::OperatorQe:
        s << "op ?";
        break;
    case calculator::tokenizing::TokenType::OperatorQeQe:
        s << "op ??";
        break;
    default:
        throw util::InvalidCaseException::MakeException(v);
        break;
    }

    return s;
}

template <>
const std::initializer_list<calculator::tokenizing::TokenType> &util::ListValues<calculator::tokenizing::TokenType>()
{
    static const std::initializer_list<calculator::tokenizing::TokenType> list = {
        calculator::tokenizing::TokenType::String,
        calculator::tokenizing::TokenType::Number,
        calculator::tokenizing::TokenType::Identifier,
        calculator::tokenizing::TokenType::Seperator,
        calculator::tokenizing::TokenType::OpeningBracket,
        calculator::tokenizing::TokenType::ClosingBracket,
        calculator::tokenizing::TokenType::SetStart,
        calculator::tokenizing::TokenType::SetEnd,
        calculator::tokenizing::TokenType::AccessorStart,
        calculator::tokenizing::TokenType::AccessorEnd,
        calculator::tokenizing::TokenType::FunctionStart,
        calculator::tokenizing::TokenType::FunctionEnd,
        calculator::tokenizing::TokenType::LazyEvalSeperator,
        calculator::tokenizing::TokenType::Operator,
        calculator::tokenizing::TokenType::OperatorAdd,
        calculator::tokenizing::TokenType::OperatorAddEq,
        calculator::tokenizing::TokenType::OperatorSub,
        calculator::tokenizing::TokenType::OperatorSubEq,
        calculator::tokenizing::TokenType::OperatorMul,
        calculator::tokenizing::TokenType::OperatorMulEq,
        calculator::tokenizing::TokenType::OperatorDiv,
        calculator::tokenizing::TokenType::OperatorDivEq,
        calculator::tokenizing::TokenType::OperatorEq,
        calculator::tokenizing::TokenType::OperatorNot,
        calculator::tokenizing::TokenType::OperatorEqEq,
        calculator::tokenizing::TokenType::OperatorNotEq,
        calculator::tokenizing::TokenType::OperatorNotNot,
        calculator::tokenizing::TokenType::OperatorEqEqEq,
        calculator::tokenizing::TokenType::OperatorNotEqEq,
        calculator::tokenizing::TokenType::OperatorGt,
        calculator::tokenizing::TokenType::OperatorGtEq,
        calculator::tokenizing::TokenType::OperatorGtGt,
        calculator::tokenizing::TokenType::OperatorGtGtEq,
        calculator::tokenizing::TokenType::OperatorLs,
        calculator::tokenizing::TokenType::OperatorLsEq,
        calculator::tokenizing::TokenType::OperatorLsLs,
        calculator::tokenizing::TokenType::OperatorLsLsEq,
        calculator::tokenizing::TokenType::OperatorNeq,
        calculator::tokenizing::TokenType::OperatorQe,
        calculator::tokenizing::TokenType::OperatorQeQe,
    };

    return list;
}