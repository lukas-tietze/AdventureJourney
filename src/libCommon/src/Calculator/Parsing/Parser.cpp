#include "libCommon/Calculator.hpp"
#include "libCommon/Exception.hpp"
#include "../Functions.internal.hpp"
#include "./Internal.hpp"
#include "../Tokenizing/Internal.hpp"

namespace
{
calculator::OperatorType GetOperatorType(calculator::tokenizing::TokenType type)
{
    return static_cast<calculator::OperatorType>(static_cast<int>(type) & ~static_cast<int>(calculator::tokenizing::TokenType::Operator));
}

int GetOperatorPriority(calculator::tokenizing::TokenType type)
{
    return static_cast<int>(type) & 0x00000f00;
}

std::string GetEscapedValue(const calculator::tokenizing::Token &token, const calculator::Config &config)
{
    std::string buf;

    buf.reserve(token.len);

    bool escaped = false;

    for (int i = 0; i < token.len; i++)
    {
        if (escaped)
        {
            buf.push_back(util::Escape(token.start[i]));
            escaped = false;
        }
        else if (token.start[i] == config.GetStringEscapeMarker())
        {
            escaped = true;
        }
        else
        {
            buf.push_back(token.start[i]);
        }
    }

    return buf;
}

std::string GetValue(const calculator::tokenizing::Token &token)
{
    return std::string(token.start, token.len);
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

        switch (token.type)
        {
        case calculator::tokenizing::TokenType::String:
            out.push_back(new ValueExpression(GetEscapedValue(token, config)));
            break;
        case calculator::tokenizing::TokenType::Number:
            out.push_back(new ValueExpression(GetValue(token)));
            break;
        case calculator::tokenizing::TokenType::Identifier:
            out.push_back(new VariableExpression(GetValue(token)));
            break;
        case calculator::tokenizing::TokenType::LazyEvalSeperator:
            out.push_back(new ValueExpression(new LazyValue(GetValue(token))));
            break;
        case calculator::tokenizing::TokenType::OpeningBracket:
            operatorStack.push(tokenizing::TokenType::OpeningBracket);
            break;
        case calculator::tokenizing::TokenType::ClosingBracket:
            operatorStack.push(tokenizing::TokenType::ClosingBracket);
            break;
        case calculator::tokenizing::TokenType::FunctionStart:
            operatorStack.push(tokenizing::TokenType::FunctionStart);
            functionStack.push(GetValue(token));
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

            if (token.type == calculator::tokenizing::TokenType::FunctionEnd || token.type == calculator::tokenizing::TokenType::SetEnd)
            {
                auto argCount = argCountStack.top();
                argCountStack.pop();

                if (tokens[i - 1].type != calculator::tokenizing::TokenType::FunctionStart && tokens[i - 1].type != calculator::tokenizing::TokenType::SetStart)
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
        default:
            if (static_cast<int>(token.type) & static_cast<int>(tokenizing::TokenType::Operator))
            {
                if (operatorStack.empty() || GetOperatorPriority(token.type) > GetOperatorPriority(operatorStack.top()))
                {
                    operatorStack.push(token.type);
                }
                else
                {
                    auto op = operatorStack.top();
                    operatorStack.pop();

                    out.push_back(new FunctionExpression(config.GetOperator(GetOperatorType(op))));

                    while (!operatorStack.empty() && GetOperatorPriority(op) > GetOperatorPriority(operatorStack.top()))
                    {
                        out.push_back(new FunctionExpression(config.GetOperator(GetOperatorType(operatorStack.top()))));
                        operatorStack.pop();
                    }

                    operatorStack.push(token.type);
                }
            }
            else
            {
                throw util::InvalidCaseException::MakeException(token.type);
            }
            break;
        }
    }

    while (operatorStack.size() > 0)
    {
        out.push_back(new FunctionExpression(config.GetOperator(GetOperatorType(operatorStack.top()))));
        operatorStack.pop();
    }

    return true;
}