using System.Collections.Generic;
using System.Globalization;

namespace Matheparser.Values
{
    public static class ValueHelper
    {
        public static IValue Create(object value, CultureInfo culture)
        {
            if (value is IValue ivalue)
            {
                return Copy(ivalue);
            }
            if (value is string stringValue)
            {
                return Create(stringValue, culture);
            }
            else if (value is double doubleValue)
            {
                return new DoubleValue(doubleValue);
            }
            else if (value is IEnumerable<object> enumerableValue)
            {
                return new ArrayValue(enumerableValue, culture);
            }
            else
            {
                return Create(value.ToString(), culture);
            }
        }

        public static IValue Copy(IValue value)
        {
            switch (value.Type)
            {
                case ValueType.Number:
                    return new DoubleValue(value.AsDouble);
                case ValueType.Set:
                    return new ArrayValue(value.AsSet);
                case ValueType.String:
                    return new StringValue(value.AsString);
                default:
                    throw new System.NotSupportedException();
            }
        }

        public static IValue Create(string expression, CultureInfo culture)
        {
            if (double.TryParse(expression, System.Globalization.NumberStyles.AllowDecimalPoint, culture, out var res))
            {
                return new DoubleValue(res);
            }

            return new StringValue(expression);
        }
    }
}
