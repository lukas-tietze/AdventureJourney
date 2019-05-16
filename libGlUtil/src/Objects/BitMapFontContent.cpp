#include "Objects.hpp"
#include "data/EnumHelper.hpp"

std::ostream &glutil::operator<<(std::ostream &s, BitMapFontContent value)
{
    switch (value)
    {
    case BitMapFontContent::AZaz09Space:
        s << "AZaz09Space";
        break;
    case BitMapFontContent::Ascii32To126:
        s << "Ascii32To126";
        break;
    case BitMapFontContent::Custom:
        s << "Custom";
        break;
    default:
        throw util::InvalidCaseException::MakeException(value);
    }

    return s;
}

template <>
const std::initializer_list<glutil::BitMapFontContent> &util::ListValues<glutil::BitMapFontContent>()
{
    return std::initializer_list<glutil::BitMapFontContent>{
        glutil::BitMapFontContent::AZaz09Space,
        glutil::BitMapFontContent::Ascii32To126,
        glutil::BitMapFontContent::Custom,
    };
}
