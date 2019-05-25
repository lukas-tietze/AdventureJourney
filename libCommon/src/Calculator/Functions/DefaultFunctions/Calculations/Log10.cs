using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Log10 : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "LOG10";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Log10(arg);
        }
    }
}
