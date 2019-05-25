namespace Matheparser.Functions.DefaultFunctions.Set
{
    using Matheparser.Exceptions;
    using Matheparser.Util;
    using Matheparser.Values;

    public sealed class Range : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "RANGE";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            if (parameters[0].Type == ValueType.Set && parameters.Length == 2)
            {
                return this.Extract(parameters[0].AsSet, parameters[1].AsSet);
            }

            if (parameters[0].Type == ValueType.Set && parameters.Length == 3)
            {
                return this.Extract(parameters[0].AsSet, (int)parameters[1].AsDouble, (int)parameters[1].AsDouble);
            }

            if (parameters[0].Type == ValueType.String && parameters.Length == 2)
            {
                return this.Extract(parameters[0].AsString, parameters[1].AsSet);
            }

            if (parameters[0].Type == ValueType.String && parameters.Length == 3)
            {
                return this.Extract(parameters[0].AsString, (int)parameters[1].AsDouble, (int)parameters[1].AsDouble);
            }

            throw new System.NotSupportedException();
        }

        private IValue Extract(string arg, int start, int end)
        {
            if(start < 0 || end > arg.Length || start > end)
            {
                throw new IndexOutOfBoundsException();
            }

            return new StringValue(arg.Substring(start, end - start));
        }

        private IValue Extract(string arg, IArray selection)
        {
            var chars = new char[selection.Count];
            var i = -1;

            foreach(var item in selection)
            {
                if(item.Type != ValueType.Number)
                {
                    throw new WrongOperandTypeException();
                }

                var index = (int)item.AsDouble;

                if (index < 0 || index > arg.Length)
                {
                    throw new IndexOutOfBoundsException();
                }

                chars[++i] = arg[index];
            }

            return new StringValue(new string(chars));
        }

        private IValue Extract(IArray set, int start, int end)
        {
            return new ArrayValue(set.Range(start, end));
        }

        private IValue Extract(IArray set, IArray selection)
        {
            var res = new ListArray();

            foreach (var item in selection)
            {
                if (item.Type != ValueType.Number)
                {
                    throw new WrongOperandTypeException();
                }

                res.Add(set.At((int)item.AsDouble));
            }

            return new ArrayValue(res);
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length < 2 || parameters.Length > 3)
            {
                throw new OperandNumberException();
            }

            if ((parameters[0].Type != ValueType.Set && parameters[0].Type != ValueType.String) ||
                (parameters.Length == 2 && parameters[1].Type != ValueType.Set) ||
                (parameters.Length == 3 && (parameters[1].Type != ValueType.Number || parameters[2].Type != ValueType.Number)))
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
