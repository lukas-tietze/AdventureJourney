#include "libCommon/io/Channel.hpp"

util::io::FileStdErrChannel::FileStdErrChannel() : FileChannel(stderr)
{
}

util::io::FileStdErrChannel util::io::FileStdErrChannel::Instance = util::io::FileStdErrChannel();