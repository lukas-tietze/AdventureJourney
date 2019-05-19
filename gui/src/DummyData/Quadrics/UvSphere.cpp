#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"

bool gui::quadrics::UVSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &out)
{
    return UVSphere(slices, stacks, out, QuadricConfig());
}

bool gui::quadrics::UVSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config);

    float x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
    float slr = (2 * (float)M_PI) / (float)slices;
    float str = (float)(M_PI) / (float)stacks;

    for (size_t iSt = 0; iSt < stacks; ++iSt)
    {
        float rho = -(float)M_PI / 2.0f + (float)M_PI * (float(iSt) / float(stacks));
        for (size_t iSl = 0; iSl < slices; ++iSl)
        {
            float phi = 2.0f * (float)M_PI * float(iSl) / float(slices);

            x0 = cos(rho) * cos(phi);
            y0 = cos(rho) * sin(phi);
            z0 = sin(rho);
            x1 = cos(rho) * cos(phi + slr);
            y1 = cos(rho) * sin(phi + slr);
            z1 = sin(rho);
            x2 = cos(rho + str) * cos(phi + slr);
            y2 = cos(rho + str) * sin(phi + slr);
            z2 = sin(rho + str);
            x3 = cos(rho + str) * cos(phi);
            y3 = cos(rho + str) * sin(phi);
            z3 = sin(rho + str);

            if (iSt == 0)
            {
                // TODO
                // m_addTriangle(0, 0, -1, 0, 0, -1,
                //               x2, y2, z2, x2, y2, z2,
                //               x3, y3, z3, x3, y3, z3);
            }
            else if (iSt == stacks - 1)
            {
                // TODO
                // m_addTriangle(x0, y0, z0, x0, y0, z0,
                //               x1, y1, z1, x1, y1, z1,
                //               0, 0, 1, 0, 0, 1);
            }
            else
            {
                // TODO
                // m_addQuad(x0, y0, z0, x0, y0, z0,
                //           x1, y1, z1, x1, y1, z1,
                //           x2, y2, z2, x2, y2, z2,
                //           x3, y3, z3, x3, y3, z3);
            }
        }
    }

    return q.CreateMesh(out);
}