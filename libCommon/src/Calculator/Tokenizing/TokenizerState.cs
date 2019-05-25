namespace Matheparser.Tokenizing
{
    public class TokenizerState
    {
        private readonly string data;
        private readonly int pos;
        private readonly Token lastToken;

        public TokenizerState(char[] data, int pos, Token lastToken)
        {
            this.data = new string(data);
            this.pos = pos;
            this.lastToken = lastToken;
        }

        public string Data
        {
            get
            {
                return this.data;
            }
        }

        public int Pos
        {
            get
            {
                return this.pos;
            }
        }

        public Token LastToken
        {
            get
            {
                return this.lastToken;
            }
        }
    }
}
