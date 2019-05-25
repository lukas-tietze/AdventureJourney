using Matheparser.Values;

namespace Matheparser.Variables
{
    public interface IVariable
    {
        string Name
        {
            get;
        }

        ValueType Type
        {
            get;
        }

        IValue Value
        {
            get;
            set;
        }

        event System.EventHandler<ValueChangedEventArgs> ValueChanged;
    }
}
