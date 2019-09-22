#include "libCommon/data/Io.hpp"

util::Channel util::out = util::Channel(stdout);
util::Channel util::err = util::Channel(stderr);
util::Channel util::dbg = util::Channel(stdout);
util::Communicator util::com = util::Communicator();