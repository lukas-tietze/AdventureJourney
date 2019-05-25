namespace Matheparser.Parsing.Expressions.Binary.Compare
{
    using System.Diagnostics;
    using Matheparser.Util;

    [DebuggerDisplay("Operator <")]
    public sealed class LessExpression : CompareOperatorBase
    {
        internal override bool CompareNumber(double double1, double double2)
        {
            return double1 < double2;
        }

        internal override bool CompareString(string string1, string string2)
        {
            return string1.CompareTo(string2) < 0;
        }

        public override string ToString()
        {
            return "Op <";
        }

        internal override bool CompareSet(IArray setA, IArray setB)
        {
            return this.CompareNumber(setA.Count, setB.Count);
        }
    }
}
