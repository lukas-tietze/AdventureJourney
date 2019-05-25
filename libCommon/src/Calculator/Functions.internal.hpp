#include "Calculator.hpp"

namespace util
{
struct InternalFunction
{
    std::string name;
    std::string operatorSign;
    int priority;
    bool isUnary;
    function_t func;
};

extern InternalFunction OperatorAdd;
extern InternalFunction OperatorSub;
extern InternalFunction OperatorMul;
extern InternalFunction OperatorDiv;
extern InternalFunction OperatorMod;
extern InternalFunction OperatorPow;
extern InternalFunction OperatorEqual;
extern InternalFunction OperatorNotEqual;
extern InternalFunction OperatorGreater;
extern InternalFunction OperatorGreaterEqual;
extern InternalFunction OperatorLess;
extern InternalFunction OperatorLessEqual;
extern InternalFunction OperatorEqualWithType;
extern InternalFunction OperatorNotEqualWithType;
extern InternalFunction OperatorNot;
extern InternalFunction OperatorAnd;
extern InternalFunction OperatorOr;
extern InternalFunction OperatorXor;
extern InternalFunction OperatorBool;
extern InternalFunction OperatorLength;
extern InternalFunction CreateSet;

} // namespace util