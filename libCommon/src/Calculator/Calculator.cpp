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

util::IValue *Evaluate(const std::string &)
{
    return nullptr;
}