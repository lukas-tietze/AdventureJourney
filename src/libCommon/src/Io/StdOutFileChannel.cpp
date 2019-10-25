#include "libCommon/io/Channel.hpp"

util::io::FileStdOutChannel::FileStdOutChannel() : FileChannel(stdout)
{
}

util::io::FileStdOutChannel util::io::FileStdOutChannel::Instance = util::io::FileStdOutChannel();