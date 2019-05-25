using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class ArcTan : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "ATAN";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Atan(arg);
        }
    }
}
