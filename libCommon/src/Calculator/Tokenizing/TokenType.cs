namespace Matheparser.Tokenizing
{
    public enum TokenType
    {
        String = 0x0000,
        Number = 0x0001,
        Identifier = 0x0002,
        Seperator = 0x0003,
        OpeningBracket = 0x0004,
        ClosingBracket = 0x0005,
        SetStart = 0x0006,
        SetEnd = 0x0007,
        AccessorStart = 0x0008,
        AccessorEnd = 0x0009,
        FunctionStart = 0x000A,
        FunctionEnd = 0x000B,
        LazyEvalSeperator = 0x000C,

        Operator = 0x1000,
        OperatorAdd = 0x1C01,
        OperatorSub = 0x1C02,
        OperatorMul = 0x1D03,
        OperatorDiv = 0x1D04,
        OperatorExp = 0x1E05,
        OperatorMod = 0x1D05,
        OperatorNot = 0x1C06,
        OperatorLength = 0x1C07,
        OperatorEqual = 0x1A08,
        OperatorNotEqual = 0x1A09,
        OperatorGreater = 0x1A0A,
        OperatorGreaterEqual = 0x1A0B,
        OperatorLess = 0x1A0C,
        OperatorLessEqual = 0x1A0D,
    }
}
