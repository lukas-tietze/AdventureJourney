#ifndef VERSION_HPP
#define VERSION_HPP

#include <string>
#include <cstring>

namespace version
{
const auto MajorVersion = 0;
const auto MinorVersion = 1;
const auto ProjectName = "AdventureJourney";
const auto VersionName = "Pre-Alpha";

namespace
{
std::string version_string = "";
}

const std::string &get_version()
{
    if (version_string.length() == 0)
    {
        auto count = 2+3+std::strlen(ProjectName) + std::strlen(VersionName) + 1;
        auto buf = new char[count];

        std::sprintf(buf, "%s v. %00i.%000i (%s)", ProjectName, MajorVersion, MinorVersion, VersionName);

        version_string.assign(buf, count - 1);

        delete[] buf;
    }

    return version_string;
}
} // namespace version

#endif /*VERSION_HPP*/