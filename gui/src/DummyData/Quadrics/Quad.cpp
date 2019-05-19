#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"

bool gui::quadrics::Quad(glutil::Mesh &out)
{
    return Quad(out, QuadricConfig());
}

bool gui::quadrics::Quad(glutil::Mesh &out, const QuadricConfig &config)
{
    QuadricContext q(config);

    q.Reserve(4, 6);

    q.SetNormal(0, 1, 0);

    q.SetPosition(-1, 0, 1);
    q.SetTexCoords(0, 0);
    q.Push();

    q.SetPosition(1, 0, 1);
    q.SetTexCoords(1, 0);
    q.Push();

    q.SetPosition(1, 0, -1);
    q.SetTexCoords(1, 1);
    q.Push();

    q.SetPosition(-1, 0, -1);
    q.SetTexCoords(0, 1);
    q.Push();

    q.PushQuad(0, 1, 2, 3);

    return q.CreateMesh(out);
}