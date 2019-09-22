#include <cstdlib>
#include <string>
#include <cstdio>

#include "libCommon/data/Args.hpp"
#include "libCommon/data/String.hpp"

util::Args::Args(int argc, char **argv) : pos(1),
                                          argc(argc),
                                          argv(argv),
                                          last()
{
}

bool util::Args::NextInt(int &target)
{
    if (!Next())
        return false;

    return ParseIntegral(last, target);
}

bool util::Args::NextUint(uint &target)
{
    if (!Next())
        return false;

    return ParseIntegral(last, target);
}

bool util::Args::NextDouble(double &buf)
{
    if (!Next())
        return false;

    return ParseFloat(last, buf);
}

bool util::Args::HasNextDouble() const
{
    std::string stringBuf;

    if (Peek(stringBuf))
    {
        double buf;
        return ParseIntegral(stringBuf, buf);
    }

    return false;
}

bool util::Args::NextFloat(float &buf)
{
    if (!Next())
        return false;

    return ParseFloat(this->last, buf);
}

bool util::Args::HasNextFloat() const
{
    std::string stringBuf;

    if (Peek(stringBuf))
    {
        float buf;
        return ParseIntegral(stringBuf, buf);
    }

    return false;
}

bool util::Args::NextBool(bool &buf)
{
    if (!Next())
        return false;

    if (this->last == "true")
    {
        buf = true;
        return true;
    }
    else if (this->last == "false")
    {
        buf = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool util::Args::HasNextBool() const
{
    std::string stringBuf;

    if (Peek(stringBuf))
    {
        return stringBuf == "true" || stringBuf == "false";
    }

    return false;
}

bool util::Args::HasNextInt() const
{
    std::string stringBuf;

    if (Peek(stringBuf))
    {
        int buf;
        return ParseIntegral(stringBuf, buf);
    }

    return false;
}

bool util::Args::HasNextUint() const
{
    std::string stringBuf;
    uint buf;

    if (Peek(stringBuf))
    {
        return ParseIntegral(stringBuf, buf);
    }

    return false;
}

bool util::Args::Next(std::string &target)
{
    if (!Next())
        return false;

    target = last;

    return true;
}

const std::string &util::Args::Current()
{
    return last;
}

bool util::Args::HasNext() const
{
    return pos < argc;
}

bool util::Args::Peek(std::string &target) const
{
    if (!HasNext())
    {
        return false;
    }

    target.assign(argv[pos]);
    return true;
}

bool util::Args::Next()
{
    bool hasNext = HasNext();

    if (hasNext)
    {
        last.assign(argv[pos]);
        pos++;
    }
    else
    {
        last.clear();
    }

    return hasNext;
}