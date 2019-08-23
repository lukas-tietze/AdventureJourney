#pragma once

#include "Calculator.hpp"
#include "../Tokenizing/Internal.hpp"

namespace calculator
{
namespace parsing
{
class ExpressionBase
{
private:
    int argCount;

public:
    ExpressionBase(int);

    int GetArgCount() const;

    virtual IValue *Eval(const std::vector<IValue *> &args, EvaluationContext &) = 0;
};

class VariableExpression : public ExpressionBase
{
private:
    std::string name;

public:
    VariableExpression(const std::string &);

    IValue *Eval(const std::vector<IValue *> &args, EvaluationContext &);
};

class FunctionExpression : public ExpressionBase
{
private:
    std::string name;
    int args;

public:
    FunctionExpression(const Operator *);
    FunctionExpression(function_t, int args);
    FunctionExpression(const std::string &, int);

    IValue *Eval(const std::vector<IValue *> &args, EvaluationContext &);
};

class ValueExpression : public ExpressionBase
{
private:
    IValue *value;

public:
    ValueExpression(IValue *);
    ValueExpression(const std::string &);

    IValue *Eval(const std::vector<IValue *> &args, EvaluationContext &);
};

bool CreatePostFixExpression(const std::vector<tokenizing::Token> &tokens, std::vector<ExpressionBase *> &out, const Config &);
} // namespace parsing

} // namespace calculator
