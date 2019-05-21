#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"
#include "data/String.hpp"

bool gui::quadrics::Cone(uint32_t slices, uint32_t stacks, glutil::Mesh &out)
{
    return Cone(slices, stacks, out, QuadricConfig());
}

bool gui::quadrics::Cone(uint32_t slices, uint32_t stacks, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config, util::Format("Cone (%, %)", slices, stacks));

    // this is a small normal trick:
    float n[3] = {1, 0, 1};
    float len = sqrt(n[0] * n[0] + n[2] * n[2]);
    n[0] /= len;
    n[2] /= len;
    // create (loops-1) rings
    for (float iSt = 0; iSt < 1.f; iSt += (1.f / (float)stacks))
    {
        float br = (1.0f - iSt);                         // bottom radius
        float tr = (1.0f - iSt - (1.f / (float)stacks)); // top radius
        float bz = iSt;
        float tz = iSt + (1.f / (float)stacks);
        // with (slices-1) elements
        for (uint32_t iSl = 0; iSl < slices; iSl++)
        {
            float sliceRatioL = float(iSl) / float(slices);
            float sliceRatioR = float(iSl + 1) / float(slices);
            float cl = cosf(sliceRatioL * (float)M_PI * 2.0f), sl = sinf(sliceRatioL * (float)M_PI * 2.0f),
                  cr = cosf(sliceRatioR * (float)M_PI * 2.0f), sr = sinf(sliceRatioR * (float)M_PI * 2.0f);
            float nlx = cl * n[0], nly = sl * n[0], nlz = n[2],
                  nrx = cr * n[0], nry = sr * n[0], nrz = n[2];

            if (iSt < (1.0f - (1.f / (float)stacks)))
            {
                // TODO!
                // m_addQuad(cl * br, sl * br, bz, nlx, nly, nlz,
                //           cr * br, sr * br, bz, nrx, nry, nrz,
                //           cr * tr, sr * tr, tz, nrx, nry, nrz,
                //           cl * tr, sl * tr, tz, nlx, nly, nlz);
            }
            else
            {
                // TODO!
                // m_addTriangle(cl * br, sl * br, bz, nlx, nly, nlz,
                //               cr * br, sr * br, bz, nrx, nry, nrz,
                //               0, 0, tz, nrx, nry, nrz);
            }
        }
    }

    return q.CreateMesh(out);
}