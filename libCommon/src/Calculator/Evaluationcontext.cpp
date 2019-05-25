#include "Calculator.hpp"

util::EvaluationContext::EvaluationContext(Config *config) : config(config)
{
}

util::Operator *util::EvaluationContext::GetOperator(char op)
{
    return this->config->GetOperator(op);
}

util::function_t util::EvaluationContext::GetFunction(const std::string &name)
{
    return this->config->GetFunction(name);
}

util::IValue *util::EvaluationContext::GetVariable(const std::string &name)
{
    return this->config->GetVariable(name);
}
