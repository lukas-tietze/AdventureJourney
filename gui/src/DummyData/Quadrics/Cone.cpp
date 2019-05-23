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

    float phi;
    float x, y, r;
    size_t slice, stack;
    float sliceStep = 1.f / static_cast<float>(slices);
    float stackStep = 1.f / static_cast<float>(stacks);

    for (slice = 0; slice < slices + 1; slice++)
    {
        phi = 2.0f * M_PI * slice * sliceStep;
        x = cos(phi);
        y = sin(phi);
        q.SetNormal(x, 0.5f, y);

        for (stack = 0; stack < stacks + 1; stack++)
        {
            r = (1.f - stack * stackStep);

            q.SetPosition(r * x, stack * stackStep * 2.f - 1.f, r * y);
            q.SetTexCoords(slice * sliceStep, stack * stackStep);
            q.Push();
        }

        if (slice < slices)
        {
            q.PushTriangle(slice * (stacks + 1) + stacks,
                           slice * (stacks + 1) + stacks - 1,
                           (slice + 1) * (stacks + 1) + stacks - 1);

            for (stack = 0; stack < stacks - 1; stack++)
            {
                q.PushQuad(slice * (stacks + 1) + stack,
                           (slice + 1) * (stacks + 1) + stack,
                           (slice + 1) * (stacks + 1) + stack + 1,
                           slice * (stacks + 1) + stack + 1);
            }
        }
    }

    return q.CreateMesh(out);
}