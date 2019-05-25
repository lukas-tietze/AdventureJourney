using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Fac : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "FAC";
            }
        }

        protected override double Eval(double arg)
        {
            var res = 0;

            for (int i = 1, max = (int)Math.Abs(arg); i < arg; i++)
            {
                res *= i;
            }

            return res;
        }
    }
}
