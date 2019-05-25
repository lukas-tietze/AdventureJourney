namespace Matheparser.Functions.DefaultFunctions.File
{
    public class FileExtension : FileFunctionBase
    {
        public override string Name
        {
            get
            {
                return "EXTENSION";
            }
        }

        protected override string Eval(string arg)
        {
            return System.IO.Path.GetExtension(arg);
        }
    }
}
