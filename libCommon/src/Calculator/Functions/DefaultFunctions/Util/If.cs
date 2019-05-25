using System;
using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Util
{
    public sealed class If : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "IF";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            var thenBranch = default(IValue);
            var elseBranch = default(IValue);

            if (parameters.Length == 2)
            {
                thenBranch = parameters[1];
                elseBranch = new EmptyValue();
            }
            else if (parameters.Length == 3)
            {
                thenBranch = parameters[1];
                elseBranch = parameters[2];
            }
            else
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != Values.ValueType.Number)
            {
                throw new WrongOperandTypeException();
            }

            return parameters[0].AsDouble != 0 ? thenBranch : elseBranch;
        }
    }
}
