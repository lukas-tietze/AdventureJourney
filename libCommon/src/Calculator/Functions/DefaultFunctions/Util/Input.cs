using System;
using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Util
{
    public class Input : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "INPUT";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            Console.WriteLine(parameters[0].AsString);

            return new StringValue(Console.ReadLine());
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 1)
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
