namespace Matheparser.Exceptions
{
    using System;

    public class CalculationException : Exception
    {
        public CalculationException() : base("Calculation error")
        {
        }

        public CalculationException(string message) : base(message)
        {
        }
    }
}
