#include "GlUtils.hpp"
#include "data/Io.hpp"

GLuint glutil::LoadShader(const std::string &path, GLenum type)
{
    auto text = util::ReadFile(path);
    auto sId = glCreateShader(type);
    auto buf = text.c_str();

    glShaderSource(sId, 1, &buf, nullptr);
    glCompileShader(sId);

    if (!glutil::CheckShader(sId))
    {
        glDeleteShader(sId);
        sId = 0;
    }

    return sId;
}

GLuint glutil::CreateProgram(GLuint vsId, GLuint fsId)
{
    auto pId = glCreateProgram();
    glAttachShader(pId, vsId);
    glAttachShader(pId, fsId);
    glLinkProgram(pId);

    if (!glutil::CheckProgram(pId))
    {
        glDeleteProgram(pId);
        pId = 0;
    }

    return pId;
}

GLuint CreateProgram(const std::string &vsSrc, const std::string &fsSrc)
{
    auto vsId = glutil::LoadShader(vsSrc, GL_VERTEX_SHADER);
    auto fsId = glutil::LoadShader(fsSrc, GL_FRAGMENT_SHADER);
    auto pId = glutil::CreateProgram(vsId, fsId);

    if (vsId != 0)
        glDeleteShader(vsId);

    if (fsId != 0)
        glDeleteShader(fsId);

    return pId;
}

bool glutil::CheckShader(GLuint shader)
{
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::string errorLog;
    errorLog.resize(static_cast<size_t>(maxLength));
    glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

    //TODO Debugausgaben

    return isCompiled == GL_TRUE;
}

bool CheckProgram(GLuint prog)
{
    GLint isLinked = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &isLinked);

    GLint maxLen = 0;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &maxLen);

    // The maxLength includes the NULL character
    std::string errorLog;
    errorLog.resize(static_cast<size_t>(maxLen));
    glGetProgramInfoLog(prog, maxLen, &maxLen, &errorLog[0]);

    //TODO Debugausgaben!

    return isLinked == GL_TRUE;
}