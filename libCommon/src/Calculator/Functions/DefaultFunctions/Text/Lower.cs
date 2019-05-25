namespace Matheparser.Functions.DefaultFunctions.Text
{
    public sealed class Lower : OneParameterStringModificationFunction
    {
        public override string Name
        {
            get
            {
                return "LOWER";
            }
        }

        protected override string Eval(string arg)
        {
            return arg.ToLower();
        }
    }
}
