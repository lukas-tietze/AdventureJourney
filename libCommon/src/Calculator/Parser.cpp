#include "Calculator.hpp"
#include "Functions.internal.hpp"

namespace
{
using util::Config;
using util::parsing::ExpressionBase;
using util::parsing::FunctionExpression;
using util::tokenizing::TokenType;

ExpressionBase *CreateOperatorExpression(TokenType op, const Config &)
{
    switch (op)
    {
    case TokenType::String:
    case TokenType::Number:
    case TokenType::Identifier:
    case TokenType::Seperator:
        throw ArgumentException();
    case TokenType::Operator:
        return new FunctionExpression();
    case TokenType::FunctionStart:
    case TokenType::FunctionEnd:
    case TokenType::SetStart:
    case TokenType::SetEnd:
        return nullptr;
    case TokenType::OpeningBracket:
    case TokenType::ClosingBracket:
        return nullptr;
    default:
        throw util::InvalidCaseException::MakeException(op);
    }
}
} // namespace

bool util::parsing::CreatePostFixExpression(const std::vector<tokenizing::Token> &tokens, std::vector<ExpressionBase *> &out, const Config &config)
{
    std::stack<TokenType> operatorStack;
    std::stack<std::string> functionStack;
    std::stack<int> argCountStack;

    for (auto i = 0; i < tokens.size(); i++)
    {
        const auto &token = tokens[i];

        switch (token.GetType())
        {
        case TokenType::String:
            out.push_back(new ValueExpression(token.GetValue()));
            break;
        case TokenType::Number:
            out.push_back(new ValueExpression(token.GetValue()));
            break;
        case TokenType::Identifier:
            out.push_back(new VariableExpression(token.GetValue()));
            break;
        case TokenType::LazyEvalSeperator:
            out.push_back(new LazyExpression(token.GetValue()));
            break;
        case TokenType::OpeningBracket:
        case TokenType::ClosingBracket:
            operatorStack.push(token.GetType());
            break;
        case TokenType::FunctionStart:
            operatorStack.push(token.GetType());
            functionStack.push(token.GetValue());
            argCountStack.push(0);
            break;
        case TokenType::SetStart:
            operatorStack.push(token.GetType());
            functionStack.push(util::CreateSet.name);
            argCountStack.push(0);
            break;
        case TokenType::SetEnd:
        case TokenType::FunctionEnd:
        case TokenType::Seperator:
            auto top = operatorStack.top();

            while (operatorStack.size() > 0)
            {
                if (top == TokenType::FunctionStart || top == TokenType::Seperator || top == TokenType::SetStart)
                {
                    break;
                }
                else
                {
                    AddOperatorExpression(operatorStack.Pop(), expressions);
                }

                top = operatorStack.Peek();
            }

            if (token.GetType() == TokenType::FunctionEnd || token.GetType() == TokenType::SetEnd)
            {
                auto argCount = argCountStack.Pop();

                if (tokens[i - 1].GetType() != TokenType::FunctionStart && tokens[i - 1].GetType() != TokenType::SetStart)
                {
                    argCount++;
                }

                out.push_back(new FunctionExpression(functionStack.top(), argCount));
                functionStack.pop();
            }
            else
            {
                argCountStack.push(argCountStack.top() + 1);
                argCountStack.pop();
            }

            break;
        case TokenType::AccessorStart:
        case TokenType::AccessorEnd:
            throw NotImplementedException();
        case TokenType::Operator:
            if ((token.GetType() & TokenType::Operator) != 0)
            {
                if (operatorStack.Count == 0 || IsHigherPriority(token.GetType(), operatorStack.Peek()))
                {
                    operatorStack.push(token.GetType());
                }
                else
                {
                    AddOperatorExpression(operatorStack.Pop(), expressions);

                    while (operatorStack.Count > 0 && !IsHigherPriority(token.GetType(), operatorStack.Peek()))
                    {
                        AddOperatorExpression(operatorStack.Pop(), expressions);
                    }

                    operatorStack.push(token.GetType());
                }

                break;
            }
            else
            {
                throw util::NotSupportedException();
            }
        default:
            throw NotSupportedException();
        }
    }

    while (operatorStack.Count > 0)
    {
        AddOperatorExpression(operatorStack.Pop(), expressions);
    }

    return expressions.AsReadOnly();
}