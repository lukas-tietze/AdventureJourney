using System.Collections.Generic;
using Matheparser.Exceptions;
using Matheparser.Functions;
using Matheparser.Util;
using Matheparser.Values;

namespace Matheparser.Parsing.Expressions.Binary
{
    public abstract class BinaryOperatorExpressionBase : IPostFixExpression
    {
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
                return 2;
            }
        }

        public IValue Eval(CalculationContext context, IValue[] operands)
        {
            this.Validate(operands);

            if (operands[0].Type == ValueType.Set || operands[1].Type == ValueType.Set)
            {
                return this.EvalSet(operands[0].AsSet, operands[1].AsSet);
            }

            if (operands[0].Type == ValueType.Number)
            {
                return this.EvalNumber(operands[0].AsDouble, operands[1].AsDouble);
            }

            return this.EvalString(operands[0].AsString, operands[1].AsString);
        }

        internal abstract IValue EvalString(string string1, string string2);
        internal abstract IValue EvalNumber(double double1, double double2);
        internal abstract IValue EvalSet(IArray setA, IArray setB);

        private void Validate(IValue[] operands)
        {
            if (operands.Length != 2)
            {
                throw new OperandNumberException();
            }

            if (operands[0].Type != operands[1].Type && operands[0].Type != ValueType.Set)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
