#include "Objects.hpp"
#include "data/EnumHelper.hpp"

std::ostream &glutil::operator<<(std::ostream &s, FontContent value)
{
    switch (value)
    {
    case FontContent::AZaz09Space:
        s << "AZaz09Space";
        break;
    case FontContent::Ascii32To126:
        s << "Ascii32To126";
        break;
    case FontContent::Custom:
        s << "Custom";
        break;
    default:
        throw util::InvalidCaseException::MakeException(value);
    }

    return s;
}

template <>
const std::initializer_list<glutil::FontContent> &util::ListValues<glutil::FontContent>()
{
    static constexpr std::initializer_list<glutil::FontContent> values{
        glutil::FontContent::AZaz09Space,
        glutil::FontContent::Ascii32To126,
        glutil::FontContent::Custom,
    };

    return values;
}
