using System.Collections.Generic;

namespace Matheparser.Io
{
    public class MultiWriter : IWriter
    {
        private List<IWriter> writers;

        public MultiWriter()
        {
            this.writers = new List<IWriter>();
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

        public void Add(IWriter writer)
        {
            this.writers.Add(writer);
        }

        public void BeginIndent(string indent, bool append)
        {
            foreach (var writer in this.writers)
            {
                writer.BeginIndent(indent, append);
            }
        }

        public void Clear()
        {
            foreach (var writer in this.writers)
            {
                writer.Clear();
            }
        }

        public void ClearIndent()
        {
            foreach (var writer in this.writers)
            {
                writer.ClearIndent();
            }
        }

        public void Dispose()
        {
            foreach (var writer in this.writers)
            {
                writer.Dispose();
            }
        }

        public void EndIndent()
        {
            foreach (var writer in this.writers)
            {
                writer.EndIndent();
            }
        }

        public void Remove(IWriter writer)
        {
            this.writers.Remove(writer);
        }

        public void Write(string msg)
        {
            foreach (var writer in this.writers)
            {
                writer.Write(msg);
            }
        }

        public void Write(string format, params object[] args)
        {
            foreach (var writer in this.writers)
            {
                writer.Write(format, args);
            }
        }

        public void WriteLine(string msg)
        {
            foreach (var writer in this.writers)
            {
                writer.WriteLine(msg);
            }
        }

        public void WriteLine(string format, params object[] args)
        {
            foreach (var writer in this.writers)
            {
                writer.WriteLine(format, args);
            }
        }

        public void WriteLine()
        {
            foreach (var writer in this.writers)
            {
                writer.WriteLine();
            }
        }
    }
}