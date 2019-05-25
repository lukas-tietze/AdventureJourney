namespace Matheparser.Io
{
    using System;
    using System.Collections.Generic;
    using System.IO;

    public class FileWriter : WriterBase
    {
        private StreamWriter output;

        public FileWriter(string path)
        {
            this.output = new StreamWriter(path);
        }

        public override void Clear()
        {
            this.output.Flush();
        }

        protected override void WriteCore(string msg)
        {
            this.output.Write(msg);
        }

        protected override void WriteLineCore(string msg)
        {
            this.output.WriteLine(msg);
        }

        protected override void WriteLineCore()
        {
            this.output.WriteLine();
        }

        public override void Dispose()
        {
            this.output.Close();
            this.output.Dispose();
        }
    }
}