#include "Objects.hpp"

#include <cstring>
#include <algorithm>

#include "data/Io.hpp"

// #include "ft2build.h"
// #include FT_FREETYPE_H

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

void glutil::BitMapFont::TransferFrom(BitMapFont &other)
{
    this->data = other.data;
}

bool glutil::BitMapFont::Load(const std::string &path)
{
    FontInfo info;
    json::Node *n;
    json::Parser p;

    p.parse(util::ReadFile(path), n);
    info.Deserialize(n);

    return this->Load(info);
}

bool glutil::BitMapFont::LoadTrueTypeFont(const FontInfo &info)
{
    // this->DestroyGlObjects();

    // FT_Library ft;
    // FT_Face face;
    // FT_Error err;

    // err = FT_Init_FreeType(&ft);

    // if (!err)
    // {
    //     err = FT_New_Face(ft, info.source.c_str(), 0, &face);

    //     if (!err)
    //     {
    //         FT_Set_Pixel_Sizes(face, 0, 48);

    //         this->data.assign(info.charList.size(), BitMapFontUboData());

    //         int wTotal, hTotal;

    //         struct
    //         {
    //             int w;
    //             int h;
    //             unsigned char *buf;
    //         } buffers[256];

    //         for (size_t i = 0; i < info.charList.length(); i++)
    //         {
    //             auto c = info.charList[i];
    //             auto &item = this->data[i];

    //             FT_Load_Char(face, 0, FT_LOAD_RENDER);

    //             this->charMapping[info.charList[i]] = i;

    //             item.advance = glm::vec2(face->glyph->advance.x, face->glyph->advance.y);
    //             item.bearing = glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top);

    //             auto bufSize = face->glyph->bitmap.width * face->glyph->bitmap.rows * sizeof(unsigned char);

    //             buffers[i].w = face->glyph->bitmap.width;
    //             buffers[i].h = face->glyph->bitmap.rows;
    //             buffers[i].buf = new unsigned char[bufSize];

    //             std::memcpy(buffers[i].buf, face->glyph->bitmap.buffer, bufSize);

    //             wTotal += buffers[i].w;
    //             hTotal = std::max(hTotal, buffers[i].w);
    //         }

    //         glGenTextures(1, &this->tex);
    //         glBindTexture(GL_TEXTURE_2D, this->tex);
    //         glTexImage2D(GL_TEXTURE_2D, 0,
    //                      GL_RED, wTotal, hTotal, 0,
    //                      GL_RED, GL_UNSIGNED_BYTE, nullptr);
    //         glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //         int w = 0;

    //         for (size_t i = 0; i < info.charList.length(); i++)
    //         {
    //             glTexSubImage2D(GL_TEXTURE_2D, 0,
    //                             w, 0, buffers[i].w, buffers[i].h,
    //                             GL_RED, GL_UNSIGNED_BYTE, buffers[i].buf);
    //         }
    //     }

    //     FT_Done_Face(face);
    // }

    // FT_Done_FreeType(ft);

    // return !err;

    return false;
}

bool glutil::BitMapFont::Load(const glutil::FontInfo &info)
{
    if (info.type == FontType::BitMap)
        return this->LoadBitMapFont(info);
    else if (info.type == FontType::TrueType)
        return this->LoadTrueTypeFont(info);
}

bool glutil::BitMapFont::LoadBitMapFont(const glutil::FontInfo &info)
{
    auto lc = this->LoadCoordinates(info);
    auto lt = this->LoadTexture(info);

    return lc && lt;
}

bool glutil::BitMapFont::LoadTexture(const FontInfo &info)
{
    this->tex.SetInternalFormat(GL_RED);
    return this->tex.LoadData(info.source);
}

bool glutil::BitMapFont::LoadCoordinates(const FontInfo &info)
{
    auto size = glm::vec2(info.cols * info.strideX, info.rows * info.strideY);
    auto offset = size / glm::vec2(info.offsetX, info.offsetY);
    auto stride = size / glm::vec2(info.strideX, info.strideY);

    this->data.assign(info.charList.length(), BitMapFontUboData());
    this->SetDirty();

    for (int i = 0; i < info.charList.length() && i < (info.rows * info.cols); i++)
    {
        int row = i / info.cols;
        int col = i % info.cols;

        auto &item = this->data[i];

        item.pos = offset + glm::vec2(col, row) * stride;
        item.size = size / glm::vec2(info.charWidth, info.charHeight);
        item.advance = item.size;
        item.bearing = glm::vec2(0, item.size.y);
    }

    return info.rows > 0 && info.cols > 0 &&
           info.charWidth > 0 && info.charHeight > 0 &&
           info.strideX > 0 && info.strideY > 0 &&
           info.charList.length() > 0;
}

glutil::Texture *glutil::BitMapFont::GetTexture()
{
    return &this->tex;
}

void glutil::BitMapFont::Bind(GLenum target)
{
    this->tex.Bind(target);
}

bool glutil::BitMapFont::HasChar(char c) const
{
    return this->charMapping[c] > 0;
}

const glutil::BitMapFontUboData &glutil::BitMapFont::operator[](char c) const
{
    return this->data[c];
}

glutil::BitMapFont &glutil::BitMapFont::operator=(BitMapFont &&other)
{
    this->TransferFrom(other);

    return *this;
}
