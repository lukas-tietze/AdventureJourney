#pragma once

#include <string>
#include <ctime>
#include <vector>
#include <iostream>

#include "data/string.hpp"
#include "data/io.hpp"
#include "datetime/datetime_conversions.hpp"
#include "exception.hpp"

namespace test
{
typedef int (*TestFunction)();

class TestBase
{
  private:
    std::string name;

  public:
    TestBase(const std::string &name);
    virtual ~TestBase();

    const std::string &GetName() const;

    virtual void Init();
    virtual void Run() = 0;
    virtual void Dispose();
};

class SimpleTest : public TestBase
{
  private:
    TestFunction func;

  public:
    SimpleTest(const std::string &name, TestFunction func);

    void Run();
};

class TestRun
{
  private:
    TestBase *test;
    std::string message;
    bool good;
    clock_t start;
    clock_t end;

  public:
    TestRun(TestBase *test);
    ~TestRun();

    void Execute();

    double GetTimeMs() const;
    clock_t GetTime() const;
    bool IsGood() const;
    bool IsStarted() const;
    bool IsFinished() const;
    const std::string &GetMessage() const;

    friend std::ostream &operator<<(std::ostream &, const TestRun &testRun);
};

class TestConfig
{
  private:
    bool breakAfterFirstFailure;
    uint threadCount;
    long timeout;
    bool quiet;
    bool showOnlyFailed;

  public:
    TestConfig();
    TestConfig(bool breakAfterFirstFailure,
                uint threadCount,
                long timeout,
                bool quiet,
                bool showOnlyFailed);

    static TestConfig initFromArgs(int, char **);

    bool IsBreakAfterFirstFailureEnabled() const;
    uint GetThreadCount() const;
    long GetTimeout() const;
    bool IsQuietEnabled() const;
    bool IsShowOnlyFailedEnabled() const;
};

std::ostream &operator<<(std::ostream &, const TestRun &testRun);

typedef std::vector<TestRun> TestCollection;

int RunTests(TestCollection &, const TestConfig &);
} // namespace test

namespace assert
{
class AssertException : public util::Exception
{
  public:
    AssertException(const std::string &msg, const std::string &customMsg);
};

void Fail(const std::string &msg = "");
void IsNull(const void *, const std::string &msg = "");
void IsNotNull(const void *, const std::string &msg = "");
void IsTrue(bool x, const std::string &msg = "");
void IsFalse(bool x, const std::string &msg = "");

template <class T>
void AreEqual(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x == y))
    {
        throw AssertException("Expected <" + util::ToString(x) + ">, got <" + util::ToString(y) + ">!", msg);
    }
}

template <class T>
void AreNotEqual(const T &x, const T &y, const std::string &msg = "")
{
    if (x == y)
    {
        throw AssertException("<" + util::ToString(x) + "> does equal <" + util::ToString(y) + ">!", msg);
    }
}

template <class T>
void IsGreater(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x > y))
    {
        throw AssertException("<" + util::ToString(x) + "> is not greater than <" + util::ToString(y) + ">!", msg);
    }
}

template <class T>
void IsEqualOrGreater(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x >= y))
    {
        throw AssertException("<" + util::ToString(x) + "> is not greater than or equal to <" + util::ToString(y) + ">!", msg);
    }
}

template <class T>
void IsLess(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x < y))
    {
        throw AssertException("<" + util::ToString(x) + "> is not less than <" + util::ToString(y) + ">!", msg);
    }
}

template <class T>
void IsEqualOrLess(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x <= y))
    {
        throw AssertException("<" + util::ToString(x) + "> is not less than or equal to <" + util::ToString(y) + ">!", msg);
    }
}

template <class T>
void Is(const void *obj, const std::string &msg = "")
{
    if (static_cast<const T *>(obj) == nullptr)
    {
        throw AssertException("<" + util::ToString(&obj) + "> is not of type <" + typeid(T).name() + ">!", msg);
    }
}
} // namespace assert