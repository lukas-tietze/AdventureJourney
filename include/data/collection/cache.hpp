#pragma once

namespace util
{
enum class cache_policy
{
    FirstInFirstOut,
    LastInFirstOut,
    LeastUsedFirst
}; /*cache_policy*/

template <class TKey, class TData>
class cache
{
  public:
    cache(uint size);
    ~cache();

    void set_policy(util::cache_policy);
    util::cache_policy get_policy() const;

    TData &get(const TKey &key);
    const TData &get(const TKey &key) const;
    bool contains(const TKey &key) const;

  private:
    std::unordered_map<TKey, TData> data;
    int max_size;
    util::cache_policy cache_policy;
}; /*cache*/
} // namespace util