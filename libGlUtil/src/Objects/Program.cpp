#include "Objects.hpp"

#include <algorithm>

#include "glad/glad.h"
#include "data/IteratorUtils.hpp"
#include "GlUtils.hpp"
#include "data/Io.hpp"

glutil::Program::Program() : shaders(),
                             id(0)
{
}

glutil::Program::Program(const Program &program)
{
    this->CopyFrom(program);
}

glutil::Program::Program(Program &&program)
{
    this->TransferFrom(program);
}

glutil::Program::~Program()
{
    this->DestroyGlObjects();
}

void glutil::Program::DestroyGlObjects()
{
    if (this->id)
    {
        glDeleteProgram(this->id);
        this->id = 0;
    }
}

void glutil::Program::CopyFrom(const Program &program)
{
    this->shaders = program.shaders;
    this->Link();
}

void glutil::Program::TransferFrom(Program &program)
{
    this->shaders = program.shaders;
    this->id = program.id;

    program.shaders.clear();
    program.id = 0;
}

void glutil::Program::AttachAll(const std::initializer_list<Shader *> &shaderList)
{
    this->shaders.insert(this->shaders.end(), shaderList);
}

void glutil::Program::Attach(Shader *shader)
{
    this->shaders.push_back(shader);
}

void glutil::Program::Detach(Shader *shader)
{
    auto pos = std::find(this->shaders.begin(), this->shaders.end(), shader);

    if (pos != this->shaders.end())
        this->shaders.erase(pos);
}

void glutil::Program::Clear()
{
    this->shaders.clear();
}

bool glutil::Program::Link()
{
    util::dbg.WriteLine("Linking program % from: %.", this->id, util::WrapPointerIterable(this->shaders.begin(), this->shaders.end(), "\n\t"));

    this->DestroyGlObjects();
    this->id = glCreateProgram();

    for (auto shader : this->shaders)
        glAttachShader(this->id, shader->GetId());

    glLinkProgram(this->id);

    if (!this->Check())
        return false;

    util::dbg.WriteLine("Done!\n");

    return true;
}

bool glutil::Program::LinkAll(const std::initializer_list<Shader *> &shaders)
{
    this->Clear();
    this->AttachAll(shaders);
    return this->Link();
}

bool glutil::Program::ReloadAll()
{
    for (auto shader : this->shaders)
        shader->Reload();

    return this->Link();
}

void glutil::Program::Use()
{
    glUseProgram(this->id);
}

bool glutil::Program::Check()
{
    GLint isLinked = 0;
    GLint maxLen = 0;
    std::string errorLog;
    glGetProgramiv(this->id, GL_LINK_STATUS, &isLinked);
    glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &maxLen);

    if (maxLen > 0)
    {
        errorLog.resize(static_cast<size_t>(maxLen));
        glGetProgramInfoLog(this->id, maxLen, &maxLen, &errorLog[0]);
    }

    if (!isLinked)
        util::dbg.WriteLine("Failed! %", errorLog);
    else if (maxLen > 0)
        util::dbg.WriteLine("Completed with warnings! %", errorLog);

    return isLinked == GL_TRUE;
}

glutil::Program &glutil::Program::operator=(const Program &program)
{
    this->CopyFrom(program);

    return *this;
}

glutil::Program &glutil::Program::operator=(Program &&program)
{
    this->TransferFrom(program);

    return *this;
}
