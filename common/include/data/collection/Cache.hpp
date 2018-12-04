#pragma once

#include <unordered_map>

namespace util
{
enum class CachePolicy
{
    FirstInFirstOut,
    LastInFirstOut,
    LeastUsedFirst
}; /*CachePolicy*/

template <class TKey, class TData>
class Cache
{
  public:
    Cache(uint size);
    ~Cache();

    void SetPolicy(util::CachePolicy);
    util::CachePolicy GetPolicy() const;

    bool Contains(const TKey &key) const;

  private:
    std::unordered_map<TKey, TData> data;
    int maxSize;
    util::CachePolicy CachePolicy;
}; /*Cache*/
} // namespace util