#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"
#include "data/IteratorUtils.hpp"
#include "data/Io.hpp"

bool gui::quadrics::Box(glutil::Mesh &out)
{
    return Box(out, QuadricConfig());
}

bool gui::quadrics::Box(glutil::Mesh &out, const QuadricConfig &config)
{
    return Box(1, 1, 1, out, config);
}

bool gui::quadrics::Box(uint32_t slicesX, uint32_t slicesY, uint32_t slicesZ, glutil::Mesh &out)
{
    return Box(slicesX, slicesY, slicesZ, out, QuadricConfig());
}

bool gui::quadrics::Box(uint32_t slicesX, uint32_t slicesY, uint32_t slicesZ, glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config);

    q.Reserve(2 * (slicesX + 1) * (slicesY + 1) +
                  2 * (slicesY + 1) * (slicesZ + 1) +
                  2 * (slicesZ + 1) * (slicesX + 1),
              2 * 6 * slicesX * slicesY +
                  2 * 6 * slicesY * slicesZ +
                  2 * 6 * slicesZ * slicesX);

    float stepX = 2.f / static_cast<float>(slicesX);
    float stepY = 2.f / static_cast<float>(slicesY);
    float stepZ = 2.f / static_cast<float>(slicesZ);
    size_t indexOffset = 0;

    ////front & back
    {
        ////vertices
        for (uint32_t iX = 0; iX < slicesX + 1; iX++)
        {
            for (uint32_t iY = 0; iY < slicesY + 1; iY++)
            {
                q.SetPosition(iX * stepX - 1.f, iY * stepY - 1.f, 1);
                q.SetNormal(0, 0, 1);
                q.SetTexCoords(iX * stepX / 2.f, iY * stepY / 2.f);
                q.Push();

                q.Pos()[2] = -1;
                q.Normal()[2] = -1;
                q.Push();
            }
        }

        ////indices
        for (uint32_t iX = 0; iX < slicesX; iX++)
        {
            for (uint32_t iY = 0; iY < slicesY; iY++)
            {
                uint16_t quad[4] = {
                    iX + iY * (slicesX + 1),
                    iX + 1 + iY * (slicesX + 1),
                    iX + 1 + (iY + 1) * (slicesX + 1),
                    iX + (iY + 1) * (slicesX + 1),
                };

                for (int i = 0; i < 4; i++)
                    quad[i] = quad[i] * 2 + indexOffset;

                q.PushQuad(quad);

                for (int i = 0; i < 4; i++)
                    quad[i]++;

                q.PushQuad(quad);
            }
        }

        indexOffset += q.VertexCount();
    }

    ////left & right
    {
        ////vertices
        for (uint32_t iY = 0; iY < slicesY + 1; iY++)
        {
            for (uint32_t iZ = 0; iZ < slicesZ + 1; iZ++)
            {
                q.SetPosition(1, iY * stepY - 1.f, iZ * stepZ - 1.f);
                q.SetNormal(1, 0, 0);
                q.SetTexCoords(iY * stepY / 2.f, iZ * stepZ / 2.f);
                q.Push();

                q.Pos()[0] = -1;
                q.Normal()[0] = -1;
                q.Push();
            }
        }

        ////indices
        for (uint32_t iY = 0; iY < slicesY; iY++)
        {
            for (uint32_t iZ = 0; iZ < slicesZ; iZ++)
            {
                uint16_t quad[4] = {
                    static_cast<uint16_t>((iY + iZ * (slicesY + 1)) * 2 + indexOffset),
                    static_cast<uint16_t>((iY + 1 + iZ * (slicesY + 1)) * 2 + indexOffset),
                    static_cast<uint16_t>((iY + 1 + (iZ + 1) * (slicesY + 1)) * 2 + indexOffset),
                    static_cast<uint16_t>((iY + (iZ + 1) * (slicesY + 1)) * 2 + indexOffset),
                };

                q.PushQuad(quad);

                for (int i = 0; i < 4; i++)
                    quad[i]++;

                q.PushQuad(quad);
            }
        }

        indexOffset = q.VertexCount();
    }

    ////top & bottom
    {
        ////vertices
        for (uint32_t iZ = 0; iZ < slicesZ + 1; iZ++)
        {
            for (uint32_t iX = 0; iX < slicesX + 1; iX++)
            {
                q.SetPosition(iX * stepX - 1.f, 1, iZ * stepZ - 1.f);
                q.SetNormal(0, 1, 0);
                q.SetTexCoords(iZ * stepZ / 2.f, iX * stepX / 2.f);
                q.Push();

                q.Pos()[1] = -1;
                q.Normal()[1] = -1;
                q.Push();
            }
        }

        ////indices
        for (uint32_t iZ = 0; iZ < slicesZ; iZ++)
        {
            for (uint32_t iX = 0; iX < slicesX; iX++)
            {
                uint16_t quad[4] = {
                    iZ + iX * (slicesZ + 1),
                    iZ + 1 + iX * (slicesZ + 1),
                    iZ + 1 + (iX + 1) * (slicesZ + 1),
                    iZ + (iX + 1) * (slicesZ + 1),
                };

                for (int i = 0; i < 4; i++)
                    quad[i] = quad[i] * 2 + indexOffset;

                q.PushQuad(quad);

                for (int i = 0; i < 4; i++)
                    quad[i]++;

                q.PushQuad(quad);
            }
        }
    }

    return q.CreateMesh(out);
}