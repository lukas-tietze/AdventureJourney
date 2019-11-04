#include "libCommon/io/Channel.hpp"

#include <cstdio>

util::io::FileChannel::FileChannel(std::FILE* file) : file(file)
{
}

util::io::FileChannel::FileChannel(const FileChannel& copy) : file(copy.file)
{
}

util::io::FileChannel::FileChannel(FileChannel&& transfer) : file(transfer.file)
{
	transfer.file = nullptr;
}

util::io::FileChannel::~FileChannel()
{
	std::fflush(this->file);

	if (this->file != stdout && this->file != stderr)
	{
		std::fclose(this->file);
	}
}

void util::io::FileChannel::Write(const std::string& s)
{
	if (this->file != nullptr)
	{
		std::fprintf(this->file, "%s", s.c_str());
	}
}

std::ostream& util::io::FileChannel::StreamHandle()
{
	throw InvalidHandleRequestedException();
}

const std::ostream& util::io::FileChannel::StreamHandle() const
{
	throw InvalidHandleRequestedException();
}

std::FILE* util::io::FileChannel::FileHandle()
{
	return this->file;
}

const std::FILE* util::io::FileChannel::FileHandle() const
{
	return this->file;
}

bool util::io::FileChannel::IsChannelBased() const
{
	return false;
}

bool util::io::FileChannel::IsFileBased() const
{
	return true;
}

void util::io::FileChannel::Flush()
{
	if (this->file != nullptr)
	{
		std::fflush(this->file);
	}
}
