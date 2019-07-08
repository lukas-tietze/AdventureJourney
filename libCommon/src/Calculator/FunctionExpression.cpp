#include "Calculator.hpp"

calculator::parsing::FunctionExpression::FunctionExpression(const Operator *op) : ExpressionBase(op->IsBinary() ? 2 : 1),
                                                                            name(),
                                                                            args()
{
}

calculator::parsing::FunctionExpression::FunctionExpression(function_t, int args) : ExpressionBase(args),
                                                                              name(),
                                                                              args()
{
}

calculator::parsing::FunctionExpression::FunctionExpression(const std::string &, int args) : ExpressionBase(args),
                                                                                  name(),
                                                                                  args()
{
}

calculator::IValue *calculator::parsing::FunctionExpression::Eval(const std::vector<IValue *> &args, EvaluationContext &context)
{
    return context.GetFunction(this->name)(args.data(), args.size(), context);
}
