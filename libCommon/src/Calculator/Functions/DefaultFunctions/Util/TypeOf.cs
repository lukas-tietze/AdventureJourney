using System;
using Matheparser.Util;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Util
{
    public class TypeOf : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "TYPEOF";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            if (parameters.Length == 1)
            {
                return new StringValue(parameters[0].Type.ToString());
            }
            else
            {
                var res = new ListArray();

                foreach(var parameter in parameters)
                {
                    res.Add(new StringValue(parameter.Type.ToString()));
                }

                return new ArrayValue(res);
            }
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length == 0)
            {
                throw new Exceptions.OperandNumberException();
            }
        }
    }
}