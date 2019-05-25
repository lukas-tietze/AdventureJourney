using System.Collections.Generic;
using System.Diagnostics;

namespace Matheparser.Tokenizing
{

    [DebuggerDisplay("Type={type}, Value={value}")]
    public sealed class Token
    {
        private TokenType type;
        private string value;

        public Token(TokenType type):
            this(type, string.Empty)
        {
        }

        public Token(TokenType type, string value)
        {
            this.type = type;
            this.value = value;
        }

        public TokenType Type
        {
            get
            {
                return this.type;
            }
        }

        public string Value
        {
            get
            {
                return this.value;
            }
        }
    }
}
