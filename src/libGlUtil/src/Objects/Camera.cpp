#include "GlUtils.hpp"
#include "Objects.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "data/Io.hpp"

glutil::Camera::Camera() : position(3.f, 3.f, 3.f),
                           up(glutil::AXIS_Y),
                           direction(glutil::AXIS_X),
                           fov(glm::radians(75.f)),
                           nearPlane(0.1f),
                           farPlane(100.f),
                           aspectRation(1.f),
                           viewDirty(true),
                           projectionDirty(1.f)
{
}

void glutil::Camera::SetPosition(glm::vec3 const &pos)
{
    this->position = pos;
    this->viewDirty = true;
}

void glutil::Camera::SetUp(glm::vec3 const &up)
{
    this->up = glm::normalize(up);
    this->viewDirty = true;
}

void glutil::Camera::SetViewDirection(glm::vec3 const &direction)
{
    this->direction = glm::normalize(direction);
    this->viewDirty = true;
}

void glutil::Camera::MoveBy(glm::vec3 const &dist)
{
    this->position += dist;
    this->viewDirty = true;
}

void glutil::Camera::Rotate(float degrees, glm::vec3 const &axis)
{
    if (degrees != 0)
    {
        this->direction = glm::rotate(this->direction, glm::radians(degrees), axis);
        this->viewDirty = true;
    }
}

void glutil::Camera::SetFov(float fov)
{
    if (this->fov != fov)
    {
        this->fov = fov;
        this->projectionDirty = true;
    }
}

void glutil::Camera::SetNear(float nearPlane)
{
    if (this->nearPlane != nearPlane)
    {
        this->nearPlane = nearPlane;
        this->projectionDirty = true;
    }
}

void glutil::Camera::SetFar(float farPlane)
{
    if (this->farPlane != farPlane)
    {
        this->farPlane = farPlane;
        this->projectionDirty = true;
    }
}

void glutil::Camera::SetRange(float nearPlane, float farPlane)
{
    if (this->nearPlane != nearPlane || this->farPlane != farPlane)
    {
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
        this->projectionDirty = true;
    }
}

void glutil::Camera::SetAspectRation(int w, int h)
{
    if (this->aspectRation != static_cast<float>(w) / static_cast<float>(h))
    {
        this->aspectRation = static_cast<float>(w) / static_cast<float>(h);
        this->projectionDirty = true;
    }
}

void glutil::Camera::SetAspectRation(float ratio)
{
    if (this->aspectRation != ratio)
    {
        this->aspectRation = ratio;
        this->projectionDirty = true;
    }
}

void glutil::Camera::UpdateMatrices()
{
    if (this->viewDirty)
    {
        this->data.viewMat = glm::lookAt(this->position, this->position + this->direction, this->up);
        this->data.inverseViewMat = glm::inverse(this->data.viewMat);
        this->viewDirty = false;
        this->SetDirty();
    }

    if (this->projectionDirty)
    {
        this->projectionDirty = false;
        this->data.projectionMat = glm::perspective(this->fov, this->aspectRation, this->nearPlane, this->farPlane);
        this->data.inverseProjectionMat = glm::inverse(this->data.projectionMat);
        this->SetDirty();
    }
}

const glm::mat4 &glutil::Camera::GetProjectionMatrix() const
{
    return this->data.projectionMat;
}

const glm::mat4 &glutil::Camera::GetViewMatrix() const
{
    return this->data.viewMat;
}

const glm::vec3 &glutil::Camera::GetPosition() const
{
    return this->position;
}

const glm::vec3 &glutil::Camera::GetUp() const
{
    return this->up;
}

const glm::vec3 &glutil::Camera::GetViewDirection() const
{
    return this->direction;
}

float glutil::Camera::GetFov() const
{
    return this->fov;
}

float glutil::Camera::GetNear() const
{
    return this->nearPlane;
}

float glutil::Camera::GetFar() const
{
    return this->farPlane;
}

float glutil::Camera::GetAspectRation() const
{
    return this->aspectRation;
}
