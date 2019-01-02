#include "util/Conversions.hpp"
#include "data/String.hpp"

std::string logic::FormatAsTons(long value)
{
    if (value < 1000)
    {
        return util::Format("%li t", value);
    }
    else if (value < 1000 * 1000)
    {
        return util::Format("%.1f kt", value / 1000.0);
    }
    else if (value < 1000 * 1000 * 1000)
    {
        return util::Format("%.1f mt", value / (1000.0 * 1000.0));
    }
    else
    {
        return util::Format("%.1f gt", value / (1000.0 * 1000.0 * 1000.0));
    }
}