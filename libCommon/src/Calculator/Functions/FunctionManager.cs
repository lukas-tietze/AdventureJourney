namespace Matheparser.Functions
{
    using System;
    using System.Collections.Generic;
    using Matheparser.Exceptions;
    using Matheparser.Functions.DefaultFunctions.Calculations;

    public class FunctionManager
    {
        private readonly Dictionary<string, IFunction> functions;

        public FunctionManager() :
            this(false)
        {
        }

        public FunctionManager(bool defineDefaultFunctions)
        {
            this.functions = new Dictionary<string, IFunction>();

            if (defineDefaultFunctions)
            {
                foreach (var type in typeof(FunctionManager).Assembly.GetTypes())
                {
                    if (typeof(IFunction).IsAssignableFrom(type) && !type.IsInterface && !type.IsAbstract)
                    {
                        this.Define((IFunction)Activator.CreateInstance(type));
                    }
                }
            }
        }

        public void Define(IFunction function)
        {
            this.functions.Add(function.Name, function);
        }

        public IFunction FindByName(string name)
        {
            if (this.functions.TryGetValue(name, out var function))
            {
                return function;
            }

            throw new MissingFunctionException(name);
        }

        public void Clear()
        {
            this.functions.Clear();
        }

        public bool IsDefined(string expression)
        {
            return this.functions.ContainsKey(expression);
        }
    }
}
