using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Max : TwoParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "MAX";
            }
        }

        protected override double Eval(double arg1, double arg2)
        {
            return Math.Max(arg1, arg2);
        }
    }
}
