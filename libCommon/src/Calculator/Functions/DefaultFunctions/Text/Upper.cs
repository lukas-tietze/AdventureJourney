namespace Matheparser.Functions.DefaultFunctions.Text
{
    public sealed class Upper : OneParameterStringModificationFunction
    {
        public override string Name
        {
            get
            {
                return "UPPER";
            }
        }

        protected override string Eval(string arg)
        {
            return arg.ToUpper();
        }
    }
}
