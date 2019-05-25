namespace Matheparser.Functions.DefaultFunctions.Set
{
    using System.Collections.Generic;
    using Matheparser.Exceptions;
    using Matheparser.Util;
    using Matheparser.Values;

    public sealed class CUT : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "CUT";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var res = new HashSet<IValue>();

            foreach (var value in parameters[0].AsSet)
            {
                if (!res.Contains(value))
                {
                    var found = true;

                    for (var i = 1; i < parameters.Length; i++)
                    {
                        if (!parameters[i].AsSet.Contains(value))
                        {
                            found = false;
                            break;
                        }
                    }
                    
                    if (found)
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
