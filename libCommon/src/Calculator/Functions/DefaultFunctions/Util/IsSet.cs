namespace Matheparser.Functions.DefaultFunctions.Util
{
    using Matheparser.Values;
    using Matheparser.Exceptions;

    public sealed class IsSet : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "ISSET";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            return new DoubleValue(parameters[0].Type == ValueType.Set ? 1 : 0);
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
