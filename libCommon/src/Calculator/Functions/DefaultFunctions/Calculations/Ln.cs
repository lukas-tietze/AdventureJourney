using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Ln : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "LN";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Log(arg);
        }
    }
}
