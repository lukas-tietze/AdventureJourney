#include "Calculator.hpp"

calculator::Config::Config()
{
}

void calculator::Config::CreateDefaultConfig()
{
}

void calculator::Config::AddOperator(OperatorType type, Operator *op)
{
    this->operators[type] = op;
}

void calculator::Config::AddFunction(const std::string &name, function_t f)
{
    this->functions[name] = f;
}

void calculator::Config::AddVariable(const std::string &name, IValue *v)
{
    this->variables[name] = v;
}

bool calculator::Config::RemoveOperator(OperatorType type)
{
    return this->operators.erase(type);
}

bool calculator::Config::RemoveFunction(const std::string &name)
{
    return this->functions.erase(name);
}

bool calculator::Config::RemoveVariable(const std::string &name)
{
    return this->variables.erase(name);
}

void calculator::Config::ClearOperators()
{
    this->operators.clear();
}

void calculator::Config::ClearFunctions()
{
    this->functions.clear();
}

void calculator::Config::ClearVariables()
{
    this->variables.clear();
}

void calculator::Config::SetBracketMarker(char opening, char closing)
{
    this->bracketMarker.opening = opening;
    this->bracketMarker.closing = closing;
}

void calculator::Config::SetStringMarker(char opening, char closing)
{
    this->stringMarker.opening = opening;
    this->stringMarker.closing = closing;
}

void calculator::Config::SetLazyEvalMarker(char opening, char closing)
{
    this->lazyEvalMarker.opening = opening;
    this->lazyEvalMarker.closing = closing;
}

void calculator::Config::SetFunctionBrackets(char opening, char closing)
{
    this->functionBrackets.opening = opening;
    this->functionBrackets.closing = closing;
}

void calculator::Config::SetSetMarkers(char opening, char closing)
{
    this->setMarkers.opening = opening;
    this->setMarkers.closing = closing;
}

void calculator::Config::SetAccessorMarkers(char opening, char closing)
{
    this->accessorMarkers.opening = opening;
    this->accessorMarkers.closing = closing;
}

void calculator::Config::GetListSeperator(char value)
{
    this->listSeperator = value;
}

void calculator::Config::SetDecimalSeperator(char value)
{
    this->decimalSeperator = value;
}

void calculator::Config::SetFunctionParameterSeperator(char value)
{
    this->functionParameterSeperator = value;
}

void calculator::Config::SetStringEscapeMarker(char value)
{
    this->stringEscapeMarker = value;
}

std::unordered_map<std::string, calculator::function_t> &calculator::Config::GetFunctions()
{
    return this->functions;
}

std::unordered_map<calculator::OperatorType, calculator::Operator *> &calculator::Config::GetOperators()
{
    return this->operators;
}

std::unordered_map<std::string, calculator::IValue *> &calculator::Config::GetVariables()
{
    return this->variables;
}

calculator::Operator *calculator::Config::GetOperator(OperatorType type)
{
    auto res = this->operators.find(type);

    return res == this->operators.end() ? nullptr : res->second;
}

calculator::function_t calculator::Config::GetFunction(const std::string &name)
{
    auto res = this->functions.find(name);

    return res == this->functions.end() ? nullptr : res->second;
}

calculator::IValue *calculator::Config::GetVariable(const std::string &name)
{
    auto res = this->variables.find(name);

    return res == this->variables.end() ? nullptr : res->second;
}

calculator::Config::CharPair &calculator::Config::GetBracketMarker()
{
    return this->bracketMarker;
}

calculator::Config::CharPair &calculator::Config::GetStringMarker()
{
    return this->stringMarker;
}

calculator::Config::CharPair &calculator::Config::GetLazyEvalMarker()
{
    return this->lazyEvalMarker;
}

calculator::Config::CharPair &calculator::Config::GetFunctionBrackets()
{
    return this->functionBrackets;
}

calculator::Config::CharPair &calculator::Config::GetSetMarkers()
{
    return this->setMarkers;
}

calculator::Config::CharPair &calculator::Config::GetAccessorMarkers()
{
    return this->accessorMarkers;
}

const std::unordered_map<std::string, calculator::function_t> &calculator::Config::GetFunctions() const
{
    return this->functions;
}

const std::unordered_map<calculator::OperatorType, calculator::Operator *> &calculator::Config::GetOperators() const
{
    return this->operators;
}

const std::unordered_map<std::string, calculator::IValue *> &calculator::Config::GetVariables() const
{
    return this->variables;
}

const calculator::Operator *calculator::Config::GetOperator(OperatorType type) const
{
    auto res = this->operators.find(type);

    return res == this->operators.end() ? nullptr : res->second;
}

const calculator::function_t calculator::Config::GetFunction(const std::string &name) const
{
    auto res = this->functions.find(name);

    return res == this->functions.end() ? nullptr : res->second;
}

const calculator::IValue *calculator::Config::GetVariable(const std::string &name) const
{
    auto res = this->variables.find(name);

    return res == this->variables.end() ? nullptr : res->second;
}

const calculator::Config::CharPair &calculator::Config::GetBracketMarker() const
{
    return this->bracketMarker;
}

const calculator::Config::CharPair &calculator::Config::GetStringMarker() const
{
    return this->stringMarker;
}

const calculator::Config::CharPair &calculator::Config::GetLazyEvalMarker() const
{
    return this->lazyEvalMarker;
}

const calculator::Config::CharPair &calculator::Config::GetFunctionBrackets() const
{
    return this->functionBrackets;
}

const calculator::Config::CharPair &calculator::Config::GetSetMarkers() const
{
    return this->setMarkers;
}

const calculator::Config::CharPair &calculator::Config::GetAccessorMarkers() const
{
    return this->accessorMarkers;
}

char calculator::Config::GetListSeperator() const
{
    return this->listSeperator;
}

char calculator::Config::GetDecimalSeperator() const
{
    return this->decimalSeperator;
}

char calculator::Config::GetFunctionParameterSeperator() const
{
    return this->functionParameterSeperator;
}

char calculator::Config::GetStringEscapeMarker() const
{
    return this->stringEscapeMarker;
}
