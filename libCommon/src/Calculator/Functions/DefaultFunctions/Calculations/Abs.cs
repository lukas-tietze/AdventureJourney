using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    class Abs : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "ABS";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Abs(arg);
        }
    }
}
