namespace Matheparser.Variables
{
    using System;

    public sealed class UndefinedVariableException : Exception
    {
        public UndefinedVariableException(string name):
            base(string.Format("The Variable {0} is undefined.", name))
        {
        }
    }
}
