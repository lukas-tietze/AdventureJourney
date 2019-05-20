#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"

bool gui::quadrics::Disk(uint32_t slices, uint32_t loops, glutil::Mesh &out)
{
    return Disk(slices, loops, out, QuadricConfig());
}

bool gui::quadrics::Disk(uint32_t slices, uint32_t loops, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config);

    // create (loops-1) rings
    for (uint32_t iL = 0; iL < loops; iL++)
    {
        float ro = (1.0f - float(iL) / float(loops));     // outer radius
        float ri = (1.0f - float(iL + 1) / float(loops)); // inner radius
        // with (slices-1) elements
        for (uint32_t iSl = 0; iSl < slices; iSl++)
        {
            float sliceRatioL = float(iSl) / float(slices);
            float sliceRatioR = float(iSl + 1) / float(slices);
            float cl = cosf(sliceRatioL * (float)M_PI * 2.0f), sl = sinf(sliceRatioL * (float)M_PI * 2.0f),
                  cr = cosf(sliceRatioR * (float)M_PI * 2.0f), sr = sinf(sliceRatioR * (float)M_PI * 2.0f);
            if (iL == loops - 1)
            {
                // TODO!
                // m_addTriangle(cl * ro, sl * ro, 0, 0, 0, 1,
                //               cr * ro, sr * ro, 0, 0, 0, 1,
                //               0, 0, 0, 0, 0, 1);
            }
            else
            {
                // TODO!
                // m_addQuad(cl * ro, sl * ro, 0, 0, 0, 1,
                //           cr * ro, sr * ro, 0, 0, 0, 1,
                //           cr * ri, sr * ri, 0, 0, 0, 1,
                //           cl * ri, sl * ri, 0, 0, 0, 1);
            }
        }
    }

    return q.CreateMesh(out);
}