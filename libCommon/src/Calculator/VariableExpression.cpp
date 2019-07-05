#include "Calculator.hpp"

util::parsing::VariableExpression::VariableExpression(const std::string &name) : ExpressionBase(0),
                                                                                 name(name)
{
}

util::IValue *util::parsing::VariableExpression::Eval(const std::vector<IValue *> &args, EvaluationContext &context)
{
    return context.GetVariable(this->name);
}
