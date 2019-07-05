#include "Calculator.hpp"

util::parsing::FunctionExpression::FunctionExpression(const Operator *op) : ExpressionBase(op->IsBinary() ? 2 : 1),
                                                                            name(),
                                                                            args()
{
}

util::parsing::FunctionExpression::FunctionExpression(function_t, int args) : ExpressionBase(args),
                                                                              name(),
                                                                              args()
{
}

util::parsing::FunctionExpression::FunctionExpression(const std::string &, int args) : ExpressionBase(args),
                                                                                  name(),
                                                                                  args()
{
}

util::IValue *util::parsing::FunctionExpression::Eval(const std::vector<IValue *> &args, EvaluationContext &context)
{
    return context.GetFunction(this->name)(args.data(), args.size(), context);
}
