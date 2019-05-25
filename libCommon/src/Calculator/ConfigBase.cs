using System;
using System.Collections.Generic;
using System.Globalization;

namespace Matheparser
{
    public class ConfigBase : IConfig
    {
        private readonly char decimalSeperator;
        private readonly char stringSeperator;
        private readonly char listSeperator;
        private readonly char stringEscapeChar;
        private readonly char[] openingBrackets;
        private readonly char[] closingBrackets;
        private char[] openingArrayBrackets;
        private char[] closingArrayBrackets;
        private CultureInfo culture;

        public static IConfig DefaultConfig
        {
            get
            {
                return new ConfigBase(
                    decimalSeperator: '.',
                    stringSeperator: '"',
                    listSeperator: ',',
                    stringEscapeChar: '\\',
                    openingBrackets: new char[] { '(' },
                    closingBrackets: new char[] { ')' }
                );
            }
        }

        public ConfigBase(char decimalSeperator,
                      char stringSeperator,
                      char listSeperator,
                      char stringEscapeChar,
                      char[] openingBrackets,
                      char[] closingBrackets)
        {
            this.decimalSeperator = decimalSeperator;
            this.stringSeperator = stringSeperator;
            this.listSeperator = listSeperator;
            this.stringEscapeChar = stringEscapeChar;
            this.openingBrackets = openingBrackets;
            this.closingBrackets = closingBrackets;

            if (!this.Validate())
            {
                throw new ArgumentException();
            }

            this.culture = (CultureInfo)CultureInfo.CurrentCulture.Clone();

            this.culture.NumberFormat.NumberDecimalSeparator = this.decimalSeperator.ToString();
        }

        public CultureInfo Culture
        {
            get
            {
                return this.culture;
            }
        }

        private bool Validate()
        {
            var chars = new List<char>()
            {
                this.decimalSeperator,
                this.stringSeperator,
                this.listSeperator,
                this.stringEscapeChar,
            };

            chars.AddRange(this.openingBrackets);
            chars.AddRange(this.closingBrackets);

            for (var i = 0; i < chars.Count - 1; i++)
            {
                for (var j = i + 1; j < chars.Count; j++)
                {
                    if (chars[i] == chars[j])
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        public bool IsOpeningBracket(char c)
        {
            for (var i = 0; i < this.openingBrackets.Length; i++)
            {
                if (this.openingBrackets[i] == c)
                {
                    return true;
                }
            }

            return false;
        }

        public bool IsClosingBracket(char c)
        {
            for (var i = 0; i < this.closingBrackets.Length; i++)
            {
                if (this.closingBrackets[i] == c)
                {
                    return true;
                }
            }

            return false;
        }

        public bool AreMatchingBrackets(char a, char b)
        {
            for (var i = 0; i < this.openingBrackets.Length; i++)
            {
                if (this.openingBrackets[i] == a)
                {
                    return this.closingBrackets[i] == b;
                }
            }

            throw new ArgumentException("Bracket type not found");
        }

        public char StringSeperator
        {
            get
            {
                return this.stringSeperator;
            }
        }

        public char DecimalSeperator
        {
            get
            {
                return this.decimalSeperator;
            }
        }

        public char ListSeperator
        {
            get
            {
                return this.listSeperator;
            }
        }

        public char StringEscapeChar
        {
            get
            {
                return this.stringEscapeChar;
            }
        }

        public IConfig Clone()
        {
            return new ConfigBase
            (
                decimalSeperator: this.decimalSeperator,
                stringSeperator: this.stringSeperator,
                listSeperator: this.listSeperator,
                stringEscapeChar: this.stringEscapeChar,
                openingBrackets: this.openingBrackets,
                closingBrackets: this.closingBrackets
            );
        }
    }
}
