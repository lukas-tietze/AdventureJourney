using System;

namespace Matheparser.Io
{
    public interface IReader : IDisposable
    {
        bool EnablePrompt
        {
            set;
        }

        string ReadLine();

        string ReadLine(string prompt);

        System.ConsoleKey ReadKey();

        System.ConsoleKey ReadKey(string prompt);
    }
}