using System;
using Matheparser.Values;
using Matheparser.Exceptions;
using Matheparser.Variables;

namespace Matheparser.Functions.DefaultFunctions.Util
{
    public sealed class Set : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "SET";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var var = this.Context.VariableManager.GetVariable(parameters[0].AsString).Value = parameters[1];

            return parameters[1];
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 2)
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != Values.ValueType.String)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
