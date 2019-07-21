#include "Internal.hpp"

calculator::parsing::ValueExpression::ValueExpression(IValue *value) : ExpressionBase(0),
                                                                 value(value)
{
}

calculator::parsing::ValueExpression::ValueExpression(const std::string &) : ExpressionBase(0),
                                                                       value(nullptr)
{
}

calculator::IValue *calculator::parsing::ValueExpression::Eval(const std::vector<IValue *> &args, EvaluationContext &)
{
    return this->value;
}