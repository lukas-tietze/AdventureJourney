#include "Functions.internal.hpp"

namespace
{
using calculator::EvaluationContext;
using calculator::IValue;

IValue *FunctionOperatorAdd(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorSub(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorMul(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorDiv(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorMod(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorPow(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorEqual(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNotEqual(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorGreater(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorGreaterEqual(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLess(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLessEqual(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorEqualWithType(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNotEqualWithType(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNot(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorAnd(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorOr(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorXor(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorBool(IValue *const *, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLength(IValue *const *, int, EvaluationContext &)
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

// IValue *__template__(IValue *const*, int, EvaluationContext &);
} // namespace

calculator::InternalFunction::InternalFunction()
{
}

calculator::InternalFunction::InternalFunction(const std::string &name, function_t func) : name(name),
                                                                                           operatorSign(""),
                                                                                           priority(-1),
                                                                                           isUnary(false),
                                                                                           func(func)

{
}

calculator::InternalFunction::InternalFunction(std::string name, calculator::OperatorType op, int priority, bool isUnary, function_t func) : name(name),
                                                                                                                                             opType(op),
                                                                                                                                             priority(priority),
                                                                                                                                             isUnary(isUnary),
                                                                                                                                             func(func)
{
}

std::vector<calculator::InternalFunction> calculator::internalFunctions = {
    calculator::InternalFunction("Add", "+", 0, false, FunctionOperatorAdd),
    calculator::InternalFunction("Sub", "-", 0, false, FunctionOperatorSub),
    calculator::InternalFunction("Mul", "*", 0, false, FunctionOperatorMul),
    calculator::InternalFunction("Div", "/", 0, false, FunctionOperatorDiv),
    calculator::InternalFunction("Mod", "%", 0, false, FunctionOperatorMod),
    calculator::InternalFunction("Pow", "^", 0, false, FunctionOperatorPow),
    calculator::InternalFunction("Equal", "==", 0, false, FunctionOperatorEqual),
    calculator::InternalFunction("NotEqual", "!=", 0, false, FunctionOperatorNotEqual),
    calculator::InternalFunction("Greater", ">", 0, false, FunctionOperatorGreater),
    calculator::InternalFunction("GreaterEqual", ">=", 0, false, FunctionOperatorGreaterEqual),
    calculator::InternalFunction("Less", "<", 0, false, FunctionOperatorLess),
    calculator::InternalFunction("LessEqual", "<=", 0, false, FunctionOperatorLessEqual),
    calculator::InternalFunction("EqualWithType", "===", 0, false, FunctionOperatorEqualWithType),
    calculator::InternalFunction("NotEqualWithType", "!==", 0, false, FunctionOperatorNotEqualWithType),
    calculator::InternalFunction("Not", "!", 0, false, FunctionOperatorNot),
    calculator::InternalFunction("And", "&", 0, false, FunctionOperatorAnd),
    calculator::InternalFunction("Or", "|", 0, false, FunctionOperatorOr),
    calculator::InternalFunction("Bool", "?", 0, false, FunctionOperatorBool),
    calculator::InternalFunction("Length", "#", 0, false, FunctionOperatorLength),
    calculator::InternalFunction("XOr", FunctionOperatorXor),
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
