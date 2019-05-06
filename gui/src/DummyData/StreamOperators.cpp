#include "DummyData.hpp"

std::ostream &gui::operator<<(std::ostream &s, const Vertex_XYZ &v)
{
    s << "XYZ={"
      << v.position[0] << ", "
      << v.position[1] << ", "
      << v.position[2] << "}";

    return s;
}

std::ostream &gui::operator<<(std::ostream &s, const Vertex_XYZ_RGB &v)
{
    s << "XYZ={"
      << v.position[0] << ", "
      << v.position[1] << ", "
      << v.position[2] << "}";

    s << ", RGB={"
      << v.color[0] << ", "
      << v.color[1] << ", "
      << v.color[2] << "}";

    return s;
}

std::ostream &gui::operator<<(std::ostream &s, const Vertex_XYZ_RGB_ST &v)
{
    s << "XYZ={"
      << v.position[0] << ", "
      << v.position[1] << ", "
      << v.position[2] << "}";

    s << ", RGB={"
      << v.color[0] << ", "
      << v.color[1] << ", "
      << v.color[2] << "}";

    s << ", ST={"
      << v.texture[0] << ", "
      << v.texture[1] << "}";

    return s;
}

std::ostream &gui::operator<<(std::ostream &s, const Vertex_XYZ_NRM_RGB &v)
{
    s << "XYZ={"
      << v.position[0] << ", "
      << v.position[1] << ", "
      << v.position[2] << "}";

    s << ", NRM={"
      << v.normal[0] << ", "
      << v.normal[1] << ", "
      << v.normal[2] << "}";

    s << ", RGB={"
      << v.color[0] << ", "
      << v.color[1] << ", "
      << v.color[2] << "}";

    return s;
}

std::ostream &gui::operator<<(std::ostream &s, const Vertex_XYZ_NRM_RGB_ST &v)
{
    s << "XYZ={"
      << v.position[0] << ", "
      << v.position[1] << ", "
      << v.position[2] << "}";

    s << ", NRM={"
      << v.normal[0] << ", "
      << v.normal[1] << ", "
      << v.normal[2] << "}";

    s << ", RGB={"
      << v.color[0] << ", "
      << v.color[1] << ", "
      << v.color[2] << "}";

    s << ", ST={"
      << v.texture[0] << ", "
      << v.texture[1] << "}";

    return s;
}
