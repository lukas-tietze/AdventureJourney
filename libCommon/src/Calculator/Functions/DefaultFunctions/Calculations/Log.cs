using System;
using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    public sealed class Log : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "LOG";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            if (parameters.Length == 1)
            {
                if (parameters[0].Type == Values.ValueType.Number)
                {
                    return new DoubleValue(Math.Log(parameters[0].AsDouble));
                }
                else
                {
                    throw new WrongOperandTypeException();
                }
            }
            else if (parameters.Length == 2)
            {
                if (parameters[0].Type == Values.ValueType.Number && parameters[1].Type == Values.ValueType.Number)
                {
                    return new DoubleValue(Math.Log(parameters[0].AsDouble, parameters[1].AsDouble));
                }
                else
                {
                    throw new WrongOperandTypeException();
                }
            }
            else
            {
                throw new OperandNumberException();
            }
        }

        private void Validate(IValue[] parameters)
        {
            throw new NotImplementedException();
        }
    }
}
