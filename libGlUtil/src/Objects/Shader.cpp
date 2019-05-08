#include "Objects.hpp"
#include "GlUtils.hpp"
#include "data/Io.hpp"
#include "boost/filesystem.hpp"

namespace{
    constexpr const char *EXT_VERTEX_SHADER = ".vert";
    constexpr const char *EXT_VERTEX_SHADER_ALT = ".vert";
    constexpr const char *EXT_VERTEX_SHADER = ".vert";
    constexpr const char *EXT_VERTEX_SHADER = ".vert";
    constexpr const char *EXT_VERTEX_SHADER = ".vert";
}

glutil::Shader::Shader() : path(),
                           type(0),
                           id(0)
{
}

glutil::Shader::Shader(const Shader &shader)
{
    this->CopyFrom(shader);
}

glutil::Shader::Shader(Shader &&shader)
{
    this->TransferFrom(shader);
}

glutil::Shader::~Shader()
{
    this->DestroyGlObjects();
}

void glutil::Shader::DestroyGlObjects()
{
    if (this->id)
    {
        glDeleteShader(this->id);
        this->id = 0;
    }
}

void glutil::Shader::CopyFrom(const Shader &shader)
{
    this->LoadFrom(shader.path, shader.type);
}

void glutil::Shader::TransferFrom(Shader &shader)
{
    this->path = shader.path;
    this->type = shader.type;
    this->id = shader.id;

    shader.path.clear();
    shader.type = 0;
    shader.id = 0;
}

GLuint glutil::Shader::GetId() const
{
    return this->id;
}

bool glutil::Shader::LoadFrom(const std::string &path, GLenum type)
{
    this->path = path;
    this->type = type;

    return this->Reload();
}

bool glutil::Shader::LoadFrom(const std::string &path)
{
    auto ext = boost::filesystem::extension(path);

    if(ext == )

    this->path = path;
    this->type = type;

    return this->Reload();
}

bool glutil::Shader::Reload()
{
    this->DestroyGlObjects();
    this->id = glCreateShader(this->type);

    auto text = util::ReadFile(this->path);
    auto buf = text.c_str();

    glShaderSource(this->id, 1, &buf, nullptr);
    glCompileShader(this->id);

    if (!glutil::CheckShader(this->id))
        return false;
    else
        util::dbg.WriteLine("Loaded shader % (%) from %.", this->id, this->type, this->path);

    return true;
}

glutil::Shader &glutil::Shader::operator=(const Shader &shader)
{
    this->CopyFrom(shader);

    return *this;
}

glutil::Shader &glutil::Shader::operator=(Shader &&shader)
{
    this->TransferFrom(shader);

    return *this;
}

std::ostream &glutil::operator<<(std::ostream &s, const Shader &shader)
{
    s << "source=" << shader.path << ", type=" << shader.type << ", id=" << shader.id;

    return s;
}
