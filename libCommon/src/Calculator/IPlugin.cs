using Matheparser.Functions;

namespace Api
{
    public interface IPlugin
    {
        void Init(CalculationContext activeContext);

        void Dispose();
    }
}