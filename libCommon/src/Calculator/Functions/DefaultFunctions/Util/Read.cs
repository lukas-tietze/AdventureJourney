namespace Matheparser.Functions.DefaultFunctions.Util
{
    using Matheparser.Values;

    public class Read : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "R";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            switch (parameters[0].Type)
            {
                case ValueType.Number:
                    return new DoubleValue(parameters[0].AsDouble);
                case ValueType.String:
                    return new StringValue(parameters[0].AsString);
                case ValueType.Set:
                    return new ArrayValue(parameters[0].AsSet);
                default:
                    throw new System.NotSupportedException();
            }
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 1)
            {
                throw new Exceptions.OperandNumberException();
            }
        }
    }
}