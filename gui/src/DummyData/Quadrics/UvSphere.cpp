#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"
#include "data/String.hpp"

bool gui::quadrics::UvSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &out)
{
    return UvSphere(slices, stacks, out, QuadricConfig());
}

bool gui::quadrics::UvSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config, util::Format("UvSphere (%, %)", slices, stacks));

    q.Reserve((stacks - 1) * slices + 2, (stacks - 1) * slices * 6 + 2 * +3 * slices);

    float phi, rho;
    size_t slice, stack;

    ///Top
    q.SetTexCoords(0.5f, 0.0f);
    q.SetPositionAndNormal(0.f, 1.f, 0.f);
    q.Push();
    ///Bottom
    q.SetTexCoords(0.5f, 1.0f);
    q.SetPositionAndNormal(0.f, -1.f, 0.f);
    q.Push();

    for (slice = 0; slice < slices + 1; ++slice)
    {
        phi = 2.0f * M_PI * static_cast<float>(slice) / static_cast<float>(slices);

        for (stack = 0; stack < stacks - 1; ++stack)
        {
            rho = -M_PI / 2.0 + M_PI * (static_cast<float>(stack + 1) / static_cast<float>(stacks));

            q.SetPositionAndNormal(cos(rho) * cos(phi), sin(rho), cos(rho) * sin(phi));
            q.SetSphericalTexCoords();
            q.Push();
        }

        ///Texturkoordinaten werden 0 bei y = 0!

        if (slice < slices - 1)
        {
            for (stack = 0; stack < stacks - 2; ++stack)
            {
                q.PushQuad(slice * (stacks - 1) + stack + 2,
                           (slice + 1) * (stacks - 1) + stack + 2,
                           (slice + 1) * (stacks - 1) + (stack + 1) + 2,
                           slice * (stacks - 1) + (stack + 1) + 2);
            }
        }

        q.PushTriangle(1, slice * (stacks - 1) + 2, (slice + 1) * (stacks - 1) + 2);
        q.PushTriangle(0, slice * (stacks - 1) + stacks, (slice + 1) * (stacks - 1) + stacks);
    }

    return q.CreateMesh(out);
}