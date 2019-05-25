namespace Matheparser.Functions.DefaultFunctions.File
{
    public class BaseDir : FileFunctionBase
    {
        public override string Name
        {
            get
            {
                return "BASEDIR";
            }
        }

        protected override string Eval(string arg)
        {
            return System.IO.Path.GetDirectoryName(arg);
        }
    }
}
