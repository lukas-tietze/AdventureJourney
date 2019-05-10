#include "Objects.hpp"

template <class TKey, class TValue>
bool glutil::Scene::DeleteItem(std::map<TKey, TValue *> &map, const TKey &key)
{
    auto kvp = map.find(key);

    if (kvp != map.end())
    {
        delete kvp->second;

        map.erase(kvp);

        return true;
    }

    return false;
}

template <class TKey, class TValue>
TValue *glutil::Scene::FindOrCreateItem(std::map<TKey, TValue *> &map, const TKey &key)
{
    auto kvp = map.find(key);

    if (kvp == map.end())
    {
        auto res = new TValue();

        map.insert(std::make_pair(key, res));

        // util::dbg.WriteLine("Created new % with key %", typeid(TValue).name(), key);
     
        return res;
    }

    return kvp->second;
}

template <class TKey, class TValue>
const TValue *glutil::Scene::FindItemOrNull(const std::map<TKey, TValue *> &map, const TKey &key) const
{
    auto kvp = map.find(key);

    return kvp == map.end() ? nullptr : kvp->second;
}

template <class TKey, class TValue>
void glutil::Scene::DeleteAll(std::map<TKey, TValue *> &map)
{
    for (auto &kvp : map)
        delete kvp.second;

    map.clear();
}