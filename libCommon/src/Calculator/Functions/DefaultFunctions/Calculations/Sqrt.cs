using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Sqrt : OneParamaterMathFunctionBase
    {
        public override string Name
        {
            get
            {
                return "SQRT";
            }
        }

        protected override double Eval(double arg)
        {
            return Math.Sqrt(arg);
        }
    }
}
