namespace Matheparser.Exceptions
{
    using System;

    internal class MissingFunctionException : CalculationException
    {
        public MissingFunctionException(string name):
            base(string.Format("The function {0} is not deifned.", name))
        {
        }
    }
}