using System;
using System.Collections.Generic;
using Matheparser.Exceptions;
using Matheparser.Functions;
using Matheparser.Util;
using Matheparser.Values;

namespace Matheparser.Parsing.Expressions.Unary
{
    public abstract class UnaryOperatorExpressionBase : IPostFixExpression
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
                return 1;
            }
        }

        public IValue Eval(CalculationContext context, IValue[] operands)
        {
            this.Validate(operands);

            switch (operands[0].Type)
            {
                case Values.ValueType.String:
                    return this.EvalString(operands[0].AsString);
                case Values.ValueType.Number:
                    return this.EvalNumber(operands[0].AsDouble);
                case Values.ValueType.Set:
                    return this.EvalSet(operands[0].AsSet);
                default:
                    throw new NotSupportedException();
            }
        }

        internal abstract IValue EvalSet(IArray operand);
        internal abstract IValue EvalNumber(double operand);
        internal abstract IValue EvalString(string operand);

        private void Validate(IValue[] operands)
        {
            if (operands.Length != 1)
            {
                throw new OperandNumberException();
            }
        }
    }
}
