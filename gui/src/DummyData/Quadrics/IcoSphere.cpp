#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"

namespace
{
void SubdivideTriangle(int subdiv, float r, float g, float b,
                       float x0, float y0, float z0,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2)
{
    if (subdiv > 0)
    {
        //subdivide further
        --subdiv;
        float x3, y3, z3, x4, y4, z4, x5, y5, z5;
        //1. calculate new positions
        x3 = 0.5f * x0 + 0.5f * x1; //            v2                //
        y3 = 0.5f * y0 + 0.5f * y1; //           /  \               //
        z3 = 0.5f * z0 + 0.5f * z1; //          /    \              //
                                    //         /      \             //
        x4 = 0.5f * x1 + 0.5f * x2; //        /        \            //
        y4 = 0.5f * y1 + 0.5f * y2; //       v5---------v4          //
        z4 = 0.5f * z1 + 0.5f * z2; //      / \        / \          //
                                    //     /   \      /   \         //
        x5 = 0.5f * x2 + 0.5f * x0; //    /     \    /     \        //
        y5 = 0.5f * y2 + 0.5f * y0; //   /       \  /       \       //
        z5 = 0.5f * z2 + 0.5f * z0; // v0---------v3---------v1     //
        //2. normalize them
        float l;
        l = sqrt(x3 * x3 + y3 * y3 + z3 * z3);
        x3 /= l;
        y3 /= l;
        z3 /= l;
        l = sqrt(x4 * x4 + y4 * y4 + z4 * z4);
        x4 /= l;
        y4 /= l;
        z4 /= l;
        l = sqrt(x5 * x5 + y5 * y5 + z5 * z5);
        x5 /= l;
        y5 /= l;
        z5 /= l;
        SubdivideTriangle(subdiv, r, g, b,
                          x0, y0, z0,
                          x3, y3, z3,
                          x5, y5, z5);
        SubdivideTriangle(subdiv, r, g, b,
                          x3, y3, z3,
                          x1, y1, z1,
                          x4, y4, z4);
        SubdivideTriangle(subdiv, r, g, b,
                          x5, y5, z5,
                          x3, y3, z3,
                          x4, y4, z4);
        SubdivideTriangle(subdiv, r, g, b,
                          x2, y2, z2,
                          x5, y5, z5,
                          x4, y4, z4);
    }
    else
    {
        // TODO!
        // m_addTriangle(x0, y0, z0, x0, y0, z0,
        //               x1, y1, z1, x1, y1, z1,
        //               x2, y2, z2, x2, y2, z2);
    }
}
} // namespace

bool gui::quadrics::Ico8Sphere(uint32_t subdiv, glutil::Mesh &out, uint32_t color)
{
    std::vector<gui::Vertex_Full> vertices;
    std::vector<uint16_t> indices;

    // create 4 initial triangles
    //upper part
    SubdivideTriangle(subdiv, 1, 1, 1,
                      1, 0, 0,
                      0, 0, -1,
                      0, 1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      0, 0, -1,
                      -1, 0, 0,
                      0, 1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      -1, 0, 0,
                      0, 0, 1,
                      0, 1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      0, 0, 1,
                      1, 0, 0,
                      0, 1, 0);
    //lower part
    SubdivideTriangle(subdiv, 1, 1, 1,
                      0, 0, -1,
                      1, 0, 0,
                      0, -1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      -1, 0, 0,
                      0, 0, -1,
                      0, -1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      0, 0, 1,
                      -1, 0, 0,
                      0, -1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      1, 0, 0,
                      0, 0, 1,
                      0, -1, 0);

    return gui::quadrics::CreateMesh(out, vertices, indices);
}

bool gui::quadrics::Ico12Sphere(uint32_t subdiv, glutil::Mesh &out, uint32_t color)
{
    std::vector<gui::Vertex_Full> vertices;
    std::vector<uint16_t> indices;

    // create 4 initial triangles
    //upper part
    SubdivideTriangle(subdiv, 1, 1, 1,
                      1, 0, 0,
                      0, 0, -1,
                      0, 1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      0, 0, -1,
                      -1, 0, 0,
                      0, 1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      -1, 0, 0,
                      0, 0, 1,
                      0, 1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      0, 0, 1,
                      1, 0, 0,
                      0, 1, 0);
    //lower part
    SubdivideTriangle(subdiv, 1, 1, 1,
                      0, 0, -1,
                      1, 0, 0,
                      0, -1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      -1, 0, 0,
                      0, 0, -1,
                      0, -1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      0, 0, 1,
                      -1, 0, 0,
                      0, -1, 0);
    SubdivideTriangle(subdiv, 1, 1, 1,
                      1, 0, 0,
                      0, 0, 1,
                      0, -1, 0);

    return gui::quadrics::CreateMesh(out, vertices, indices);
}