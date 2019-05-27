#include "Calculator.hpp"
#include "Functions.internal.hpp"

bool util::parsing::CreatePostFixExpression(const std::vector<tokenizing::Token> &tokens, std::vector<ExpressionBase *> &out, const Config &config)
{
    std::stack<util::tokenizing::TokenType> operatorStack;
    std::stack<std::string> functionStack;
    std::stack<std::string> operatorNameStack;
    std::stack<int> argCountStack;

    for (auto i = 0; i < tokens.size(); i++)
    {
        const auto &token = tokens[i];

        switch (token.GetType())
        {
        case util::tokenizing::TokenType::String:
            out.push_back(new ValueExpression(token.GetValue()));
            break;
        case util::tokenizing::TokenType::Number:
            out.push_back(new ValueExpression(token.GetValue()));
            break;
        case util::tokenizing::TokenType::Identifier:
            out.push_back(new VariableExpression(token.GetValue()));
            break;
        case util::tokenizing::TokenType::LazyEvalSeperator:
            out.push_back(new ValueExpression(new LazyValue(token.GetValue())));
            break;
        case util::tokenizing::TokenType::OpeningBracket:
        case util::tokenizing::TokenType::ClosingBracket:
            operatorStack.push(token.GetType());
            break;
        case util::tokenizing::TokenType::FunctionStart:
            operatorStack.push(token.GetType());
            functionStack.push(token.GetValue());
            argCountStack.push(0);
            break;
        case util::tokenizing::TokenType::SetStart:
            operatorStack.push(token.GetType());
            functionStack.push(util::CreateSet.name);
            argCountStack.push(0);
            break;
        case util::tokenizing::TokenType::SetEnd:
        case util::tokenizing::TokenType::FunctionEnd:
        case util::tokenizing::TokenType::Seperator:
        {
            auto top = operatorStack.top();

            while (operatorStack.size() > 0)
            {
                if (top == util::tokenizing::TokenType::FunctionStart || top == util::tokenizing::TokenType::Seperator || top == util::tokenizing::TokenType::SetStart)
                {
                    break;
                }
                else
                {
                    operatorStack.pop();

                    if (top == util::tokenizing::TokenType::Operator)
                    {
                        auto op = config.GetOperator(operatorNameStack.top());

                        if (op != nullptr)
                        {
                            out.push_back(new FunctionExpression(op));
                            operatorNameStack.pop();
                        }
                        else
                        {
                            throw util::NotSupportedException();
                        }
                    }
                }

                top = operatorStack.top();
            }

            if (token.GetType() == util::tokenizing::TokenType::FunctionEnd || token.GetType() == util::tokenizing::TokenType::SetEnd)
            {
                auto argCount = argCountStack.top();
                argCountStack.pop();

                if (tokens[i - 1].GetType() != util::tokenizing::TokenType::FunctionStart && tokens[i - 1].GetType() != util::tokenizing::TokenType::SetStart)
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
        case util::tokenizing::TokenType::AccessorStart:
        case util::tokenizing::TokenType::AccessorEnd:
            throw util::NotImplementedException();
        case util::tokenizing::TokenType::Operator:
        {
            auto op1 = config.GetOperator(token.GetValue());
            auto op2 = operatorStack.empty() ? nullptr : config.GetOperator(operatorNameStack.top());

            if (operatorStack.size() == 0 ||
                (op1 && op2 && op1->GetPriority() > op2->GetPriority()))
            {
                operatorStack.push(token.GetType());
            }
            else
            {
                auto op = config.GetOperator(operatorNameStack.top());
                operatorStack.pop();

                if (op != nullptr)
                    out.push_back(new FunctionExpression(op));
                else
                    throw util::NotSupportedException();

                op2 = operatorStack.empty() ? nullptr : config.GetOperator(operatorNameStack.top());

                while (operatorStack.size() > 0 && !(op1 && op2 && op1->GetPriority() > op2->GetPriority()))
                {
                    out.push_back(new FunctionExpression(config.GetOperator(operatorNameStack.top())));
                    operatorNameStack.pop();
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
        out.push_back(new FunctionExpression(config.GetOperator(operatorNameStack.top())));
        operatorNameStack.pop();
    }

    return true;
}