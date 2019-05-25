using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Text
{
    public abstract class OneParameterStringModificationFunction : FunctionBase
    {
        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            return new StringValue(this.Eval(parameters[0].AsString));
        }

        protected abstract string Eval(string arg);

        protected virtual void Validate(IValue[] parameters)
        {
            if (parameters.Length == 0)
            {
                throw new OperandNumberException();
            }
        }
    }
}
