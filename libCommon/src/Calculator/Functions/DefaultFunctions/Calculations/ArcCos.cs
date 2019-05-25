using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class ArcCos : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "ACOS";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Acos(arg);
        }
    }
}
