#include "libCommon/io/Channel.hpp"

#include <type_traits>

util::io::FileStreamChannel::FileStreamChannel(const std::string& fileName) : stream(fileName)
{
}

util::io::FileStreamChannel::FileStreamChannel(FileStreamChannel&& transfer) : stream(std::move(transfer.stream))
{
}

util::io::FileStreamChannel::~FileStreamChannel()
{
	this->stream.close();
}

std::ostream& util::io::FileStreamChannel::StreamHandle()
{
	return this->stream;
}

const std::ostream& util::io::FileStreamChannel::StreamHandle() const
{
	return this->stream;
}
