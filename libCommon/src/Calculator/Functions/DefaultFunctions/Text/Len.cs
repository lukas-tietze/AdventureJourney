using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Matheparser.Functions.DefaultFunctions.Text
{
    class Len : OneParameterStringAnalysisFunction
    {
        public override string Name
        {
            get
            {
                return "LEN";
            }
        }

        protected override double Eval(string arg)
        {
            return arg.Length;
        }
    }
}
