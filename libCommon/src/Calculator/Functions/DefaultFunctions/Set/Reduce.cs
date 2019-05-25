namespace Matheparser.Functions.DefaultFunctions.Set
{
    using System.Collections.Generic;
    using Matheparser.Exceptions;
    using Matheparser.Parsing;
    using Matheparser.Parsing.Evaluation;
    using Matheparser.Tokenizing;
    using Matheparser.Values;
    using Matheparser.Variables;

    public sealed class Reduce : FunctionBase
    {
        public override string Name
        {
            get
            {
                return "REDUCE";
            }
        }

       public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            var set = parameters[0].AsSet;
            var evaluator = default(PostFixEvaluator);
            var i = this.Context.VariableManager.CreateTempVariable();
            var res = this.Context.VariableManager.CreateTempVariable();

            try
            {
                var tokenizer = new Tokenizer(parameters[2].AsString, this.Context.Config);
                tokenizer.Run();
                var tokens = new List<Token>();

                tokens.Add(new Token(TokenType.FunctionStart, new Functions.DefaultFunctions.Util.Set().Name));
                tokens.Add(new Token(TokenType.String, res.Name));
                tokens.Add(new Token(TokenType.Seperator, ","));
                tokens.Add(new Token(TokenType.Identifier, res.Name));
                tokens.AddRange(tokenizer.Tokens);
                tokens.Add(new Token(TokenType.Identifier, i.Name));
                tokens.Add(new Token(TokenType.FunctionEnd));

                var parser = new Parser(tokens, this.Context.Config);
                evaluator = new PostFixEvaluator(parser.CreatePostFixExpression(), this.Context);
            }
            catch (System.Exception)
            {
                throw new OperandEvaluationException();
            }

            foreach (var item in set)
            {
                i.Value = item;
                evaluator.Run();
            }

            this.Context.VariableManager.Remove(i.Name);
            this.Context.VariableManager.Remove(res.Name);

            return res.Value;
        }

        private void Validate(IValue[] parameters)
        {
            if (parameters.Length != 2)
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
