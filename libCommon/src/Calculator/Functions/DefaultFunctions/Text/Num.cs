using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Text
{
    public sealed class Num : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "NUM";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            return new DoubleValue(double.Parse(parameters[0].ToString(), this.Context.Culture));
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 1)
            {
                throw new OperandNumberException();
            }
        }
    }
}
