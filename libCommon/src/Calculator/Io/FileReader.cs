using System;
using System.IO;

namespace Matheparser.Io
{
    public class FileReader : IReader
    {
        private string path;
        private StreamReader input;

        public FileReader(string path)
        {
            this.path = path;
            this.input = new StreamReader(path);
        }

        public bool EnablePrompt
        {
            get;
            set;
        }

        public ConsoleKey ReadKey()
        {
            return (ConsoleKey)this.input.Read();
        }

        public ConsoleKey ReadKey(string prompt)
        {
            return this.ReadKey();
        }

        public string ReadLine()
        {
            return this.input.ReadLine();
        }

        public string ReadLine(string prompt)
        {
            return this.ReadLine();
        }

        public virtual void Dispose()
        {
            this.input.Close();
            this.input.Dispose();
        }
    }
}