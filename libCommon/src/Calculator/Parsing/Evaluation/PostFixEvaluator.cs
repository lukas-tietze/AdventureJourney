using System;
using System.Collections.Generic;
using Matheparser.Functions;
using Matheparser.Parsing.Expressions;
using Matheparser.Values;
using Matheparser.Variables;

namespace Matheparser.Parsing.Evaluation
{
    public class PostFixEvaluator
    {
        private readonly IReadOnlyList<IPostFixExpression> expressions;
        private readonly CalculationContext context;

        public PostFixEvaluator(IReadOnlyList<IPostFixExpression> expressions, CalculationContext context)
        {
            this.expressions = expressions;
            this.context = context;
        }

        public IReadOnlyList<IPostFixExpression> Expressions
        {
            get
            {
                return this.expressions;
            }
        }

        public CalculationContext Context
        {
            get
            {
                return this.context;
            }
        }

        public IValue Run()
        {
            var stack = new Stack<IValue>();

            foreach (var expression in this.expressions)
            {
                switch (expression.Type)
                {
                    case ExpressionType.Value:
                        stack.Push(expression.Eval(this.context, null));
                        break;
                    case ExpressionType.Function:
                        var args = new IValue[expression.ArgCount];

                        for (var i = 0; i < expression.ArgCount; i++)
                        {
                            args[expression.ArgCount - i - 1] = stack.Pop();
                        }

                        stack.Push(expression.Eval(this.context, args));

                        break;
                    default:
                        throw new NotSupportedException();
                }
            }

            return stack.Pop();
        }
    }
}
