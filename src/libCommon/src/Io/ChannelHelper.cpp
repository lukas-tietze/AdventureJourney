#include "libCommon/io/Channel.hpp"

#define __STDC_WANT_SECURE_LIB__ 1

util::io::Channel OpenFile(const std::string & path)
{
	FILE* file;

	if (fopen_s(&file, path.c_str(), "rw"))
	{
		return std::make_shared<util::io::FileChannel>(file);
	}
	else
	{
		return nullptr;
	}
}

util::io::Channel OpenStdErrFile()
{
	return std::make_shared<util::io::FileStdErrChannel>();
}

util::io::Channel OpenStdOutFile()
{
	return std::make_shared<util::io::FileStdOutChannel>();
}

util::io::Channel OpenFileStream(const std::string& path)
{
	return std::make_shared<util::io::FileStreamChannel>(path);
}

util::io::Channel OpenStdErrStream()
{
	return std::make_shared<util::io::StdErrStreamChannel>();
}

util::io::Channel OpenStdOutStream()
{
	return std::make_shared<util::io::StdOutStreamChannel>();
}

util::io::Channel OpenStringStream()
{
	return std::make_shared<util::io::StringStreamChannel>();
}
