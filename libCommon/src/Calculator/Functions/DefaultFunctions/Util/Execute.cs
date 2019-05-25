namespace Matheparser.Functions.DefaultFunctions.Util
{
    using Matheparser.Values;

    public class Execute : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "EXEC";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            if (parameters.Length > 0)
            {
                return parameters[parameters.Length - 1];
            }

            return new EmptyValue();
        }
    }
}
