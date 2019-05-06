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

    // FRONT + BACK
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

            vertex.texture[0] = iX * stepX / 2.f;
            vertex.texture[1] = iY * stepY / 2.f;

            vertices.push_back(vertex);

            vertex.position[2] = -1;
            vertex.normal[2] = -1;

            vertices.push_back(vertex);
        }
    }

    for (int iX = 0; iX < slicesX; iX++)
    {
        for (int iY = 0; iY < slicesY; iY++)
        {
            uint16_t quad[4] = {
                iX + iY * (slicesX + 1) + indexOffset,
                iX + 1 + iY * (slicesX + 1) + indexOffset,
                iX + (iY + 1) * (slicesX + 1) + indexOffset,
                iX + 1 + (iY + 1) * (slicesX + 1) + indexOffset,
            };

            indices.push_back(quad[0]);
            indices.push_back(quad[2]);
            indices.push_back(quad[3]);
            indices.push_back(quad[3]);
            indices.push_back(quad[1]);
            indices.push_back(quad[0]);

            for (int i = 0; i < 4; i++)
                quad[i] += (slicesX + 1) * (slicesY + 1);

            indices.push_back(quad[0]);
            indices.push_back(quad[2]);
            indices.push_back(quad[3]);
            indices.push_back(quad[3]);
            indices.push_back(quad[1]);
            indices.push_back(quad[0]);
        }
    }

    indexOffset = vertices.size();

    vertices.shrink_to_fit();
    indices.shrink_to_fit();

    util::dbg.WriteLine("Created Box Quadric with vertices: %\nindices: %",
                        util::WrapIterable(vertices.begin(), vertices.end(), ", "),
                        util::WrapIterable(indices.begin(), indices.end()), ", ");

    // // LEFT + RIGHT
    // for (int iY = 0; iY < slicesY; iY++)
    // {
    //     for (int iZ = 0; iZ < slicesZ; iZ++)
    //     {
    //         float left = -1, //float(iX)  /float(slicesX)*sizeX,
    //             right = 1,   //float(iX+1)/float(slicesX)*sizeX,
    //             bottom = float(iY) / float(slicesY) * 2.0f - 1.0f,
    //               top = float(iY + 1) / float(slicesY) * 2.0f - 1.0f,
    //               back = float(iZ) / float(slicesZ) * 2.0f - 1.0f,
    //               front = float(iZ + 1) / float(slicesZ) * 2.0f - 1.0f;
    //         float u0 = float(iY) / float(slicesY),
    //               u1 = float(iY + 1) / float(slicesY),
    //               v0 = float(iZ) / float(slicesZ),
    //               v1 = float(iZ + 1) / float(slicesZ);
    //         // m_addQuad(left, bottom, back, -1, 0, 0,
    //         //           left, bottom, front, -1, 0, 0,
    //         //           left, top, front, -1, 0, 0,
    //         //           left, top, back, -1, 0, 0);
    //         // m_addQuad(right, bottom, back, 1, 0, 0,
    //         //           right, top, back, 1, 0, 0,
    //         //           right, top, front, 1, 0, 0,
    //         //           right, bottom, front, 1, 0, 0);
    //     }
    // }

    // // TOP + BOTTOM
    // for (int iZ = 0; iZ < slicesZ; iZ++)
    // {
    //     for (int iX = 0; iX < slicesX; iX++)
    //     {
    //         float left = float(iX) / float(slicesX) * 2.0f - 1.0f,
    //               right = float(iX + 1) / float(slicesX) * 2.0f - 1.0f,
    //               bottom = -1,
    //               top = 1,
    //               back = float(iZ) / float(slicesZ) * 2.0f - 1.0f,
    //               front = float(iZ + 1) / float(slicesZ) * 2.0f - 1.0f;
    //         float u0 = float(iZ) / float(slicesZ),
    //               u1 = float(iZ + 1) / float(slicesZ),
    //               v0 = float(iX) / float(slicesX),
    //               v1 = float(iX + 1) / float(slicesX);
    //         // m_addQuad(left, top, front, 0, 1, 0,
    //         //           right, top, front, 0, 1, 0,
    //         //           right, top, back, 0, 1, 0,
    //         //           left, top, back, 0, 1, 0);
    //         // m_addQuad(left, bottom, front, 0, -1, 0,
    //         //           left, bottom, back, 0, -1, 0,
    //         //           right, bottom, back, 0, -1, 0,
    //         //           right, bottom, front, 0, -1, 0);
    //     }
    // }

    return gui::CreateMesh(vertices, indices);
}