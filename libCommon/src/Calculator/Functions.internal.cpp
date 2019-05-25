#include "Functions.internal.hpp"

namespace
{
using util::EvaluationContext;
using util::IValue;

IValue *FunctionOperatorAdd(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorSub(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorMul(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorDiv(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorMod(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorPow(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorEqual(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorNotEqual(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorGreater(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorGreaterEqual(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorLess(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorLessEqual(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorEqualWithType(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorNotEqualWithType(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorNot(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorAnd(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorOr(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorXor(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorBool(IValue **, int, EvaluationContext &);
IValue *FunctionOperatorLength(IValue **, int, EvaluationContext &);
IValue *FunctionCreateSet(IValue **, int, EvaluationContext &);
} // namespace

util::InternalFunction util::OperatorAdd = {"Add", "+", 0, false, FunctionOperatorAdd};
util::InternalFunction util::OperatorSub = {"Sub", "-", 0, false, FunctionOperatorSub};
util::InternalFunction util::OperatorMul = {"Mul", "*", 0, false, FunctionOperatorMul};
util::InternalFunction util::OperatorDiv = {"Div", "/", 0, false, FunctionOperatorDiv};
util::InternalFunction util::OperatorMod = {"Mod", "%", 0, false, FunctionOperatorMod};
util::InternalFunction util::OperatorPow = {"Pow", "^", 0, false, FunctionOperatorPow};
util::InternalFunction util::OperatorEqual = {"Equal", "==", 0, false, FunctionOperatorEqual};
util::InternalFunction util::OperatorNotEqual = {"NotEqual", "!=", 0, false, FunctionOperatorNotEqual};
util::InternalFunction util::OperatorGreater = {"Greater", ">", 0, false, FunctionOperatorGreater};
util::InternalFunction util::OperatorGreaterEqual = {"GreaterEqual", ">=", 0, false, FunctionOperatorGreaterEqual};
util::InternalFunction util::OperatorLess = {"Less", "<", 0, false, FunctionOperatorLess};
util::InternalFunction util::OperatorLessEqual = {"LessEqual", "<=", 0, false, FunctionOperatorLessEqual};
util::InternalFunction util::OperatorEqualWithType = {"EqualWithType", "===", 0, false, FunctionOperatorEqualWithType};
util::InternalFunction util::OperatorNotEqualWithType = {"NotEqualWithType", "!==", 0, false, FunctionOperatorNotEqualWithType};
util::InternalFunction util::OperatorNot = {"Not", "!", 0, false, FunctionOperatorNot};
util::InternalFunction util::OperatorAnd = {"And", "&", 0, false, FunctionOperatorAnd};
util::InternalFunction util::OperatorOr = {"Or", "|", 0, false, FunctionOperatorOr};
util::InternalFunction util::OperatorBool = {"Bool", "?", 0, false, FunctionOperatorBool};
util::InternalFunction util::OperatorLength = {"Length", "#", 0, false, FunctionOperatorLength};

util::InternalFunction util::OperatorXor = {"XOr", "", -1, false, FunctionOperatorXor};
util::InternalFunction util::CreateSet = {"__create_set__", "", -1, false, FunctionCreateSet};
