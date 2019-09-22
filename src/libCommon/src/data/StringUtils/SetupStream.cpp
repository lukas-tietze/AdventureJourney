#include "libCommon/data/String.hpp"

namespace
{
int ReadHex(std::iostream &stream, const std::string &format, int i)
{
	return i;
}
} // namespace

/*
 * Format:
 *      %{options}
 * Optionen:
 *      hex     format integer as hexadecimal number
 *      bin     format integer as binary number
 *      oct     format integer as octal number
 *      x.y     print x digits before comma and y after
 *      0x.y    print x digits before commat and y after
 */
void util::SetupStreamByPrintfFormat(std::iostream &stream, const std::string &format)
{
    for (int i = 0; i < format.length(); i++)
    {
        switch (format[i])
        {
        case 'h':
            break;
        case 'o':
            break;
        case 'b':
            break;
        case '0':
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            break;
        default:
            break;
        }
    }
}