using Matheparser.Values;

namespace Matheparser.Functions
{
    public interface IFunction
    {
        string Name
        {
            get;
        }

        IValue Eval(CalculationContext context, IValue[] parameters);

        FunctionInfo[] GetFunctionInfos();
    }
}
