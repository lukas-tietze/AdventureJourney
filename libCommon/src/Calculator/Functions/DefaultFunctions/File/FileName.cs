namespace Matheparser.Functions.DefaultFunctions.File
{
    public class FileName : FileFunctionBase
    {
        public override string Name
        {
            get
            {
                return "FILE";
            }
        }

        protected override string Eval(string arg)
        {
            return System.IO.Path.GetFileName(arg);
        }
    }
}
