#include "libCommon/io/Channel.hpp"

util::io::FileStdErrChannel::FileStdErrChannel() : FileChannel(stderr)
{
}