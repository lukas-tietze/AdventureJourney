namespace Matheparser.Parsing.Expressions.Binary.Compare
{
    using System.Diagnostics;
    using Matheparser.Util;

    [DebuggerDisplay("Operator !=")]
    public sealed class NotEqualExpression : CompareOperatorBase
    {
        internal override bool CompareNumber(double double1, double double2)
        {
            return double1 != double2;
        }

        internal override bool CompareString(string string1, string string2)
        {
            return !string1.Equals(string2);
        }

        internal override bool CompareSet(IArray setA, IArray setB)
        {
            return !setA.Equals(setB);
        }

        public override string ToString()
        {
            return "Op !=";
        }
    }
}
