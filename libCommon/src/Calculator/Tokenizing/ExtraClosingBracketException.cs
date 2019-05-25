namespace Matheparser.Tokenizing
{
    using System;

    internal class ExtraClosingBracketException : Exception
    {
        public ExtraClosingBracketException(TokenizerState state):
            base(string.Format("Extra Closing Bracket at {0} in {1}", state.Pos, state.Data))
        {
        }
    }
}