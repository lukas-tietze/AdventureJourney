#include "Calculator.hpp"

calculator::parsing::ExpressionBase::ExpressionBase(int)
{
}

int calculator::parsing::ExpressionBase::GetArgCount() const
{
    return this->argCount;
}