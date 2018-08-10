#include "test.hpp"

constexpr clock_t InvalidTime = (clock_t)(-1);

test::test_run::test_run(test_base *test) : test(test),
                                            message(""),
                                            good(false),
                                            start(InvalidTime),
                                            end(InvalidTime)
{
}

test::test_run::~test_run()
{
    delete this->test;
}

void test::test_run::execute()
{
    try
    {
        this->test->init();
    }
    catch (const std::exception &e)
    {
    }

    try
    {
        this->start = std::clock();

        this->test->run();

        this->end = std::clock();
        this->good = true;
        this->message.clear();
    }
    catch (const std::exception &e)
    {
        this->end = std::clock();
        this->good = false;
        this->message.assign(e.what());
    }

    try
    {
        this->test->dispose();
    }
    catch (const std::exception &e)
    {
    }
}

double test::test_run::get_time_ms() const
{
    return util::clock_to_ms(this->get_time());
}

clock_t test::test_run::get_time() const
{
    return this->end - this->start;
}

bool test::test_run::is_good() const
{
    return this->good;
}

bool test::test_run::is_started() const
{
    return this->start != InvalidTime;
}

bool test::test_run::is_finished() const
{
    return this->end != InvalidTime;
}

const std::string &test::test_run::get_message() const
{
    return this->message;
}

std::ostream &test::operator<<(std::ostream &stream, const test::test_run &testRun)
{
    if (testRun.good)
    {
        stream << "[good] " << testRun.test->get_name() << "(" << testRun.get_time_ms() << "ms)" << std::endl;
    }
    else
    {
        stream << "[failed] " << testRun.test->get_name() << "(" << testRun.get_time_ms() << "ms)" << std::endl;
        stream << "\t> " << testRun.message << std::endl;
    }

    return stream;
}