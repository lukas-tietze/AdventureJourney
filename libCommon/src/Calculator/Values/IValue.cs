namespace Matheparser.Values
{
    using Matheparser.Util;

    public interface IValue
    {
        ValueType Type
        {
            get;
        }

        double AsDouble
        {
            get;
        }

        string AsString
        {
            get;
        }

        IArray AsSet
        {
            get;
        }

        string Description
        {
            get;
        }
    }
}
