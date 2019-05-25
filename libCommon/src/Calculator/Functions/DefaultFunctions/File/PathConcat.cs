using System;
using System.IO;
using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.File
{
    public class PathConcat : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "PATHCONCAT";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var args = new string[parameters.Length];

            for (var i = 0; i < parameters.Length; i++)
            {
                args[i] = parameters[i].AsString;
            }

            return new StringValue(Path.Combine(args));
        }

        public void Validate(IValue[] parameters)
        {
            foreach (var parameter in parameters)
            {
                if (parameter.Type != Values.ValueType.String)
                {
                    throw new WrongOperandTypeException();
                }
            }
        }
    }
}
