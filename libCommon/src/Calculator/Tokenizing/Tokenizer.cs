using System;
using System.Collections.Generic;
using System.Text;

namespace Matheparser.Tokenizing
{
    public class Tokenizer
    {
        private readonly char[] data;
        private int pos;
        private readonly IConfig config;
        private readonly List<Token> tokens;
        private readonly Stack<char> bracketStack;
        bool lastWasWhiteSpace;
        private const char functionBracketMask = (char)(1 << (sizeof(char) * 8 - 2));

        public Tokenizer(string data, IConfig config)
        {
            this.data = data.ToCharArray();
            this.pos = 0;
            this.config = config;
            this.tokens = new List<Token>();
            this.bracketStack = new Stack<char>();
            this.lastWasWhiteSpace = false;
        }

        public TokenizerState State
        {
            get
            {
                return new TokenizerState(this.data, this.pos, this.tokens.Count > 0 ? this.tokens[this.tokens.Count - 1] : null);
            }
        }

        public IReadOnlyList<Token> Tokens
        {
            get
            {
                return this.tokens.AsReadOnly();
            }
        }

        public bool Finished
        {
            get
            {
                return this.pos >= this.data.Length;
            }
        }

        public void Reset()
        {
            this.pos = 0;
            this.tokens.Clear();
            this.bracketStack.Clear();
            this.lastWasWhiteSpace = false;
        }

        public void Run()
        {
            while (this.pos < this.data.Length)
            {
                var next = this.ReadNext();

                if (next != null)
                {
                    this.tokens.Add(next);
                }
            }

            if (this.bracketStack.Count != 0)
            {
                throw new MissingBracketException();
            }
        }

        private Token ReadNext()
        {
            this.lastWasWhiteSpace = false;

            if (char.IsWhiteSpace(this.data[this.pos]))
            {
                this.SkipWhiteSpace();
            }

            if (this.pos >= this.data.Length)
            {
                return null;
            }

            var c = this.data[this.pos];

            if (this.IsStartOfNumber(c))
            {
                return this.ReadNumber();
            }
            else if (c == this.config.StringSeperator)
            {
                return this.ReadString();
            }
            else if (this.IsStartOfIdentifier(c))
            {
                return this.ReadIdentifier();
            }
            else if(c == '$')
            {
                return this.ReadLazyExpression();
            }
            ////TODO An Config binden
            else if (c == '(')
            {
                var res = default(Token);

                if (this.tokens.Count != 0 && this.tokens[this.tokens.Count - 1].Type == TokenType.Identifier)
                {
                    res = new Token(TokenType.FunctionStart, this.tokens[this.tokens.Count - 1].Value);
                    this.tokens.RemoveAt(this.tokens.Count - 1);
                    c |= functionBracketMask;
                }
                else
                {
                    res = new Token(TokenType.OpeningBracket, c.ToString());
                }

                this.pos++;
                this.bracketStack.Push(c);
                return res;
            }
            ////TODO an config binden
            else if (c == ')')
            {
                if (this.bracketStack.Count == 0)
                {
                    throw new ExtraClosingBracketException(this.State);
                }

                this.pos++;
                var last = this.bracketStack.Pop();
                var type = TokenType.ClosingBracket;

                if ((last & functionBracketMask) != 0)
                {
                    last = (char)(last & ~functionBracketMask);
                    type = TokenType.FunctionEnd;
                }

                if (!this.config.AreMatchingBrackets(last, c))
                {
                    throw new MismatchingBracketException();
                }

                return new Token(type, c.ToString());
            }
            ////TODO an config binden
            else if (c == '{')
            {
                this.pos++;
                return new Token(TokenType.SetStart);
            }
            ////TODO an config binden
            else if (c == '}')
            {
                this.pos++;
                return new Token(TokenType.SetEnd);
            }
            ////TODO an config binden
            else if (c == '[')
            {
                this.pos++;
                return new Token(TokenType.AccessorStart);
            }
            ////TODO an config binden
            else if (c == ']')
            {
                this.pos++;
                return new Token(TokenType.AccessorEnd);
            }
            else if (c == this.config.ListSeperator)
            {
                this.pos++;
                return new Token(TokenType.Seperator, c.ToString());
            }
            else if (this.TryReadOperator(out var token))
            {
                return token;
            }
            else
            {
                throw new NotSupportedException();
            }
        }

        private Token ReadLazyExpression()
        {
            var start = ++this.pos;

            while(this.pos < this.data.Length && this.data[this.pos] != '$')
            {
                pos++;
            }

            pos++;

            return new Token(TokenType.LazyEvalSeperator, new string(this.data, start, pos - start - 1));
        }

        private bool TryReadOperator(out Token tokenOut)
        {
            var c1 = this.data[this.pos];
            var c2 = this.pos < this.data.Length - 1 ? this.data[this.pos + 1] : default(char);
            var token = default(Token);

            switch (c1)
            {
                case '+':
                    this.pos++;
                    token = new Token(TokenType.OperatorAdd);
                    break;
                case '-':
                    this.pos++;
                    token = new Token(TokenType.OperatorSub);
                    break;
                case '*':
                    this.pos++;
                    token = new Token(TokenType.OperatorMul);
                    break;
                case '/':
                    this.pos++;
                    token = new Token(TokenType.OperatorDiv);
                    break;
                case '%':
                    this.pos++;
                    token = new Token(TokenType.OperatorMod);
                    break;
                case '#':
                    this.pos++;
                    token = new Token(TokenType.OperatorLength);
                    break;
                case '^':
                    this.pos++;
                    token = new Token(TokenType.OperatorExp);
                    break;
                case '=':
                    if (c2 == '=')
                    {
                        this.pos += 2;
                        token = new Token(TokenType.OperatorEqual);
                        break;
                    }
                    else
                    {
                        throw new TokenizerException();
                    }
                case '>':
                    if (c2 == '=')
                    {
                        this.pos += 2;
                        token = new Token(TokenType.OperatorGreaterEqual);
                    }
                    else
                    {
                        this.pos += 1;
                        token = new Token(TokenType.OperatorGreater);
                    }

                    break;
                case '<':
                    if (c2 == '=')
                    {
                        this.pos += 2;
                        token = new Token(TokenType.OperatorLessEqual);
                    }
                    else
                    {
                        this.pos += 1;
                        token = new Token(TokenType.OperatorLess);
                    }
                    break;

                case '!':
                    if (c2 == '=')
                    {
                        this.pos += 2;
                        token = new Token(TokenType.OperatorNotEqual);
                    }
                    else
                    {
                        this.pos += 1;
                        token = new Token(TokenType.OperatorNot);
                    }
                    break;
            }

            tokenOut = token;
            return token != default(Token);
        }

        private Token ReadIdentifier()
        {
            var readStart = this.pos;

            do
            {
                ++this.pos;
            }
            while (this.pos < this.data.Length && this.IsPartOfIdentifier(this.data[this.pos]));

            return new Token(TokenType.Identifier, new string(this.data, readStart, this.pos - readStart));
        }

        private Token ReadString()
        {
            var sb = new StringBuilder();
            var escaped = false;

            while (++this.pos < this.data.Length)
            {
                var c = this.data[this.pos];

                if (escaped)
                {
                    sb.Append(this.Escape(c));
                    escaped = false;
                }
                else if (c == this.config.StringEscapeChar)
                {
                    escaped = true;
                }
                else if (c == this.config.StringSeperator)
                {
                    this.pos++;
                    break;
                }
                else
                {
                    sb.Append(c);
                }
            }

            return new Token(TokenType.String, sb.ToString());
        }

        private char Escape(char c)
        {
            switch (c)
            {
                case 'a':
                    return '\a';
                case 'b':
                    return '\b';
                case 'f':
                    return '\f';
                case 'n':
                    return '\n';
                case 'r':
                    return '\r';
                case 't':
                    return '\t';
                case 'v':
                    return '\v';
                case '\'':
                    return '\'';
                case '\"':
                    return '\"';
                case '\\':
                    return '\\';
                default:
                    throw new InvalidEscapeSequenceException();
            }
        }

        private Token ReadNumber()
        {
            var decSeperatorRead = false;
            var prefixRead = false;
            var readStart = this.pos;

            while (this.pos < this.data.Length)
            {
                var c = this.data[this.pos];

                if (!this.IsDigit(c))
                {
                    if (c == this.config.DecimalSeperator && !decSeperatorRead)
                    {
                        decSeperatorRead = true;
                    }
                    else if (c != '-' || prefixRead)
                    {
                        break;
                    }
                }

                prefixRead = true;

                this.pos++;
            }

            return new Token(TokenType.Number, new string(this.data, readStart, this.pos - readStart));
        }

        private void SkipWhiteSpace()
        {
            var readStart = this.pos;

            while (this.pos < this.data.Length && char.IsWhiteSpace(this.data[this.pos]))
            {
                this.pos++;
            }

            this.lastWasWhiteSpace = true;
        }

        private bool IsStartOfIdentifier(char c)
        {
            ////TODO: Vielleicht auch in die Config auslagern.
            return c >= 'a' && c <= 'z' ||
                    c >= 'A' && c <= 'Z' ||
                    c == '_';
        }

        private bool IsPartOfIdentifier(char c)
        {
            ////TODO: Vielleicht auch in die Config auslagern.
            return c >= 'a' && c <= 'z' ||
                    c >= 'A' && c <= 'Z' ||
                    c == '_';
        }

        private bool IsDigit(char c)
        {
            return c >= '0' && c <= '9';
        }

        private bool IsStartOfNumber(char c)
        {
            return this.IsDigit(c) || c == this.config.DecimalSeperator ||
                (c == '-' && (this.tokens.Count == 0 ||
                   (this.tokens.Count > 0 && this.tokens[this.tokens.Count - 1].Type == TokenType.OpeningBracket)));
        }
    }
}
