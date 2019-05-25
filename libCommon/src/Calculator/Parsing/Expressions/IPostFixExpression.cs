using Matheparser.Functions;
using Matheparser.Values;

namespace Matheparser.Parsing.Expressions
{
    public interface IPostFixExpression
    {
        int ArgCount
        {
            get;
        }

        ExpressionType Type
        {
            get;
        }

        IValue Eval(CalculationContext context, IValue[] operands);
    }
}
