#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "libCommon/Defs.hpp"

namespace util
{
class ArgSet
{
private:
    int readPos = 0;
    bool lastReadState = true;
    std::stringstream currentItem;
    std::vector<std::string> items;

    bool LoadNext();

public:
    ArgSet(int argc, char **argv);

    std::string Next();
    bool HasNext() const;

    operator bool() const;

    const std::string &Current();
    bool Peek(std::string &target) const;

    template <class T>
    bool Extract(T &buf)
    {
        if (this->LoadNext())
        {
            this->currentItem >> buf;

            return true;
        }

        return false;
    }

    std::vector<std::string>::iterator begin();
    std::vector<std::string>::const_iterator cbegin();
    std::vector<std::string>::reverse_iterator rbegin();
    std::vector<std::string>::const_reverse_iterator crbegin();
    std::vector<std::string>::iterator end();
    std::vector<std::string>::const_iterator cend();
    std::vector<std::string>::reverse_iterator rend();
    std::vector<std::string>::const_reverse_iterator crend();
};

template <class T>
ArgSet &operator>>(ArgSet &a, T &buf)
{
    a.Extract(buf);
}
} // namespace util