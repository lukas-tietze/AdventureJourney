using System.Collections.Generic;
using System.Diagnostics;
using Matheparser.Functions;
using Matheparser.Parsing.Evaluation;
using Matheparser.Values;

namespace Matheparser.Parsing.Expressions
{
    [DebuggerDisplay("Lazy expression:")]
    public class LazyExpression : IPostFixExpression
    {
        private string expression;
        private LazyValue lastValue;
        private CalculationContext lastContext;

        public LazyExpression(string expression)
        {
            this.expression = expression;
            this.lastValue = null;
        }

        public int ArgCount
        {
            get
            {
                return 0;
            }
        }

        public ExpressionType Type
        {
            get
            {
                return ExpressionType.Value;
            }
        }

        public IValue Eval(CalculationContext context, IValue[] operands)
        {
            if (this.lastContext == null || !this.lastContext.Equals(context))
            {
                this.lastValue = new LazyValue(this.expression, context);
            }
            
            return this.lastValue;
        }
    }
}