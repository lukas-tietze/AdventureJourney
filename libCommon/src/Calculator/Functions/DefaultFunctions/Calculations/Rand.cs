namespace Matheparser.Functions.DefaultFunctions.Calculations
{
    using System;
    using Matheparser.Values;

    public sealed class Rand : FunctionBase
    {
        private readonly Random rand;

        public Rand()
        {
            this.rand = new Random();
        }

        public override string Name
        {
            get
            {
                return "RND";
            }
        }

        public override IValue Eval(IValue[] parameters)
        {
            if (parameters.Length == 0)
            {
                return new DoubleValue(this.rand.NextDouble());
            }
            else if(parameters.Length == 1 && parameters[0].Type == Values.ValueType.Number)
            {
                return new DoubleValue(this.rand.NextDouble() * parameters[0].AsDouble);
            }
            else if(parameters.Length == 2 && parameters[0].Type == Values.ValueType.Number && parameters[1].Type == Values.ValueType.Number)
            {
                return new DoubleValue(this.rand.NextDouble() * (parameters[1].AsDouble - parameters[0].AsDouble) + parameters[0].AsDouble);
            }
            else
            {
                throw new ArgumentException();
            }
        }
    }
}
