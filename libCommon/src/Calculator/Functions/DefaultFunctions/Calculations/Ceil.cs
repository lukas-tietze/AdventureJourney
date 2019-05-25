using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Ceil : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "CEIL";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Ceiling(arg);
        }
    }
}
