using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public abstract class TwoParamaterMathFunctionBase : FunctionBase
    {
        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            return new DoubleValue(this.Eval(parameters[0].AsDouble, parameters[1].AsDouble));
        }

        protected abstract double Eval(double arg1, double arg2);

        protected virtual void Validate(IValue[] parameters)
        {
            if (parameters.Length != 2)
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != ValueType.Number || parameters[1].Type != ValueType.Number)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
