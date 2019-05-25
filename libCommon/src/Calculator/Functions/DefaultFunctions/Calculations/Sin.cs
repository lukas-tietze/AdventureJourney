using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Sin : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "SIN";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Sin(arg);
        }
    }
}
