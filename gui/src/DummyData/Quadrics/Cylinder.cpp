#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"
#include "data/String.hpp"

bool gui::quadrics::Cylinder(uint32_t slices, uint32_t stacks, glutil::Mesh &out)
{
    return Cylinder(slices, stacks, out, QuadricConfig());
}

bool gui::quadrics::Cylinder(uint32_t slices, uint32_t stacks, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config, util::Format("cylinder (%, %)", slices, stacks));

    // create (stacks-1) rings
    for (uint32_t iSt = 0; iSt < stacks; iSt++)
    {
        float zb = float(iSt) / float(stacks);
        float zt = float(iSt + 1) / float(stacks);
        // with (slices-1) elements
        for (uint32_t iSl = 0; iSl < slices; iSl++)
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

    return q.CreateMesh(out);
}