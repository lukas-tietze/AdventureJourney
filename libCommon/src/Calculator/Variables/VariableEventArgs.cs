namespace Matheparser.Variables
{
    public class VariableEventArgs : System.EventArgs
    {
        public VariableEventArgs(IVariable variable)
        {
            this.Variable = variable;
            this.VariableName = variable.Name;
        }

        public VariableEventArgs(string variableName)
        {
            this.Variable = null;
            this.VariableName = variableName;
        }

        public string VariableName
        {
            get;
        }

        public IVariable Variable
        {
            get;
            set;
        }
    }
}