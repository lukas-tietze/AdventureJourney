#include "Calculator.hpp"

calculator::Config &calculator::Calculator::GetConfig()
{
    return this->config;
}

const calculator::Config &calculator::Calculator::GetConfig() const
{
    return this->config;
}

void calculator::Calculator::SetConfig(const Config &c)
{
    this->config = c;
}

calculator::IValue *calculator::Calculator::Evaluate(const std::string &s)
{
    calculator::tokenizing::Tokenizer t;
    std::vector<calculator::parsing::ExpressionBase *> expressions;
    t.Tokenize(s, &this->config);
    calculator::parsing::CreatePostFixExpression(t.GetTokens(), expressions, this->config);
}