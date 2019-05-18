#include "Objects.hpp"
#include "GlUtils.hpp"
#include "data/Io.hpp"

namespace
{
constexpr const char EXT_VERTEX_SHADER[] = ".vert";
constexpr const char EXT_VERTEX_SHADER_ALT[] = ".vs.glsl";
constexpr const char EXT_FRAGMENT_SHADER[] = ".frag";
constexpr const char EXT_FRAGMENT_SHADER_ALT[] = ".fs.glsl";
constexpr const char EXT_COMPUTATION_SHADER[] = ".cmp";
constexpr const char EXT_COMPUTATION_SHADER_ALT[] = ".cp.glsl";
constexpr const char EXT_TESSELATION_CONTROL_SHADER[] = ".tctrl";
constexpr const char EXT_TESSELATION_CONTROL_SHADER_ALT[] = ".tc.glsl";
constexpr const char EXT_TESSELATION_EVALUAION_SHADER[] = ".teval";
constexpr const char EXT_TESSELATION_EVALUAION_SHADER_ALT[] = ".te.glsl";
} // namespace

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
    this->path = path;

    if (util::EndsWith(path, EXT_VERTEX_SHADER) || util::EndsWith(path, EXT_VERTEX_SHADER_ALT))
        this->type = GL_VERTEX_SHADER;
    else if (util::EndsWith(path, EXT_FRAGMENT_SHADER) || util::EndsWith(path, EXT_FRAGMENT_SHADER_ALT))
        this->type = GL_FRAGMENT_SHADER;
    else if (util::EndsWith(path, EXT_COMPUTATION_SHADER) || util::EndsWith(path, EXT_COMPUTATION_SHADER_ALT))
        this->type = GL_COMPUTE_SHADER;
    else if (util::EndsWith(path, EXT_TESSELATION_CONTROL_SHADER) || util::EndsWith(path, EXT_TESSELATION_CONTROL_SHADER_ALT))
        this->type = GL_TESS_CONTROL_SHADER;
    else if (util::EndsWith(path, EXT_TESSELATION_EVALUAION_SHADER) || util::EndsWith(path, EXT_TESSELATION_EVALUAION_SHADER_ALT))
        this->type = GL_TESS_EVALUATION_SHADER;
    else
        throw util::Exception("Failed to load shader! Can't deduce shader type from file extension!");

    return this->Reload();
}

bool glutil::Shader::Reload()
{
    std::string text;
    if (!util::TryReadFile(this->path, text))
    {
        util::dbg.WriteLine("Failed to Load shader! Could not read file %", this->path);
        return false;
    }

    this->DestroyGlObjects();
    this->id = glCreateShader(this->type);

    util::dbg.WriteLine("Compiling shader % from: %.", this->id, this->path);

    auto buf = text.c_str();

    glShaderSource(this->id, 1, &buf, nullptr);
    glCompileShader(this->id);

    if (!this->Check())
        return false;

    util::dbg.WriteLine("Done!");

    return true;
}

bool glutil::Shader::Check()
{
    GLint isCompiled = 0;
    GLint maxLen = 0;
    std::string errorLog;

    glGetShaderiv(this->id, GL_COMPILE_STATUS, &isCompiled);
    glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &maxLen);

    if (maxLen > 0)
    {
        errorLog.resize(static_cast<size_t>(maxLen));
        glGetShaderInfoLog(this->id, maxLen, &maxLen, &errorLog[0]);
    }

    if (!isCompiled)
        util::dbg.WriteLine("Compiler Error! %", errorLog);
    else if (maxLen > 0)
        util::dbg.WriteLine("Completed with warnings! %", errorLog);

    return isCompiled == GL_TRUE;
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
    s << "id=" << shader.id << ", type=" << shader.type << ", source=" << shader.path;

    return s;
}
