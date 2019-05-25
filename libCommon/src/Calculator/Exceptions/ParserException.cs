namespace Matheparser.Exceptions
{
    public class ParserException : CalculationException
    {
        public ParserException() : base("Unknown parser exception")
        {
        }

        public ParserException(string message) : base(message)
        {
        }
    }
}
