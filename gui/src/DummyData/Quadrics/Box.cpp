#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"
#include "data/IteratorUtils.hpp"
#include "data/Io.hpp"

glutil::Mesh gui::quadrics::Box(uint32_t color)
{
    return Box(1, 1, 1, color);
}
//---------------------------------------------------------------------------
glutil::Mesh gui::quadrics::Box(int slicesX, int slicesY, int slicesZ, uint32_t color)
{
    std::vector<gui::Vertex_Full> vertices;
    vertices.reserve(2 * (slicesX + 1) * (slicesY + 1) +
                     2 * (slicesY + 1) * (slicesZ + 1) +
                     2 * (slicesZ + 1) * (slicesX + 1));
    std::vector<uint16_t> indices;
    indices.reserve(2 * 6 * slicesX * slicesY +
                    2 * 6 * slicesY * slicesZ +
                    2 * 6 * slicesZ * slicesX);

    float stepX = 2.f / static_cast<float>(slicesX);
    float stepY = 2.f / static_cast<float>(slicesY);
    float stepZ = 2.f / static_cast<float>(slicesZ);
    Vertex_Full vertex;
    size_t indexOffset = 0;

    ////front & back
    {
        ////vertices
        for (int iX = 0; iX < slicesX + 1; iX++)
        {
            for (int iY = 0; iY < slicesY + 1; iY++)
            {
                vertex.position[0] = iX * stepX - 1.f;
                vertex.position[1] = iY * stepY - 1.f;
                vertex.position[2] = 1;

                vertex.color[0] = (color & 0xff000000) >> 24;
                vertex.color[1] = (color & 0x00ff0000) >> 16;
                vertex.color[2] = (color & 0x0000ff00) >> 8;

                vertex.normal[0] = 0;
                vertex.normal[1] = 0;
                vertex.normal[2] = 1;

                vertex.texture[0] = TexCoord(static_cast<float>(iX) * stepX / 2.f);
                vertex.texture[1] = TexCoord(static_cast<float>(iY) * stepY / 2.f);

                vertices.push_back(vertex);

                vertex.position[2] = -1;
                vertex.normal[2] = -1;

                vertices.push_back(vertex);
            }
        }

        ////indices
        for (int iX = 0; iX < slicesX; iX++)
        {
            for (int iY = 0; iY < slicesY; iY++)
            {
                uint16_t quad[4] = {
                    iX + iY * (slicesX + 1),
                    iX + 1 + iY * (slicesX + 1),
                    iX + (iY + 1) * (slicesX + 1),
                    iX + 1 + (iY + 1) * (slicesX + 1),
                };

                indices.push_back(quad[0] * 2 + indexOffset);
                indices.push_back(quad[2] * 2 + indexOffset);
                indices.push_back(quad[3] * 2 + indexOffset);
                indices.push_back(quad[3] * 2 + indexOffset);
                indices.push_back(quad[1] * 2 + indexOffset);
                indices.push_back(quad[0] * 2 + indexOffset);

                indices.push_back(quad[0] * 2 + 1 + indexOffset);
                indices.push_back(quad[2] * 2 + 1 + indexOffset);
                indices.push_back(quad[3] * 2 + 1 + indexOffset);
                indices.push_back(quad[3] * 2 + 1 + indexOffset);
                indices.push_back(quad[1] * 2 + 1 + indexOffset);
                indices.push_back(quad[0] * 2 + 1 + indexOffset);
            }
        }

        indexOffset += vertices.size();
    }

    ////left & right
    {
        ////vertices
        for (int iY = 0; iY < slicesY + 1; iY++)
        {
            for (int iZ = 0; iZ < slicesZ + 1; iZ++)
            {
                vertex.position[0] = 1;
                vertex.position[1] = iY * stepY - 1.f;
                vertex.position[2] = iZ * stepZ - 1.f;

                vertex.color[0] = (color & 0xff000000) >> 24;
                vertex.color[1] = (color & 0x00ff0000) >> 16;
                vertex.color[2] = (color & 0x0000ff00) >> 8;

                vertex.normal[0] = 0;
                vertex.normal[1] = 0;
                vertex.normal[2] = 1;

                vertex.texture[0] = TexCoord(static_cast<float>(iY) * stepY / 2.f);
                vertex.texture[1] = TexCoord(static_cast<float>(iZ) * stepZ / 2.f);

                vertices.push_back(vertex);

                vertex.position[0] = -1;
                vertex.normal[0] = -1;

                vertices.push_back(vertex);
            }
        }

        ////indices
        for (int iY = 0; iY < slicesY; iY++)
        {
            for (int iZ = 0; iZ < slicesZ; iZ++)
            {
                uint16_t quad[4] = {
                    iY + iZ * (slicesY + 1),
                    iY + 1 + iZ * (slicesY + 1),
                    iY + (iZ + 1) * (slicesY + 1),
                    iY + 1 + (iZ + 1) * (slicesY + 1),
                };

                indices.push_back(quad[0] * 2 + indexOffset);
                indices.push_back(quad[2] * 2 + indexOffset);
                indices.push_back(quad[3] * 2 + indexOffset);
                indices.push_back(quad[3] * 2 + indexOffset);
                indices.push_back(quad[1] * 2 + indexOffset);
                indices.push_back(quad[0] * 2 + indexOffset);

                indices.push_back(quad[0] * 2 + 1 + indexOffset);
                indices.push_back(quad[2] * 2 + 1 + indexOffset);
                indices.push_back(quad[3] * 2 + 1 + indexOffset);
                indices.push_back(quad[3] * 2 + 1 + indexOffset);
                indices.push_back(quad[1] * 2 + 1 + indexOffset);
                indices.push_back(quad[0] * 2 + 1 + indexOffset);
            }
        }

        indexOffset = vertices.size();
    }

    ////top & bottom
    {
        ////vertices
        for (int iZ = 0; iZ < slicesZ + 1; iZ++)
        {
            for (int iX = 0; iX < slicesX + 1; iX++)
            {
                vertex.position[0] = iX * stepX - 1.f;
                vertex.position[1] = 1;
                vertex.position[2] = iZ * stepZ - 1.f;

                vertex.color[0] = (color & 0xff000000) >> 24;
                vertex.color[1] = (color & 0x00ff0000) >> 16;
                vertex.color[2] = (color & 0x0000ff00) >> 8;

                vertex.normal[0] = 0;
                vertex.normal[1] = 0;
                vertex.normal[2] = 1;

                vertex.texture[0] = TexCoord(static_cast<float>(iZ) * stepZ / 2.f);
                vertex.texture[1] = TexCoord(static_cast<float>(iX) * stepX / 2.f);

                vertices.push_back(vertex);

                vertex.position[1] = -1;
                vertex.normal[1] = -1;

                vertices.push_back(vertex);
            }
        }

        ////indices
        for (int iZ = 0; iZ < slicesZ; iZ++)
        {
            for (int iX = 0; iX < slicesX; iX++)
            {
                uint16_t quad[4] = {
                    iZ + iX * (slicesZ + 1),
                    iZ + 1 + iX * (slicesZ + 1),
                    iZ + (iX + 1) * (slicesZ + 1),
                    iZ + 1 + (iX + 1) * (slicesZ + 1),
                };

                indices.push_back(quad[0] * 2 + indexOffset);
                indices.push_back(quad[2] * 2 + indexOffset);
                indices.push_back(quad[3] * 2 + indexOffset);
                indices.push_back(quad[3] * 2 + indexOffset);
                indices.push_back(quad[1] * 2 + indexOffset);
                indices.push_back(quad[0] * 2 + indexOffset);

                indices.push_back(quad[0] * 2 + 1 + indexOffset);
                indices.push_back(quad[2] * 2 + 1 + indexOffset);
                indices.push_back(quad[3] * 2 + 1 + indexOffset);
                indices.push_back(quad[3] * 2 + 1 + indexOffset);
                indices.push_back(quad[1] * 2 + 1 + indexOffset);
                indices.push_back(quad[0] * 2 + 1 + indexOffset);
            }
        }

        indexOffset = vertices.size();
    }

    util::dbg.WriteLine("Created Box Quadric with vertices: {%}\nindices: {%}",
                        util::WrapIterable(vertices.begin(), vertices.end(), "}, {"),
                        util::WrapIterable(indices.begin(), indices.end()), ", ");

    return gui::CreateMesh(vertices, indices);
}