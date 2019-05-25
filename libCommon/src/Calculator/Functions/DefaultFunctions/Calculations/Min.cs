using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Min : TwoParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "MIN";
            }
        }

        protected override double Eval(double arg1, double arg2)
        {
            return Math.Min(arg1, arg2);
        }
    }
}
