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

    q.Reserve((slices + 1) * (stacks + 1), slices * stacks * 6);

    float phi;
    float x, y;
    size_t slice, stack;
    float sliceStep = 1.f / static_cast<float>(slices);
    float stackStep = 1.f / static_cast<float>(stacks);

    for (slice = 0; slice < slices + 1; slice++)
    {
        phi = 2.0f * M_PI * slice * sliceStep;
        x = cos(phi);
        y = sin(phi);
        q.SetNormal(x, 0, y);

        for (stack = 0; stack < stacks + 1; stack++)
        {
            q.SetPosition(x, stack * stackStep * 2.f - 1.f, y);
            q.SetTexCoords(slice * sliceStep, stack * stackStep);
            q.Push();
        }

        // stacks = 2, slices = 2
        //  0  1  2
        //0 0--3--6
        //  |  |  |
        //1 1--4--7
        //  |  |  |
        //2 2--5--8

        if (slice < slices)
        {
            for (stack = 0; stack < stacks; stack++)
            {
                q.PushQuad(slice * (stacks + 1) + stack,
                           (slice + 1) * (stacks + 1) + stack,
                           (slice + 1) * (stacks + 1) + (stack + 1),
                           slice * (stacks + 1) + (stack + 1));
            }
        }
    }
    
    return q.CreateMesh(out);
}