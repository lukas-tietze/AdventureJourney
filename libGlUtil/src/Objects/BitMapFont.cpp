#include "Objects.hpp"

glutil::BitMapFont::BitMapFont()
{
}

glutil::BitMapFont::BitMapFont(BitMapFont &&other)
{
    this->TransferFrom(other);
}

glutil::BitMapFont::~BitMapFont()
{
    this->DestroyGlObjects();
}

void glutil::BitMapFont::DestroyGlObjects()
{
    if (this->tex)
    {
        glDeleteTextures(1, &this->tex);
        this->tex = 0;
    }
}

void glutil::BitMapFont::TransferFrom(BitMapFont &other)
{
    this->data = other.data;
}

bool glutil::BitMapFont::Load(const std::string &path)
{
    BitMapFontInfo info;
    json::Node *n;
    json::Parser p;

    p.parse(path, n);
    info.Deserialize(n);

    return this->Load(info);
}

bool glutil::BitMapFont::Load(const glutil::BitMapFontInfo &info)
{
    auto lc = this->LoadCoordinates(info);
    auto lt = this->LoadTexture(info);

    return lc && lt;
}

bool glutil::BitMapFont::LoadTexture(const BitMapFontInfo &info)
{
    glutil::Texture tex;
    tex.SetInternalFormat(GL_RED);
    auto res = tex.LoadData(info.source);

    this->tex = tex.DisownId();

    return res;
}

bool glutil::BitMapFont::LoadCoordinates(const BitMapFontInfo &info)
{
    auto size = glm::vec2(info.cols * info.strideX, info.rows * info.strideY);
    auto offset = size / glm::vec2(info.offsetX, info.offsetY);
    auto stride = size / glm::vec2(info.strideX, info.strideY);

    this->data.charSize = size / glm::vec2(info.charWidth, info.charHeight);

    for (int i = 0; i < info.charList.length() && i < (info.rows * info.cols); i++)
    {
        int row = i / info.cols;
        int col = i % info.cols;

        this->data.positions[info.charList[i]] = offset + glm::vec2(col, row) * stride;
    }

    return info.rows > 0 && info.cols > 0 &&
           info.charWidth > 0 && info.charHeight > 0 &&
           info.strideX > 0 && info.strideY > 0 &&
           info.charList.length() > 0;
}

void glutil::BitMapFont::Bind(GLenum target)
{
    glBindTexture(this->tex, target);
}

glm::vec4 glutil::BitMapFont::GetTexCoords(char c)
{
    return glm::vec4(this->data.positions[c], this->data.positions[c] + this->data.charSize);
}

glutil::BitMapFont &glutil::BitMapFont::operator=(BitMapFont &&other)
{
    this->TransferFrom(other);

    return *this;
}
