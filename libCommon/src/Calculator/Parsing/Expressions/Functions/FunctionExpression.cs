using Matheparser.Functions;
using Matheparser.Values;

namespace Matheparser.Parsing.Expressions.Functions
{
    public class FunctionExpression : IPostFixExpression
    {
        private readonly string name;
        private readonly int argCount;

        public FunctionExpression(string name, int argCount)
        {
            this.name = name;
            this.argCount = argCount;
        }

        public ExpressionType Type
        {
            get
            {
                return ExpressionType.Function;
            }
        }

        public int ArgCount
        {
            get
            {
                return this.argCount;
            }
        }

        public IValue Eval(CalculationContext context, IValue[] operands)
        {
            var function = context.FunctionManager.FindByName(this.name);

            return function.Eval(context, operands);
        }
    }
}
