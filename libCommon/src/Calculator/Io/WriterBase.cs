using System.Collections.Generic;

namespace Matheparser.Io
{
    public abstract class WriterBase : IWriter
    {
        private Stack<string> indentStack;

        public WriterBase()
        {
            this.indentStack = new Stack<string>();
            this.Enabled = true;
            this.IndentEnabled = true;
        }

        public bool Enabled
        {
            get;
            set;
        }

        public bool IndentEnabled
        {
            get;
            set;
        }

        public void BeginIndent(string indent, bool append)
        {
            this.indentStack.Push(append && this.indentStack.Count > 0 ? this.indentStack.Peek() + indent : indent);
        }

        public void ClearIndent()
        {
            this.indentStack.Clear();
        }

        public void EndIndent()
        {
            if (this.indentStack.Count > 0)
            {
                this.indentStack.Pop();
            }
        }

        public abstract void Clear();

        public void Write(string msg)
        {
            if (this.Enabled)
            {
                this.WriteCore(this.GetMsg(msg));
            }
        }

        public void Write(string format, params object[] args)
        {
            if (this.Enabled)
            {
                this.WriteCore(this.GetMsg(format, args));
            }
        }

        public void WriteLine(string msg)
        {
            if (this.Enabled)
            {
                this.WriteLineCore(this.GetMsg(msg));
            }
        }

        public void WriteLine(string format, params object[] args)
        {
            if (this.Enabled)
            {
                this.WriteLineCore(this.GetMsg(format, args));
            }
        }

        public void WriteLine()
        {
            if (this.Enabled)
            {
                this.WriteLineCore();
            }
        }

        private string GetMsg(string format, object[] args)
        {
            return this.GetMsg(string.Format(format, args));
        }

        private string GetMsg(string msg)
        {
            if (this.indentStack.Count > 0 && this.IndentEnabled)
            {
                return string.Concat(this.indentStack.Peek(), msg);
            }

            return msg;
        }

        protected abstract void WriteCore(string msg);

        protected abstract void WriteLineCore(string msg);

        protected abstract void WriteLineCore();

        public virtual void Dispose()
        {
        }
    }
}