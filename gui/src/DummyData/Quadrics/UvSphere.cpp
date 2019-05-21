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
    
    float phi, rho;
    size_t slice, stack, nextSlice, nextStack;

    ///Top
    q.SetTexCoords(0.5f, 0.0f);
    q.SetPositionAndNormal(0.f, 1.f, 0.f);
    q.Push();
    ///Bottom
    q.SetTexCoords(0.5f, 0.0f);
    q.SetPositionAndNormal(0.f, 1.f, 0.f);
    q.Push();

    for (slice = 0; slice < slices; ++slice)
    {
        phi = 2.0f * M_PI * static_cast<float>(slice) / static_cast<float>(slices);
        nextSlice = (slice + 1) % slices;

        for (stack = 0; stack < stacks - 1; ++stack)
        {
            rho = -M_PI / 2.0 + M_PI * (static_cast<float>(stack) / static_cast<float>(stacks));

            q.SetPositionAndNormal(cos(rho) * cos(phi), cos(rho) * sin(phi), sin(rho));
            q.SetSphericalTexCoords();
            q.Push();
        }

        for (stack = 0; stack < stacks - 2; ++stack)
        {
            nextStack = stack + 1;

            q.PushQuad(stack * slice + 2,
                       stack * nextSlice + 2,
                       nextStack * nextSlice + 2,
                       nextStack * slice + 2);
        }

        // q.PushTriangle(0, slice * stacks + 2, nextSlice * stacks + 2);
        // q.PushTriangle(1, slice * stacks + 2 + stacks, nextSlice * stacks + 2 + stacks);
    }

    return q.CreateMesh(out);
}