#include "DummyData.hpp"

#include <cmath>

#include "QuadricHelper.internal.hpp"
#include "Defs.hpp"

namespace
{
struct SubdivData
{
    float x0;
    float y0;
    float z0;

    float x1;
    float y1;
    float z1;

    float x2;
    float y2;
    float z2;

    float x3;
    float y3;
    float z3;

    float x4;
    float y4;
    float z4;

    float x5;
    float y5;
    float z5;
};

void CalcSubdivision(SubdivData &data)
{
    //1. calculate new positions
    data.x3 = 0.5f * data.x0 + 0.5f * data.x1;  //            v2                //
    data.y3 = 0.5f * data.y0 + 0.5f * data.y1;  //           /  \               //
    data.z3 = 0.5f * data.z0 + 0.5f * data.z1;  //          /    \              //
                                                //         /      \             //
    data.x4 = 0.5f * data.x1 + 0.5f * data.x2;  //        /        \            //
    data.y4 = 0.5f * data.y1 + 0.5f * data.y2;  //       v5---------v4          //
    data.z4 = 0.5f * data.z1 + 0.5f * data.z2;  //      / \        / \          //
                                                //     /   \      /   \         //
    data.x5 = 0.5f * data.x2 + 0.5f * data.x0;  //    /     \    /     \        //
    data.y5 = 0.5f * data.y2 + 0.5f * data.y0;  //   /       \  /       \       //
    data.z5 = 0.5f * data.z2 + 0.5f * data.z0;  // v0---------v3---------v1     //

    //2. normalize them
    float l;
    l = sqrt(data.x3 * data.x3 + data.y3 * data.y3 + data.z3 * data.z3);
    data.x3 /= l;
    data.y3 /= l;
    data.z3 /= l;
    l = sqrt(data.x4 * data.x4 + data.y4 * data.y4 + data.z4 * data.z4);
    data.x4 /= l;
    data.y4 /= l;
    data.z4 /= l;
    l = sqrt(data.x5 * data.x5 + data.y5 * data.y5 + data.z5 * data.z5);
    data.x5 /= l;
    data.y5 /= l;
    data.z5 /= l;
}

void SubdivideTriangles(std::vector<gui::Vertex_Full> &vertices, std::vector<uint16_t> &indices)
{
}

gui::Vertex_Full &BaseQuadCorner(gui::Vertex_Full &vertex, int i, int c1, int c2)
{
    float values[3];

    values[(i + 0) % 3] = c1 * 1;
    values[(i + 0) % 3] = c2 * M_INV_GR;
    values[(i + 0) % 3] = 0;

    return gui::quadrics::SetPositionAndNormal(vertex, values[0], values[1], values[2]);
}
} // namespace

bool gui::quadrics::IcoSphere(uint32_t subdiv, glutil::Mesh &out, uint32_t color)
{
    std::vector<gui::Vertex_Full> vertices;
    std::vector<uint16_t> indices;

    vertices.reserve(12 * std::pow(4, subdiv));
    indices.reserve(20 * 3);
    // indices.insert(indices.begin(), 20 * 3, 0);

    gui::Vertex_Full vertex;

    FillColor(vertex, color);
    vertex.texture[0] = 0;
    vertex.texture[1] = 0;

    // ////Konstruktion nach https://upload.wikimedia.org/wikipedia/commons/9/9c/Icosahedron-golden-rectangles.svg
    // ////3 Rechtecke
    // for (int i = 0; i < 3; i++)
    // {
    //     vertices.push_back(BaseQuadCorner(vertex, i, 1, 1));
    //     vertices.push_back(BaseQuadCorner(vertex, i, 1, -1));
    //     vertices.push_back(BaseQuadCorner(vertex, i, -1, 1));
    //     vertices.push_back(BaseQuadCorner(vertex, i, -1, -1));

    //     indices.push_back(i * 4 + 0);
    //     indices.push_back(i * 4 + 3);
    //     indices.push_back(i * 4 + 1);
    //     indices.push_back(i * 4 + 3);
    //     indices.push_back(i * 4 + 2);
    //     indices.push_back(i * 4 + 1);

    //     // for (int j = 0; j < 20; j++)
    //     // {
    //     //     indices[i * 20 + j] = i * 4 + j % 5;
    //     // }
    // }

    ////Lade statische Werte von https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/

    const float X = .525731112119133606f;
    const float Z = .850650808352039932f;
    const float N = 0.f;

    vertices.push_back(SetPositionAndNormal(vertex, -X, N, Z));
    vertices.push_back(SetPositionAndNormal(vertex, X, N, Z));
    vertices.push_back(SetPositionAndNormal(vertex, -X, N, Z));
    vertices.push_back(SetPositionAndNormal(vertex, X, N, Z));
    vertices.push_back(SetPositionAndNormal(vertex, N, Z, X));
    vertices.push_back(SetPositionAndNormal(vertex, N, Z, X));
    vertices.push_back(SetPositionAndNormal(vertex, N, -Z, X));
    vertices.push_back(SetPositionAndNormal(vertex, N, -Z, X));
    vertices.push_back(SetPositionAndNormal(vertex, Z, X, N));
    vertices.push_back(SetPositionAndNormal(vertex, -Z, X, N));
    vertices.push_back(SetPositionAndNormal(vertex, Z, -X, N));
    vertices.push_back(SetPositionAndNormal(vertex, -Z, -X, N));

    indices.assign({0, 4, 1,
                    0, 9, 4,
                    9, 5, 4,
                    4, 5, 8,
                    4, 8, 1,
                    8, 10, 1,
                    8, 3, 10,
                    5, 3, 8,
                    5, 2, 3,
                    2, 7, 3,
                    7, 10, 3,
                    7, 6, 10,
                    7, 11, 6,
                    11, 0, 6,
                    0, 1, 6,
                    6, 1, 10,
                    9, 0, 11,
                    9, 11, 2,
                    9, 2, 5,
                    7, 2, 11});

    for (int i = 0; i < subdiv; i++)
        SubdivideTriangles(vertices, indices);

    return gui::quadrics::CreateMesh(out, vertices, indices);
}