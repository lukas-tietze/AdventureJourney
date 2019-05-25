using Matheparser.Values;

namespace Matheparser.Functions
{
    public abstract class FunctionBase : IFunction
    {
        public abstract string Name
        {
            get;
        }

        protected CalculationContext Context
        {
            get;
            private set;
        }

        public abstract IValue Eval(IValue[] parameters);

        public IValue Eval(CalculationContext context, IValue[] parameters)
        {
            this.Context = context;
            return this.Eval(parameters);
        }

        // public abstract FunctionInfo[] GetFunctionInfos()
        public FunctionInfo[] GetFunctionInfos()
        {
            return new FunctionInfo[] { FunctionInfo.MissingInfo };
        }
    }
}
