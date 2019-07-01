#include "GlUtils.hpp"

void glutil::PushDebugGroup(const std::string &msg)
{
    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, msg.length(), msg.c_str());
}

void glutil::PopDebugGroup()
{
    glPopDebugGroup();
}

void glutil::NextDebugGroup(const std::string &)
{
    glPopDebugGroup();
    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, msg.length(), msg.c_str());
}
