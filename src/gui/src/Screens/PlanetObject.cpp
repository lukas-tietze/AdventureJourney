#include "GlScreens.hpp"
#include "data/Random.hpp"
#include "Defs.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <algorithm>

namespace
{
util::Random rnd;
}

gui::PlanetObject::PlanetObject(glutil::SceneObject *obj, float radius) : object(obj),
                                                                          radius(radius),
                                                                          arc(rnd.Next(0.0, 2 * M_PI)),
                                                                          speed(rnd.Next(0.2f, 0.4f)),
                                                                          size(rnd.Next(0.2f, 1.2f))
{
}

void gui::PlanetObject::Update(double delta)
{
    this->radius += delta * this->speed;

    this->object->SetModelMatrix(
        glm::translate(glm::vec3(std::cos(this->radius), 0, std::sin(this->radius)) * this->radius) *
        glm::rotate(this->radius, glutil::AXIS_Y) *
        glm::scale(glm::vec3(this->size)));
}