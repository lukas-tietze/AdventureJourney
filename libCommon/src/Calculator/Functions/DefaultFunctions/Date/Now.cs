using System;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Date
{
    public class Now : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "SYSNOW";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            return new DoubleValue(DateTime.Now.Ticks);
        }

        private void Validate(IValue[] parameters)
        {
            if(parameters.Length != 0)
            {
                throw new Exceptions.OperandNumberException();
            }
        }
    }
}