#include "Calculator.hpp"

util::Config &util::Calculator::GetConfig()
{
    return this->config;
}

const util::Config &util::Calculator::GetConfig() const
{
    return this->config;
}

void util::Calculator::SetConfig(const Config &c)
{
    this->config = c;
}

util::IValue *util::Calculator::Evaluate(const std::string &s)
{
    util::tokenizing::Tokenizer t;
    std::vector<util::parsing::ExpressionBase *> expressions;
    t.Tokenize(s, &this->config);
    util::parsing::CreatePostFixExpression(t.GetTokens(), expressions, this->config);
}