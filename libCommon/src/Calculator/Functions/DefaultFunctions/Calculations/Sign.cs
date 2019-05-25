using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Sign : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "SIGN";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Sign(arg);
        }
    }
}
