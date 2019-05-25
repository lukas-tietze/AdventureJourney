namespace Matheparser.Functions
{
    using System.Text;

    public sealed class FunctionInfo
    {
        private string shortInfo;
        private string fullInfo;

        public FunctionInfo(string name, ParameterInfo[] parameters, ParameterInfo returnValue, string description)
        {
            this.Name = name;
            this.Parameters = parameters;
            this.ReturnValue = returnValue;
            this.Description = description;

            this.shortInfo = string.Empty;
            this.fullInfo = string.Empty;
        }

        public static FunctionInfo MissingInfo
        {
            get
            {
                return new FunctionInfo("<missing info>", null, null, "The Function is not yet properly described.");
            }
        }

        public string Name
        {
            get;
        }

        public ParameterInfo[] Parameters
        {
            get;
        }

        public ParameterInfo ReturnValue
        {
            get;
        }

        public string Description
        {
            get;
        }

        public string ShortInfo
        {
            get
            {
                if (string.IsNullOrEmpty(this.shortInfo))
                {
                    var sb = new StringBuilder();

                    sb.AppendFormat("{0} {1}(", this.ReturnValue == null ? "void" : this.ReturnValue.Type.ToString(), this.Name);

                    if (this.Parameters != null)
                    {
                        for (int i = 0; i < this.Parameters.Length; i++)
                        {
                            sb.Append(this.Parameters[i].Type.ToString());

                            if (i < this.Parameters.Length - 1)
                            {
                                sb.Append(", ");
                            }
                        }
                    }

                    sb.AppendFormat(") - {0}", this.Description);

                    this.shortInfo = sb.ToString();
                }

                return this.shortInfo;
            }
        }

        public string FullInfo
        {
            get
            {
                if (string.IsNullOrEmpty(this.fullInfo))
                {
                    var sb = new StringBuilder();

                    sb.AppendLine(this.ShortInfo);

                    if (this.Parameters != null)
                    {
                        for (int i = 0; i < this.Parameters.Length; i++)
                        {
                            sb.AppendFormat("\t{0} {1} - {2}", this.Parameters[i].Type, this.Parameters[i].Name, this.Parameters[i].Description).AppendLine();
                        }
                    }

                    this.fullInfo = sb.ToString();
                }

                return this.fullInfo;
            }
        }
    }
}