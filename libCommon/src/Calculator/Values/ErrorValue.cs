namespace Matheparser.Values
{
    internal class ErrorValue : StringValue
    {
        public ErrorValue(System.Exception exception) : base(string.Format("{0}: {1}", exception.GetType().Name, exception.Message))
        {
        }
    }
}