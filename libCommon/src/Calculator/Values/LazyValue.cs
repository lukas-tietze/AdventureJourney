namespace Matheparser.Values
{
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Text;
    using Matheparser.Functions;
    using Matheparser.Parsing.Evaluation;
    using Matheparser.Parsing.Expressions;
    using Matheparser.Util;
    using Matheparser.Variables;

    [DebuggerDisplay("Expression: {rawExpression}")]
    public sealed class LazyValue : IValue
    {
        private readonly string rawExpression;
        private PostFixEvaluator evaluator;
        private IValue value;
        private CalculationContext context;
        private bool dirty;
        private bool alwaysDirty;
        private bool lastRequestWasType;

        public LazyValue(IReadOnlyList<IPostFixExpression> expressions, CalculationContext context)
        {
            this.context = context;
            this.lastRequestWasType = false;
            this.evaluator = new PostFixEvaluator(expressions, context);
            this.dirty = true;
            var sb = new StringBuilder();

            foreach (var expression in expressions)
            {
                sb.Append(expression.ToString()).Append(' ');
            }

            this.rawExpression = sb.ToString();

            this.BindEvents();
        }

        public LazyValue(string expression, CalculationContext context)
        {
            this.context = context;
            this.lastRequestWasType = false;
            this.rawExpression = expression;
            this.dirty = true;
            var tokenizer = new Tokenizing.Tokenizer(expression, context.Config);
            tokenizer.Run();
            var parser = new Parsing.Parser(tokenizer.Tokens, context.Config);
            this.evaluator = new PostFixEvaluator(parser.CreatePostFixExpression(), context);

            this.BindEvents();
        }

        public IValue Value
        {
            get
            {
                if (this.dirty && !this.lastRequestWasType)
                {
                    this.value = this.evaluator.Run();

                    this.dirty = this.alwaysDirty;
                }

                return this.value;
            }
        }

        public ValueType Type
        {
            get
            {
                var res = this.Value.Type;

                this.lastRequestWasType = true;

                return res;
            }
        }

        public double AsDouble
        {
            get
            {
                var res = this.Value.AsDouble;

                this.lastRequestWasType = false;

                return res;
            }
        }

        public string AsString
        {
            get
            {
                var res = this.Value.AsString;

                this.lastRequestWasType = false;

                return res;
            }
        }

        public IArray AsSet
        {
            get
            {
                var res = this.Value.AsSet;

                this.lastRequestWasType = false;

                return res;
            }
        }

        public string Description
        {
            get
            {
                return this.rawExpression;
            }
        }

        public override string ToString()
        {
            var res = this.Value.ToString();

            this.lastRequestWasType = false;

            return res;
        }

        private void HandleVariableValueChanged(object sender, ValueChangedEventArgs args)
        {
            this.dirty = true;
        }

        private void BindEvents()
        {
            this.alwaysDirty = true;

            foreach (var expression in this.evaluator.Expressions)
            {
                if (expression is VariableExpression variableExpression)
                {
                    if (this.context.VariableManager.IsDefined(variableExpression.VariableName))
                    {
                        this.context.VariableManager.GetVariable(variableExpression.VariableName).ValueChanged += this.HandleVariableValueChanged;
                    }
                }
            }
        }
    }
}
