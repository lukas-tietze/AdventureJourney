using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Tan : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "TAN";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Tan(arg);
        }
    }
}
