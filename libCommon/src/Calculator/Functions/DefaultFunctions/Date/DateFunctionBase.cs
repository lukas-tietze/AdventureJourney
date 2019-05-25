using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Date
{
    public abstract class DateFunctionBase : FunctionBase
    {
        public override IValue Eval(IValue[] parameters)
        {
            return this.Eval(this.Validate(parameters));
        }

        protected abstract IValue Eval(System.DateTime dateTime);

        private System.DateTime Validate(IValue[] parameters)
        {
            if (parameters.Length != 1)
            {
                throw new Exceptions.OperandNumberException();
            }

            switch (parameters[0].Type)
            {
                case ValueType.Number:
                    return new System.DateTime((long)parameters[0].AsDouble);
                case ValueType.String:
                    if (System.DateTime.TryParse(parameters[0].AsString, out var res))
                    {
                        return res;
                    }

                    throw new Exceptions.OperandEvaluationException();
                case ValueType.Set:
                    throw new Exceptions.WrongOperandTypeException();
                default:
                    throw new System.NotSupportedException();
            }
        }
    }
}