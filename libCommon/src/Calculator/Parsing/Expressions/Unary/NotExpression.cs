namespace Matheparser.Parsing.Expressions.Unary
{
    using System;
    using System.Diagnostics;
    using Matheparser.Util;
    using Matheparser.Values;

    [DebuggerDisplay("Operator !")]
    public class NotExpression : UnaryOperatorExpressionBase
    {
        internal override IValue EvalNumber(double operand)
        {
            return new DoubleValue(operand == 0 ? 1 : 0);
        }

        internal override IValue EvalString(string operand)
        {
            throw new InvalidOperationException();
        }

        internal override IValue EvalSet(IArray operand)
        {
            throw new NotSupportedException();
        }

        public override string ToString()
        {
            return "Op !";
        }
    }
}
