#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"

bool gui::quadrics::UvSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &out)
{
    return UvSphere(slices, stacks, out, QuadricConfig());
}

bool gui::quadrics::UvSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config);

    q.Reserve(0, 0);

    float x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
    float slr = (2 * (float)M_PI) / (float)slices;
    float str = (float)(M_PI) / (float)stacks;
    float phi;
    float rho;

    ///Top
    q.SetTexCoords(0.5f, 0.0f);
    q.SetPositionAndNormal(0.f, 1.f, 0.f);
    q.Push();
    ///Bottom
    q.SetTexCoords(0.5f, 0.0f);
    q.SetPositionAndNormal(0.f, 1.f, 0.f);
    q.Push();

    for (size_t slice = 0; slice < slices; ++slice)
    {
        phi = 2.0f * M_PI * static_cast<float>(slice) / static_cast<float>(slices);

        for (size_t stack = 0; stack < stacks - 1; ++stack)
        {
            rho = -M_PI / 2.0 + M_PI * (static_cast<float>(stack) / static_cast<float>(stacks));

            q.SetPositionAndNormal(cos(rho) * cos(phi), cos(rho) * sin(phi), sin(rho));
            q.SetSphericalTexCoords();
            q.Push();
            q.PushQuad(slice * stacks + 2,
                       (((slice + 1) % slices) * stacks + 2),
                       (((slice + 1) % slices) * (stacks + 1) + 2),
                       slice * (stacks + 1) + 2);
        }

        q.PushTriangle(0, slice * stacks + 2, ((slice + 1) % slices) * stacks + 2);
        q.PushTriangle(1, slice * stacks + 2 + stacks, ((slice + 1) % slices) * stacks + 2 + stacks);
    }

    return q.CreateMesh(out);
}