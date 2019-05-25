namespace Matheparser.Functions
{
    using System.Globalization;
    using Matheparser.Io;
    using Matheparser.Variables;

    public sealed class CalculationContext
    {
        private IWriter outWriter;
        private IWriter errWriter;
        private IReader reader;

        public CalculationContext(IConfig config)
        {
            this.VariableManager = new VariableManager(true);
            this.FunctionManager = new FunctionManager(true);
            this.Config = config;
            this.Culture = config.Culture;
            this.Out = new ConsoleWriter();
            this.Err = new ConsoleWriter();
            this.In = new ConsoleReader();
        }

        public CalculationContext(VariableManager variableManager, FunctionManager functionManager, IConfig config, IWriter outWriter, IWriter errWriter, IReader reader)
        {
            this.VariableManager = variableManager;
            this.FunctionManager = functionManager;
            this.Config = config;
            this.Culture = config.Culture;
            this.Out = outWriter;
            this.Err = errWriter;
            this.In = reader;
        }

        public VariableManager VariableManager { get; set; }

        public FunctionManager FunctionManager { get; set; }

        public IConfig Config { get; set; }

        public CultureInfo Culture { get; set; }

        public IWriter Out
        {
            get
            {
                return this.outWriter;
            }

            set
            {
                if (this.outWriter != null)
                {
                    this.outWriter.Dispose();
                }

                this.outWriter = value;
            }
        }

        public IWriter Err
        {
            get
            {
                return this.errWriter;
            }

            set
            {
                if (this.errWriter != null)
                {
                    this.errWriter.Dispose();
                }

                this.errWriter = value;
            }
        }

        public IReader In
        {
            get
            {
                return this.reader;
            }

            set
            {
                if (this.reader != null)
                {
                    this.reader.Dispose();
                }

                this.reader = value;
            }
        }
    }
}
