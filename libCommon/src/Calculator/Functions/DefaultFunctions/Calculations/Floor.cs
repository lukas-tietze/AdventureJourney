using System;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Floor : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "FLOOR";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Floor(arg);
        }
    }
}
