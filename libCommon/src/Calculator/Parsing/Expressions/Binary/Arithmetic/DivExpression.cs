namespace Matheparser.Parsing.Expressions.Binary.Arithmetic
{
    using System;
    using System.Diagnostics;
    using Matheparser.Util;
    using Matheparser.Values;

    [DebuggerDisplay("Operator /")]
    public sealed class DivExpression : BinaryOperatorExpressionBase
    {
        internal override IValue EvalNumber(double double1, double double2)
        {
            return new DoubleValue(double1 / double2);
        }

        internal override IValue EvalString(string string1, string string2)
        {
            throw new InvalidOperationException();
        }

        internal override IValue EvalSet(IArray setA, IArray setB)
        {
            throw new NotSupportedException();
        }

        public override string ToString()
        {
            return "/";
        }
    }
}
