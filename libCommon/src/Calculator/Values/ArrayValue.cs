namespace Matheparser.Values
{
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Globalization;
    using System.Text;
    using Matheparser.Util;

    [DebuggerDisplay("Array: Count={values.Count}")]
    public class ArrayValue : IValue
    {
        private readonly ListArray values;

        public ArrayValue()
        {
            this.values = new ListArray();
        }

        public ArrayValue(IEnumerable<IValue> values) :
            this()
        {
            foreach (var item in values)
            {
                this.values.Add(item);
            }
        }

        public ArrayValue(IEnumerable<object> items, CultureInfo cultureInfo) :
            this()
        {
            foreach (var item in items)
            {
                this.values.Add(ValueHelper.Create(item, cultureInfo));
            }
        }

        public ValueType Type
        {
            get
            {
                return ValueType.Set;
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
                return string.Empty;
            }
        }

        public IArray AsSet
        {
            get
            {
                return this.values;
            }
        }

        public string Description
        {
            get
            {
                return this.ToString();
            }
        }

        public override string ToString()
        {
            var sb = new StringBuilder();

            sb.Append("{ ");

            var enumerator = this.values.GetEnumerator();

            if (enumerator.MoveNext())
            {
                sb.Append(enumerator.Current);
            }

            while(enumerator.MoveNext())
            {
                sb.Append(", ").Append(enumerator.Current);
            }

            sb.Append(" }");

            return sb.ToString();
        }

        public override bool Equals(object obj)
        {
            return obj is ArrayValue value &&
                   EqualityComparer<IArray>.Default.Equals(this.values, value.values);
        }

        public override int GetHashCode()
        {
            return 1649527923 + EqualityComparer<IArray>.Default.GetHashCode(this.values);
        }
    }
}
