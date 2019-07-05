#include "Calculator.hpp"

util::parsing::ExpressionBase::ExpressionBase(int)
{
}

int util::parsing::ExpressionBase::GetArgCount() const
{
    return this->argCount;
}