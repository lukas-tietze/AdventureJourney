#pragma once

#include <string>
#include <cstring>

namespace version
{
const auto MajorVersion = 0;
const auto MinorVersion = 1;
const auto ProjectName = "AdventureJourney";
const auto VersionName = "Pre-Alpha";

const std::string &GetVersionString();
} // namespace version