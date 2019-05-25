using System;
using Matheparser.Values;

namespace Matheparser.Variables
{
    public class ValueChangedEventArgs : EventArgs
    {
        public ValueChangedEventArgs(IValue oldValue, IValue newValue)
        {
            OldValue = oldValue;
            NewValue = newValue;
        }

        public IValue OldValue { get; }
        public IValue NewValue { get; }
    }
}