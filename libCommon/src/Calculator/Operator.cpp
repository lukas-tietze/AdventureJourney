#include "Calculator.hpp"

util::Operator::Operator(int priority, bool isUnary, function_t function) : priority(priority),
                                                                            isUnary(isUnary),
                                                                            function(function)
{
}

int util::Operator::GetPriority() const
{
    return this->priority;
}

bool util::Operator::IsUnary() const
{
    return this->isUnary;
}

bool util::Operator::IsBinary() const
{
    return !this->isUnary;
}

util::function_t *util::Operator::GetFunction()
{
    return this->function;
}

const util::function_t *util::Operator::GetFunction() const
{
    return this->function;
}
