namespace Matheparser.Parsing.Expressions.Unary
{
    using System;
    using System.Diagnostics;
    using Matheparser.Util;
    using Matheparser.Values;

    [DebuggerDisplay("Operator #")]
    public class LengthExpression : UnaryOperatorExpressionBase
    {
        internal override IValue EvalNumber(double operand)
        {
            return new DoubleValue(Math.Abs(operand));
        }

        internal override IValue EvalString(string operand)
        {
            return new DoubleValue(operand.Length);
        }

        internal override IValue EvalSet(IArray operand)
        {
            return new DoubleValue(operand.Count);
        }

        public override string ToString()
        {
            return "Op #";
        }
    }
}
