using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class ArcSin : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "ASIN";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Asin(arg);
        }
    }
}
