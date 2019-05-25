using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Round : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "ROUND";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Round(arg);
        }
    }
}
