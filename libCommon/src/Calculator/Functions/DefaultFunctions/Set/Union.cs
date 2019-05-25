namespace Matheparser.Functions.DefaultFunctions.Set
{
    using System.Collections.Generic;
    using Matheparser.Exceptions;
    using Matheparser.Util;
    using Matheparser.Values;

    public sealed class Union : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "UNION";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var res = new HashSet<IValue>();

            foreach(var parameter in parameters)
            {
                foreach(var value in parameter.AsSet)
                {
                    if(!res.Contains(value))
                    {
                        res.Add(value);
                    }
                }
            }

            return new ArrayValue(new ListArray(res));
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length < 2)
            {
                throw new OperandNumberException();
            }

            foreach (var parameter in parameters)
            {
                if (parameter.Type != ValueType.Set)
                {
                    throw new WrongOperandTypeException();
                }
            }
        }
    }
}
