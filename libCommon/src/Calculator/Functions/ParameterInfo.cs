namespace Matheparser.Functions
{
    using System.Text;
    using Matheparser.Values;

    public sealed class ParameterInfo
    {
        public ParameterInfo(string name, ValueType type, string description)
        {
            this.Name = name;
            this.Type = type;
            this.Description = description;
        }

        public string Name
        {
            get;
        }

        public ValueType Type
        {
            get;
        }

        public string Description
        {
            get;
        }
    }
}