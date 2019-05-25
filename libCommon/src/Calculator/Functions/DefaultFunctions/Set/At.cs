namespace Matheparser.Functions.DefaultFunctions.Set
{
    using Matheparser.Exceptions;
    using Matheparser.Values;

    public sealed class At : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "AT";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            if (parameters[0].Type == Values.ValueType.Set)
            {
                return parameters[0].AsSet.At((int)parameters[1].AsDouble);
            }

            return this.Extract(parameters[0].AsString, (int)parameters[1].AsDouble);
        }

        private IValue Extract(string arg, int index)
        {
            if (index < 0 || index >= arg.Length)
            {
                throw new IndexOutOfBoundsException();
            }

            return new StringValue(arg[index].ToString());
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 2)
            {
                throw new OperandNumberException();
            }

            if ((parameters[0].Type != Values.ValueType.Set && parameters[0].Type != Values.ValueType.String) ||
                parameters[1].Type != Values.ValueType.Number)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
