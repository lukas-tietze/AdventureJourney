#include "Calculator.hpp"

util::parsing::ValueExpression::ValueExpression(IValue *value) : ExpressionBase(0),
                                                                 value(value)
{
}

util::parsing::ValueExpression::ValueExpression(const std::string &) : ExpressionBase(0),
                                                                       value(nullptr)
{
}

util::IValue *util::parsing::ValueExpression::Eval(const std::vector<IValue *> &args, EvaluationContext &)
{
    return this->value;
}