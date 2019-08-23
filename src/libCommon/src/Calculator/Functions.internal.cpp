#include "Functions.internal.hpp"

namespace
{
using calculator::EvaluationContext;
using calculator::IValue;

IValue *FunctionOperatorAdd(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorAddEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorSub(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorSubEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorMul(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorMulEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorDiv(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorDivEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNot(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorEqEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNotEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNotNot(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorEqEqEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNotEqEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorGt(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorGtEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorGtGt(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorGtGtEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLs(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLsEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLsLs(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLsLsEq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNeq(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorQe(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorQeQe(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorHash(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionXor(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionCreateSet(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *If(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *SetUnion(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *SetCut(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *SetNot(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *SetAdd(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *SetRemove(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *SetClear(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *SetFind(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *SetAt(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *Foreach(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *For(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *While(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *StringSubstr(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *StringTrim(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *StringConcat(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *StringFind(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *StringCharAt(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}
} // namespace

calculator::InternalFunction::InternalFunction()
{
}

calculator::InternalFunction::InternalFunction(const std::string &name, function_t func) : name(name),
                                                                                           opType(static_cast<calculator::OperatorType>(0)),
                                                                                           priority(-1),
                                                                                           isUnary(false),
                                                                                           func(func)

{
}

calculator::InternalFunction::InternalFunction(std::string name, calculator::OperatorType op, bool isUnary, function_t func) : name(name),
                                                                                                                               opType(op),
                                                                                                                               priority(GET_OPERATOR_PRIO(op)),
                                                                                                                               isUnary(isUnary),
                                                                                                                               func(func)
{
}

std::vector<calculator::InternalFunction> calculator::internalFunctions =
    {
        calculator::InternalFunction("Add", calculator::OperatorType::Add, false, FunctionOperatorAdd),
        calculator::InternalFunction("AddEq", calculator::OperatorType::AddEq, false, FunctionOperatorAddEq),
        calculator::InternalFunction("Sub", calculator::OperatorType::Sub, false, FunctionOperatorSub),
        calculator::InternalFunction("SubEq", calculator::OperatorType::SubEq, false, FunctionOperatorSubEq),
        calculator::InternalFunction("Mul", calculator::OperatorType::Mul, false, FunctionOperatorMul),
        calculator::InternalFunction("MulEq", calculator::OperatorType::MulEq, false, FunctionOperatorMulEq),
        calculator::InternalFunction("Div", calculator::OperatorType::Div, false, FunctionOperatorDiv),
        calculator::InternalFunction("DivEq", calculator::OperatorType::DivEq, false, FunctionOperatorDivEq),
        calculator::InternalFunction("Eq", calculator::OperatorType::Eq, false, FunctionOperatorEq),
        calculator::InternalFunction("Not", calculator::OperatorType::Not, false, FunctionOperatorNot),
        calculator::InternalFunction("EqEq", calculator::OperatorType::EqEq, false, FunctionOperatorEqEq),
        calculator::InternalFunction("NotEq", calculator::OperatorType::NotEq, false, FunctionOperatorNotEq),
        calculator::InternalFunction("NotNot", calculator::OperatorType::NotNot, false, FunctionOperatorNotNot),
        calculator::InternalFunction("EqEqEq", calculator::OperatorType::EqEqEq, false, FunctionOperatorEqEqEq),
        calculator::InternalFunction("NotEqEq", calculator::OperatorType::NotEqEq, false, FunctionOperatorNotEqEq),
        calculator::InternalFunction("Gt", calculator::OperatorType::Gt, false, FunctionOperatorGt),
        calculator::InternalFunction("GtEq", calculator::OperatorType::GtEq, false, FunctionOperatorGtEq),
        calculator::InternalFunction("GtGt", calculator::OperatorType::GtGt, false, FunctionOperatorGtGt),
        calculator::InternalFunction("GtGtEq", calculator::OperatorType::GtGtEq, false, FunctionOperatorGtGtEq),
        calculator::InternalFunction("Ls", calculator::OperatorType::Ls, false, FunctionOperatorLs),
        calculator::InternalFunction("LsEq", calculator::OperatorType::LsEq, false, FunctionOperatorLsEq),
        calculator::InternalFunction("LsLs", calculator::OperatorType::LsLs, false, FunctionOperatorLsLs),
        calculator::InternalFunction("LsLsEq", calculator::OperatorType::LsLsEq, false, FunctionOperatorLsLsEq),
        calculator::InternalFunction("Neq", calculator::OperatorType::Neq, false, FunctionOperatorNeq),
        calculator::InternalFunction("Qe", calculator::OperatorType::Qe, false, FunctionOperatorQe),
        calculator::InternalFunction("QeQe", calculator::OperatorType::QeQe, false, FunctionOperatorQeQe),
        calculator::InternalFunction("Hash", calculator::OperatorType::Hash, false, FunctionOperatorHash),
        calculator::InternalFunction("XOr", FunctionXor),
        calculator::InternalFunction("CreateSet", FunctionCreateSet),
        calculator::InternalFunction("If", If),
        calculator::InternalFunction("SetUnion", SetUnion),
        calculator::InternalFunction("SetCut", SetCut),
        calculator::InternalFunction("SetNot", SetNot),
        calculator::InternalFunction("SetAdd", SetAdd),
        calculator::InternalFunction("SetRemove", SetRemove),
        calculator::InternalFunction("SetClear", SetClear),
        calculator::InternalFunction("SetFind", SetFind),
        calculator::InternalFunction("SetAt", SetAt),
        calculator::InternalFunction("Foreach", Foreach),
        calculator::InternalFunction("For", For),
        calculator::InternalFunction("While", While),
        calculator::InternalFunction("StringSubstr", StringSubstr),
        calculator::InternalFunction("StringTrim", StringTrim),
        calculator::InternalFunction("StringConcat", StringConcat),
        calculator::InternalFunction("StringFind", StringFind),
        calculator::InternalFunction("StringCharAt", StringCharAt),
};
