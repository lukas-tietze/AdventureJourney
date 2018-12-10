namespace test
{
namespace jsonTest
{
int Integrity();
int ExpandedRead();
int CompactRead();
int ExpandedWrite();
int CompactWrite();
int ReadWrite();
int WriteRead();
int StringEscaping();
int NumberParsing();
} // namespace JsonTest
namespace colorTest
{
int BasicColorValues();
}
namespace eventTest
{
int FunctionEvents();
int ListenerEvents();
int HandlerEvents();
int MemberHandlerEvents();
} // namespace EventTest
namespace geometryTest
{
int TestRectangle();
}
namespace stringTest
{
int Format();
int ToUpper();
int ToLower();
int SplitSpace();
int SplitCustomChar();
int SplitMultipleChars();
int SplitFunction();
int Strip();
int StripFront();
int StripBack();
} // namespace StringTest
namespace mathTest
{
int TestHex4ToNumber();
int TestHexToNumber();
int TestIsHexChar();
int TestCrop();
} // namespace MathTest
namespace dataTest
{
namespace collectionTest
{
int TestArray();
int TestCollectRope();
int TestCache();
} // namespace CollectionTest
} // namespace DataTest
} // namespace test