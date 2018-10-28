#include <cstdlib>
#include <string>
#include <cstdio>

#include "data/args.hpp"
#include "data/string.hpp"

util::args::args(int argc, char **argv) : m_pos(1),
                                          m_argc(argc),
                                          m_argv(argv),
                                          m_last()
{
}

bool util::args::next_int(int &target)
{
    if (!next())
        return false;

    return parse_integral(m_last, target);
}

bool util::args::next_uint(uint &target)
{
    if (!next())
        return false;

    return parse_integral(m_last, target);
}

bool util::args::next_double(double &buf)
{
    if (!next())
        return false;

    return parse_float(m_last, buf);
}

bool util::args::has_next_double() const
{
    std::string stringBuf;

    if (peek(stringBuf))
    {
        double buf;
        return parse_integral(stringBuf, buf);
    }

    return false;
}

bool util::args::next_float(float &buf)
{
    if (!next())
        return false;

    return parse_float(this->m_last, buf);
}

bool util::args::has_next_float() const
{
    std::string stringBuf;

    if (peek(stringBuf))
    {
        float buf;
        return parse_integral(stringBuf, buf);
    }

    return false;
}

bool util::args::next_bool(bool &buf)
{
    if (!next())
        return false;

    if (this->m_last == "true")
    {
        buf = true;
        return true;
    }
    else if (this->m_last == "false")
    {
        buf = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool util::args::has_next_bool() const
{
    std::string stringBuf;

    if (peek(stringBuf))
    {
        return stringBuf == "true" || stringBuf == "false";
    }

    return false;
}

bool util::args::has_next_int() const
{
    std::string stringBuf;

    if (peek(stringBuf))
    {
        int buf;
        return parse_integral(stringBuf, buf);
    }

    return false;
}

bool util::args::has_next_uint() const
{
    std::string stringBuf;
    uint buf;

    if (peek(stringBuf))
    {
        return parse_integral(stringBuf, buf);
    }

    return false;
}

bool util::args::next(std::string &target)
{
    if (!next())
        return false;

    target = m_last;

    return true;
}

const std::string &util::args::current()
{
    return m_last;
}

bool util::args::has_next() const
{
    return m_pos < m_argc;
}

bool util::args::peek(std::string &target) const
{
    if (!has_next())
    {
        return false;
    }

    target.assign(m_argv[m_pos]);
    return true;
}

bool util::args::next()
{
    bool hasNext = has_next();

    if (hasNext)
    {
        m_last.assign(m_argv[m_pos]);
        m_pos++;
    }
    else
    {
        m_last.clear();
    }

    return hasNext;
}