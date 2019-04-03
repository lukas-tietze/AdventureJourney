#include "data/String.hpp"

/*
 * Format:
 *      %{[index:]options} => %{[(0-9)+:(optionslist...)]}
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
    }
}