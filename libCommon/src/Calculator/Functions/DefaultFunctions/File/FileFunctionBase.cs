namespace Matheparser.Functions.DefaultFunctions.File
{
    using Matheparser.Exceptions;
    using Matheparser.Values;

    public abstract class FileFunctionBase : FunctionBase
    {
        public override IValue Eval(IValue[] parameters)
        {
            this.Validate(parameters);

            return new StringValue(this.Eval(parameters[0].AsString));
        }

        protected abstract string Eval(string arg);

        protected virtual void Validate(IValue[] parameters)
        {
            if(parameters.Length != 1)
            {
                throw new OperandNumberException();
            }

            if(parameters[0].Type != Values.ValueType.String)
            {
                throw new WrongOperandTypeException();
            }
        }
    }
}
