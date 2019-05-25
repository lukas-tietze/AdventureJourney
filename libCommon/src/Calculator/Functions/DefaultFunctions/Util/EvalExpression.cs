using Matheparser.Exceptions;
using Matheparser.Solving;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Util
{
    public sealed class EvalExpression : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "EVAL";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var solver = new Calculator(this.Context);
            return solver.Calculate(parameters[0].AsString);
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 1)
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != Values.ValueType.String)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
