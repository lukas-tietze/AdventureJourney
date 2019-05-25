using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Log2 : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "LOG2";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Log(arg, 2);
        }
    }
}
