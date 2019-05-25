namespace Matheparser.Parsing.Expressions.Binary.Arithmetic
{
    using System.Diagnostics;
    using Matheparser.Util;
    using Matheparser.Values;

    [DebuggerDisplay("Operator +")]
    public sealed class AddExpression : BinaryOperatorExpressionBase
    {
        internal override IValue EvalNumber(double double1, double double2)
        {
            return new DoubleValue(double1 + double2);
        }

        internal override IValue EvalString(string string1, string string2)
        {
            return new StringValue(string.Concat(string1, string2));
        }

        internal override IValue EvalSet(IArray setA, IArray setB)
        {
            return new ArrayValue(setA.Combine(setB));
        }

        public override string ToString()
        {
            return "+";
        }
    }
}
