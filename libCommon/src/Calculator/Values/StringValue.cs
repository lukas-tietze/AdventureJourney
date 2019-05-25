using System.Collections.Generic;
using Matheparser.Util;

namespace Matheparser.Values
{
    public class StringValue : IValue
    {
        private string value;

        public StringValue(string value)
        {
            this.value = value;
        }

        public ValueType Type
        {
            get
            {
                return ValueType.String;
            }
        }

        public double AsDouble
        {
            get
            {
                return double.NaN;
            }
        }

        public string AsString
        {
            get
            {
                return this.value;
            }
        }

        public IArray AsSet
        {
            get
            {
                return new ListArray(this);
            }
        }

        public string Description
        {
            get
            {
                return this.ToString();
            }
        }

        public override bool Equals(object obj)
        {
            return obj is StringValue value &&
                   this.value == value.value;
        }

        public override int GetHashCode()
        {
            return -1584136870 + EqualityComparer<string>.Default.GetHashCode(this.value);
        }

        public override string ToString()
        {
            return this.value;
        }
    }
}
