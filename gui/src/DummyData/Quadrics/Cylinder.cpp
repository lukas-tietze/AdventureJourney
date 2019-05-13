#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"

//---------------------------------------------------------------------------
bool gui::quadrics::Cylinder(uint32_t slices, uint32_t stacks, glutil::Mesh &out, uint32_t color)
{
    std::vector<gui::Vertex_Full> vertices;
    std::vector<uint16_t> indices;

    // create (stacks-1) rings
    for (int iSt = 0; iSt < stacks; iSt++)
    {
        float zb = float(iSt) / float(stacks);
        float zt = float(iSt + 1) / float(stacks);
        // with (slices-1) elements
        for (int iSl = 0; iSl < slices; iSl++)
        {
            float sliceRatioL = float(iSl) / float(slices);
            float sliceRatioR = float(iSl + 1) / float(slices);
            float cl = cosf(sliceRatioL * (float)M_PI * 2.0f), sl = sinf(sliceRatioL * (float)M_PI * 2.0f),
                  cr = cosf(sliceRatioR * (float)M_PI * 2.0f), sr = sinf(sliceRatioR * (float)M_PI * 2.0f);

            // TODO!
            // m_addQuad(cl, sl, zb, cl, sl, 0,
            // 	cr, sr, zb, cr, sr, 0,
            // 	cr, sr, zt, cr, sr, 0,
            // 	cl, sl, zt, cl, sl, 0);
        }
    }

    return gui::quadrics::CreateMesh(out, vertices, indices);
}