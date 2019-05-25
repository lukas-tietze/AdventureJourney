namespace Matheparser.Functions.DefaultFunctions.Set
{
    using Matheparser.Exceptions;
    using Matheparser.Util;
    using Matheparser.Values;

    class GenSet : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "GENSET";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var res = new ListArray();

            for(double i = parameters[0].AsDouble, end = parameters[2].AsDouble; i <= end; i += parameters[1].AsDouble)
            {
                res.Add(new DoubleValue(i));
            }

            return new ArrayValue(res);
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 3)
            {
                throw new OperandNumberException();
            }

            if(parameters[0].Type != ValueType.Number ||
                parameters[1].Type != ValueType.Number ||
                parameters[2].Type != ValueType.Number)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
