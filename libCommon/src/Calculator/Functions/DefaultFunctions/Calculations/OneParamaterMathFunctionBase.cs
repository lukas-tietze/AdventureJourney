using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public abstract class OneParamaterMathFunctionBase : FunctionBase
    {
        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            return new DoubleValue(this.Eval(parameters[0].AsDouble));
        }

        protected abstract double Eval(double arg);

        protected virtual void Validate(IValue[] parameters)
        {
            if (parameters.Length != 1)
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != ValueType.Number)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
