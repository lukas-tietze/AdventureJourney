#include "Objects.hpp"
#include "GlUtils.hpp"
#include "glm/gtx/transform.hpp"

gui::Camera::Camera() : position(1.f, 1.f, 1.f),
                        up(glutil::AXIS_Y),
                        direction(glutil::AXIS_X),
                        fov(60.f),
                        near(0.1f),
                        far(100.f),
                        aspectRation(1.f)
{
}

void gui::Camera::SetPosition(glm::vec3 const &pos)
{
    this->position = pos;
}

void gui::Camera::SetUp(glm::vec3 const &up)
{
    this->up = up;
}

void gui::Camera::SetViewDirection(glm::vec3 const &direction)
{
    this->direction = direction;
}

void gui::Camera::MoveBy(glm::vec3 const &dist)
{
    this->position += dist;
}

void gui::Camera::Rotate(float degrees, glm::vec3 const &axis)
{
    this->direction = glm::rotate(glm::radians(degrees), axis) * this->direction;
}

void gui::Camera::SetFov(float fov)
{
    this->fov = fov;
}

void gui::Camera::SetNear(float near)
{
    this->near = near;
}

void gui::Camera::SetFar(float far)
{
    this->far = far;
}

void gui::Camera::SetRange(float near, float far)
{
    this->near = near;
    this->far = far;
}

void gui::Camera::SetAspectRation(int w, int h)
{
    this->aspectRation = static_cast<float>(w) / static_cast<float>(h);
}

void gui::Camera::SetAspectRation(float ratio)
{
    this->aspectRation = ratio;
}

void gui::Camera::Flush(glm::mat4 &projectionBuf, glm::mat4 &viewBuf)
{
    projectionBuf = glm::perspective(this->fov, this->aspectRation, this->near, this->far);
    viewBuf = glm::lookAt(this->position, this->position + this->direction, this->up);
}
