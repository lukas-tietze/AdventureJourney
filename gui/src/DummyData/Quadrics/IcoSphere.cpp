#include "DummyData.hpp"

#include <cmath>

#include "QuadricHelper.internal.hpp"
#include "Defs.hpp"

namespace
{
struct SubdivData
{
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
    glm::vec3 v4;
    glm::vec3 v5;
};

void CalcSubdivision(SubdivData &data)
{
    //1. calculate new positions
    data.v3.x = 0.5f * data.v0.x + 0.5f * data.v1.x; //            v2                //
    data.v3.y = 0.5f * data.v0.y + 0.5f * data.v1.y; //           /  \               //
    data.v3.z = 0.5f * data.v0.z + 0.5f * data.v1.z; //          /    \              //
                                                     //         /      \             //
    data.v4.x = 0.5f * data.v1.x + 0.5f * data.v2.x; //        /        \            //
    data.v4.y = 0.5f * data.v1.y + 0.5f * data.v2.y; //       v5---------v4          //
    data.v4.z = 0.5f * data.v1.z + 0.5f * data.v2.z; //      / \        / \          //
                                                     //     /   \      /   \         //
    data.v5.x = 0.5f * data.v2.x + 0.5f * data.v0.x; //    /     \    /     \        //
    data.v5.y = 0.5f * data.v2.y + 0.5f * data.v0.y; //   /       \  /       \       //
    data.v5.z = 0.5f * data.v2.z + 0.5f * data.v0.z; // v0---------v3---------v1     //

    data.v3 = glm::normalize(data.v3);
    data.v4 = glm::normalize(data.v4);
    data.v5 = glm::normalize(data.v5);
}

void SubdivideTriangles(gui::quadrics::QuadricContext &q)
{
    auto &vertices = q.Vertices();
    auto &indices = q.Indices();
    SubdivData data;
    int length;
    int indexBuf[6];

    for (size_t c = 0, max = q.IndexCount() / 3; c < max; c++)
    {
        length = vertices.size();

        indexBuf[0] = indices[c * 3 + 0];
        indexBuf[1] = indices[c * 3 + 1];
        indexBuf[2] = indices[c * 3 + 2];
        indexBuf[3] = length;
        indexBuf[4] = length + 1;
        indexBuf[5] = length + 2;

        data.v0 = vertices[indexBuf[0]].pos;
        data.v1 = vertices[indexBuf[1]].pos;
        data.v2 = vertices[indexBuf[2]].pos;

        CalcSubdivision(data);

        q.SetPositionAndNormal(data.v3);
        q.SetTexCoords(std::acos(data.v3.z), atan2(data.v3.y, data.v3.x));
        q.Push();

        q.SetPositionAndNormal(data.v4);
        q.SetTexCoords(std::acos(data.v4.z), atan2(data.v4.y, data.v4.x));
        q.Push();

        q.SetPositionAndNormal(data.v5);
        q.SetTexCoords(std::acos(data.v5.z), atan2(data.v5.y, data.v5.x));
        q.Push();

        indices[c * 3 + 0] = indexBuf[0];
        indices[c * 3 + 1] = indexBuf[3];
        indices[c * 3 + 2] = indexBuf[5];

        // q.PushTriangle(indexBuf[0], indexBuf[3], indexBuf[5]);
        q.PushTriangle(indexBuf[3], indexBuf[1], indexBuf[4]);
        q.PushTriangle(indexBuf[3], indexBuf[4], indexBuf[5]);
        q.PushTriangle(indexBuf[5], indexBuf[4], indexBuf[2]);
    }
}
} // namespace

bool gui::quadrics::IcoSphere(uint32_t subdiv, glutil::Mesh &out)
{
    return IcoSphere(subdiv, out, QuadricConfig());
}

bool gui::quadrics::IcoSphere(uint32_t subdiv, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config);

    q.Reserve(12 * std::pow(4, subdiv), 20 * 3);

    q.SetTexCoords(0, 0);

    ////Lade statische Werte von https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/

    const float X = .525731112119133606f;
    const float Z = .850650808352039932f;
    const float N = 0.f;

    q.SetPositionAndNormal(-X, N, Z);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(X, N, Z);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(-X, N, -Z);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(X, N, -Z);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(N, Z, X);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(N, Z, -X);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(N, -Z, X);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(N, -Z, -X);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(Z, X, N);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(-Z, X, N);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(Z, -X, N);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();
    
    q.SetPositionAndNormal(-Z, -X, N);
    q.SetTexCoords(std::acos(q.Current().pos.z), atan2(q.Current().pos.y, q.Current().pos.x));
    q.Push();

    q.PushTriangle(0, 4, 1);
    q.PushTriangle(0, 9, 4);
    q.PushTriangle(9, 5, 4);
    q.PushTriangle(4, 5, 8);
    q.PushTriangle(4, 8, 1);
    q.PushTriangle(8, 10, 1);
    q.PushTriangle(8, 3, 10);
    q.PushTriangle(5, 3, 8);
    q.PushTriangle(5, 2, 3);
    q.PushTriangle(2, 7, 3);
    q.PushTriangle(7, 10, 3);
    q.PushTriangle(7, 6, 10);
    q.PushTriangle(7, 11, 6);
    q.PushTriangle(11, 0, 6);
    q.PushTriangle(0, 1, 6);
    q.PushTriangle(6, 1, 10);
    q.PushTriangle(9, 0, 11);
    q.PushTriangle(9, 11, 2);
    q.PushTriangle(9, 2, 5);
    q.PushTriangle(7, 2, 1);

    for (size_t i = 0; i < subdiv; i++)
        SubdivideTriangles(q);
        
    return q.CreateMesh(out);
}