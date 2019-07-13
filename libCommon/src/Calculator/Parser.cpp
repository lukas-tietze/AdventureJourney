#include "Calculator.hpp"
#include "Functions.internal.hpp"
#include "Exception.hpp"

namespace
{
calculator::OperatorType GetOperatorType(calculator::tokenizing::TokenType type)
{
    return static_cast<calculator::OperatorType>(static_cast<int>(type) & ~static_cast<int>(calculator::tokenizing::TokenType::Operator));
}
} // namespace

bool calculator::parsing::CreatePostFixExpression(const std::vector<calculator::tokenizing::Token> &tokens, std::vector<ExpressionBase *> &out, const Config &config)
{
    std::stack<calculator::tokenizing::TokenType> operatorStack;
    std::stack<std::string> functionStack;
    std::stack<int> argCountStack;

    for (auto i = 0; i < tokens.size(); i++)
    {
        const auto &token = tokens[i];

        switch (token.GetType())
        {
        case calculator::tokenizing::TokenType::String:
            out.push_back(new ValueExpression(token.GetValue()));
            break;
        case calculator::tokenizing::TokenType::Number:
            out.push_back(new ValueExpression(token.GetValue()));
            break;
        case calculator::tokenizing::TokenType::Identifier:
            out.push_back(new VariableExpression(token.GetValue()));
            break;
        case calculator::tokenizing::TokenType::LazyEvalSeperator:
            out.push_back(new ValueExpression(new LazyValue(token.GetValue())));
            break;
        case calculator::tokenizing::TokenType::OpeningBracket:
            operatorStack.push(tokenizing::TokenType::OpeningBracket);
            break;
        case calculator::tokenizing::TokenType::ClosingBracket:
            operatorStack.push(tokenizing::TokenType::ClosingBracket);
            break;
        case calculator::tokenizing::TokenType::FunctionStart:
            operatorStack.push(tokenizing::TokenType::FunctionStart);
            functionStack.push(token.GetValue());
            argCountStack.push(0);
            break;
        case calculator::tokenizing::TokenType::SetStart:
            operatorStack.push(tokenizing::TokenType::SetStart);
            functionStack.push("CreateSet");
            argCountStack.push(0);
            break;
        case calculator::tokenizing::TokenType::SetEnd:
        case calculator::tokenizing::TokenType::FunctionEnd:
        case calculator::tokenizing::TokenType::Seperator:
        {
            auto top = operatorStack.top();

            while (operatorStack.size() > 0)
            {
                if (top == tokenizing::TokenType::FunctionStart ||
                    top == tokenizing::TokenType::Seperator ||
                    top == tokenizing::TokenType::SetStart)
                {
                    break;
                }
                else
                {
                    operatorStack.pop();
                    auto op = config.GetOperator((OperatorType)top);

                    if (op != nullptr)
                        out.push_back(new FunctionExpression(op));
                    else
                        throw util::NotSupportedException();
                }

                top = operatorStack.top();
            }

            if (token.GetType() == calculator::tokenizing::TokenType::FunctionEnd || token.GetType() == calculator::tokenizing::TokenType::SetEnd)
            {
                auto argCount = argCountStack.top();
                argCountStack.pop();

                if (tokens[i - 1].GetType() != calculator::tokenizing::TokenType::FunctionStart && tokens[i - 1].GetType() != calculator::tokenizing::TokenType::SetStart)
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
        }
        case calculator::tokenizing::TokenType::AccessorStart:
        case calculator::tokenizing::TokenType::AccessorEnd:
            throw util::NotImplementedException();
        case calculator::tokenizing::TokenType::Operator:
        {
            auto op1 = config.GetOperator(GetOperatorType(token.GetType()));
            auto op2 = operatorStack.empty() ? nullptr : config.GetOperator(GetOperatorType(operatorStack.top()));

            if (operatorStack.size() == 0 ||
                (op1 && op2 && op1->GetPriority() > op2->GetPriority()))
            {
                operatorStack.push(token.GetType());
            }
            else
            {
                auto op = config.GetOperator(GetOperatorType(operatorStack.top()));
                operatorStack.pop();

                if (op != nullptr)
                    out.push_back(new FunctionExpression(op));
                else
                    throw util::NotSupportedException();

                op2 = operatorStack.empty() ? nullptr : config.GetOperator(GetOperatorType(operatorStack.top()));

                while (operatorStack.size() > 0 && !(op1 && op2 && op1->GetPriority() > op2->GetPriority()))
                {
                    out.push_back(new FunctionExpression(config.GetOperator(GetOperatorType(operatorStack.top()))));
                    operatorStack.pop();
                }

                operatorStack.push(token.GetType());
            }

            break;
        }
        default:
            throw util::NotSupportedException();
        }
    }

    while (operatorStack.size() > 0)
    {
        out.push_back(new FunctionExpression(config.GetOperator(GetOperatorType(operatorStack.top()))));
        operatorStack.pop();
    }

    return true;
}