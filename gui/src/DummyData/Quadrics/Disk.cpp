#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"

bool gui::quadrics::Disk(uint32_t slices, uint32_t loops, glutil::Mesh &out)
{
    return Disk(slices, loops, out, QuadricConfig());
}

bool gui::quadrics::Disk(uint32_t slices, uint32_t loops, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config);

    q.Reserve(loops * slices + 1, slices * 3 + loops * (slices - 1));

    size_t loop, slice, nextSlice;
    float loopStep = 1.f / loops;
    float sliceStep = static_cast<float>(1.0 / slices * 2 * M_PI);

    q.SetNormal(0, 1, 0);
    q.SetPosition(0, 0, 0);
    q.SetTexCoords(0.5f, 0.5f);
    q.Push();

    for (slice = 0; slice < slices; slice++)
    {
        nextSlice = (slice + 1) % slices;

        for (loop = 0; loop < loops; loop++)
        {
            float a = std::sin(slice * sliceStep) * loop * loopStep;
            float b = std::cos(slice * sliceStep) * loop * loopStep;

            q.SetPosition(a, 0, b);
            q.SetTexCoords(a, b);
            q.Push();
        }

        for (loop = 0; loop < loops - 1; loop++)
            q.PushQuad(slice * loops * loop + 1,
                       nextSlice * loops + loop + 1,
                       nextSlice * loops + loop + 2,
                       slice * loops + loop + 2);

        q.PushTriangle(0, slice * loops + 1, nextSlice * loops + 1);
    }

    return q.CreateMesh(out);
}