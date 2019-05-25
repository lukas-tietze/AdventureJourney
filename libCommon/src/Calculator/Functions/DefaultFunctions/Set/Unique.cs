namespace Matheparser.Functions.DefaultFunctions.Set
{
    using System.Collections.Generic;
    using Matheparser.Exceptions;
    using Matheparser.Util;
    using Matheparser.Values;

    public sealed class Uniqe : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "UNIQE";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var res = new HashSet<IValue>();

            foreach(var value in parameters[0].AsSet)
            {
                if(!res.Contains(value))
                {
                    res.Add(value);
                }
            }

            return new ArrayValue(new ListArray(res));
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 1)
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != Values.ValueType.Set)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
