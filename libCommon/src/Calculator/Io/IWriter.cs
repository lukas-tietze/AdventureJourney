using System;

namespace Matheparser.Io
{
    public interface IWriter : IDisposable
    {
        bool Enabled
        {
            get;
            set;
        }

        bool IndentEnabled
        {
            get;
            set;
        }

        void BeginIndent(string indent, bool append);

        void EndIndent();

        void ClearIndent();

        void Clear();

        void Write(string msg);

        void WriteLine(string msg);

        void Write(string format, params object[] args);

        void WriteLine(string format, params object[] args);
        
        void WriteLine();
    }
}