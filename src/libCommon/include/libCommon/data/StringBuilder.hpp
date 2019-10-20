#pragma once

#include <string>
#include <sstream>
#include <list>

namespace util
{
template <typename TChar, typename TAllocator>
class BasicStringBuilder
{
    friend std::ostream &operator<<(std::ostream &s, const BasicStringBuilder<TChar, TAllocator> &t);

private:
    std::list<std::basic_string<TChar, std::char_traits<TChar>, TAllocator>, TAllocator> nodes;
    std::basic_stringstream<TChar, std::char_traits<TChar>, TAllocator> buf;
    uint32_t totalLen;

public:
    BasicStringBuilder() : nodes(),
                           buf(),
                           totalLen(0)
    {
    }

    BasicStringBuilder<TChar, TAllocator> &Append(const std::string &s, uint32_t begin, uint32_t len = std::numeric_limits<uint32_t>::max())
    {
        this->node.emplace_back(s, begin, len);

        return *this;
    }

    BasicStringBuilder<TChar, TAllocator> &AppendLine(const std::string &s, uint32_t begin, uint32_t len = std::numeric_limits<uint32_t>::max())
    {
        this->nodes.emplace_back(len + 1);
        this->nodes.back().assign(s, begin, len);
        this->nodes.this->nodes.back().push_back('\n');

        return *this;
    }

    template <typename T>
    BasicStringBuilder &Append(const T &arg)
    {
        this->nodes.push_back(this->buf.str());

        return *this;
    }

    template <typename T>
    BasicStringBuilder &AppendLine(const T &arg)
    {
        this->buf.clear();
        this->buf << arg << '\n';
        this->nodes.push_back(this->buf.str());

        return *this;
    }

    std::string ToString() const
    {
        this->nodes.front().reserve(this->totalLen);

        // TODO!!!

        return this->nodes.front();
    }

    uint32_t Length()
    {
        return this->totalLen;
    }
};

template <typename TChar, typename TAllocator>
std::ostream &operator<<(std::ostream &s, const BasicStringBuilder<TChar, TAllocator> &t)
{
    for (const auto &node : t.nodes)
    {
        s << node.
    }

    return s;
}
} // namespace util