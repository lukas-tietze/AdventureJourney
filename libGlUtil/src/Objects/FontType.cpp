#include "Objects.hpp"
#include "data/EnumHelper.hpp"

std::ostream &glutil::operator<<(std::ostream &s, FontType value)
{
    switch (value)
    {
    case FontType::BitMap:
        s << "BitMap";
        break;
    case FontType::TrueType:
        s << "TrueTypes";
        break;
    default:
        throw util::InvalidCaseException::MakeException(value);
    }

    return s;
}

template <>
const std::initializer_list<glutil::FontType> &util::ListValues<glutil::FontType>()
{
    static constexpr std::initializer_list<glutil::FontType> values{
        glutil::FontType::BitMap,
        glutil::FontType::TrueType,
    };

    return values;
}
