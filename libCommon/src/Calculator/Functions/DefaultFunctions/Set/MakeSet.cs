namespace Matheparser.Functions.DefaultFunctions.Set
{
    using Matheparser.Values;

    public class MakeSet : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "MKSET";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            return new ArrayValue(parameters);
        }
    }
}
