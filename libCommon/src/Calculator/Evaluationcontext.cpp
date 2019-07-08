#include "Calculator.hpp"

calculator::EvaluationContext::EvaluationContext(Config *config) : config(config)
{
}

calculator::Operator *calculator::EvaluationContext::GetOperator(const std::string &op)
{
    return this->config->GetOperator(op);
}

calculator::function_t calculator::EvaluationContext::GetFunction(const std::string &name)
{
    return this->config->GetFunction(name);
}

calculator::IValue *calculator::EvaluationContext::GetVariable(const std::string &name)
{
    return this->config->GetVariable(name);
}
