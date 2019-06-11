#include "Objects.hpp"

glutil::Light::Light()
{
}

glutil::Light &glutil::Light::SetPosition(const glm::vec3 &pos)
{
    this->position_type.x = pos.x;
    this->position_type.y = pos.y;
    this->position_type.z = pos.z;

    return *this;
}

glutil::Light &glutil::Light::SetType(LightType type)
{
    this->position_type.w = static_cast<uint32_t>(type);

    return *this;
}

glutil::Light &glutil::Light::SetColor(const glm::vec3 &clr)
{
    this->color_ambientFactor.r = clr.r;
    this->color_ambientFactor.g = clr.g;
    this->color_ambientFactor.b = clr.b;

    return *this;
}

glutil::Light &glutil::Light::SetAmbientFactor(float f)
{
    this->color_ambientFactor.a = f;

    return *this;
}

glutil::Light &glutil::Light::SetActive(bool active)
{
    this->spotExponent_size_enabled.w = active;

    return *this;
}

glm::vec3 glutil::Light::GetPosition() const
{
    return glm::vec3(this->position_type.x,
                     this->position_type.y,
                     this->position_type.z);
}

glutil::LightType glutil::Light::GetType() const
{
    return static_cast<LightType>(static_cast<int>(this->position_type.w));
}

glm::vec3 glutil::Light::GetColor() const
{
    return glm::vec3(this->color_ambientFactor.r,
                     this->color_ambientFactor.g,
                     this->color_ambientFactor.b);
}

float glutil::Light::GetAmbientFactor() const
{
    return this->color_ambientFactor.a;
}

bool glutil::Light::IsActive() const
{
    return this->spotExponent_size_enabled.w;
}
