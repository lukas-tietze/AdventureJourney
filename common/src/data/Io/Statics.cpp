#include "data/Io.hpp"

util::Channel util::out = util::Channel(stdout);
util::Channel util::err = util::Channel(stderr);
util::Communicator util::com = util::Communicator();