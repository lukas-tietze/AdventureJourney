#include "Objects.hpp"

glutil::SimpleLight::SimpleLight()
{
}

glutil::SimpleLight::SimpleLight(const glm::vec3 &position, bool directionalLigth, const glm::vec3 &color, float ambientFactor, bool active)
{
}

const glm::vec3 &glutil::SimpleLight::GetPosition() const
{
    return this->data.position;
}

glutil::LightType glutil::SimpleLight::GetType() const
{
    return static_cast<LightType>(this->data.type);
}

const glm::vec3 &glutil::SimpleLight::GetColor() const
{
    return this->data.color;
}

float glutil::SimpleLight::GetAmbientFactor() const
{
    return this->data.ambientFactor;
}

bool glutil::SimpleLight::IsActive() const
{
    return this->data.active;
}

void glutil::SimpleLight::SetPosition(const glm::vec3 &pos)
{
    this->data.position = pos;
    this->SetDirty();
}

void glutil::SimpleLight::SetType(LightType type)
{
    this->data.type = static_cast<uint32_t>(type);
    this->SetDirty();
}

void glutil::SimpleLight::SetColor(const glm::vec3 &clr)
{
    this->data.color = clr;
    this->SetDirty();
}

void glutil::SimpleLight::SetAmbientFactor(float f)
{
    this->data.ambientFactor = f;
    this->SetDirty();
}

void glutil::SimpleLight::SetActive(bool active)
{
    this->data.active = active;
    this->SetDirty();
}
