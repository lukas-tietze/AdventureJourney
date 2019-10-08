#include "libCommon/Test.hpp"

constexpr clock_t InvalidTime = (clock_t)(-1);

test::TestRun::TestRun(TestBase* test) : test(test),
message(""),
good(false),
start(InvalidTime),
end(InvalidTime)
{
}

test::TestRun::~TestRun()
{
	if (this->IsFinished())
	{
		delete this->test;
	}
}

void test::TestRun::Execute()
{
	try
	{
		this->test->Init();
	}
	catch (std::exception& e)
	{
	}

	try
	{
		this->start = std::clock();

		this->test->Run();

		this->end = std::clock();
		this->good = true;
		this->message.clear();
	}
	catch (const util::Exception& e)
	{
		this->end = std::clock();
		this->good = false;
		this->message = e.GetMessage();
		this->message.push_back('.\n');
	}
	catch (std::exception& e)
	{
		this->good = false;
		this->message.assign(e.what());
	}

	try
	{
		this->test->Dispose();
	}
	catch (std::exception& e)
	{
	}
}

double test::TestRun::GetTimeMs() const
{
	return util::ClockToMs(this->GetTime());
}

clock_t test::TestRun::GetTime() const
{
	return this->end - this->start;
}

bool test::TestRun::IsGood() const
{
	return this->good;
}

bool test::TestRun::IsStarted() const
{
	return this->start != InvalidTime;
}

bool test::TestRun::IsFinished() const
{
	return this->end != InvalidTime;
}

const std::string& test::TestRun::GetMessage() const
{
	return this->message;
}

std::ostream& test::operator<<(std::ostream& stream, const test::TestRun& testRun)
{
	if (testRun.good)
	{
		stream << "[good] " << testRun.test->GetName() << "(" << testRun.GetTimeMs() << "ms)" << std::endl;
	}
	else
	{
		stream << "[failed] " << testRun.test->GetName() << "(" << testRun.GetTimeMs() << "ms)" << std::endl;
		stream << "\t> " << testRun.message << std::endl;
	}

	return stream;
}