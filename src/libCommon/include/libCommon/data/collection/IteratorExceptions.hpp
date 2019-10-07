#pragma once

#include "libCommon/Exception.hpp"

namespace util
{
namespace collections
{
class CollectionChangedException : public util::Exception
{
public:
    CollectionChangedException();
};
} // namespace collections
} // namespace util
