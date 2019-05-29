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
    float sliceStep = 1.f / static_cast<float>(slices);
    float stackStep = 1.f / static_cast<float>(stacks);

    for (slice = 0; slice < slices + 1; ++slice)
    {
        ///vertices
        {
            ///Bottom
            q.SetPositionAndNormal(0.f, -1.f, 0.f);
            q.SetTexCoords(slice * sliceStep, 0.0f);
            q.Push();

            phi = 2.0f * M_PI * slice * sliceStep;

            for (stack = 0; stack < stacks - 1; ++stack)
            {
                rho = -M_PI / 2.0 + M_PI * (stack + 1) * stackStep;

                q.SetPositionAndNormal(cos(rho) * cos(phi), sin(rho), cos(rho) * sin(phi));
                q.SetTexCoords(slice * sliceStep, stack * stackStep);
                q.Push();
            }

            ///Top
            q.SetPositionAndNormal(0.f, 1.f, 0.f);
            q.SetTexCoords(slice * sliceStep, 1.0f);
            q.Push();
        }
        ///indices
        {
            if (slice < slices)
            {
                for (stack = 1; stack < stacks - 1; ++stack)
                {
                    q.PushQuad(slice * (stacks + 1) + stack,
                               (slice + 1) * (stacks + 1) + stack,
                               (slice + 1) * (stacks + 1) + stack + 1,
                               slice * (stacks + 1) + stack + 1);
                }

                q.PushTriangle(slice * (stacks + 1),
                               slice * (stacks + 1) + 1,
                               (slice + 1) * (stacks + 1) + 1);

                q.PushTriangle(slice * (stacks + 1) + stacks,
                               slice * (stacks + 1) + stacks - 1,
                               (slice + 1) * (stacks + 1) + stacks - 1);
            }
        }
    }

    return q.CreateMesh(out);
}