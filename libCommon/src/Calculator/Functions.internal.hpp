#include "Calculator.hpp"

namespace calculator
{
struct InternalFunction
{
    std::string name;
    calculator::OperatorType opType;
    int priority;
    bool isUnary;
    function_t func;

    InternalFunction();
    InternalFunction(const std::string &, function_t func);
    InternalFunction(std::string name, calculator::OperatorType t, int priority, bool isUnary, function_t func);
};

extern std::vector<InternalFunction> internalFunctions;

} // namespace calculator