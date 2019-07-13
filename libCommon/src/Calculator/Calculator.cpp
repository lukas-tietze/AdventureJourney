#include "Calculator.hpp"

#include "./Parsing/Internal.hpp"

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
    std::vector<calculator::tokenizing::Token> tokens;
    std::vector<calculator::parsing::ExpressionBase *> expressions;
    calculator::tokenizing::Tokenize(s, tokens, this->config);
    calculator::parsing::CreatePostFixExpression(tokens, expressions, this->config);
}