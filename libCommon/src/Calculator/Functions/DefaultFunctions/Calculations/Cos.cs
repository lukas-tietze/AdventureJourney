using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class COS : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "COS";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Cos(arg);
        }
    }
}
