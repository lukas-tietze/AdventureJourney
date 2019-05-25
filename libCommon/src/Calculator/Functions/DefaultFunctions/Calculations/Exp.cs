using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Exp : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "EXP";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Exp(arg);
        }
    }
}
