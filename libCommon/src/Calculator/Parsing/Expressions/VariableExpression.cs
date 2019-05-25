using Matheparser.Exceptions;
using Matheparser.Functions;
using Matheparser.Values;
using Matheparser.Variables;

namespace Matheparser.Parsing.Expressions
{
    public sealed class VariableExpression : IPostFixExpression
    {
        private readonly string name;

        public VariableExpression(string name)
        {
            this.name = name;
        }

        public string VariableName
        {
            get
            {
                return this.name;
            }
        }

        public ExpressionType Type
        {
            get
            {
                return ExpressionType.Value;
            }
        }

        public int ArgCount
        {
            get
            {
                return 0;
            }
        }

        public IValue Eval(CalculationContext context, IValue[] operands)
        {
            this.Validate(operands);

            return context.VariableManager.GetValue(this.name);
        }

        private void Validate(IValue[] operands)
        {
            if (operands != null && operands.Length != 0)
            {
                throw new OperandEvaluationException();
            }
        }
    }
}
