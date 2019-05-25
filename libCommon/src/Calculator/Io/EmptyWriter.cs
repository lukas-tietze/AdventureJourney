namespace Matheparser.Io
{
    public class EmptyWriter : WriterBase
    {
        public override void Clear()
        {
        }

        protected override void WriteCore(string msg)
        {
        }

        protected override void WriteLineCore(string msg)
        {
        }

        protected override void WriteLineCore()
        {
        }
    }
}