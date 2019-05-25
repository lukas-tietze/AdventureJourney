namespace Matheparser.Parsing
{
    using System;
    using System.Collections.Generic;
    using Matheparser.Parsing.Expressions;
    using Matheparser.Parsing.Expressions.Binary.Arithmetic;
    using Matheparser.Parsing.Expressions.Binary.Compare;
    using Matheparser.Parsing.Expressions.Functions;
    using Matheparser.Parsing.Expressions.Unary;
    using Matheparser.Tokenizing;

    public class Parser
    {
        private readonly IReadOnlyList<Token> tokens;
        private readonly IConfig config;

        public Parser(IReadOnlyList<Token> tokens, IConfig config)
        {
            this.tokens = tokens;
            this.config = config;
        }

        public IReadOnlyList<IPostFixExpression> CreatePostFixExpression()
        {
            var operatorStack = new Stack<TokenType>();
            var functionStack = new Stack<string>();
            var argCountStack = new Stack<int>();
            var expressions = new List<IPostFixExpression>();

            for (var i = 0; i < this.tokens.Count; i++)
            {
                var token = this.tokens[i];

                switch (token.Type)
                {
                    case TokenType.String:
                        expressions.Add(new ValueExpression(token.Value, this.config.Culture));
                        break;
                    case TokenType.Number:
                        expressions.Add(new ValueExpression(token.Value, this.config.Culture));
                        break;
                    case TokenType.Identifier:
                        expressions.Add(new VariableExpression(token.Value));
                        break;
                    case TokenType.LazyEvalSeperator:
                        expressions.Add(new LazyExpression(token.Value));
                        break;
                    case TokenType.OpeningBracket:
                    case TokenType.ClosingBracket:
                        operatorStack.Push(token.Type);
                        break;
                    case TokenType.FunctionStart:
                        operatorStack.Push(token.Type);
                        functionStack.Push(token.Value);
                        argCountStack.Push(0);
                        break;
                    case TokenType.SetStart:
                        operatorStack.Push(token.Type);
                        functionStack.Push(new Functions.DefaultFunctions.Set.MakeSet().Name);
                        argCountStack.Push(0);
                        break;
                    case TokenType.SetEnd:
                    case TokenType.FunctionEnd:
                    case TokenType.Seperator:
                        var top = operatorStack.Peek();

                        while (operatorStack.Count > 0)
                        {
                            if (top == TokenType.FunctionStart || top == TokenType.Seperator || top == TokenType.SetStart)
                            {
                                break;
                            }
                            else
                            {
                                this.AddOperatorExpression(operatorStack.Pop(), expressions);
                            }

                            top = operatorStack.Peek();
                        }

                        if (token.Type == TokenType.FunctionEnd || token.Type == TokenType.SetEnd)
                        {
                            var argCount = argCountStack.Pop();

                            if (this.tokens[i - 1].Type != TokenType.FunctionStart && this.tokens[i - 1].Type != TokenType.SetStart)
                            {
                                argCount++;
                            }

                            expressions.Add(new FunctionExpression(functionStack.Pop(), argCount));
                        }
                        else
                        {
                            argCountStack.Push(argCountStack.Pop() + 1);
                        }

                        break;
                    case TokenType.AccessorStart:
                    case TokenType.AccessorEnd:
                        throw new NotImplementedException();
                    case TokenType.Operator:
                    case TokenType.OperatorAdd:
                    case TokenType.OperatorSub:
                    case TokenType.OperatorMul:
                    case TokenType.OperatorDiv:
                    case TokenType.OperatorExp:
                    case TokenType.OperatorMod:
                    case TokenType.OperatorNot:
                    case TokenType.OperatorLength:
                    case TokenType.OperatorEqual:
                    case TokenType.OperatorNotEqual:
                    case TokenType.OperatorGreater:
                    case TokenType.OperatorGreaterEqual:
                    case TokenType.OperatorLess:
                    case TokenType.OperatorLessEqual:
                        if ((token.Type & TokenType.Operator) != 0)
                        {
                            if (operatorStack.Count == 0 || IsHigherPriority(token.Type, operatorStack.Peek()))
                            {
                                operatorStack.Push(token.Type);
                            }
                            else
                            {
                                this.AddOperatorExpression(operatorStack.Pop(), expressions);

                                while (operatorStack.Count > 0 && !IsHigherPriority(token.Type, operatorStack.Peek()))
                                {
                                    this.AddOperatorExpression(operatorStack.Pop(), expressions);
                                }

                                operatorStack.Push(token.Type);
                            }

                            break;
                        }
                        else
                        {
                            throw new NotSupportedException();
                        }
                    default:
                        throw new NotSupportedException();
                }
            }

            while (operatorStack.Count > 0)
            {
                this.AddOperatorExpression(operatorStack.Pop(), expressions);
            }

            return expressions.AsReadOnly();
        }

        public IReadOnlyCollection<IPostFixExpression> CreateAbstractSyntxTree()
        {
            return null;
        }

        private bool IsHigherPriority(TokenType opA, TokenType opB)
        {
            var mask = 0x0F00;

            return ((int)opA & mask) > ((int)opB & mask);
        }

        private void AddOperatorExpression(TokenType type, List<IPostFixExpression> target)
        {
            var token = this.CreateOperatorExpression(type);

            if (token != null)
            {
                target.Add(token);
            }
        }

        private IPostFixExpression CreateOperatorExpression(TokenType op)
        {
            switch (op)
            {
                case TokenType.String:
                case TokenType.Number:
                case TokenType.Identifier:
                case TokenType.Seperator:
                case TokenType.Operator:
                    throw new ArgumentException();
                case TokenType.FunctionStart:
                case TokenType.FunctionEnd:
                case TokenType.SetStart:
                case TokenType.SetEnd:
                    return null;
                case TokenType.OpeningBracket:
                case TokenType.ClosingBracket:
                    return null;
                case TokenType.OperatorAdd:
                    return new AddExpression();
                case TokenType.OperatorSub:
                    return new SubExpression();
                case TokenType.OperatorMul:
                    return new MulExpression();
                case TokenType.OperatorDiv:
                    return new DivExpression();
                case TokenType.OperatorExp:
                    return new ExpExpression();
                case TokenType.OperatorNot:
                    return new NotExpression();
                case TokenType.OperatorLength:
                    return new LengthExpression();
                case TokenType.OperatorEqual:
                    return new EqualExpression();
                case TokenType.OperatorNotEqual:
                    return new NotEqualExpression();
                case TokenType.OperatorGreater:
                    return new GreaterExpression();
                case TokenType.OperatorGreaterEqual:
                    return new GreaterEqualExpression();
                case TokenType.OperatorLess:
                    return new LessExpression();
                case TokenType.OperatorLessEqual:
                    return new LessEqualExpression();
                case TokenType.OperatorMod:
                    return new ModExpression();
                default:
                    throw new NotSupportedException();
            }
        }
    }
}