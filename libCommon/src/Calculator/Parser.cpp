#include "Calculator.hpp"
#include "Functions.internal.hpp"

bool util::parsing::CreatePostFixExpression(const std::vector<tokenizing::Token> &tokens, std::vector<ExpressionBase *> &out, const Config &config)
{
    std::stack<std::string> operatorStack;
    std::stack<std::string> functionStack;
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
            operatorStack.push(std::string({config.GetBracketMarker().opening}));
            break;
        case util::tokenizing::TokenType::ClosingBracket:
            operatorStack.push(std::string({config.GetBracketMarker().closing}));
            break;
        case util::tokenizing::TokenType::FunctionStart:
            operatorStack.push(std::string({config.GetFunctionBrackets().opening}));
            functionStack.push(token.GetValue());
            argCountStack.push(0);
            break;
        case util::tokenizing::TokenType::SetStart:
            operatorStack.push(std::string({config.GetSetMarkers().opening}));
            functionStack.push("CreateSet");
            argCountStack.push(0);
            break;
        case util::tokenizing::TokenType::SetEnd:
        case util::tokenizing::TokenType::FunctionEnd:
        case util::tokenizing::TokenType::Seperator:
        {
            auto top = operatorStack.top();

            while (operatorStack.size() > 0)
            {
                if (top.length() == 1 &&
                    (top[0] == config.GetFunctionBrackets().opening ||
                     top[0] == config.GetListSeperator() ||
                     top[0] == config.GetSetMarkers().opening))
                {
                    break;
                }
                else
                {
                    operatorStack.pop();
                    auto op = config.GetOperator(top);

                    if (op != nullptr)
                        out.push_back(new FunctionExpression(op));
                    else
                        throw util::NotSupportedException();
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
            auto op2 = operatorStack.empty() ? nullptr : config.GetOperator(operatorStack.top());

            if (operatorStack.size() == 0 ||
                (op1 && op2 && op1->GetPriority() > op2->GetPriority()))
            {
                operatorStack.push(token.GetValue());
            }
            else
            {
                auto op = config.GetOperator(operatorStack.top());
                operatorStack.pop();

                if (op != nullptr)
                    out.push_back(new FunctionExpression(op));
                else
                    throw util::NotSupportedException();

                op2 = operatorStack.empty() ? nullptr : config.GetOperator(operatorStack.top());

                while (operatorStack.size() > 0 && !(op1 && op2 && op1->GetPriority() > op2->GetPriority()))
                {
                    out.push_back(new FunctionExpression(config.GetOperator(operatorStack.top())));
                    operatorStack.pop();
                }

                operatorStack.push(token.GetValue());
            }

            break;
        }
        default:
            throw util::NotSupportedException();
        }
    }

    while (operatorStack.size() > 0)
    {
        out.push_back(new FunctionExpression(config.GetOperator(operatorStack.top())));
        operatorStack.pop();
    }

    return true;
}