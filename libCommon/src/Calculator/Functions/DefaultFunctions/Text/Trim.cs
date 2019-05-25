namespace Matheparser.Functions.DefaultFunctions.Text
{
    public sealed class Trim : OneParameterStringModificationFunction
    {
        public override string Name
        {
            get
            {
                return "TRIM";
            }
        }

        protected override string Eval(string arg)
        {
            return arg.Trim();
        }
    }
}
