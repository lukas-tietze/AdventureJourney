namespace Matheparser.Functions.DefaultFunctions.Text
{
    using Matheparser.Exceptions;
    using Matheparser.Values;

    class Split : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "SPLIT";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var arg = parameters[0].AsString;
            var split = parameters[1].AsString.ToCharArray();

            return new ArrayValue(arg.Split(split), this.Context.Culture);
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length < 1 || parameters.Length > 2)
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != Values.ValueType.String || parameters[1].Type != Values.ValueType.String)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}