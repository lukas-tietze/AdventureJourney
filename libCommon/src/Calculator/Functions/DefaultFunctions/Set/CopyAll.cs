namespace Matheparser.Functions.DefaultFunctions.Set
{
    using Matheparser.Exceptions;
    using Matheparser.Parsing;
    using Matheparser.Parsing.Evaluation;
    using Matheparser.Tokenizing;
    using Matheparser.Util;
    using Matheparser.Values;
    using Matheparser.Variables;

    public sealed class CopyAll : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "COPYALL";
            }
        }
        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var set = parameters[0].AsSet;
            var res = new ListArray();
            var i = new Variable(parameters[1].AsString, new DoubleValue(0));

            this.Context.VariableManager.Define(i);

            foreach (var item in set)
            {
                i.Value = item;
                res.Add(ValueHelper.Copy(parameters[2]));
            }

            return new ArrayValue(res);
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 3)
            {
                throw new OperandNumberException();
            }

            if (parameters[0].Type != ValueType.Set ||
                parameters[1].Type != ValueType.String)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
