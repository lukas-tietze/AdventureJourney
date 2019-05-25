using System;

namespace Matheparser.Io
{
    public class EmptyReader : IReader
    {
        public bool EnablePrompt
        {
            get;
            set;
        }

        public ConsoleKey ReadKey()
        {
            return default(ConsoleKey);
        }

        public ConsoleKey ReadKey(string prompt)
        {
            return this.ReadKey();
        }

        public string ReadLine()
        {
            return string.Empty;
        }

        public string ReadLine(string prompt)
        {
            return this.ReadLine();
        }

        public void Dispose()
        {
        }
    }
}