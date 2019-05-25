namespace Matheparser.Functions.DefaultFunctions.Set
{
    using Matheparser.Exceptions;
    using Matheparser.Parsing;
    using Matheparser.Parsing.Evaluation;
    using Matheparser.Tokenizing;
    using Matheparser.Util;
    using Matheparser.Values;
    using Matheparser.Variables;

    public sealed class EvalAll : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "EVALALL";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var set = parameters[0].AsSet;
            var res = new ListArray();
            var i = new Variable(parameters[1].AsString, new DoubleValue(0));
            var evaluator = default(PostFixEvaluator);

            this.Context.VariableManager.Define(i);

            try
            {
                var tokenizer = new Tokenizer(parameters[2].AsString, this.Context.Config);
                tokenizer.Run();
                var parser = new Parser(tokenizer.Tokens, this.Context.Config);
                evaluator = new PostFixEvaluator(parser.CreatePostFixExpression(), this.Context);
            }
            catch (System.Exception)
            {
                throw new OperandEvaluationException();
            }

            foreach (var item in set)
            {
                i.Value = item;
                res.Add(evaluator.Run());
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
                parameters[1].Type != ValueType.String ||
                parameters[2].Type != ValueType.String)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
