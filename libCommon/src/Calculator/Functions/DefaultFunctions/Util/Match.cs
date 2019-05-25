namespace Matheparser.Functions.DefaultFunctions.Util
{
    using Matheparser.Values;
    using Matheparser.Exceptions;

    public sealed class Match : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "MATCH";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            return new DoubleValue(System.Text.RegularExpressions.Regex.IsMatch(parameters[0].AsString, parameters[1].AsString) ? 1 : 0);
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 2)
            {
                throw new OperandNumberException();
            }

            if(parameters[0].Type != ValueType.String || parameters[1].Type != ValueType.String)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
