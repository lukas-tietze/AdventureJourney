#include "util/Version.hpp"

namespace
{
std::string versionString = "";
}

const std::string &version::GetVersionString()
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