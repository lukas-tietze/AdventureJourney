using System;
using System.Collections.Generic;
using Matheparser.Values;

namespace Matheparser.Variables
{
    public class VariableManager
    {
        private Dictionary<string, IVariable> variables;
        private MissingVariableMode missingVariableMode;

        public VariableManager() :
            this(false)
        {
        }

        public VariableManager(bool setDefaultVariables)
        {
            this.variables = new Dictionary<string, IVariable>();
            this.missingVariableMode = MissingVariableMode.Error;

            if (setDefaultVariables)
            {
                this.SetDefaultVariables();
            }
        }

        public event EventHandler<VariableEventArgs> VariableDefined;

        public event EventHandler<VariableEventArgs> VariableRemoved;

        public event EventHandler<VariableEventArgs> VariableMissing;

        public void Remove(string key)
        {
            if (this.variables.TryGetValue(key, out var variable))
            {
                this.variables.Remove(key);

                this.OnVariableRemoved(variable);
            }
        }

        public void Define(IVariable variable)
        {
            this.variables[variable.Name] = variable;

            this.OnVariableDefined(variable);
        }

        public IVariable GetVariable(string name)
        {
            if (this.variables.TryGetValue(name, out var res))
            {
                return this.variables[name];
            }

            throw new UndefinedVariableException(name);
        }

        public IVariable CreateTempVariable()
        {
            var count = DateTime.UtcNow.Ticks;
            var nameBase = "__temp__";
            var name = nameBase + count;

            while (this.variables.ContainsKey(name))
            {
                name = nameBase + ++count;
            }

            var tmp = new Variable(name, new EmptyValue());

            this.Define(tmp);

            return tmp;
        }

        public bool IsDefined(string name)
        {
            return this.variables.ContainsKey(name);
        }

        public IValue GetValue(string name)
        {
            if (this.variables.TryGetValue(name, out var res))
            {
                return res.Value;
            }

            throw new UndefinedVariableException(name);
        }

        public void ClearAll()
        {
            ////TODO evtl. überarbeiten, sodass für jede Variable ein Remove-Event kommt?
            this.variables.Clear();
        }

        public void ClearUserVariables()
        {
            this.ClearAll();
            this.SetDefaultVariables();
        }

        private void SetDefaultVariables()
        {
            this.Define(new Variable("e", new DoubleValue(Math.E)));
            this.Define(new Variable("pi", new DoubleValue(Math.PI)));
        }

        private void OnVariableDefined(IVariable variable)
        {
            var args = new VariableEventArgs(variable);

            this.VariableDefined?.Invoke(this, args);
        }

        private void OnVariableRemoved(IVariable variable)
        {
            var args = new VariableEventArgs(variable);

            this.VariableRemoved?.Invoke(this, args);
        }

        private IVariable OnVariableMissing(string name)
        {
            var args = new VariableEventArgs(name);

            this.VariableMissing?.Invoke(this, args);

            return args.Variable;
        }

        private IVariable HandleMissingVariable(string name)
        {
            var res = default(IVariable);

            switch (this.missingVariableMode)
            {
                case MissingVariableMode.Error:
                    throw new UndefinedVariableException(name);
                case MissingVariableMode.DefaultValue:
                    res = new Variable(name, new EmptyValue());
                    this.Define(res);
                    return res;
                case MissingVariableMode.Ask:
                    res = this.OnVariableMissing(name);

                    if (res != null)
                    {
                        this.Define(res);
                        return res;
                    }

                    throw new UndefinedVariableException(name);
                default:
                    throw new System.NotSupportedException();
            }
        }

        public enum MissingVariableMode
        {
            Error,
            DefaultValue,
            Ask,
        }
    }
}
