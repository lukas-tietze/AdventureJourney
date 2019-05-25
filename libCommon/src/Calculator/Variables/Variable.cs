using Matheparser.Values;

namespace Matheparser.Variables
{
    public class Variable : IVariable
    {
        private string name;
        private IValue value;

        public Variable(string name, IValue value)
        {
            this.name = name;
            this.value = value;
        }

        public string Name
        {
            get
            {
                return this.name;
            }
        }

        public ValueType Type
        {
            get
            {
                return this.value.Type;
            }
        }

        public IValue Value
        {
            get
            {
                return this.value;
            }

            set
            {
                if (this.value != value)
                {
                    var eventArgs = new ValueChangedEventArgs(this.value, value);
                    this.value = value;
                    this.ValueChanged?.Invoke(this, eventArgs);
                }
            }
        }

        public event System.EventHandler<ValueChangedEventArgs> ValueChanged;

        public override string ToString()
        {
            return string.Format("\"{0}\" ({1}): {2}", this.name, this.value.Type, this.value);
        }
    }
}
