using System.Text;
using Matheparser.Exceptions;
using Matheparser.Values;

namespace Matheparser.Functions.DefaultFunctions.Text
{
    public sealed class Format : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "FORMAT";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var args = new object[parameters.Length - 1];

            for (var i = 0; i < args.Length; i++)
            {
                args[i] = parameters[i + 1];
            }

            return new StringValue(string.Format(parameters[0].AsString, args));
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length == 0)
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != ValueType.String)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
