#include "Internal.hpp"

calculator::parsing::VariableExpression::VariableExpression(const std::string &name) : ExpressionBase(0),
                                                                                 name(name)
{
}

calculator::IValue *calculator::parsing::VariableExpression::Eval(const std::vector<IValue *> &args, EvaluationContext &context)
{
    return context.GetVariable(this->name);
}
