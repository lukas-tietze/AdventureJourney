#include "GlUtils.hpp"
#include "Objects.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "data/Io.hpp"

glutil::Camera::Camera() : position(3.f, 3.f, 3.f),
                           up(glutil::AXIS_Y),
                           direction(glutil::AXIS_X),
                           fov(60.f),
                           near(0.1f),
                           far(100.f),
                           aspectRation(1.f),
                           viewMat(true),
                           viewDirty(true),
                           projectionMat(1.f),
                           projectionDirty(1.f),
                           viewProjectionMat(1.f)
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
    this->direction = glm::rotate(this->direction, glm::radians(degrees), axis);
    this->viewDirty = true;
}

void glutil::Camera::SetFov(float fov)
{
    this->fov = fov;
    this->projectionDirty = true;
}

void glutil::Camera::SetNear(float near)
{
    this->near = near;
    this->projectionDirty = true;
}

void glutil::Camera::SetFar(float far)
{
    this->far = far;
    this->projectionDirty = true;
}

void glutil::Camera::SetRange(float near, float far)
{
    this->near = near;
    this->far = far;
    this->projectionDirty = true;
}

void glutil::Camera::SetAspectRation(int w, int h)
{
    this->aspectRation = static_cast<float>(w) / static_cast<float>(h);
    this->projectionDirty = true;
}

void glutil::Camera::SetAspectRation(float ratio)
{
    this->aspectRation = ratio;
    this->projectionDirty = true;
}

void glutil::Camera::UpdateMatrices()
{
    if (this->viewDirty)
        this->viewMat = glm::lookAt(this->position, this->position + this->direction, this->up);

    if (this->projectionDirty)
        this->projectionMat = glm::perspective(this->fov, this->aspectRation, this->near, this->far);

    if (this->viewDirty || this->projectionDirty)
    {
        this->viewProjectionMat = this->projectionMat * this->viewMat;
        this->viewDirty = false;
        this->projectionDirty = false;
    }
}

const glm::mat4 &glutil::Camera::GetViewProjectionMatrix() const
{
    return this->viewProjectionMat;
}

const glm::mat4 &glutil::Camera::GetProjectionMatrix() const
{
    return this->projectionMat;
}

const glm::mat4 &glutil::Camera::GetViewMatrix() const
{
    return this->viewMat;
}

const glm::mat4 &glutil::Camera::GetViewProjectionMatrix()
{
    this->UpdateMatrices();

    return this->viewProjectionMat;
}

const glm::mat4 &glutil::Camera::GetProjectionMatrix()
{
    this->UpdateMatrices();

    return this->projectionMat;
}

const glm::mat4 &glutil::Camera::GetViewMatrix()
{
    this->UpdateMatrices();

    return this->viewMat;
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
    return this->near;
}

float glutil::Camera::GetFar() const
{
    return this->far;
}

float glutil::Camera::GetAspectRation() const
{
    return this->aspectRation;
}
