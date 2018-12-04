#pragma once

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
std::string versionString = "";
}

const std::string &GetVersion()
{
    if (versionString.length() == 0)
    {
        auto count = 2+3+std::strlen(ProjectName) + std::strlen(VersionName) + 1;
        auto buf = new char[count];

        std::sprintf(buf, "%s v. %00i.%000i (%s)", ProjectName, MajorVersion, MinorVersion, VersionName);

        versionString.assign(buf, count - 1);

        delete[] buf;
    }

    return versionString;
}
} // namespace version