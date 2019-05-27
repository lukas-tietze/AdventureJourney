#include "Functions.internal.hpp"

namespace
{
using util::EvaluationContext;
using util::IValue;

IValue *FunctionOperatorAdd(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorSub(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorMul(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorDiv(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorMod(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorPow(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorEqual(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNotEqual(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorGreater(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorGreaterEqual(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLess(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLessEqual(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorEqualWithType(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNotEqualWithType(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorNot(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorAnd(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorOr(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorXor(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorBool(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionOperatorLength(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *FunctionCreateSet(IValue **, int, EvaluationContext &)
{
    return nullptr;
}

IValue *If(IValue **, int, EvaluationContext &);
IValue *SetUnion(IValue **, int, EvaluationContext &);
IValue *SetCut(IValue **, int, EvaluationContext &);
IValue *SetNot(IValue **, int, EvaluationContext &);
IValue *SetAdd(IValue **, int, EvaluationContext &);
IValue *SetRemove(IValue **, int, EvaluationContext &);
IValue *SetClear(IValue **, int, EvaluationContext &);
IValue *SetFind(IValue **, int, EvaluationContext &);
IValue *SetAt(IValue **, int, EvaluationContext &);
IValue *Foreach(IValue **, int, EvaluationContext &);
IValue *For(IValue **, int, EvaluationContext &);
IValue *While(IValue **, int, EvaluationContext &);
IValue *StringSubstr(IValue **, int, EvaluationContext &);
IValue *StringTrim(IValue **, int, EvaluationContext &);
IValue *StringConcat(IValue **, int, EvaluationContext &);
IValue *StringFind(IValue **, int, EvaluationContext &);
IValue *StringCharAt(IValue **, int, EvaluationContext &);
// IValue *__template__(IValue **, int, EvaluationContext &);
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
