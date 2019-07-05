#include "Functions.internal.hpp"

namespace
{
using util::EvaluationContext;
using util::IValue;

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

util::InternalFunction::InternalFunction()
{
}

util::InternalFunction::InternalFunction(const std::string &name, function_t func) : name(name),
                                                                                     operatorSign(""),
                                                                                     priority(-1),
                                                                                     isUnary(false),
                                                                                     func(func)

{
}

util::InternalFunction::InternalFunction(std::string name, std::string operatorSign, int priority, bool isUnary, function_t func) : name(name),
                                                                                                                                    operatorSign(operatorSign),
                                                                                                                                    priority(priority),
                                                                                                                                    isUnary(isUnary),
                                                                                                                                    func(func)
{
}

std::vector<util::InternalFunction> util::internalFunctions = {
    util::InternalFunction("Add", "+", 0, false, FunctionOperatorAdd),
    util::InternalFunction("Sub", "-", 0, false, FunctionOperatorSub),
    util::InternalFunction("Mul", "*", 0, false, FunctionOperatorMul),
    util::InternalFunction("Div", "/", 0, false, FunctionOperatorDiv),
    util::InternalFunction("Mod", "%", 0, false, FunctionOperatorMod),
    util::InternalFunction("Pow", "^", 0, false, FunctionOperatorPow),
    util::InternalFunction("Equal", "==", 0, false, FunctionOperatorEqual),
    util::InternalFunction("NotEqual", "!=", 0, false, FunctionOperatorNotEqual),
    util::InternalFunction("Greater", ">", 0, false, FunctionOperatorGreater),
    util::InternalFunction("GreaterEqual", ">=", 0, false, FunctionOperatorGreaterEqual),
    util::InternalFunction("Less", "<", 0, false, FunctionOperatorLess),
    util::InternalFunction("LessEqual", "<=", 0, false, FunctionOperatorLessEqual),
    util::InternalFunction("EqualWithType", "===", 0, false, FunctionOperatorEqualWithType),
    util::InternalFunction("NotEqualWithType", "!==", 0, false, FunctionOperatorNotEqualWithType),
    util::InternalFunction("Not", "!", 0, false, FunctionOperatorNot),
    util::InternalFunction("And", "&", 0, false, FunctionOperatorAnd),
    util::InternalFunction("Or", "|", 0, false, FunctionOperatorOr),
    util::InternalFunction("Bool", "?", 0, false, FunctionOperatorBool),
    util::InternalFunction("Length", "#", 0, false, FunctionOperatorLength),
    util::InternalFunction("XOr", FunctionOperatorXor),
    util::InternalFunction("CreateSet", FunctionCreateSet),
    util::InternalFunction("If", If),
    util::InternalFunction("SetUnion", SetUnion),
    util::InternalFunction("SetCut", SetCut),
    util::InternalFunction("SetNot", SetNot),
    util::InternalFunction("SetAdd", SetAdd),
    util::InternalFunction("SetRemove", SetRemove),
    util::InternalFunction("SetClear", SetClear),
    util::InternalFunction("SetFind", SetFind),
    util::InternalFunction("SetAt", SetAt),
    util::InternalFunction("Foreach", Foreach),
    util::InternalFunction("For", For),
    util::InternalFunction("While", While),
    util::InternalFunction("StringSubstr", StringSubstr),
    util::InternalFunction("StringTrim", StringTrim),
    util::InternalFunction("StringConcat", StringConcat),
    util::InternalFunction("StringFind", StringFind),
    util::InternalFunction("StringCharAt", StringCharAt),
};
