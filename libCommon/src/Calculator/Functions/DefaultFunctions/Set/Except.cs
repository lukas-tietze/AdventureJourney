namespace Matheparser.Functions.DefaultFunctions.Set
{
    using System.Collections.Generic;
    using Matheparser.Exceptions;
    using Matheparser.Util;
    using Matheparser.Values;

    public sealed class Except : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "EXCEPT";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var res = new HashSet<IValue>();
            var except = new HashSet<IValue>();

            for (var i = 1; i < parameters.Length; i++)
            {
                foreach (var value in parameters[i].AsSet)
                {
                    {
                        if (!except.Contains(value))
                            except.Add(value);
                    }
                }
            }

            foreach (var value in parameters[0].AsSet)
            {
                if (!except.Contains(value))
                {
                    res.Add(value);
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
