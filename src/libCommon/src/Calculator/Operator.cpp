#include "libCommon/Calculator.hpp"

calculator::Operator::Operator(int priority, bool isUnary, function_t function) : priority(priority),
                                                                            isUnary(isUnary),
                                                                            function(function)
{
}

int calculator::Operator::GetPriority() const
{
    return this->priority;
}

bool calculator::Operator::IsUnary() const
{
    return this->isUnary;
}

bool calculator::Operator::IsBinary() const
{
    return !this->isUnary;
}

calculator::function_t calculator::Operator::GetFunction()
{
    return this->function;
}

const calculator::function_t calculator::Operator::GetFunction() const
{
    return this->function;
}
